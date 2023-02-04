
#include <iostream>

#include "Bomb.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void Bomb::Draw() const
{
    MyTools::SetColor(CC_LightMagenta);
    GotoXY(x, y);
    cout << "*";
}

void BombDecorator::Draw() const {
	bomb->Draw();
	MyTools::SetColor(CC_Green);
	GotoXY(x + 1, y);
	cout << ">";
	GotoXY(x - 1, y);
	cout << "<";
	MyTools::SetColor(CC_LightBlue);
	GotoXY(x , y - 1 );
	cout << "Y";
};
void BombDecorator::Move(uint16_t time) { 
	bomb->SetSpeed(3);
	bomb->Move(time);
	/*x += xDirction * speed * time * 0.001; 
	y += yDirection * speed * time * 0.001;*/
};


