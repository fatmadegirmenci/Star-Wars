#include "MasterYoda.h"

MasterYoda::MasterYoda() {
	setCharacterType("iyi");

	health = 6;
}

MasterYoda::~MasterYoda()
{

}

int MasterYoda::getHealth() {
	return health;
}

void MasterYoda::setHealth(int health) {
	this->health = health;
}


