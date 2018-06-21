#include <stdio.h>
#include <string.h>
#include "strukturdata.h"

void MakeTreeStatistik(TreeStatistik *tree, FILE *file,int urutanFile){
	int i=0;
	char karakter;
	char kata[20];
	
	while((karakter=getc(file)) != EOF){
		if(karakter==' '){ //ketika menemukan spasi
			i=0;
			printf("%s",kata);
			memset(kata, 0, sizeof(kata));
		}else{
			kata[i]=karakter;
			i++;
		}
	}
	printf("%s",kata); // kata terakhir
}

int main(){
	int jmlFile,i;
	char fileName[20];
	FILE *fl;
	TreeStatistik treeStatistik;
	NodeTree *root = NULL;
	
	root = insert(root, "10");
  root = insert(root, "20");
  root = insert(root, "30");
  root = insert(root, "40");
  root = insert(root, "50");
  root = insert(root, "25");
	printf("Preorder traversal of the constructed AVL tree is \n");
  	preOrder(root);
	
	printf("\nMasukkan banyak yang akan dibandingkan: ");
	scanf("%d",&jmlFile);
	i=1;
	while(i<jmlFile+1){
		printf("\nMasukan nama file ke-%d:",i);
		scanf("%s",&fileName);
		fl = fopen(fileName,"r"); // Read file
		if(fl != NULL){
			printf("File %d berhasil dibuka",i);
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
