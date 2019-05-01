#ifndef DARTHVADER_H
#define DARTHVADER_H
#include "Karakter.h"
#include "KyloRen.h"
#include "DarthVader.h"
#include "Stormtrooper.h"

class DarthVader : public Karakter
{
	public:
		DarthVader();
		virtual ~DarthVader();
		int shortestPath(vector<Karakter*>* badCharacters, Karakter * character, int olcum, vector<int>*fin, vector <vector <int> > *coord, vector<int> *ro, int index);

	protected:

	private:
};

#endif // DARTHVADER_H
