#include <stdio.h>
#include <stdlib.h>

// We are inputting BMP file which always has 54 bytes

#define HEADER_SIZE 54

int main() 
{
	FILE *original= fopen( "input.bmp", "rb" ); // the image to be used for hding the message
	FILE *new = fopen( "output.bmp", "wb" ); // output with the message
	FILE *msg_file= fopen( "message.txt", "r"); // opening the message to hide in read only mode

	// error handling if the inputted files are empty
	if ( original == NULL || new == NULL || msg_file == NULL ) 
	{
		printf("Error opening files. \n");
		return 1;
	}


	// copying the original image to new output file
	unsigned char header[HEADER_SIZE];
	fread( header, sizeof(unsigned char), HEADER_SIZE, original );
	fwrite( header, sizeof(unsigned char), HEADER_SIZE, new );
	
	fseek( msg_file, 0, SEEK_END );
	long msg_size = ftell(msg_file);
	rewind( msg_file );

	
	fseek ( original, 0, SEEK_END );
	long image_size = ftell(original);
	rewind(original);

	// defining capacity excluding header
	long pixel_capacity = image_size - HEADER_SIZE;

	char *message = malloc( msg_size + 1 ); // +1 for \0
	fread( message, sizeof(char), msg_size, msg_file );
	message[msg_size] = '\0';

	if ( (msg_size + 1)* 8 > pixel_capacity ) {
		printf("Error : Message too large to embed in the image. \n");
		fclose(original);
		fclose(new);
		fclose(msg_file);
		free(message);
		return 1;
        }




	unsigned char pixel;
	int char_index = 0; // char i am encoding from the message
	int bit_index = 0; // which bit of that char i am currently on
	int message_done = 0; // if the message is done or not

	while ( fread(&pixel, sizeof(unsigned char), 1, original) )
	{
		if ( !message_done  ) 
		{
			// Clearing LSB
			pixel &= 0xFE;

			// getting the current message bit using bitewise and
			int bit = (message[char_index] >> bit_index & 1);

			// setting lsb to that bit
			pixel |= bit;

			bit_index++;
			if (bit_index == 8) {
			bit_index = 0;
			char_index++;
			}


			if (message[char_index] == '\0') {
			message_done = 1;
			}
		}

		fwrite ( &pixel, sizeof(unsigned char), 1, new );
	}


	fclose(original);
	fclose(new);
	fclose(msg_file);

	printf("Image copied and encoded successfully. \n");


	

	return 0;

}
