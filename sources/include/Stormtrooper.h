#ifndef STORMTROOPER_H
#define STORMTROOPER_H
#include "Karakter.h"

class Stormtrooper : public Karakter
{
	public:
		Stormtrooper();
		virtual ~Stormtrooper();
        virtual int shortestPath(vector<Karakter*>* badCharacters, Karakter * character, int olcum, vector<int>*fin, vector <vector <int> > *coord, vector<int> *ro, int index);

	protected:

	private:
};

#endif // STORMTROOPER_H
