#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main (){
//	char a[], b[]
	string a, b;
//	a = "bore";
//	b = "bore-bear";
	
//	int start, stop;
//	int j;
//	string temp;
//	for(int i=0; i<b.length(); i++){
//		cout << b.substr(i, i+3) << endl;
//		if(b.substr(i, i+3) == " / "){
//			stop = i+3;
//			j = stop;
//			while(b[j] > 'a' && b[j] < 'z') j++;
//			cout << b.substr(stop, j);
////			for(b[int j=stop])
//		}	
//	}
//	
	a = "drunk";
	b = "drunk-drink";
	int i = a.length();
//	if(strcmp(a, b.substr(0, i-1) == 0))
	cout << b.substr(0, i) << endl;
	if(a == b.substr((0, i)))
//	int x = a.compare(b.substr(0, i));
	if(a.compare(b.substr(0, i)) == 0){
		a = b.substr(i+1);
	}
	cout << a << endl;
//	if(x == 0)
//		cout << "true";
//	else cout << "false" << endl;
		
		
	return 0;
}
