#include "Entity.h"
 

Entity::Entity(raylib::Texture* texture, raylib::Rectangle inclip, raylib::Rectangle outclip, int w, int h,int level)
	:screenwidth(w), screenhieght(h)
{
	inclip.x +=((level - 1) * 8);

	this->texture = texture;
	this->inclip = inclip;
	this->outclip = outclip;
	enabled = true;
	damagepoint = 2;
}

void Entity::Event() {
	if (!enabled)
		return;
     //Nothing
}

void Entity::Update()
{
	if (!enabled)
		return;
  
	//Nothing

}

void Entity::draw()
{
	texture->Draw(inclip, outclip);
}



void Entity::changetext(int num)
{
	if (num == 1)
	{
		this->inclip.x = 8;
		this->inclip.y = 16;
	}
	else if (num == 2)
	{
		this->inclip.x = 8;
		this->inclip.y = 24;
	}
	else if (num == 3)
	{
		this->inclip.x = 22;
		this->inclip.y = 32;
	}
}

bool Entity::iscolliding(Entity *e) {
	if (!enabled || !e->enabled)
		return false;


	return 
		outclip.x + outclip.GetSize().x >= e->outclip.x
		&& outclip.y + outclip.GetSize().y >= e->outclip.y
		&& outclip.x < e->outclip.x + e->outclip.GetSize().x
		&& outclip.y < e->outclip.y + e->outclip.GetSize().y
		;
 
}

int Entity::Recieve(int i) {

	switch (i) {
	
	case Damage:
		damagepoint--;
		if(damagepoint==0)
		enabled = false;
		break;
	}
	return (GetScreenHeight() - outclip.y);
}