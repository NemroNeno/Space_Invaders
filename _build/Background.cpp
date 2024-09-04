#include "Background.h"


Background::Star Background::generatestar() {
	Star star;
	star.pos.x = GetRandomValue(0, screenw);
	star.pos.y = GetRandomValue(0, screenh);
	star.color.r = GetRandomValue(250, 255);
	star.color.g = GetRandomValue(250, 255);
	star.color.b = GetRandomValue(250, 255);
	star.color.a = GetRandomValue(250, 255);
	return star;
}


Background::Background(int h,int w,int numstar) 
    :numstars{numstar}
{
    star = new Star[numstar];
	screenh = h;
	screenw = w;
	for (int i = 0; i < 100; i++) {
		star[i] = generatestar();
	}

}
void Background::drawbackground() {


    for (int i = 0; i <numstars; i++) {
        DrawRectangle(star[i].pos.x, star[i].pos.y, 2, 2, star[i].color);
    }


}



void Background::updatebackground(int i) {
    if (i == 0)
    {

        for (int i = 0; i < numstars; i++) {
            // Move the star
            star[i].pos.x += 0.5;
            star[i].pos.y += 100;

            // Wrap the star around the screen if it goes offscreen
            if (star[i].pos.x < 0) {
                star[i].pos.x = screenw;
            }
            else if (star[i].pos.x > screenw) {
                star[i].pos.x = 0;
            }
            if (star[i].pos.y < 0) {
                star[i].pos.y = screenh;
            }
            else if (star[i].pos.y > screenh) {
                star[i].pos.y = 0;
            }

            // Make the star twinkle
            if (GetRandomValue(0, 100) < 5) {
                star[i].color.a = GetRandomValue(10, 250);
            }
        }
    }
    else if (i == 1)
    {
        for (int i = 0; i < numstars; i++) {
            // Move the star
            star[i].pos.x += 0.5;
            star[i].pos.y += 5;

            // Wrap the star around the screen if it goes offscreen
            if (star[i].pos.x < 0) {
                star[i].pos.x = screenw;
            }
            else if (star[i].pos.x > screenw) {
                star[i].pos.x = 0;
            }
            if (star[i].pos.y < 0) {
                star[i].pos.y = screenh;
            }
            else if (star[i].pos.y > screenh) {
                star[i].pos.y = 0;
            }

            // Make the star twinkle
            if (GetRandomValue(0, 100) < 5) {
                star[i].color.a = GetRandomValue(10, 250);
            }
        }
    }
}

Background::~Background() {

    delete[] star;

}



