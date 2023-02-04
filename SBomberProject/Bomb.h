#pragma once

#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10; // стоимость бомбы в очках

	void Draw() const override;

private:

};

//-----2-----/////////////
class BombDecorator : public DynamicObject
{
private:
	DynamicObject* bomb;
public:
	BombDecorator(DynamicObject* bomb) : bomb(bomb) {}
	void Draw() const override;
	void Move(uint16_t time) override; 
	
};


