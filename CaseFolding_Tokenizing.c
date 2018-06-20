#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(){
	int t;
	int i;
	int count, len;
	FILE *infile;
	char ch;
	char word[15];
//	char *token;
//	char *rest = str;
	
	infile = fopen("input.in", "r");
	printf("FILE YANG TERBACA : \n");
	while(fread(&ch, sizeof(ch), 1, infile)){ // selama belum EOF, assign satu karakter dari file ke var ch
		printf("%c", ch);
	}
	printf("\n\n");
//	printf("123");
	
	rewind(infile);
	i = 0;
	while(fread(&ch, sizeof(ch), 1, infile)){ // selama belum EOF, assign satu karakter dari file ke var ch
		
		if(ch >= 'A' && ch <= 'Z'){ 
			ch +=32 ;	// ISI DISINI
		}
		
		if(ch >= 'a' && ch <= 'z'){
			// ISI DISINI
			word [i] = ch;
			i++;
		}

		if(ch == ' ' || ch == '.'){
			i = 0;
			puts(word); // print word
			memset(word, 0, sizeof(word)); // set array word jadi null / kosong
		}
	}
	
    fclose(infile);
	return 0;
}
