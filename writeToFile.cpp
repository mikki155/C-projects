#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <map>

using namespace std;

int writeToFile(){
	ofstream filen;
	filen.open("filen.txt");

	if (filen.fail()){
		cout << "Kunne ikke aapne fil." << endl;
	}

	cout << "Skriv inn et ord (skriv 'quit' for aa avslutte):" << endl;
	string s;
	getline(cin, s);

	while (s != "quit"){
		filen << s << endl << flush;
		cout << "Skriv inn et nytt ord:" << endl;
		getline(cin, s);
	}

	filen.close();
	return 0;

};

int readAndWrite(){
	ifstream filen;
	filen.open("filen.txt");
	ofstream tingen;
	tingen.open("tingen.txt");

	if (filen.fail() | tingen.fail()){
		cout << "Kunne ikke aapne fil." << endl;
	}
	string s;
	while (!filen.eof()){
		getline(filen, s);
		tingen << s << endl << flush;
	}
	filen.close();
	tingen.close();
	return 0;

};

int letterStatistics(){
	ifstream filen;
	filen.open("filen.txt");
	int chars[26];
	for (int i = 0; i < 26; i++){
		chars[i] = 0;
	}
	char alphabet[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0'};

	if (filen.fail()){
		cout << "Kunne ikke aapne fil." << endl;
	}
	char letter = filen.get();
	int total = 0;
	while (!filen.eof()){
		for (int i = 0; i < 26; i++){
			if (tolower(letter) == alphabet[i]){
				chars[i]++;
				total++;
			}
			
		}
		letter = filen.get();
		
	}
	cout << "Character statistics:" << endl;
	cout << "Total number of characters: " << total << endl;
	for (int i = 0; i < 26; i++)
		cout << alphabet[i] << ": " << chars[i] << endl;
	return 0;

};

void largerStatistics(){
	ofstream statistic;
	statistic.open("statistic.txt");
	ifstream Part3;
	Part3.open("Part3.txt");

	if (statistic.fail() | Part3.fail()){
		cout << "Kunne ikke aapne fil." << endl;
	}

	string rawText;
	string s;
	string rensetSetning;
	int totalLines = 0;
	while (!Part3.eof()){
		getline(Part3, s);
		totalLines++;
		for (unsigned int i = 0; i < s.size(); i++){
			if (s[i] == ' ' || tolower(s[i]) >= 'a' && tolower(s[i]) <= 'z'){
				rensetSetning.append(1, tolower(s[i]));
			}
		}
		rawText += rensetSetning;
		rensetSetning = ' ';
	}
	stringstream ss(rawText);
	string ord;
	map<string, int> forekomst;
	int totalWords = 0;
	string lengsteOrd;
	while(ss >> ord){
		totalWords++;
		if (ord.size() > lengsteOrd.size()){
			lengsteOrd = ord;
		}
		forekomst[ord]++;
	}
	statistic << "Text statistics:" << endl;
	statistic << "Longest word: " << lengsteOrd << endl;
	statistic << "Numbers of words: " << totalWords << endl;
	statistic << "Number of lines: " << totalLines << endl;
	for (auto& x : forekomst){
		statistic << x.first << ": " << x.second << endl;
	}

	statistic.close();
	Part3.close();
}

int randomWithLimits(int lower, int upper){
	int randomNumber = rand() % (upper - lower + 1) + lower;

	return randomNumber;
};