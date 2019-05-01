#ifndef KYLOREN_H
#define KYLOREN_H
#include "Karakter.h"

#include "KyloRen.h"

using namespace std;

class KyloRen: public Karakter //cok hizli. tek hamlede 2 basamak ilerliyor
{
	public:
		KyloRen();
		virtual ~KyloRen();
        virtual int shortestPath(vector<Karakter*>* badCharacters, Karakter * character, int olcum, vector<int>*fin, vector <vector <int> > *coord, vector<int> *ro, int index); //en kisa yol algoritmasi
};

#endif // KYLOREN_H
