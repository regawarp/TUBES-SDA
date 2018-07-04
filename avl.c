// C program to insert a node in AVL tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "strukturdata.h"
 
// A utility function to get the height of the tree
int height(NodeTree *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

NodeStatistik* newNodeStat(){
	NodeStatistik* node=(NodeStatistik*)malloc(sizeof(NodeStatistik));
	node->jumlah=0;
	node->next=NULL;
	return(node);
}

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



NodePersentase* newNodePersentase(int fileA, int fileB){
	NodePersentase* node=(NodePersentase*)malloc(sizeof(NodePersentase));
	node->totalSameWord=0;
	node->totalWord=0;
	node->fileA=fileA;
	node->fileB=fileB;
	return(node);
}

NodeTree* newNode(char* kata, int jumlahFile,int urutan)
{
	NodeStatistik* temp;
    NodeTree* node = (NodeTree*)malloc(sizeof(NodeTree));
    node->kata = (char*)malloc(strlen(kata) * sizeof(char));
    
    strcpy(node->kata,kata);
	node->kiri	= NULL;
	node->kanan	= NULL;
	node->headStatistik = NULL;
	node->height= 1;
	// buat node statistik sesuai jumlah file
	int i;
	for(i=1;i<=jumlahFile;i++){
		if(i==1){
			temp=newNodeStat();
			node->headStatistik = temp;
		}else{
			temp->next=newNodeStat();
			temp=temp->next;
		}
		if(i==urutan){
			temp->jumlah=1;
		}
	}
	
	return(node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
NodeTree *rightRotate(NodeTree *y)
{
    NodeTree *x = y->kiri;
    NodeTree *T2 = x->kanan;
 
    // Perform rotation
    x->kanan	= y;
	y->kiri		= T2;
 
    // Update heights
    y->height	= max(height(y->kiri), height(y->kanan))+1;
    x->height	= max(height(x->kiri), height(x->kanan))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
NodeTree *leftRotate(NodeTree *x)
{
    NodeTree *y = x->kanan;
    NodeTree *T2 = y->kiri;
 
    // Perform rotation
    y->kiri	 = x;
	x->kanan = T2;
 
    //  Update heights
    x->height = max(height(x->kiri), height(x->kanan))+1;
    y->height = max(height(y->kiri), height(y->kanan))+1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(NodeTree *N)
{
    if (N == NULL)
        return 0;
    else
    	return height(N->kiri) - height(N->kanan);
}
 
// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
NodeTree* insert(NodeTree* node, char* kata, int jumlahFile, int urutan)
{
    /* 1.  Perform the normal BST insertion */
    if(node == NULL)
        return(newNode(kata,jumlahFile,urutan));
 
    if(strcmp(kata,node->kata) < 0){
        node->kiri = insert(node->kiri, kata,jumlahFile,urutan);
    }
    else if(strcmp(kata,node->kata) > 0){
        node->kanan = insert(node->kanan, kata,jumlahFile,urutan);
    }
    else{ // Equal keys are not allowed in BST
    	NodeStatistik* temp;
    	int i=1;
    	temp=node->headStatistik;
    	while(i!=urutan){
    		temp=temp->next;
    		i++;
    	}
    	temp->jumlah+=1;
        return node;
	}
	
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->kiri), height(node->kanan));
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && strcmp(kata, node->kiri->kata) < 0)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && strcmp(kata, node->kanan->kata) > 0)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && strcmp(kata, node->kiri->kata) > 0)
    {
        node->kiri =  leftRotate(node->kiri);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && strcmp(kata, node->kanan->kata) < 0)
    {
        node->kanan = rightRotate(node->kanan);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}

NodeTree* search(NodeTree *root, char *inword){
//	printf("inword : %s\n", inword);
	if(root == NULL || strcmp(inword, root->kata) == 0){
		return root;
	}
	
	if(strcmp(inword, root->kata) < 0){
		return search(root->kiri, inword);
	}	
	
	return search(root->kanan, inword);
}
 
// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(NodeTree *root)
{
    if(root != NULL)
    {
        printf("%s ada %d\n", root->kata,root->headStatistik->jumlah);
		preOrder(root->kiri);
        preOrder(root->kanan);
    }
}

void preOrderStatistik(NodeTree *root, int jmlFile)
{
	int i=1;
	NodeStatistik* temp;
	
    if(root != NULL)
    {
        printf("||%15s||", root->kata);
        temp=root->headStatistik;
		while(i<=jmlFile){
        	printf("%9d||", temp->jumlah);
        	
        	temp=temp->next;
        	i++;
        }
        
        printf("\n");
		preOrderStatistik(root->kiri, jmlFile);
        preOrderStatistik(root->kanan, jmlFile);
    }
}

void preOrderFileStatistik(NodeTree *root, int jmlFile,FILE *outfile)
{
	int i=1;
	NodeStatistik* temp;
	
    if(root != NULL)
    {
        fprintf(outfile,"||%15s||", root->kata);
        temp=root->headStatistik;
		while(i<=jmlFile){
        	fprintf(outfile,"%9d||", temp->jumlah);
        	
        	temp=temp->next;
        	i++;
        }
        
        fprintf(outfile,"\n");
		preOrderFileStatistik(root->kiri, jmlFile, outfile);
        preOrderFileStatistik(root->kanan, jmlFile, outfile);
    }
}

void preOrderPresentase(NodeTree *root, int jmlFile, NodePersentase *persentase)
{
	int i=1,min=0;
	NodeStatistik* temp;
		
    if(root != NULL)
    {
    	temp=root->headStatistik;
		while(i < persentase->fileA){
			temp=temp->next;
			++i;
		}
//        printf("||%15s||", root->kata);
        
        min=temp->jumlah;
		while(i<=jmlFile){
			if(i==persentase->fileA || i==persentase->fileB){
//        		printf("%9d||", temp->jumlah);
        		persentase->totalWord += temp->jumlah; // Jumlahkan Seluruh kata

				if(temp->jumlah<min){
					min=temp->jumlah;
				}
			}
        	temp=temp->next;
        	i++;
        }
        persentase->totalSameWord += min*2;
        
//        printf("\n");
		preOrderPresentase(root->kiri, jmlFile, persentase);
        preOrderPresentase(root->kanan, jmlFile, persentase);
    }
}
