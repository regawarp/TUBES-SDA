#include "strukturdata.h"

void MakeTreeStatistik(TreeStatistik *tree, FILE *file, int jumlahFile, int urutanFile);
void stopwordRemoval(char *kata);
void createStopwordTree();
void createIrregularVerbTree();
void showMenu();
void substr(char dest[], char source[], int pos, int length);

