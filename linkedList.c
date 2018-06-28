#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "strukturdata.h"

NodeNamaFile* newNodeNamaFile(char *fileName){
	NodeNamaFile* node=(NodeNamaFile*)malloc(sizeof(NodeNamaFile));
	node->nama = (char*)malloc(strlen(fileName) * sizeof(char));
	strcpy(node->nama, fileName);
	return(node);	
}

NodeStatistik* newNodeStat(){
	NodeStatistik* node=(NodeStatistik*)malloc(sizeof(NodeStatistik));
	node->jumlah=0;
	node->next=NULL;
	return(node);
}
