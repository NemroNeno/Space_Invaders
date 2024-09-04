#ifndef _BACKGROUND
#define _BACKGROUND
#include "Entity.h"
class Background 
{

public:
	struct Star {
		Vector2 pos;
		Color color;

	};
	Background(int ,int,int);
	
	~Background();
	void drawbackground();
	void updatebackground(int i);
	Star generatestar();





protected:
	int screenw;
	int screenh;
	const int numstars;
	Star *star;

};
#endif
