/**
 * Header file for the steganography library
 */

#ifndef STEGO_H
#define STEGO_H

#include <stdint.h>
#include <stddef.h>

// Distribution modes for bit embedding
typedef enum {
    STEGO_SEQUENTIAL = 0,  // sequential bits in the image
    STEGO_RANDOM = 1       // pseudorandom bit positions
} stego_distribution_t;

//for status updates
typedef void (*status_callback_t)(float progress);

// config structure
typedef struct {
    uint8_t bits_per_byte; // Number of bits to use per byte of image
    uint8_t bit_position;  // Position of bit to use (0-7, with 0 being LSB)
    stego_distribution_t distribution_mode; // Distribution mode (...)
    char password[32];            // Encryption password (optional)
    status_callback_t status_callback; // Status callback function (optional)
} stego_config_t;

// default values
void stego_init_config(stego_config_t *config);

// encoding
int stego_encode(const char *input_image, const char *output_image, 
                const uint8_t *message, size_t message_size, 
                stego_config_t *config);

// decoding
uint8_t *stego_decode(const char *input_image, size_t *message_size, 
                     stego_config_t *config);

// get the last error message
const char *stego_get_error();

#endif /* STEGO_H */
