#include "pgmErrors.h"


//Usage: leave filename and/or miscMessage blank if 
//they will be unsused
int printOutMsg(int errorCode, const char *programName, 
const char *filename, const char *miscMessage) 
{
	char callerID[strlen(programName) - 5];
	
	//Create a string that chops off the leading 
	//"./pgm" so our main switch statement is more 
	//readable
	//We need the entire title, not only for 
	//readablility, since the names of 
	//the modules may share inital letters
	for(int i = 5; i <= strlen(programName); ++i)
		callerID[i - 5] = programName[i];
		
	switch(errorCode)
	{
		case -1:
		if(!strcmp(callerID, "Comp"))
			printf("DIFFERENT");
		errorCode = 0;
		break;
		case 0:	
			//if(!strcmp(callerID, "Read"))
				//printf("READ");
			//if(!strcmp(callerID, "Write"))
				//printf("WRITTEN");
			if(!strcmp(callerID, "Echo"))
				printf("ECHOED");	
			if(!strcmp(callerID, "Comp"))
				printf("IDENTICAL");
			if(!strcmp(callerID,"a2b") || 
			!strcmp(callerID,"b2a")) 
				printf("CONVERTED");
			if(!strcmp(callerID, "Reduce"))
				printf("REDUCED");
			if(!strcmp(callerID, "Tile"))
				printf("TILED");
			if(!strcmp(callerID, "Assemble"))
				printf("ASSEMBLED");
			//if(!strcmp(callerID, "Allocate"))
				//printf("DATA ALLOCATED");
		break;
		
		break;
		case 1 ... 100:
			printf("ERROR: ");
		//We're using the defines here in case 
		//the error codes are changed around at any point
		switch(errorCode) 
		{
			///Wrong number of arguments (but not zero arguments)
 			case BAD_ARG_NO:
				printf("Bad Argument Count ");
			break;
			//Read filename does not exist
 			case BAD_FILENAME:
				printf("Bad File Name ");
			break;
			//Magic number is invalid
 			case BAD_MAGIC_NO:
				printf("Bad Magic Number ");
			break;
			//Comment line is corrupted or otherwise incorrect
 			case BAD_COMMENT:
				printf("Bad Comment Line ");
			break;
			//Width and/or height are outside the min_max range
 			case BAD_DIMENSIONS:
				printf("Bad Dimensions ");
			break;
			//Max gray does not equal 255
 			case BAD_MAX_GRAY:
				printf("Bad Max Gray Value ");
			break;
			//Malloc of data for pointer failed 
 			case FAILED_MALLOC:
				printf("Image Malloc Failed ");
			break;
		 	//Reading in image data failed
 			case BAD_DATA:
				printf("Bad Data ");
			break;
			//Writing in image data failed
 			case FAILED_OUTPUT:
				printf("Output Failed ");
			break;
			//Assembly layout went wrong
 			case BAD_LAYOUT:
				printf("Bad Layout ");
			break;
			//Any other error
 			case MISC_ERROR:
				printf("Miscellaneous ");
			break;
		}
		break;
		case 101:
		printf("Usage: ");
			if(!strcmp(callerID, "Echo"))
				printf("./pgmEcho inputImage.pgm outputImage.pgm");
			if(!strcmp(callerID, "Comp"))
				printf("./pgmComp inputImage.pgm inputImage.pgm");
			if(!strcmp(callerID, "a2b"))
				printf("./pgma2b inputImage.pgm outputImage.pgm");
			if(!strcmp(callerID, "b2a"))
				printf("./pgmb2a inputImage.pgm outputImage.pgm");
			if(!strcmp(callerID, "Reduce"))
				printf("./pgmReduce inputImage.pgm reduction_factor outputImage.pgm");
			if(!strcmp(callerID, "Tile"))
				printf("./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm");
			if(!strcmp(callerID, "Assemble"))
				printf("./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+");
			errorCode = 0;
		break;
	}
	//Only printing the file name
	//and/or message if they exist
	if(strcmp(filename, ""))
		printf("(%s)", filename);
	if(strcmp(miscMessage, ""))
		printf("(%s)", miscMessage);
	printf("\n");
	return errorCode;
}
