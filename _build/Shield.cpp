#include "Shield.h"

Shield::Shield(raylib::Texture2D* texture, raylib::Rectangle outRect, raylib::Rectangle inRect,int level) : Entity(texture, outRect, inRect, GetScreenWidth(), GetScreenHeight(),1), hp(8)
{

}

void Shield::Update()

{

	if (!enabled)
	{
		return;
	}
	if (hp > 0)
		inclip.x = 40 + (((hp/2) - 1) * 16);

}
void Shield::draw()

{
	if (!enabled)
	{
		return;
	}
	texture->Draw(inclip, outclip);
}

void Shield::Event()
{

}

int Shield::Recieve(int i) {

	switch (i) {

	case Damage:

		hp--;
		if (hp <= 0)
			enabled = false;
		break;

	}
	return 0;
}


