#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <map>
#include "writeToFile.h"

using namespace std;

class Substitution{
public:
	Substitution(char filename[]);
	void play();
private:
	const int maxWords = 15;
	map<char, char> cipher;
	map<char, char> decodeCipher;
	map<char, char> guessCipher;
	string plaintext;
	string ciphertext;
	string rawText;
	char encodeChar(char a, map<char, char>& cipher);
	string encodeString(string plainText, map<char, char>& cipher);
	int countSpaces(string input);
	int checkForErrors(string input);
	string cleanString(string input);
	void generateCipher();
	void selectRandomText();
	void askUser();
	int printErrors(string userPlaintext);
	void printUserInformation(string userPlaintext);
	string parseDecryptedText(string userPlaintext);
	void swap(char i, char j);
};

string Substitution::cleanString(string input){
	string cleansedWord;

	for (unsigned int i = 0; i < input.size(); i++){
		if (input[i] == ' ' || tolower(input[i]) >= 'a' && tolower(input[i]) <= 'z'){
			cleansedWord.append(1, tolower(input[i]));
		}
	}
	return cleansedWord;
};

Substitution::Substitution(char filename[]){
	ifstream filen;
	filen.open(filename);

	if (filen.fail()){
		cout << "Kunne ikke aapne fil." << endl;
	}

	string s;
	while (!filen.eof()){
		getline(filen, s);
		rawText += cleanString(s);
	}
	filen.close();
};

void Substitution::selectRandomText(){
	int pointer = randomWithLimits(1, rawText.length()-1);
	int words = randomWithLimits(1, maxWords);
	int totalWords = 0;
	int index = 0;
	string tempSentence;

	if ((pointer + 1) / (rawText.length()) < 0.5){
		index = pointer;
		while (rawText[index] != ' '){
			index++;
		}
		while (totalWords <= words){
			plaintext.append(1, rawText[index]);
			index++;
			if (rawText[index] == ' '){
				totalWords++;
			}
		}

	}
	else if ((pointer + 1) / (rawText.length()) >= 0.5){
		index = pointer;
		while (rawText[index] != ' '){
			index--;
		}
		while (totalWords <= words){
			plaintext.append(1, rawText[index]);
			index--;
			if (rawText[index] == ' '){
				totalWords++;
			}
		}

	}

};

void Substitution::swap(char i, char j){
	char temp = cipher[i];
	cipher[i] = cipher[j];
	cipher[j] = temp;
};

void Substitution::generateCipher(){
	for (char i = 'a'; i <= 'z'; i++){
		guessCipher[i] = i;
	}
	for (char i = 'a'; i <= 'z'; i++){
		cipher[i] = i;
	}


	int randomNumber1 = randomWithLimits('a', 'z');
	int randomNumber2 = randomWithLimits('a', 'z');
	for (int i = 0; i <= 1000; i++){
		randomNumber1 = randomWithLimits('a', 'z');
		randomNumber2 = randomWithLimits('a', 'z');
		swap(randomNumber1, randomNumber2);
	}

	/*int randomNumber = randomWithLimits((int)'a', (int)'z');
	cipher['a'] = randomNumber;
	for (char i = 'b'; i <= 'z'; i++){
		randomNumber = randomWithLimits((int)'a', (int)'z');
		for (char j = 'a'; j <= i; j++){
			while (cipher[j] == (char)randomNumber){
				randomNumber = randomWithLimits((int)'a', (int)'z');
			}
		}
		cipher[i] = randomNumber;
	}*/

	for (char i = 'a'; i <= 'z'; i++){
		decodeCipher[cipher[i]] = i;
	}

};

char Substitution::encodeChar(char a, map<char, char>& cipher){

	return cipher[a];

};


string Substitution::encodeString(string plainText, map<char, char>& cipher){
	string tempString;

	for (unsigned int i = 0; i < plainText.size(); i++){
		if (plainText[i] >= 'a' && plainText[i] <= 'z'){
			tempString.append(1, encodeChar(plainText[i], cipher));
		}
		else {
			tempString.append(1, ' ');
		}
		
	}
	return tempString;
}

int Substitution::countSpaces(string input){
	int totalSpaces = 0;
	for (unsigned int i = 0; i < input.size(); i++){
		if (input[i] == ' '){
			totalSpaces++;
		}
	}
	return totalSpaces;
};

int Substitution::checkForErrors(string input){
	int totalErrors = 0;
	for (unsigned int i = 0; i < input.size(); i++){
		if (tolower(input[i]) != plaintext[i] && input[i] != ' ')
			totalErrors++;
	}
	return totalErrors;
};

void Substitution::askUser(){
	char charToChange;
	cout << "Hvilken bokstav vil du endre paa?" << endl;
	cin >> charToChange;
	char changeTo;
	cout << "Hva vil du endre den til?" << endl;
	cin >> changeTo;
	guessCipher[tolower(charToChange)] = tolower(changeTo);

};

int Substitution::printErrors(string userPlaintext){
	int errors = checkForErrors(userPlaintext);
	cout << "Du hadde " << errors << " bokstaver feil." << endl;
	int spaces = countSpaces(userPlaintext);
	int totalSize = plaintext.size();
	double grade = ((double)totalSize - (double)spaces - (double)errors) / ((double)totalSize - (double)spaces) * 100;
	cout << "Prosentandel riktig: " << grade << "%" << endl;
	return errors;
};


string Substitution::parseDecryptedText(string userPlaintext){
	string crypted = userPlaintext;
	for (unsigned int i = 0; i < userPlaintext.size(); i++){
		if (userPlaintext[i] == plaintext[i]){
			crypted[i] = toupper(crypted[i]);
		}
	}
	return crypted;
};

void Substitution::printUserInformation(string userPlaintext){
	string s = parseDecryptedText(userPlaintext);
	cout << "Kryptert tekst: " << ciphertext << endl;
	cout << "Dekodet tekst: " << s << endl;

};

void Substitution::play(){
	string decodeText;
	selectRandomText();
	generateCipher();
	cout << plaintext << endl;
	ciphertext = encodeString(plaintext, cipher);
	decodeText = ciphertext;
	printUserInformation(decodeText);
	int errors = 0;
	errors = printErrors(decodeText);
	while (errors != 0){
		askUser();
		decodeText = encodeString(ciphertext, guessCipher);
		printUserInformation(decodeText);
		errors = checkForErrors(decodeText);
		printErrors(decodeText);
	}
	

};