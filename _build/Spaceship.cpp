#include "Spaceship.h"

Spaceship::Spaceship(raylib::Texture* texture, raylib::Rectangle inclip, raylib::Rectangle outclip, float speed,int level) : Entity(texture, inclip, outclip, GetScreenWidth(), GetScreenHeight(),level), speed(speed) {
	moveTimer = 5 + (rand() % 15);
}


void Spaceship::Update() {
	if (enabled)
		return;
	if (moveTimer <= 0.0f)
	{
		outclip.x += speed * GetFrameTime();
		if (outclip.x > GetScreenWidth())
		{
			outclip.x = -outclip.GetSize().x;
			moveTimer = 5 + (rand() % 15);
		}
	}
	else
	{
		moveTimer -= GetFrameTime();
	}
}

