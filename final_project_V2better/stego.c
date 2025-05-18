/** This c file contains an advanced steganography library that implements lsb stego. for BMP images 
 * with encryption and error handling, and configurable bit distribution
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "stego.h"

/** constraints for the library
 * since i am using bmp format the message size is limite
 */

#define BMP_HEADER_SIZE 54 // skipping header to access pixel data
#define BYTES_PER_PIXEL 3 // for rgb
#define MAX_PASSWORD_LENGTH 32 // limit for password length
#define SIGNATURE "STEG" // marker to prevent false positives when scanning data
#define SIGNATURE_LENGTH 4
#define METADATA_SIZE (SIGNATURE_LENGTH + sizeof(uint32_t) + sizeof(uint32_t))

// Global variables for error handling
static char error_message[256] = {0};

//  sets the last error message
static void set_error(const char *message) {
    strncpy(error_message, message, sizeof(error_message) - 1);
    error_message[sizeof(error_message) - 1] = '\0';
}

// gets the last error message
const char *stego_get_error() {
    return error_message;
}

// XOR encryption/decryption function for password
static void encrypt_decrypt(uint8_t *data, size_t size, const char *password) {
    size_t password_len = strlen(password);

    if (password_len == 0) return; // getting the length of the password, if it is empty does nothing

    for (size_t i = 0; i < size; i++) {
        data[i] ^= password[i % password_len]; // xor between the data byte and a corresponding byte from password to obscure the hidden data in image
    }
}

// function to check if the input is valid bmp
static int is_valid_bmp(FILE *file) {
    uint8_t header[BMP_HEADER_SIZE];
    long current_pos = ftell(file);

    rewind(file);
    size_t read = fread(header, 1, BMP_HEADER_SIZE, file);
    fseek(file, current_pos, SEEK_SET);

    if (read != BMP_HEADER_SIZE) {
        set_error("Failed to read BMP header");
        return 0;
    }

    // check for BM signature 
    if (header[0] != 'B' || header[1] != 'M') {
        set_error("Not a valid BMP file (missing BM signature)");
        return 0;
    }

    // check bit depth which must be 24-bit
    if (*(uint16_t*)&header[28] != 24) {
        set_error("Only 24-bit BMP file are supported");
        return 0;
    }

    // the input file must be uncompressed
    if (*(uint32_t*)&header[30] != 0) {
        set_error("Only uncompressed BMP files are supported");
        return 0;
    }

    return 1;
} 

// get the available capacity for hiding data
static size_t get_available_capacity(FILE *image, stego_config_t *config) {
    long current_pos = ftell(image);

    fseek(image, 0, SEEK_END);
    long file_size = ftell(image);

    fseek(image, current_pos, SEEK_SET);

    //calculate the pixels 
    size_t payload_bytes = file_size - BMP_HEADER_SIZE;
    size_t capacity_bits = payload_bytes * config->bits_per_byte;

    // convert bits and accounting for metadata overhead
    return (capacity_bits / 8) - METADATA_SIZE;
}

// embed a single bit into a byte
static uint8_t embed_bit(uint8_t byte, uint8_t bit, uint8_t bit_position) {
    // clear the bit at the specified position
    byte &= ~(1 << bit_position);
    // set the bit to the new value
    byte |= (bit & 1) << bit_position;
    return byte;
}

// extracting one bit from a byte
static uint8_t extract_bit(uint8_t byte, uint8_t bit_position) {
    return (byte >> bit_position) & 1;
}

// initialize the steganography configuration with default values
void stego_init_config(stego_config_t *config) {
    if (config == NULL) return;

    config->bits_per_byte = 1;       // by default use 1 bit per byte (LSB)
    config->bit_position = 0;        // use the least significant bit
    config->distribution_mode = STEGO_SEQUENTIAL;  // sequential bits
    config->password[0] = '\0';      // no encryption
    config->status_callback = NULL;  // no callback
}

