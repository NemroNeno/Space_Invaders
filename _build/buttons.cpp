#include "buttons.h"

buttons::buttons() :button_height(100), button_width(250), button_x_coor(0), button_y_coor(0), usual(WHITE), hover(GRAY), clickon(RED), clicked(0), state(None)
{
    rect = { button_x_coor, button_y_coor, button_width, button_height };
}

buttons::~buttons()
{

}

void buttons::button_coordinates_setter(int x_coor, int y_coor)
{
    this->button_x_coor = x_coor;
    this->rect.SetX((float)x_coor);
    this->button_y_coor = y_coor;
    this->rect.SetY((float)y_coor);
}

void buttons::Draw(int i)
{
    DrawRectangleRec(rect, state_colour);
    if (i == 0)
    {
        DrawText("New_Game", this->button_x_coor + 10, this->button_y_coor + 40, 30
            , BLUE);

    }
    else if (i == 1)
    {
        DrawText("LeaderBoard", this->button_x_coor + 10, this->button_y_coor + 40, 30
            , BLUE);

    }
    else if (i == 2)
    {
        DrawText("Accessories", this->button_x_coor + 10, this->button_y_coor + 40, 30
            , BLUE);

    }
    else if (i == 3)
    {
        DrawText("Quit", this->button_x_coor + 10, this->button_y_coor + 40, 30
            , BLUE);

    }
    else if (i == 6)
    {
        DrawText("Ship1", this->button_x_coor + 10, this->button_y_coor + 40, 30
            , BLUE);

    }
    else if (i == 7)
    {
        DrawText("Ship2", this->button_x_coor + 10, this->button_y_coor + 40, 30
            , BLUE);

    }
    else if (i == 8)
    {
        DrawText("Ship3", this->button_x_coor + 10, this->button_y_coor + 40, 30
            , BLUE);


    }

}


int buttons::Update() {
    switch (this->state) {
    case None:
        this->state_colour = usual;
        return 0;
        break;
    case Hovered:
        this->state_colour = this->hover;
        return 0;
        break;
    case Clicked:
        this->state_colour = this->clickon;
        this->clicked = true;
        return 1;
        break;
    }
}

void buttons::updateButtonState(Vector2 mousePos) {
    if (CheckCollisionPointRec(GetMousePosition(), this->rect)) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            this->state = Clicked;

        }
        else {
            this->state = Hovered;
        }
    }
    else {
        this->state = None;
    }
}




