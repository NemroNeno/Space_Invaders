#pragma once
#include<iostream>
//#include <Windows.h>
#include <raylib-cpp.hpp>

class buttons
{
private:
	float button_height;
	float button_width;
	float button_x_coor;
	float button_y_coor;
	raylib::Rectangle rect;
	raylib::Color state_colour;
	raylib::Color usual;
	raylib::Color hover;
	raylib::Color clickon;
	bool clicked;
	enum ButtonState {
		None,
		Hovered,
		Clicked
	}state;
public:
	buttons();
	~buttons();
	
	void button_coordinates_setter(int x, int y);

	void updateButtonState(Vector2);

	int Update();
	void Draw(int );
	//void draw_text(int );

};



