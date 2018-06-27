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
				  > 
Compiler		: GCC 4.9.2
============================================================ 	 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stemming/english_stem.h"
#include "strukturdata.h"
#include "avl.c"

#include "stemming/english_stem.h"
#include "stemming/french_stem.h"
#include "stemming/german_stem.h"
#include "stemming/finnish_stem.h"
#include "stemming/swedish_stem.h"
#include "stemming/spanish_stem.h"
#include "stemming/dutch_stem.h"
#include "stemming/danish_stem.h"
#include "stemming/italian_stem.h"
#include "stemming/norwegian_stem.h"
#include "stemming/portuguese_stem.h"
#include "stemming/russian_stem.h"
#include <string>
#include <iostream>


NodeTree *stopwordTree = NULL;
NodeTree *root = NULL;
NodeTree* rootSearch = NULL;

void MakeTreeStatistik(TreeStatistik *tree, FILE *file, int urutanFile){
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
			rootSearch = search(stopwordTree, kata);
			if(rootSearch != NULL){
				printf(">> %s adalah stopword ! << \n", kata);
				puts(rootSearch->kata);	
			}else{
				printf(">> %s bukan stopword ! << \n", kata);
			}
//			kata = rootSearch->kata;
//			if(search(stopwordTree, kata) == false){
//				puts(kata);	
//			}
			memset(kata, 0, sizeof(kata)); // set array word jadi null / kosong
		}
	}
}

void stopwordRemoval(char *kata){
	
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
		stopwordTree = insert(stopwordTree, stopword);		
	}
}

void showMenu(){
	printf(">>> PILIH MENU <<< \n");	
	printf("1. Cek Plagiarisme\n");	
	printf("2. Keluar\n");	
	printf("PILIHAN ANDA : ");	
}


int main(){
	int jmlFile,i;
	char fileName[20];
	FILE *fl;
	TreeStatistik treeStatistik;
//	NodeTree *root = NULL;
	
	root = insert(root, "10");
    root = insert(root, "20");
  	root = insert(root, "30");
  	root = insert(root, "40");
    root = insert(root, "50");
  	root = insert(root, "25");
	printf("Preorder traversal of the constructed AVL tree is \n");
  	preOrder(root);
	
	createStopwordTree();
	printf("Preorder traversal of the constructed AVL tree is \n");
	preOrder(stopwordTree);
		
	jmlFile = 1;
	printf("\nMasukkan banyak yang akan dibandingkan: ");
//	scanf("%d",&jmlFile);
	i=1;
	while(i<jmlFile+1){
		strcpy(fileName, "Doc4.txt");
		printf("\nMasukan nama file ke-%d:",i);
//		scanf("%s",&fileName);
		fl = fopen(fileName,"r"); // Read file
		if(fl != NULL){
			printf("File %d berhasil dibuka \n",i);
			// MakeTreeStatistik
			MakeTreeStatistik(&treeStatistik,fl,i);
			i++;
		}else{
			printf("\n File gagal dibuka !");
			getch();
		}
		fclose(fl);
	}
	
	
	// FROM ORLEANDER STEMMING LIB
    //the word to be stemmed
    std::wstring word(L"transportation");
    /*create an instance of a "english_stem" class. The template argument for the
    stemmers are the type of std::basic_string that you are trying to stem, by default 
    std::wstring (Unicode strings). As long as the char type of your basic_string is wchar_t,
    then you can use any type of basic_string. This is to say, if your basic_string has a custom
    char_traits or allocator, then just specify it in your template argument to the stemmer. For example:

    typedef std::basic_string<wchar_t, myTraits, myAllocator> myString;
    myString word(L"documentation");
    stemming::english_stem<myString> StemEnglish;
    StemEnglish(word);*/
    stemming::english_stem<> StemEnglish;
    std::wcout << L"(English) Original text:\t" << word.c_str() << std::endl;
    //the "english_stem" has its operator() overloaded, so you can
    //treat your class instance like it's a function.  In this case,
    //pass in the std::wstring to be stemmed.  Note that this alters
    //the original std::wstring, so when the call is done the string will
    //be stemmed.
    StemEnglish(word);
    //now the variable "word" should equal "document"
    std::wcout << L"(English) Stemmed text:\t" << word.c_str() << std::endl;
    //try a similar word that should have the same stem
    word = L"documenting";
    std::wcout << L"(English) Original text:\t" << word.c_str() << std::endl;
    StemEnglish(word);
    //now the variable "word" should equal "document"
    std::wcout << L"(English) Stemmed text:\t" << word.c_str() << std::endl;

    //Now try a French word
    stemming::french_stem<> StemFrench;
    word = L"continuellement";
    std::wcout << L"\n(French) Original text:\t" << word.c_str() << std::endl;
    StemFrench(word);
    //now the variable "word" should equal "continuel"
    std::wcout << L"(French) Stemmed text:\t" << word.c_str() << std::endl;

    //Many other stemmers are also available
    stemming::german_stem<> StemGerman;
    stemming::finnish_stem<> StemFinnish;
    stemming::swedish_stem<> StemSwedish;
    stemming::dutch_stem<> StemDutch;
    stemming::spanish_stem<> StemSpanish;
    stemming::italian_stem<> StemItalian;
    stemming::norwegian_stem<> StemNorwgian;
    stemming::danish_stem<> StemDanish;
    stemming::portuguese_stem<> StemPortuguese;

    /*if you are using std::string (ANSI strings) then convert it to a temporary
    wchar_t buffer, assign that to a std::wstring, and then stem that.*/
    std::string ANSIWord("documentation");
    wchar_t* UnicodeTextBuffer = new wchar_t[ANSIWord.length()+1];
    std::wmemset(UnicodeTextBuffer, 0, ANSIWord.length()+1);
    std::mbstowcs(UnicodeTextBuffer, ANSIWord.c_str(), ANSIWord.length());
    word = UnicodeTextBuffer;
    StemEnglish(word);
    //now the variable "word" should equal "document"
    std::wcout << L"\nDemonstrating the stemming of an ANSI string:\n";
    std::wcout << L"(English) Original text:\t" << ANSIWord.c_str() << std::endl;
    std::wcout << L"(English) Stemmed text:\t" << word.c_str() << std::endl;

    return 0;
}
