//RLE with modification

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;



int encode(){

	int lenght = 0;
	ifstream input("input.txt");
	while (!input.eof()){

		char a = input.get();
		lenght = lenght + 1;
	}
	input.close();
	lenght = lenght - 1;
	ifstream reader("input.txt");
	ofstream writer("encoded.txt");


	char *text = new char[lenght];

	int counter = 0;
	cout <<  "Input : " << endl;
	for (int i = 0; i <= lenght - 1; i++){
		text[i] = reader.get();
		cout << text[i];
		counter++;
	}
	cout << endl;

	int counterchar = 0, counterchar1 = 0; char buff1[25]; char buff; int nevivel = 0;
	for (int i = 0; i <= lenght - 1; i++){
		if (text[i] == text[i + 1] && text[i + 1] == text[i + 2]){
			if (nevivel == 1){
				if (counterchar1>9) writer << counterchar1; else writer << "0" << counterchar1;
				for (int i = 0; i <= counterchar1 - 1; i++){
					writer << buff1[i];
				}
				counterchar1 = 0; nevivel = 0;
			}

			int j = i;
			while (text[j] == text[j + 1] && text[i + 1] == text[i + 2]) { //пока повторяется
				buff = text[j]; counterchar = counterchar + 1; j = j + 1;
				if (j == (lenght - 3)){ counterchar = counterchar + 2; j = lenght; nevivel = 0; break; }
			}
			i = j;
			if (counterchar + 1>9) writer << "+" << counterchar + 1 << buff; else writer << "+" << "0" << counterchar + 1 << buff;
			counterchar = 0;
		}
		else{
			buff1[counterchar1] = text[i];
			counterchar1++;
			nevivel = 1;
		}
	}

	if (nevivel == 1){ //если строка закончилась повторением, то
		if (counterchar1>9) writer << counterchar1; else writer << "0" << counterchar1;
		for (int i = 0; i <= counterchar1 - 1; i++){
			writer << buff1[i];
		}
		counterchar1 = 0; nevivel = 0;
	}


	writer.close();
	reader.close();
	return lenght;
}

int decode(){

	ifstream reader("encoded.txt");
	
	
	int lenght = 0;; 
	while (!reader.eof()){
		char a = reader.get();
		//cout << a;
		lenght++;
	}
	lenght--;
	reader.close();

	ifstream reader2("encoded.txt");
	char *todecode = new char[lenght];
	int l = 0;
	cout << endl << "Encoded : " << endl;
	while (!reader2.eof()){
		todecode[l] = reader2.get();
		cout << todecode[l];
		l++;		
	}
	reader2.close();
	cout << endl;
	
	
	
	ofstream writer("decoded.txt");
	char a[2]; int amount = 0;
	for (int i = 0; i < lenght; i++){
		if (todecode[i] == 43){ //если равен +

			a[0] = todecode[i + 1];
			a[1] = todecode[i + 2];
			amount = ((int)a[0] - 48) * 10 + ((int)a[1] - 48);
			for (int j = 0; j < amount; j++)
				writer << todecode[i + 3];
			i = i + 3;
		}
		else{ ///если не повторяющееся
			a[0] = todecode[i];
			a[1] = todecode[i + 1];
			amount = ((int)a[0] - 48) * 10 + ((int)a[1] - 48);
			i = i + 1;
			for (int j = 0; j < amount; j++){
				i++;
				writer << todecode[i];

			}
		}

	}
	writer.close();
	

	//result
	ifstream encoder("decoded.txt");
	cout << endl << "Decoded : " << endl;
	string result;
	encoder >> result;
	cout << result;

	return lenght;
}


void main(){

	float compress = (1 / (float)encode()) * 100 * decode();
	cout << endl << endl << "Compression " << endl << compress << "%";
	cin.get();
}



