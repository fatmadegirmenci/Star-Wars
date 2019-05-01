#ifndef MASTERYODA_H
#define MASTERYODA_H
#include <string>
#include "Karakter.h"

class MasterYoda: public Karakter //kotu karaktere yakalaninca cani yariya iniyor
{
	public:
		MasterYoda();
		virtual ~MasterYoda();

		int getHealth();
		void setHealth(int);

	protected:

	private:
		int health;

};

#endif // MASTERYODA_H
