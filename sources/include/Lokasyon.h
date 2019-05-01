#ifndef LOKASYON_H
#define LOKASYON_H
#include <string>

class Lokasyon
{
	public:
		Lokasyon();
		virtual ~Lokasyon();

		int getXCoordinate();
		int getYCoordinate();

		void setXCoordinate(int);
		void setYCoordinate(int);

	protected:

	private:
		int x;
		int y;
};


#endif // LOKASYON_H
