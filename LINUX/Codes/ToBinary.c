/****************************************************************************************
Purpose : This programme is written to read the bit values and convert it into binary
Programmer : Ram Singh
Date : 17 Sept 2018
Ver : 00

Input : *_bit.txt file containing the bit values.
Output : *_bit.bin file containing the binary values

Description : The programme is written to read the bit values form
input file, and convert them to binary to facilitate the entropy measurement
using the iid.out file obtained by compiling the min-entropy code provided
by the reference site.

Referecne : https://github.com/usnistgov/SP800-90B_EntropyAssessment
******************************************************************************/
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

int main()
{
	FILE *inFile;
	FILE *outFile;
	char inFilename[100];
	char outFilename[100];
	int inData[10];
	int ret = 1;
	int i, j, k;
	char outData;
	
	// Taking the filename as input from the console
	
	printf("Enter the filename to open without .txt \n");
	scanf("%s", inFilename);
	strcpy(outFilename, inFilename);
	
	strncat(inFilename,".txt",4);
	strncat(outFilename, ".bin", 4);
	
	// Opening the files
	
	inFile = fopen(inFilename, "r");
	if (inFile == NULL)
	{
		printf("Cannot open infile \n");
		exit(0);
	}

	outFile = fopen(outFilename, "wb");
	if (outFile == NULL)
	{
		printf("Cannot open outfile \n");
		exit(0);
	}

	// Loop for reading the input file till end of it and processing the data.
	while (ret == 1) {
		for (i = 0; i < 8;i++) {
			ret = fscanf(inFile, "%d", &inData[i]);
		}
		if (ret == 1) {
			outData = 128 * inData[7] + 64 * inData[6] + 32 * inData[5] + 16 * inData[4] + 8 * inData[3] + 4 * inData[2] + 2 * inData[1] + inData[0];
			fwrite(&outData, 1, 1, outFile);
		}

	}
		
	fclose(inFile);
	fclose(outFile);
	return 0;
}