// encode the message into the bmp image
int stego_encode(const char *input_image, const char *output_image, 
                 const uint8_t *message, size_t message_size, 
                 stego_config_t *config) {
    FILE *input = NULL;
    FILE *output = NULL;
    uint8_t *encrypted_message = NULL;
    uint8_t *metadata = NULL;
    int result = 0;
    uint32_t seed = 0;
    
    // making sure that all parameters present
    if (input_image == NULL || output_image == NULL || message == NULL || config == NULL) {
        set_error("Invalid parameters");
        return 0;
    }
    
    // open input image
    input = fopen(input_image, "rb");
    if (input == NULL) {
        set_error("Failed to open input image");
        return 0;
    }
    
    // checking if the format is valid
    if (!is_valid_bmp(input)) {
        fclose(input);
        return 0;
    }
    
    // calculating how many bytes can be hidden in the image
    size_t capacity = get_available_capacity(input, config);
    if (message_size > capacity) {
        set_error("Message too large for the image");
        fclose(input);
        return 0;
    }
    
    // create output image
    output = fopen(output_image, "wb");
    if (output == NULL) {
        set_error("Failed to create output image");
        fclose(input);
        return 0;
    }
    
    // copy header
    rewind(input);

    // reading and writing the first 54 bytes since they must be unchanged
    uint8_t header[BMP_HEADER_SIZE];
    if (fread(header, 1, BMP_HEADER_SIZE, input) != BMP_HEADER_SIZE) {
        set_error("Failed to read BMP header");
        goto cleanup;
    }
    
    if (fwrite(header, 1, BMP_HEADER_SIZE, output) != BMP_HEADER_SIZE) {
        set_error("Failed to write BMP header");
        goto cleanup;
    }
    
    // prepare metadata (signature + message size)
    metadata = (uint8_t *)malloc(METADATA_SIZE);
    if (metadata == NULL) {
        set_error("Memory allocation failed");
        goto cleanup;
    }
    
    // clear metadata buffer to ensure all bits are initialized
    memset(metadata, 0, METADATA_SIZE);
    
    // add signature to identify that the file has hidden message
    memcpy(metadata, SIGNATURE, SIGNATURE_LENGTH);
    
    // add message size
    uint32_t msg_size_network = message_size;
    memcpy(metadata + SIGNATURE_LENGTH, &msg_size_network, sizeof(uint32_t));
    
    // random seed for non-sequential mode (crashes during decoding...)
    if (config->distribution_mode == STEGO_RANDOM) {
        seed = (uint32_t)time(NULL);
        memcpy(metadata + SIGNATURE_LENGTH + sizeof(uint32_t), &seed, sizeof(uint32_t));
        srand(seed); 
    } else {
        // zero seed for sequential
        memcpy(metadata + SIGNATURE_LENGTH + sizeof(uint32_t), &seed, sizeof(uint32_t));
    }
    
    // preparing encrypted message if password is provided
    encrypted_message = (uint8_t *)malloc(message_size);
    if (encrypted_message == NULL) {
        set_error("Memory allocation failed");
        goto cleanup;
    }
    
    memcpy(encrypted_message, message, message_size);
    
    // encrypt password
    if (strlen(config->password) > 0) {
        encrypt_decrypt(encrypted_message, message_size, config->password);
    }
    
    // embed metadata and message
    size_t total_bytes = METADATA_SIZE + message_size;
    size_t total_bits = total_bytes * 8;
    size_t processed_bits = 0;
    
    // for progress tracking
    size_t total_pixel_bytes = 0;
    fseek(input, 0, SEEK_END);
    total_pixel_bytes = ftell(input) - BMP_HEADER_SIZE;
    fseek(input, BMP_HEADER_SIZE, SEEK_SET);
    
    // Before embedding, reset the random seed if using random mode
    if (config->distribution_mode == STEGO_RANDOM) {
        srand(seed);
    }
    
    // embedding the data
    while (processed_bits < total_bits) {
        uint8_t pixel_byte;
        // read one byte of image data
        if (fread(&pixel_byte, 1, 1, input) != 1) {
            // if less than one is returned it means the end of file was reached before all data could be embedded or error occurred
            set_error("Unexpected end of image file");
            goto cleanup;
        }
        
        // determine which part of data we're embedding (metadata or message)
        uint8_t *current_data;
        size_t current_offset;
        // first embedding the metadata and then the message
        if (processed_bits < METADATA_SIZE * 8) {
            current_data = metadata;
            current_offset = processed_bits / 8;
        } else {
            current_data = encrypted_message;
            current_offset = (processed_bits - METADATA_SIZE * 8) / 8;
        }
        
        // get the bit to embed
        uint8_t bit_to_embed = (current_data[current_offset] >> (7 - (processed_bits % 8))) & 1;
        
        // determine which bit position to use
        uint8_t bit_pos;
        
        if (config->distribution_mode == STEGO_RANDOM) {
            // use a random bit position based on the seed
            bit_pos = rand() % 3; // Use only bits 0-2 (LSBs) to avoid visible changes
        } else {
            bit_pos = config->bit_position;
        }
        
        // embed the bit
        pixel_byte = embed_bit(pixel_byte, bit_to_embed, bit_pos);
        
        // writing the modified byte
        if (fwrite(&pixel_byte, 1, 1, output) != 1) {
            set_error("Failed to write to output file");
            goto cleanup;
        }
        // moving onto the next bit
        processed_bits++;
        
        // call status callback if provided and every 1% of progress
        if (config->status_callback && (processed_bits % (total_pixel_bytes / 100 + 1) == 0)) {
            float progress = (float)processed_bits / total_bits * 100.0f;
            config->status_callback(progress);
        }
    }
    
    // copy the rest of the image unchanged
    uint8_t buffer[4096];
    size_t bytes_read;
    
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input)) > 0) {
        if (fwrite(buffer, 1, bytes_read, output) != bytes_read) {
            set_error("Failed to write to output file");
            goto cleanup;
        }
    }
    
    result = 1;  // Success!!
    
cleanup:
    if (input) fclose(input);
    if (output) fclose(output);
    if (metadata) free(metadata);
    if (encrypted_message) free(encrypted_message);
    
    return result;
}

