#include "Bullet.h"
#include <math.h>
Bullet::Bullet(raylib::Texture* texture, raylib::Rectangle inclip, raylib::Rectangle outclip, int w, int h, int level,int spe)
	:Entity(texture, inclip, outclip, w, h,level), speed(spe), hit(true)

{}
bool Bullet::Ishit() {
	return hit;
}
void Bullet::reset(raylib::Rectangle pos) {
	this->outclip = pos;
	hit = false;

}
void Bullet::update() {
	outclip.y -= 50;


	if (outclip.y<-outclip.height || outclip.y>GetScreenHeight())
		hit = true;
}

void Bullet::Update() {
	outclip.y += 15;

	if (outclip.y<-outclip.height || outclip.y>GetScreenHeight())
		hit = true;
}


void Bullet::CollisionHit() {

	hit = true;

}