#include <stdio.h>
#include <stdlib.h>

// We are inputting BMP file which always has 54 bytes

#define HEADER_SIZE 54

int main() 
{
	FILE *original= fopen("input.bmp", "rb");
	FILE *new = fopen("output.bmp", "wb");


	if ( original == NULL || new == NULL ) 
	{
		printf("Error opening files. \n");
		return 1;
	}


	unsigned char header[HEADER_SIZE];
	fread( header, sizeof(unsigned char), HEADER_SIZE, original );
	fwrite( header, sizeof(unsigned char), HEADER_SIZE, new );
	
	unsigned char pixel;
	while ( fread( &pixel, sizeof(unsigned char), 1, original ) )
	{
		fwrite( &pixel, sizeof(unsigned char), 1, new );

	}


	fclose(original);
	fclose(new);

	printf("Image copied successfully. \n");

	return 0;

}
