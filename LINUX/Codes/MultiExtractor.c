/****************************************************************************
Purpose : This programme is written to extract entropy using multi-source extractor
Programmer : Ram Singh
Date : 22 Sept 2018
Ver : 00

Input1 : File *.bit containing randomness obtained from first source
Input2 : File *.bit containing randomness obtained from second source

Output : File MultiExtractor.bit containing the extracted entropy

Description : The programme is written to extract the entropy from the multiple 
sources using Hadamard matrix. The sequence obtained from the hardware sources 
of randomness like RSS based and photoresistor based are used as input. 

Library referecne :   
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define N 32
int main()
{
	FILE *inFile1;
	FILE *inFile2;
	FILE *outFile;
	char inFilename1[100], inFilename2[100];
	
	int inData1[N];
	int inData2[N];
	int outData=0;
	int temp=0;
	
	int ret1 = 1;
	int ret2 = 1;
	int i, j, k;
	int count = 0;
	
	// Taking the filename as input from the console
	
	printf("Enter the filename1 to open without .txt \n");
	scanf("%s", inFilename1);
	printf("Enter the filename2 to open without .txt \n");
	scanf("%s", inFilename2);

	strncat(inFilename1, ".txt", 4);
	strncat(inFilename2, ".txt", 4);
	
	char outFilename[100] = "MultiExtractor.txt";
	
	// Opening the files 
	
	inFile1 = fopen(inFilename1, "r+");
	if (inFile1 == NULL)
	{
		printf("Cannot open infile1 \n");
		exit(0);
	}
	inFile2 = fopen(inFilename2, "r+");
	if (inFile2 == NULL)
	{
		printf("Cannot open infile2 \n");
		exit(0);
	}
	outFile = fopen(outFilename, "w+");
	if (outFile == NULL)
	{
		printf("Cannot open outfile \n");
		exit(0);
	}

	while (ret1 == 1 && ret2 == 1 ) {
		for (i = 0; i < N; i++) {
			ret1 = fscanf(inFile1, "%d", &inData1[i]);
			ret2 = fscanf(inFile2, "%d", &inData2[i]);
			fseek(inFile1,-(N/2), SEEK_CUR);
			
			if (ret1 != 1 || ret2 != 1)
				break;
		}
		
			for (k = 0; k < i; k++) {

				temp += inData1[k]* inData2[k];
											
			}
			
			outData = pow(-1, temp);
			if (outData == -1)
				outData = 0;
			fprintf(outFile, "%d\n", outData);
			temp = 0;
		
	}

	fclose(inFile1);
	fclose(inFile2);
	fclose(outFile);
	return 0;
}




