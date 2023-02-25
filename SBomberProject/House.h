#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
public:
	//-----1.1/2-----//
	House() {};
	House(const House& other) {
		x = other.x;
		y = other.y;
		width = other.width;
	}
	House* clone() override {
		return new House(*this);
	}
	//-----1.1/2-----//

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;

private:

	const uint16_t score = 40;
};

