#pragma once

#include "DynamicObject.h"
#include <vector>
#include <algorithm>
#include "DestroyableGroundObject.h"

class Bomb : public DynamicObject
{
public:
	static const uint16_t BombCost = 10; // стоимость бомбы в очках
	void Draw() const override;
	//
	void __fastcall Accept(const IVisitor& v)
	{
		v.log(*this);
	}
////-----2-----////////////////////
	void AddObserver(DestroyableGroundObject* DestroyableGroundObject) {
		DestroyableGroundObjects.push_back(DestroyableGroundObject);
	}

	void DelObserver(DestroyableGroundObject* DestroyableGroundObject) {
		auto it = std::find(DestroyableGroundObjects.begin(), DestroyableGroundObjects.end(), DestroyableGroundObject);
		DestroyableGroundObjects.erase(it);
	}
	€\
	DestroyableGroundObject* CheckDestoyableObjects(Bomb* pBomb)
	{
		vector<DestroyableGroundObject*> vecDestoyableObjects = SBomber::FindDestoyableGroundObjects();
		const double size = pBomb->GetWidth();
		const double size_2 = size / 2;
		for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
		{
			const double x1 = pBomb->GetX() - size_2;
			const double x2 = x1 + size;
			if (vecDestoyableObjects[i]->isInside(x1, x2))
			{
				//score += vecDestoyableObjects[i]->GetScore();
				//DeleteStaticObj(vecDestoyableObjects[i]);
				return vecDestoyableObjects[i];
			}
			else return nullptr;
		}
	}
	
private:
	std::vector<DestroyableGroundObject*> DestroyableGroundObjects;
};

