#include "Karakter.h"
#include <cmath>

using namespace std;

Karakter::Karakter() {
}

Karakter::~Karakter()
{
	//dtor
}

string Karakter::getCharacterName() {
	return characterName;
}

void Karakter::setCharacterName(string characterName) {
	this->characterName = characterName;
}

string Karakter::getCharacterType() {
	return characterType;
}

void Karakter::setCharacterType(string characterType) {
	this->characterType = characterType;
}

int Karakter::shortestPath(vector<Karakter*>* badCharacters, Karakter * character, int olcum, vector<int>*fin, vector <vector <int> > *coord, vector<int> *ro, int index) {
}