// decoding function
uint8_t *stego_decode(const char *input_image, size_t *message_size, stego_config_t *config) {
    FILE *input = NULL;
    uint8_t *message = NULL;
    uint8_t *metadata = NULL;
    uint32_t seed = 0;
    
    // validating parameters
    if (input_image == NULL || message_size == NULL || config == NULL) {
        set_error("Invalid parameters");
        return NULL;
    }

    // open input image
    input = fopen(input_image, "rb");
    if (input == NULL) {
        set_error("Failed to open input image");
        return NULL;
    }

    // validate BMP
    if (!is_valid_bmp(input)) {
        fclose(input);
        return NULL;
    }

    // skipping header
    fseek(input, BMP_HEADER_SIZE, SEEK_SET);

    // extract metadata first 
    metadata = (uint8_t *)malloc(METADATA_SIZE);
    if (metadata == NULL) {
        set_error("Memory allocation failed");
        fclose(input);
        return NULL;
    }

    memset(metadata, 0, METADATA_SIZE);

    // first, read bits sequentially to extract signature and seed
    for (size_t i = 0; i < METADATA_SIZE * 8; i++) {
        uint8_t pixel_byte;

        if (fread(&pixel_byte, 1, 1, input) != 1) {
            set_error("Unexpected end of image file");
            free(metadata);
            fclose(input);
            return NULL;
        }

	// to ensure we can properly validate the file
        uint8_t bit_pos;
        
        if (config->distribution_mode == STEGO_RANDOM && i >= (SIGNATURE_LENGTH + sizeof(uint32_t)) * 8) {
            // still sequential but might use a different bit position
            bit_pos = config->bit_position; 
        } else {
            bit_pos = config->bit_position;
        }

        uint8_t extracted_bit = extract_bit(pixel_byte, bit_pos);

        // add bit to metadata
        if (extracted_bit) {
            metadata[i / 8] |= (1 << (7 - (i % 8)));
        }

        //  extract the seed
        if (i == (SIGNATURE_LENGTH + sizeof(uint32_t) + sizeof(uint32_t)) * 8 - 1) {
            memcpy(&seed, metadata + SIGNATURE_LENGTH + sizeof(uint32_t), sizeof(uint32_t));
            
            // initialize random generator with the seed
            if (config->distribution_mode == STEGO_RANDOM) {
                srand(seed);
            }
        }
    }

    // verify signature
    if (memcmp(metadata, SIGNATURE, SIGNATURE_LENGTH) != 0) {
        set_error("Invalid steganography signature");
        free(metadata);
        fclose(input);
        return NULL;
    }

    // get message size
    uint32_t msg_size_network;
    memcpy(&msg_size_network, metadata + SIGNATURE_LENGTH, sizeof(uint32_t));
    *message_size = msg_size_network;

    // validate message size against capacity
    size_t capacity = get_available_capacity(input, config);
    if (*message_size > capacity) {
        set_error("Invalid message size detected");
        free(metadata);
        fclose(input);
        return NULL;
    }

    // reposition to the start of the message data
    fseek(input, BMP_HEADER_SIZE + METADATA_SIZE, SEEK_SET);

    if (config->distribution_mode == STEGO_RANDOM) {
        srand(seed);
    }

    // allocate memory for the message
    message = (uint8_t *)malloc(*message_size);
    if (message == NULL) {
        set_error("Memory allocation failed");
        free(metadata);
        fclose(input);
        return NULL;
    }

    // clear message buffer
    memset(message, 0, *message_size);

    // extract message bits
    for (size_t i = 0; i < *message_size * 8; i++) {
        uint8_t pixel_byte;

        if (fread(&pixel_byte, 1, 1, input) != 1) {
            set_error("Unexpected end of image file");
            free(metadata);
            free(message);
            fclose(input);
            return NULL;
        }

        // determine which bit position to use
        uint8_t bit_pos;

        if (config->distribution_mode == STEGO_RANDOM) {
            // use the same random sequence as during encoding
            bit_pos = rand() % 3; // Use only bits 0-2 (LSBs)
        } else {
            bit_pos = config->bit_position;
        }

        // extract bit
        uint8_t extracted_bit = extract_bit(pixel_byte, bit_pos);

        // add bit to message
        if (extracted_bit) {
            message[i / 8] |= (1 << (7 - (i % 8)));
        }

        // call status callback if provided and every 1% of progress
        if (config->status_callback && (*message_size > 0) && (i % ((*message_size * 8 / 100) + 1) == 0)) {
            float progress = (float)i / (*message_size * 8) * 100.0f;
            config->status_callback(progress);
        }
    }

    // decrypt message if password is provided
    if (strlen(config->password) > 0) {
        encrypt_decrypt(message, *message_size, config->password);
    }

    free(metadata);
    fclose(input);

    return message;
}

/* Summary 
 *
 * this library contains functions that
 * validate input and output BMP files
 * prepares a metadata block with signature
 * optionally encrypts the message
 * embeds metadata and message bits into the image pixel data using LSB
 * produces a new BMP file with the hidden data
 *
*/
