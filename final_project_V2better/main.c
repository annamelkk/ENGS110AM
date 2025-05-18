/** 
 * This is the main file, a command line interface for the stego library
 * I wish I had time to create an HTML/CSS + JS interface for this, if time allows me to do so
*/ 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "stego.h"


// function prototypes

void print_usage(const char *program_name);
void status_callback(float progress);

int main(int argc, char*argv[]) {
	// check for minimum arguments
	if (argc < 3) {
	print_usage(argv[0]);
	return 1;
	}

	// parse operation mode
	int encode_mode = 0;
	if (strcmp(argv[1], "encode") == 0) {
		encode_mode = 1;
	} else if (strcmp(argv[1], "decode") == 0) { 
		encode_mode = 0;
	} else {
		printf("Unknown operation mode '%s'\n", argv[1]);
		print_usage(argv[0]);
		return 1;
	}

	// initialize configuration
	stego_config_t config;
	stego_init_config(&config);

	// setting default mode and checking for the config files
	config.status_callback = status_callback;

	// parse the remaining arguments
	char *input_image = NULL;
	char *output_image = NULL;
	char *message_file = NULL;
	int i = 2;

	    while (i < argc) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            input_image = argv[i + 1];
            i += 2;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_image = argv[i + 1];
            i += 2;
        } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            message_file = argv[i + 1];
            i += 2;
        } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            strncpy(config.password, argv[i + 1], sizeof(config.password) - 1);
            config.password[sizeof(config.password) - 1] = '\0';
            i += 2;
        } else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            config.bit_position = (uint8_t)atoi(argv[i + 1]);
            if (config.bit_position > 7) {
                printf("Error: Bit position must be between 0 and 7\n");
                return 1;
            }
            i += 2;
        } else if (strcmp(argv[i], "-r") == 0) {
            config.distribution_mode = STEGO_RANDOM;
            i++;
        } else {
            printf("Error: Unknown option '%s'\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        	}
	}

	// validate required arguments
	if (input_image == NULL) {
	printf("Input image (-i) is requied\n");
	return 1;
	}


	if (encode_mode && (output_image == NULL || message_file == NULL)) {
	printf("Output image (-o) and message file (-m) are requied for encoding.\n");
	return 1;
	}

	if (!encode_mode && output_image == NULL) {
        printf("Error: Output file (-o) is required for decoding\n");
        return 1;
    	}

    // execution of encoding or decoding
   	 if (encode_mode) {
        FILE *msg_file = fopen(message_file, "rb");
        if (msg_file == NULL) {
            printf("Error: Could not open message file '%s'\n", message_file);
            return 1;
        }

        // get message size
        fseek(msg_file, 0, SEEK_END);
        size_t message_size = ftell(msg_file);
        rewind(msg_file);

        uint8_t *message = (uint8_t *)malloc(message_size);
        if (message == NULL) {
            printf("Error: Memory allocation failed\n");
            fclose(msg_file);
            return 1;
        }

        // read message
        if (fread(message, 1, message_size, msg_file) != message_size) {
            printf("Error: Could not read message file\n");
            free(message);
            fclose(msg_file);
            return 1;
        }

        fclose(msg_file);

        // encode message
        printf("Encoding message into image...\n");
        if (!stego_encode(input_image, output_image, message, message_size, &config)) {
            printf("Error: %s\n", stego_get_error());
            free(message);
            return 1;
        }

        free(message);
        printf("\nEncoding successful! Output saved to '%s'\n", output_image);
   	} else {
        // decode message
        printf("Decoding message from image...\n");
        size_t message_size;
        uint8_t *message = stego_decode(input_image, &message_size, &config);

        if (message == NULL) {
            printf("Error: %s\n", stego_get_error());
            return 1;
        }

        // write decoded message to file
        FILE *output_file = fopen(output_image, "wb");
        if (output_file == NULL) {
            printf("Error: Could not create output file '%s'\n", output_image);
            free(message);
            return 1;
        }

        if (fwrite(message, 1, message_size, output_file) != message_size) {
            printf("Error: Could not write to output file\n");
            free(message);
            fclose(output_file);
            return 1;
        }

        fclose(output_file);
        free(message);
        printf("\nDecoding successful! Message saved to '%s'\n", output_image);
    }

    return 0;
}

// usage information
void print_usage(const char *program_name) {
    printf("Advanced Steganography Tool\n");
    printf("Usage: %s <operation> [options]\n\n", program_name);
    printf("Operations:\n");
    printf("  encode    Encode a message into an image\n");
    printf("  decode    Decode a message from an image\n\n");
    printf("Options:\n");
    printf("  -i <file>    Input image file (BMP format)\n");
    printf("  -o <file>    Output file (image for encode, message for decode)\n");
    printf("  -m <file>    Message file to encode (encode mode only)\n");
    printf("  -p <pass>    Password for encryption/decryption\n");
    printf("  -b <pos>     Bit position to use (0-7, default: 0 = LSB)\n");
    printf("  -r           Use random bit distribution\n\n");
    printf("Examples:\n");
    printf("  %s encode -i input.bmp -o output.bmp -m message.txt -p secret -r\n", program_name);
    printf("  %s decode -i stego_image.bmp -o extracted_message.txt -p secret -r\n", program_name);
}

 // status callback function for progress reporting
void status_callback(float progress) {
    int bar_width = 50;
    int pos = bar_width * progress / 100.0;

    printf("\r[");
    for (int i = 0; i < bar_width; i++) {
        if (i < pos) printf("#");
        else printf(" ");
    }
    printf("] %.1f%%", progress);
    fflush(stdout);
}










