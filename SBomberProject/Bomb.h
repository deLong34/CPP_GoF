#pragma once

#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:
	//-----1.1/1-----//
	Bomb() {};
	Bomb(const Bomb& other) {
		speed = other.speed;
		xDirction = other.xDirction + 2;
		yDirection = other.yDirection;
	}

	static const uint16_t BombCost = 10; // стоимость бомбы в очках

	void Draw() const override;

	Bomb* clone() override {
		return new Bomb(*this);
	}

private:

};

