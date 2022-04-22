#include<stdio.h>

void printchar(char* name, unsigned char* A, unsigned long long L) {
	printf("%s: ", name);
	for (int i = 0; i < L; i++) printf("%02X", A[i]);
	printf("\n");
}