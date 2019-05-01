#ifndef KARAKTER_H
#define KARAKTER_H
#include <string>
#include "Lokasyon.h"
#include <vector>
#include "allegro5/allegro.h"

using namespace std;
class Karakter : public Lokasyon
{
	public:
		Karakter();
		virtual ~Karakter();

		vector <vector<int> > nodes;
		ALLEGRO_BITMAP *character = NULL;

		string getCharacterName();
		string getCharacterType();

		void setCharacterName(string);
		void setCharacterType(string);

        virtual int shortestPath(vector<Karakter*>* badCharacters, Karakter * character, int olcum, vector<int>*fin, vector <vector <int> > *coord, vector<int> *ro, int index);
		virtual int getHealth(){}
		virtual void setHealth(int){}

	protected:

	private:
		int health;
		string characterName; //karakter adi
		string characterType; //karakter turu(iyi/kotu)
		Lokasyon coordinates; //karakterin ilerledigi koordinatlari tutacak

};


#endif // KARAKTER_H
