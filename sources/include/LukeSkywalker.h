#ifndef LUKESKYWALKER_H
#define LUKESKYWALKER_H
#include <string>
#include "Karakter.h"

class LukeSkywalker: public Karakter
{
	public:
		LukeSkywalker();
		virtual ~LukeSkywalker();

		int getHealth();
		void setHealth(int);

	protected:

	private:
		int health;
};






#endif // LUKESKYWALKER_H
