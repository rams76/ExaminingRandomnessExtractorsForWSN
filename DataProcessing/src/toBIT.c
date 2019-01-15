/****************************************************************************************
Purpose : This programme is written to read the measured value and convert it into bits
Programmer : Ram Singh
Date : 17 Sept 2018
Ver : 00

Input : *.txt file containing the physical measurement values.
Output : *_bit.txt file containing the bit sequence in 0's and 1's

Description : The programme is written to read the RSSI values or Resistance
values from the input file, take mean for N=200 values and compare each value
with this mean. If measured vale is greater than mean assign 1 to output
otherwise assign 0 to output.

Referecne :  
******************************************************************************/

#include <stdio.h>
#include <string.h>

// Defining constant N the size of buffer
#define N 200

/* Function : mean()
*  Takes the array and size of array as input and returns the avg/mean value of the 
*  buffer
***********************************************************/

float mean(int m, int a[]) {
	int sum = 0, i;
	for (i = 0; i<m; i++)
		sum += a[i];
	return((float)sum / m);
}

int main()
{
	FILE *inFile;
	FILE *outFile;
	char inFilename[100];
	char outFilename[100];
	
	int inData[N];
	int ret = 1;
	int i, j, k;
	int outData[N];
	float avg;
	
	// Taking the filename as input from the console
	
	printf("Enter the filename to open without .txt \n");
	scanf("%s", inFilename);
	strcpy(outFilename, inFilename);

	strncat(inFilename, ".txt", 4);
	strncat(outFilename, "_bit.txt", 8);
	
	// Opening the file 
	inFile = fopen(inFilename, "r");
	if (inFile == NULL)
	{
		printf("Cannot open input file \n");
		exit(0);
	}

	outFile = fopen(outFilename, "w+");
	if (outFile == NULL)
	{
		printf("Cannot open output file \n");
		exit(0);
	}

	// Loop for reading the input file till end of file.
	while (ret == 1) {
		for (i = 0; i < N; i++) {
			ret = fscanf(inFile, "%d", &inData[i]);
			if (ret != 1)
				break;
		}
		avg = mean(i,inData);
		printf("%f,%d\n", avg,i);
		if (ret == 1) {
			
			for (k = 0; k < (i); k++) {
				if (inData[k] < avg)
					outData[k] = 0;
				else
					outData[k] = 1;
				fprintf(outFile, "%d\n", outData[k]);
			}
		}

	}
	
	fclose(inFile);
	fclose(outFile);
	return 0;
}


