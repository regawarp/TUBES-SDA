#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
	char a[] = "saya makan";
//	char b[20][3];
	int i, x = 20;
	int y = 2;
//	char *b = (char*)malloc(x * y * sizeof(char));
	
	char **b = (char **)malloc(x * sizeof(char *));
    for (i=0; i<x; i++)
         b[i] = (char *)malloc(y * sizeof(char));
	
	
	char c[] = "saya bermain";
	strcpy(b[0], a);
	strcpy(b[1], c);
	printf("%s\n", b[0]);
	printf("%s\n", b[1]);
	
	char d[] = "budi bersepeda";
	
	y = 4;
//	char **b2 = **b;
//	char b2[][] = b[];
	char **b2 = (char **)malloc(sizeof(char) * x);
	for(i=0; i<x; i++){
		b2[i] = (char *)malloc(y * sizeof(char));
	}
	memcpy(b2, b, sizeof(b));
	
	printf("%s\n", b2[0]);
	printf("%s\n", b2[1]);
//	printf("")
	
       
       
//	char nama[10] = "saya";
//	char panggilan[10][10];
//	strcpy(panggilan[][], saya);
//	printf("%s", panggilan[1]);
	
	return 0;
}
