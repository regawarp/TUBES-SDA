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

//#define STOPWORD_FILE stopword-en.txt

NodeTree *stopwordTree = NULL;
NodeTree *irregularTree = NULL;
NodeTree *root = NULL;
NodeTree *rootSearch = NULL;
NodeTree *rootStatistik = NULL;

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


int main(){
	int jmlFile,i;
	char fileName[30];
	FILE *fl, *f2;
	TreeStatistik treeStatistik;
//	NodeTree *root = NULL;
	
//	root = insert(root, "10",2,1);
//    root = insert(root, "20",2,1);
//  	root = insert(root, "30",2,1);
//  	root = insert(root, "40",2,1);
//    root = insert(root, "50",2,1);
//  	root = insert(root, "25",2,1);
//	printf("Preorder traversal of the constructed AVL tree is \n");
//  	preOrder(root);
	
	createStopwordTree();
	printf("Preorder traversal of the constructed AVL tree is \n");
//	preOrder(stopwordTree);
		
	createIrregularVerbTree();
//	preOrder(irregularTree);
		
	jmlFile = 1;
	printf("\nMasukkan banyak yang akan dibandingkan: ");
	scanf("%d",&jmlFile);
	i=1;
	while(i<jmlFile+1){
		strcpy(fileName, "Doc4.txt");
		printf("\nMasukan nama file ke-%d:",i);
		scanf(" %[^\n]",&fileName);
		fl = fopen(fileName,"r"); // Read file
		if(fl != NULL){
			printf("File %d berhasil dibuka \n",i);
			// MakeTreeStatistik
			MakeTreeStatistik(&treeStatistik,fl,jmlFile,i);
//			preOrder(rootStatistik);
			i++;
		}else{
			printf("\n File gagal dibuka !");
			getch();
		}
		fclose(fl);
	}
	preOrderStatistik(rootStatistik,jmlFile);
	
	// STEM stmr.c
//	char word[20];
//	
//	strcpy(word,"spotted");
//	printf("\nSebelum stem: %s",word);
//	int end = stem(word, 0, strlen(word) - 1);
//
//	word[end + 1] = 0;
//
//	printf("\nSesudah stem: %s", word);
	
	return 0;
}
