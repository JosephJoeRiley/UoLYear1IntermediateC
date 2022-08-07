#include "pgmImage.h"


int int_log(int x, int y)
{

}

int int_log_inverse(int x, int y)
{
	return (int) (1.0 /int_log(x, y));
}

void writeContentsBinary(int *err_val, PgmImage *input, FILE *file_to_write, const char* write_filename)
{
	long dataStart = ftell(file_to_write);
	fclose(file_to_write);
	FILE *binary_file = fopen(write_filename, "ab");
	fseek(binary_file, dataStart, SEEK_SET);
	
	for (int i = 0; i < input->width; i++)
	{
		fwrite(input->imageData[i], sizeof(unsigned char), 
		input->height * sizeof(unsigned char), binary_file);
	}
	fclose(binary_file);	
}
void writeContentsASCII(int *err_val, PgmImage input, FILE *file_to_write)
{
	//Loop through every pixel in the file: if we have a new line
	//then print an additional new line
	int charCount= 0;	
	int pixelsWritten = 0;
	for(int pixel_row = 0; pixel_row < input.width; ++pixel_row) {
		for(int pixel_col = 0; pixel_col < input.height; ++pixel_col)
		{
			int digitCount = 0;
			int grayVal = input.imageData[pixel_row][pixel_col];
		 	fprintf(file_to_write, "%d", grayVal);
			++pixelsWritten;
			while(grayVal /= 10)
				digitCount++;
			charCount += digitCount;
			if(charCount > 0 && charCount % 70 == 0
			|| pixelsWritten % (input.height / 42) == 0)
				fprintf(file_to_write, "\n");
			else {
				fprintf(file_to_write, " ");
				charCount += 1;
			}
		}
	}

	fclose(file_to_write);
}
/*	PGMWRITE OUTLINE
Check pgmObject_a's contents are valid
		Open file_a
		Write pgmObject_a's contents to file_a
		Close file_a
		Output WRITTEN error message
*/
void pgmWrite(char *filename, PgmImage input, int *return_value)
{
	FILE *file_to_write = fopen(filename, "w");
	
	if(file_to_write == NULL)
	{
		*return_value = BAD_FILENAME;
		return;
	}

	//Print the metadata to the output file
	size_t nBytesWritten = fprintf(file_to_write, "%c%c\n%d %d\n%d\n", input.magicNumber[0], input.magicNumber[1], 
	input.width, input.height, input.maxGray);

	//We've failed in outputting if this metadata input fails
	if(nBytesWritten < 0)
	{
		*return_value = FAILED_OUTPUT;
		return;
	}
	
	//printf("Writing contents to a");
	switch (input.magicNumber[1])
	{
	case '2':
	//	printf("n ASCII pgm (%s)\n", filename);
		writeContentsASCII(return_value, input, file_to_write);
		break;
	case '5':
	//	printf(" binary pgm (%s)\n", filename);
		writeContentsBinary(return_value, &input, file_to_write, filename);
		break;
	}
	
	//printOutMsg(*return_value,"./pgmWrite", filename, "");
	return;

}
