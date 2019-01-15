/****************************************************************************
Purpose : This programme is written to extract entropy using seeded extractor
Programmer : Ram Singh
Date : 22 Sept 2018
Ver : 00

Input : File *.bit containing randomness obtained from the sources
Output : File *_sed.bit containing the extracted entropy

Description : The programme is written to extract the entropy using the seed 
from the bit sequence obtained from the hardware sources of randomness like 
RSS based and photoresistor based. 

Library referecne :   
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M  160
#define N  8

int main()
{
	FILE *inFile;
	FILE *seedFile;
	FILE *outFile;
	char inFilename[100], c;
	char outFilename[100];
	char seedFilename[100]="seed.txt";
	int inData[M];
	int outData[N];
	int seed[M];
	int genMatrix[M][N];  // Generator matrix
	int ret = 1;
	int i, j, k;
	int count = 0;
	
	printf("Enter the filename to open without .txt \n");
	scanf("%s", inFilename);
	strcpy(outFilename, inFilename);

	strncat(inFilename, ".txt", 4);
	strncat(outFilename, "_sed.txt", 8);
	
	// Opening the files
	
	inFile = fopen(inFilename, "r");
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
	// Opening the seed file
	seedFile = fopen(seedFilename, "r");
	if (inFile == NULL)
	{
		printf("Cannot open seedfile \n");
		exit(0);
	}

	// Reading the seed from seed file
	for (i = 0; i < M; i++) {
		fscanf(seedFile, "%d", &seed[i]);
	}

	// Forming generator matrix
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			genMatrix[j][i] = seed[(j + i) % M];
			//printf("%d\t",genMatrix[j][i]);

		}
		//printf("\n");

	}
	// Initializing the output buffer
	for (i = 0; i < N; i++) {
		outData[i] = 0;
	}
	
	// Loop for reading the input file till end of it and processing
	
	while (ret == 1) {
		for (i = 0; i < M; i++) {
			ret = fscanf(inFile, "%d", &inData[i]);
			if (ret != 1)
				break;
		}
		for (j = 0; j < N; j++) {
			for (k = 0; k < i; k++) {

				outData[j] += inData[k]* genMatrix[k][j];
											
			}
			outData[j] = outData[j] % 2;
			fprintf(outFile, "%d\n", outData[j]);
			outData[j] = 0;
		}
	}

	fclose(inFile);
	fclose(outFile);
	fclose(seedFile);
	//getch();
	return 0;
}
