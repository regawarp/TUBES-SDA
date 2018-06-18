#include <stdio.h>
#include <string.h>

typedef struct NodeTree{ // Node Tree
	char kata[12];
	struct NodeTree *kiri;
	struct NodeTree *kanan;
	struct ListStatistik *headStatistik;
}NodeTree;
typedef struct TreeStatistik{ // Head tree
	struct NodeTree *root;
}TreeStatistik;
typedef struct NodeStatistik{ // Node List
	int jumlah;
	struct NodeStatistik *next;
};
typedef struct ListStatistik{ // Head List
	struct NodeStatistik *head;
}ListStatistik;

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
	
	printf("Masukkan banyak yang akan dibandingkan: ");
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
