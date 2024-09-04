#include "Alien.h"


#include "Alien.h"
#include "Bullet.h"
 float Alien::speed_increment = 0.0f;
 int Alien::count = 0;



 Alien::Alien(raylib::Texture* texture, raylib::Rectangle inclip, raylib::Rectangle outclip, float speed, float offset, float initialDelay, float delay, raylib::Texture* textureforbullets,int level) : Entity(texture, inclip, outclip, GetScreenWidth(), GetScreenWidth(),level), speed(speed*level), offset(offset), moveDelay(delay), moveTimer(initialDelay), towardsBottom(0.0f)
{
	initial = outclip.x;

	bullet = new Bullet(textureforbullets, raylib::Rectangle(24, 0, 8, -8), outclip, GetScreenWidth(), GetScreenHeight(),level, speed * 3.0f);
	shootingTimer = 5 + (rand() % (30-(10*level)));
	count++;
}


Alien::~Alien() {
	delete bullet;
}



void Alien::Update() {
	if (!enabled)
		return;

	if (moveTimer <= 0.0f)
	{

		if (moveTimer > -moveDelay)
		{
			outclip.x += ((GetFrameTime() * speed) * 2);
			if (towardsBottom > 0.0f)
			{
				//towardsBottom -= GetFrameTime()* speed;
				outclip.y += ((towardsBottom * GetFrameTime()) * 1.2);//GetFrameTime() * speed;
			}
			else
			{
				towardsBottom += GetFrameTime() * speed;
				outclip.y += ((towardsBottom * GetFrameTime()) * 1.2);//GetFrameTime() * speed;
			}
		}
		else
		{
			moveTimer += (moveDelay / 200);

		}
	}
	else {
		moveTimer -= (GetFrameTime() + moveTimer / 2500);
	}

	if (outclip.x >= initial + offset)
	{
		speed = -abs(speed);
		towardsBottom = 4;
	}
	else if (outclip.x < initial)
	{
		speed = abs(speed);
		towardsBottom = 4;
	}

	else
	{
		if (speed > 0)
			speed = abs(speed);
		else
			speed = -abs(speed);
	}




	if (shootingTimer <= 0.0f) {

		if (bullet->Ishit())
		{
			bullet->reset(outclip);
			shootingTimer = 5 + (rand() % 30);

		}

	}
	else if (shootingTimer > 0.0f) {
		shootingTimer -= GetFrameTime();
	}


	if (!bullet->Ishit()) {
		bullet->Update();
	
	}

}

void Alien::draw() {


	if (!enabled)
		return;
	texture->Draw(inclip, outclip);
	if (!bullet->Ishit()) {
		bullet->draw();
	}
	
}


void Alien::getCollisions(Entity* e) {

	if (!bullet->Ishit() && bullet->iscolliding(e))
	{
		speed_increment += 1.5;
		bullet->CollisionHit();
		e->Recieve(Damage);
	}
	}
void Alien::setSpeed(float v) {

	speed_increment = v;

}


int Alien:: getcount() {

	return count;

}
void Alien:: resetcount() {

	count = 0;

}

int Alien::Recieve(int i) {

	switch (i) {

	case Damage:
		damagepoint--;
		if (damagepoint == 0)
		{
			enabled = false;
			count--;
			speed_increment += 0.5;
		}
		break;
	}
	return (GetScreenHeight() - outclip.y);

}