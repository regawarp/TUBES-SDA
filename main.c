/* =========================================================
Program 		: main.c
Deskripsi		: Main program dari aplikasi cek plagiarisme
Author			: 	- Ahmad Aji Naufal Ali (171524002)
					- Melina Pratiwi (1715240)
					- Regawa Rama Prayoga (1715240)
					
Versi/Tanggal	: 1.00 / 2018
Referensi		: 
				  AVL
				  > https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
				  
				  STOPWORD
				  > https://github.com/igorbrigadir/stopwords
				  > (Reuters Web of Science™)
				    https://github.com/igorbrigadir/stopwords/blob/master/en/reuters_wos.txt 
				  
				  I/O FILE
				  > https://www.geeksforgeeks.org/scanf-and-fscanf-in-c-simple-yet-poweful/
				  
				  STEMMING
				  > https://github.com/OleanderSoftware/OleanderStemmingLibrary
				  
				  IRREGULAR FORM
				  > https://en.wikipedia.org/wiki/English_irregular_verbs
				  
Compiler		: GCC 4.9.2
============================================================ 	 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "strukturdata.h"
#include "stemmerfix/stmr.h"

NodeTree *stopwordTree = NULL;
NodeTree *irregularTree = NULL;
NodeTree *root = NULL;
NodeTree *rootSearch = NULL;
NodeTree *rootStatistik = NULL;


void substr(char dest[], char source[], int pos, int length){
	int c = 0;
	while (c < length) {
      dest[c] = source[pos+c];
      c++;
   }
}

void irregularToRegular(char *dest, NodeTree *irr){
	char *sub;
	
	int i = strlen(dest);
	substr(sub, irr->kata, 0, i);
	printf("%s\n", dest);
	if(strcmp(dest, sub) == 0){
		substr(dest, irr->kata, i+1, strlen(irr->kata));
		printf(">> SETELAH DIUBAH MENJADI REGULAR : %s\n", dest);
	}
}

void MakeTreeStatistik(TreeStatistik *tree, FILE *file, int jumlahFile,int urutanFile){
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
			rootSearch =(NodeTree*) search(stopwordTree, kata);
			if(rootSearch != NULL){
				printf("[%s IS A STOPWORD]\n", kata);
				printf("[%s WILL BE DELETED]\n\n", kata);
			}else{
				printf("[%s NOT A STOPWORD]\n", kata);
				printf("[PROGRAM WILL CHECK IRREGULARITY OF %s WORD]\n", kata);
				rootSearch =(NodeTree*) search(irregularTree, kata);
				if(rootSearch != NULL){
					
					printf("[%s IS IRREGULAR FORM]\n", kata);
					printf("[PROGRAM WILL CHANGE %s TO REGULAR FORM]\n", kata);
					printf("[REGULAR FORM OF %s ", kata);
					irregularToRegular(kata, rootSearch);
					printf("is %s]\n", kata);
				}else{
					printf("[%s NOT IRREGULAR FORM]\n", kata);
					printf("[%s WILL PROCEED TO STEMMING]\n", kata);
					printf("[PROGRAM WILL REMOVE PREFIX AND SUFFIX FROM %s]\n", kata);
					// Stem
					printf("[ROOT WORD FROM %s ", kata);
					kata[stem(kata, 0, strlen(kata) - 1) + 1] = '\0';
					printf("IS %s]\n", kata);
				}
				rootStatistik=(NodeTree*)insert(rootStatistik,kata,jumlahFile,urutanFile);
				printf("[%s IS INSERTED TO THE STATISTIC]\n\n", kata);
			}
			memset(kata, 0, sizeof(kata)); // set array word jadi null / kosong
		}
	}
	if(i>0){
		i = 0;
			puts(kata); // print word
			rootSearch =(NodeTree*) search(stopwordTree, kata);
			if(rootSearch != NULL){
				printf("[%s IS A STOPWORD]\n", kata);
				printf("[%s WILL BE DELETED]\n\n", kata);
			}else{
				printf("[%s NOT A STOPWORD]\n", kata);
				printf("[PROGRAM WILL CHECK IRREGULARITY OF %s WORD]\n", kata);
				rootSearch =(NodeTree*) search(irregularTree, kata);
				if(rootSearch != NULL){
					
					printf("[%s IS IRREGULAR FORM]\n", kata);
					printf("[PROGRAM WILL CHANGE %s TO REGULAR FORM]\n", kata);
					printf("[REGULAR FORM OF %s ", kata);
					irregularToRegular(kata, rootSearch);
					printf("is %s]\n", kata);
				}else{
					printf("[%s NOT IRREGULAR FORM]\n", kata);
					printf("[%s WILL PROCEED TO STEMMING]\n", kata);
					printf("[PROGRAM WILL REMOVE PREFIX AND SUFFIX FROM %s]\n", kata);
					// Stem
					printf("[ROOT WORD FROM %s ", kata);
					kata[stem(kata, 0, strlen(kata) - 1) + 1] = '\0';
					printf("IS %s]\n", kata);
				}
				rootStatistik=(NodeTree*)insert(rootStatistik,kata,jumlahFile,urutanFile);
				printf("[%s IS INSERTED TO THE STATISTIC]\n\n", kata);
			}
			
			memset(kata, 0, sizeof(kata)); // set array word jadi null / kosong
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
		stopwordTree =(NodeTree*) insert(stopwordTree, stopword,1,1);		
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
		irregularTree =(NodeTree*) insert(irregularTree, irregular, 1, 1);		
	}
}

void showMenu(){
	printf(">>> PILIH MENU <<< \n");	
	printf("1. Cek Plagiarisme\n");	
	printf("2. Keluar\n");	
	printf("PILIHAN ANDA : ");	
}


int main(){
	int jmlFile,i,j;
	char fileName[30];
	FILE *fl, *f2;
	FILE *infile;
	TreeStatistik treeStatistik;
	NodeNamaFile *rootFileName = NULL;
	
	infile = fopen("TESTCASE.txt", "r");
	createStopwordTree();
	printf("Preorder traversal of the constructed AVL tree is \n");
		
	createIrregularVerbTree();
		
	jmlFile = 1;
	printf("\nMasukkan banyak yang akan dibandingkan: ");
	fscanf(infile, "%d",&jmlFile);
	i=1;
	
	while(i<jmlFile+1){
		printf("\nMasukan nama file ke-%d:",i);
		fscanf(infile, " %[^\n]s",&fileName);
		insertNamaFile(&rootFileName, fileName);
		
		fl = fopen(fileName,"r"); // Read file
		if(fl != NULL){
			printf("File %d berhasil dibuka \n",i);
			// MakeTreeStatistik
			MakeTreeStatistik(&treeStatistik,fl,jmlFile,i);
			i++;
		}else{
			printf("\n File gagal dibuka !");
			getch();
		}
		fclose(fl);
	}
	
	FILE *outfile;	
	outfile = fopen("OUTPUT.txt","w");
	
	i=0;
	//console
	printf("||%14s||%15s||\n", "STATISTIK KATA", "JUMLAH");
	printf("||%15s||", "KATA");
	//file
	fprintf(outfile, "||%15s||", "KATA");
	
	while(i++ < jmlFile){
		//console
		printf("%8s%2d||","FILE ",  i);		
		//file
		fprintf(outfile, "%18s%2d||","FILE ",  i);		
	}
	// console
	printf("\n||%15s||", "");
	// file
	fprintf(outfile, "\n||%15s||", "");
	i=0;
	while(i++ < jmlFile){
		//console
		printf("%10s||",rootFileName->fileName);
		//file
		fprintf(outfile, "%20s||",rootFileName->fileName);
		rootFileName = rootFileName->next;
	}
	printf("\n\n");
	fprintf(outfile, "\n\n");
	preOrderStatistik(rootStatistik, jmlFile);

	// PERSENTASE PLAGIARISME
	NodePersentase *persentase = NULL;
	printf("||%32s||\n", "PERSENTASE PLAGIARISME ANTARA   ");
	fprintf(outfile, "||%32s||\n", "PERSENTASE PLAGIARISME ANTARA   ");
	for(i=1;i<=jmlFile;i++){
		for(j=i+1;j<=jmlFile;j++){
			persentase =(NodePersentase*) newNodePersentase(i,j);
			preOrderPresentase(rootStatistik, jmlFile, persentase);
			// console
			printf("||FILE %d DAN FILE %d : %9s", i, j, "");
			printf("%.02f%%||\n",100*persentase->totalSameWord/persentase->totalWord);
			// file
			fprintf(outfile, "||FILE %d DAN FILE %d : %9s", i, j, "");
			fprintf(outfile, "%.02f%%||\n",100*persentase->totalSameWord/persentase->totalWord);
		}
	}
	return 0;
}
