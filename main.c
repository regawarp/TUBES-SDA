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
				  > 
Compiler		: GCC 4.9.2
============================================================ 	 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "strukturdata.h"

//#define STOPWORD_FILE stopword-en.txt

NodeTree *stopwordTree = NULL;
NodeTree *root = NULL;
NodeTree* rootSearch = NULL;

void MakeTreeStatistik(TreeStatistik *tree, FILE *file, int urutanFile){
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
			if(rootSearch != NULL)
				printf(">> %s adalah stopword ! << \n", kata);
			else
				printf(">> %s bukan stopword ! << \n", kata);
				
//			puts(rootSearch->kata);	
//			kata = rootSearch->kata;
//			if(search(stopwordTree, kata) == false){
//				puts(kata);	
//			}
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
		stopwordTree = insert(stopwordTree, stopword);		
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
	FILE *fl;
	TreeStatistik treeStatistik;
//	NodeTree *root = NULL;
	
	root = insert(root, "10");
    root = insert(root, "20");
  	root = insert(root, "30");
  	root = insert(root, "40");
    root = insert(root, "50");
  	root = insert(root, "25");
	printf("Preorder traversal of the constructed AVL tree is \n");
  	preOrder(root);
	
	createStopwordTree();
	printf("Preorder traversal of the constructed AVL tree is \n");
	preOrder(stopwordTree);
		
	jmlFile = 1;
	printf("\nMasukkan banyak yang akan dibandingkan: ");
//	scanf("%d",&jmlFile);
	i=1;
	while(i<jmlFile+1){
		strcpy(fileName, "Doc4.txt");
		printf("\nMasukan nama file ke-%d:",i);
//		scanf(" %[^\n]",&fileName);
		fl = fopen(fileName,"r"); // Read file
		if(fl != NULL){
			printf("File %d berhasil dibuka \n",i);
			// MakeTreeStatistik
			MakeTreeStatistik(&treeStatistik,fl,i);
			i++;
		}else{
			printf("\n File gagal dibuka !");
			getch();
		}
		fclose(fl);
	}
	
	return 0;
}
