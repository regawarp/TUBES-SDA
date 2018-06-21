/* =========================================================
Program 		: main.cpp
Deskripsi		: Main program dari aplikasi cek plagiarisme
Author			: 	- Ahmad Aji Naufal Ali (171524002)
					- Melina Pratiwi (1715240)
					- Regawa Rama Prayoga (1715240)
					
Versi/Tanggal	: 1.00 / 2018
Referensi		: > https://www.geeksforgeeks.org/linked-complete-binary-tree-its-creation/
				  > https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
				  > https://www.geeksforgeeks.org/readwrite-structure-file-c/
Compiler		: GCC 4.9.2
============================================================ 	 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct node
{
   	char data;
    struct node *right,*left;
};

struct node* newNode(char data){
	struct node* temp = (struct node*) malloc(sizeof( struct node));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

void showMenu(){
	printf(">>> PILIH MENU <<< \n");	
	printf("1. Cek Plagiarisme\n");	
	printf("2. Keluar\n");	
	printf("PILIHAN ANDA : ");	
}

// VERSI BANYAK FILE
//void cekPlagiarisme(){
//	int jumlahFile;
//	char namaFile[20];
//	
//	printf("Input JUMLAH file yang ingin diperiksa : ");
//	scanf("%d", &jumlahFile);
//	for(int i=1; i<=jumlahFile; i++){
//		getchar();
//		printf("INPUT NAMA FILE Ke-%d : ", i);
//		scanf("%[^'\n']s", &namaFile);
//		cout << "Nama file yang terbaca : " << namaFile << endl;
//	}
//	
//}

// VERSI 2 FILE
// VERSI MEMBACA SATU FILE TERLEBIH DAHULU
void cekPlagiarisme(){
	int jumlahFile;
	char namaFile[20];
	FILE *infile1, *infile2	, *outfile;
	
	printf("INPUT NAMA FILE Ke-1 : ");
	scanf("%[^'\n']s", &namaFile);
		
	infile1 = fopen(namaFile, "r");
	
	
}

int main(int argc, char *argv[]) {
	int pilihan = 0;
	while(pilihan != 2 || pilihan != 1){
		showMenu();
		scanf("%d", &pilihan);
		if(pilihan == 2)
			return 0;
		else if(pilihan == 1)
			cekPlagiarisme();
		else
			printf("\n>>> PILIHAN ANDA TIDAK VALID ! <<< \n");
		getchar();
	}
	return 0;
}
