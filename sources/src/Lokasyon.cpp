#include "Lokasyon.h"

Lokasyon::Lokasyon() {
	x = y = 0;
}

Lokasyon::~Lokasyon()
{
}

int Lokasyon::getXCoordinate() {
	return x;
}

void Lokasyon::setXCoordinate(int x) {
	this->x = x;
}

int Lokasyon::getYCoordinate() {
	return y;
}

void Lokasyon::setYCoordinate(int y) {
	this->y = y;
}

