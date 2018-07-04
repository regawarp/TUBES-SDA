#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct NodeNamaFile{
	char *fileName;
	struct NodeNamaFile *next;
}NodeNamaFile;

NodeNamaFile* newNodeNamaFile(char* inName){
	printf("[inName : %s]\n", inName);
	NodeNamaFile* node= (NodeNamaFile*)malloc(sizeof(NodeNamaFile));
	node->fileName = (char*)malloc(strlen(inName) * sizeof(char));
	strcpy(node->fileName, inName);
	node->next = NULL;
	return(node);
}

void insertNamaFile(NodeNamaFile** node, char* inName){
	printf("[inName : %s]\n", inName);
    if(*node == NULL){
        *node = newNodeNamaFile(inName);
        return;
	}else{
		NodeNamaFile *trv = *node;
		while(trv->next != NULL){
//			node = node->next;
			trv = trv->next;
		}
		trv->next = newNodeNamaFile(inName);
		return;
	}
//	else{
//		while(*node->next != NULL){
//			*node = *node->next;
//		}
//		*node->next = newNodeNamaFile(inName);
//	}
}

int main (){
	NodeNamaFile *rootFileName = NULL;
	
	insertNamaFile(&rootFileName, "Regawa");	
	insertNamaFile(&rootFileName, "Rama");	
//	rootFileName = newNodeNamaFile("Regawa");
	
	printf("%s", rootFileName->fileName);
	printf("%s", rootFileName->next->fileName);
	return 0;
}
