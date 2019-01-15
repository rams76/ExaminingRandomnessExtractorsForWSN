/****************************************************************************
Purpose : This programme is written to extract entropy using deterministic
extractor.

Programmer : Ram Singh
Date : 21 Sept 2018
Ver : 00

Input : File *.bit containing randomness obtained from the sources
Output : File *_dex.bit containing the extracted entropy

Description : The programme is written to extract the entropy from the bit 
sequence obtained from the hardware sources of randomness, like RSS based and
photoresistor based. 

Library referecne :  Nil
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	FILE *inFile;
	FILE *outFile;
	char inFilename[100];
	//char inFilename[100];
	char outFilename[100];

	int inData[1000];
	int ret = 1;
	int i, k;
	int count = 0;
	int outData;
	
	// Taking the filename as input from the console
	
	printf("Enter the filename to open without .txt \n");
	scanf("%s", inFilename);
	strcpy(outFilename, inFilename);

	strncat(inFilename, ".txt", 4);
	strncat(outFilename, "_dex.txt", 8);
	
	// Opening the files
	
	inFile = fopen(inFilename, "r+");
	if (inFile == NULL)
	{
		printf("Cannot open infile \n");
		exit(0);
	}

	outFile = fopen(outFilename, "w+");
	if (outFile == NULL)
	{
		printf("Cannot open outfile \n");
		exit(0);
	}

	// Loop for reading the input file till end of it and processing
	
	while (ret == 1) {
		for (i = 0; i < 1000; i++) {
			ret = fscanf(inFile, "%d", &inData[i]);
			if (ret != 1)
				break;
		}
		for (k = 0; k < (i - 1) / 2; k++) {
			if ((inData[k * 2] == 0) && (inData[k * 2 + 1] == 1))
			{
				outData = 0;
				fprintf(outFile, "%d\n", outData);
				count++;
			}
			if ((inData[k * 2] == 1) && (inData[k * 2 + 1] == 0))
			{
				outData = 1;
				fprintf(outFile, "%d\n", outData);
				count++;
			}
		}
	}
	printf("value of count =%d",count);
	fclose(inFile);
	fclose(outFile);
	return 0;
}




