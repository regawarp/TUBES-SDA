#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ultilites.h"
#include "strukturdata.h"

void MakeTreeStatistik(TreeStatistik *tree, FILE *file, int jumlahFile, int urutanFile){
	int i=0;
	char karakter;
	char kata[20];
	
	printf("KATA YANG TERBACA : \n\n");
	// TOKENIZING DAN CASE FOLDING
	while((karakter = getc(file)) != EOF){
		
		if(karakter >= 'A' && karakter <= 'Z')
			karakter +=32 ;
		
		if(karakter >= 'a' && karakter <= 'z'){
			kata[i] = karakter;
			i++;
		} else if(i > 0){
			i = 0;
			puts(kata); // print word
			rootSearch = search(stopwordTree, kata);
			if(rootSearch != NULL){
				printf(">> %s adalah stopword ! << \n", kata);
			}else{
				printf(">> %s bukan stopword ! << \n", kata);
				rootSearch = search(irregularTree, kata);
				if(rootSearch != NULL){
					printf(">> %s adalah irregular ! <<\n", kata);
					
//					char subbuff[5];
//					memcpy( subbuff, &buff[10], 4 );
//					subbuff[4] = '\0';
				}else{
					printf(">> %s bukan irresgular !<<\n", kata);
					// Stem
					printf("\nSebelum stem: %s",kata);
					kata[stem(kata, 0, strlen(kata) - 1) + 1] = '\0';
					printf("\nSesudah stem: %s\n", kata);
				}
				rootStatistik=insert(rootStatistik,kata,jumlahFile,urutanFile);
			}
			
			memset(kata, 0, sizeof(kata)); // set array word jadi null / kosong
		}
	}
}

void stopwordRemoval(char *kata){
	
}

void createStopwordTree(){
	FILE *infile;
	char stopword[20];
	infile = fopen("stopword-en.txt","r"); // Read file
	printf("|| %20s || \n", "DAFTAR STOPWORD");
	printf("|| %20s || \n", "stopword-en.txt");
	printf("|| %20s || \n", "");
	while (fscanf(infile,"%s", stopword)==1){
		printf("|| %20s || \n", stopword);
		stopwordTree = insert(stopwordTree, stopword,1,1);		
	}
}

void createIrregularVerbTree(){
	FILE *infile;
	char irregular[20];
	infile = fopen("irregular-en.in","r"); // Read file
	printf("|| %20s || \n", "IRREGULAR VERB LIST");
	printf("|| %20s || \n", "irregular-en.in");
	printf("|| %20s || \n", "");
	while (fscanf(infile,"%s", irregular)==1){
		printf("|| %20s || \n", irregular);
		irregularTree = insert(irregularTree, irregular,1,1);		
	}
}

void showMenu(){
	printf(">>> PILIH MENU <<< \n");	
	printf("1. Cek Plagiarisme\n");	
	printf("2. Keluar\n");	
	printf("PILIHAN ANDA : ");	
}

void substr(char dest[], char source[], int pos, int length){
	int c = 0;
	while (c < length) {
      dest[c] = source[pos+c];
      c++;
   }
}

