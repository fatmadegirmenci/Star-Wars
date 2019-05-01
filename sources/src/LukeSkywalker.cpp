#include "LukeSkywalker.h"
#include "Karakter.h"

LukeSkywalker::LukeSkywalker() {
	setCharacterType("iyi");

	health = 6;
}

LukeSkywalker::~LukeSkywalker()
{
}

int LukeSkywalker::getHealth() {
	return health;
}

void LukeSkywalker::setHealth(int health) {
	this->health = health;
}
