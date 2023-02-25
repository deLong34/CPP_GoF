#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class Tank : public DestroyableGroundObject
{
public:

	//-----1.1/2-----//
	Tank() {};
	Tank (const Tank& other) {
		x = other.x;
		y = other.y;
		width = other.width;
	}
	Tank* clone() override {
		return new Tank(*this);
	}
	//-----1.1/2-----//

	static const uint16_t BombCost = 10; // стоимость бомбы в очках


	

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;




private:

	const uint16_t score = 30;
};

