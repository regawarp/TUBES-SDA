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
	double totalWord;
	double totalSameWord;
	int fileA;
	int fileB;
//	struct NodePersentase *next;
}NodePersentase;

typedef struct NodeNamaFile{
	char *fileName;
	struct NodeNamaFile *next;
}NodeNamaFile;

//
//typedef struct ListStatistik{ // Head List
//	struct NodeStatistik *head;
//}ListStatistik;

//NodeTree *stopwordTree = NULL;

