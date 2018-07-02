typedef struct NodeTree{ // Node Tree
	char *kata;
	struct NodeTree *kiri;
	struct NodeTree *kanan;
	struct NodeStatistik *headStatistik;
	int height;
}NodeTree;

typedef struct TreeStatistik{ // Head tree
	struct NodeTree *root;
}TreeStatistik;

typedef struct NodeStatistik{ // Node List
	int jumlah;
	struct NodeStatistik *next;
}NodeStatistik;

typedef struct NodePersentase{
	unsigned long totalWord;
	unsigned long totalSameWord;
}NodePersentase;

typedef struct NodeNamaFile{
	char fileName[20];
	struct NodeNamaFile *next;
};

//
//typedef struct ListStatistik{ // Head List
//	struct NodeStatistik *head;
//}ListStatistik;

//NodeTree *stopwordTree = NULL;

