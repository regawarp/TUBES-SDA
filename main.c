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
	sub = (char*)malloc(strlen(dest) * sizeof(char));
	int i;
	while(irr->kata[i] != '-') i++;
	substr(sub, irr->kata, 0, i);
	if(strcmp(dest, sub) == 0){
		substr(dest, irr->kata, i+1, strlen(irr->kata));
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
				rootSearch =(NodeTree*) searchIrr(irregularTree, kata);
				if(rootSearch != NULL){
					printf("[%s IS IRREGULAR FORM]\n", kata);
					printf("[PROGRAM WILL CHANGE %s TO REGULAR FORM]\n", kata);
					printf("[REGULAR FORM OF %s ", kata);
					irregularToRegular(&kata, rootSearch);
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

void showInputDataMenu(){
	printf("||%40s||\n", "PILIH PROSES INPUT DATA : ");
	printf("||%40s||\n", "");
	printf("||%40s||\n", "1. OTOMATIS VIA FILE");
	printf("||%40s||\n", "2. MANUAL VIA CONSOLE");
	printf("||%40s||\n", "3. PETUNJUK OTOMATIS VIA FILE");
}

void showMainMenu(){
	printf("||%40s||\n", "MAIN MENU : ");
	printf("||%40s||\n", "");
	printf("||%40s||\n", "1. DETEKSI PLAGIARISME");
	printf("||%40s||\n", "2. KELUAR");
}

void showCredit(){
	printf("||%40s||\n", "PENDETEKSI PLAGIARISME");
	printf("||%40s||\n", "MADE WITH <3 BY : ");
	printf("||%40s||\n", "Ahmad Aji Naufal Ali (171524002)");
	printf("||%40s||\n", "Melina Pratiwi (171524017)");
	printf("||%40s||\n", "Regawa Rama Prayoga (17154026)");
	printf("||%40s||\n", "");
	printf("||%40s||\n", "");
	printf("||%40s||\n", "");
}

char choose(){
	int ch;
	printf("PILIHAN ANDA : ");
	scanf("%d", &ch);
	printf("\n");
	return ch;	
}

int main(){
	int jmlFile,i,j;
	char fileName[30], fileOutName[30], karakter;
	FILE *fl, *f2, *petunjuk;
	FILE *infile;
	TreeStatistik treeStatistik;
	NodeNamaFile *rootFileName = NULL;
	
	//TAMPILAN MENU
	int ch;
	showCredit();
	do{
		showMainMenu();
		ch = choose();
	}while(ch < 1 && ch > 2);
	
	if(ch > 1){
		return 0;
	}else{
		do{
			showInputDataMenu();
			ch = choose();
			if(ch == 3){
				petunjuk = fopen("Petunjuk.txt", "r");
				while((karakter = getc(petunjuk)) != EOF)
					printf("%c", karakter);
			}			
		}while(ch != 1 && ch != 2);
	}
	
	createStopwordTree();
	createIrregularVerbTree();
	
	//membaca jumlah file	
	jmlFile = 1;
	if(ch == 1){
		infile = fopen("TESTCASE.txt", "r");
		fscanf(infile, " %d", &jmlFile);
	}else{
		printf("INPUT JUMLAH FILE YANG AKAN DIBANDINGKAN : ");
		scanf("%d", &jmlFile);
		printf("\n");
	}
	printf("[PROGRAM AKAN MEMBANDINGKAN : %d FILE]\n", jmlFile);
	
	//membaca nama tiap-tiap file
	i = 1;
	while(i < jmlFile+1){
		if(ch == 1){
			fscanf(infile, " %[^\n]s",&fileName);
		}else{
			printf("INPUT NAMA FILE KE-%d :", i);
			scanf(" %[^\n]s",&fileName);
			printf("\n");
		}
		insertNamaFile(&rootFileName, fileName);
		
		fl = fopen(fileName,"r"); // Read file
		if(fl != NULL){
			printf("[FILE KE-%d BERHASIL DIBUKA]", i);
			printf("\n");
			
			//membuat tree statistik
			MakeTreeStatistik(&treeStatistik,fl,jmlFile,i);
			i++;
		}else{
			printf("[FILA GAGAL DIBUKA !]\n");
			getch();
		}
		fclose(fl);
	}
	
	//output file
	if(ch == 1){
		fscanf(infile, " %[^\n]s",&fileName);
	}else{
		printf("INPUT/BUAT NAMA FILE OUTPUT : ");
		scanf(" %[^\n]s",&fileName);
		printf("\n");
	}
	
	FILE *outfile;	
	outfile = fopen(fileName,"w");
	//console
	printf("||%14s||%15s||\n", "STATISTIK KATA", "JUMLAH");
	printf("||%15s||", "KATA");
	//file
	fprintf(outfile, "||%15s||", "KATA");
	
	i = 0;
	while(i++ < jmlFile){
		//console
		printf("%8s%2d||","FILE ",  i);		
		//file
		fprintf(outfile, "%16s%2d||","FILE ",  i);		
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
		fprintf(outfile, "%18s||",rootFileName->fileName);
		rootFileName = rootFileName->next;
	}
	printf("\n\n");
	fprintf(outfile, "\n\n");
	preOrderStatistik(rootStatistik, jmlFile);
	preOrderFileStatistik(rootStatistik, jmlFile, outfile);

	// PERSENTASE PLAGIARISME
	NodePersentase *persentase = NULL;
	//console
	printf("||%32s||\n", "PERSENTASE PLAGIARISME ANTARA   ");
	//file
	fprintf(outfile, "||%32s||\n", "PERSENTASE PLAGIARISME ANTARA   ");
	for(i=1;i<=jmlFile;i++){
		for(j=i+1;j<=jmlFile;j++){
			persentase =(NodePersentase*) newNodePersentase(i,j);
			preOrderPresentase(rootStatistik, jmlFile, persentase);
			// console
			printf("||FILE %d DAN FILE %d : %9s", i, j, "");
			// file
			fprintf(outfile, "||FILE %d DAN FILE %d : %9s", i, j, "");
			if(persentase->totalWord==0){
				printf("Kedua File Kosong\n");
				fprintf(outfile,"Kedua File Kosong\n");
			}else{
				printf("%.02f%%||\n",100*persentase->totalSameWord/persentase->totalWord);
				fprintf(outfile, "%.02f%%||\n",100*persentase->totalSameWord/persentase->totalWord); //file
			}
		}
	}
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("TERIMA KASIH TELAH MENGGUNAKAN APP INI \n");
	printf("SILAKAN LIHAT STATISTIK DAN PERSENTASE PLAGIARISME PADA FILE %s \n", fileName);
	printf("ATAU SCROLL TAMPILAN INI KE ATAS AGAR DAPAT MELIHAT BAGAIMANA PROGRAM INI BEKERJA\n");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	return 0;
}
