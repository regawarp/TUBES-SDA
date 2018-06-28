#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void substr(char dest[], char source[], int pos, int length){
	int c = 0;
	while (c < length) {
      dest[c] = source[pos+c];
      c++;
   }
}

int main (){
	char a[] = "drunk";
	char b[] = "drunk-drink";
	char *sub;
	
	int i = strlen(a);
	substr(sub, b, 0, i);
	printf("%s\n", sub);
	if(strcmp(a, sub) == 0){
		substr(a, b, i+1, strlen(b));
		printf("%s\n", a);
	}
	return 0;
}
