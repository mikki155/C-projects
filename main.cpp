#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "writeToFile.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "SubstitutionCipher.h"

using namespace std;

int main(){
	//writeToFile();
	//largerStatistics();
	srand(time(0));
	Substitution game("Part3.txt");
	game.play();
	

};