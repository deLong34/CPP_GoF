#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"

class SBomber
{
public:
    CollisionDetector* collisionDetector;

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();
    ///
    void setExitFlag() { exitFlag = true; }
    void scoreChange(DestroyableGroundObject* obj) { score += obj->GetScore(); }
    Plane* FindPlane() const;
    LevelGUI* FindLevelGUI() const;
    Ground* FindGround() const;
    std::vector<Bomb*> FindAllBombs() const;
    void __fastcall DeleteDynamicObj(DynamicObject* pBomb);
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    void __fastcall DeleteStaticObj(GameObject* pObj);
    
protected:
   
    
private:

    //void CheckPlaneAndLevelGUI();
    //void CheckBombsAndGround();
    //void __fastcall CheckDestoyableObjects(Bomb* pBomb);

    //void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    //void __fastcall DeleteStaticObj(GameObject* pObj);

    //Ground * FindGround() const;
    //Plane * FindPlane() const;
    //LevelGUI * FindLevelGUI() const;
   // std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    //std::vector<Bomb*> FindAllBombs() const;

    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};

class CollisionDetector {
protected:
    SBomber* sbomber;
public:
    CollisionDetector(SBomber* sbomber) : sbomber(sbomber) {}
   
    void CheckPlaneAndLevelGUI()
    {
        if (sbomber->FindPlane()->GetX() > sbomber->FindLevelGUI()->GetFinishX())
        {
           sbomber->setExitFlag();
        }
    }

    void CheckBombsAndGround()
    {
        vector<Bomb*> vecBombs = sbomber->FindAllBombs();
        Ground* pGround = sbomber->FindGround();
        const double y = pGround->GetY();
        for (size_t i = 0; i < vecBombs.size(); i++)
        {
            if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
            {
                pGround->AddCrater(vecBombs[i]->GetX());
                CheckDestoyableObjects(vecBombs[i]);
               sbomber->DeleteDynamicObj(vecBombs[i]);
            }
        }

    }

    void CheckDestoyableObjects(Bomb* pBomb)
    {
        vector<DestroyableGroundObject*> vecDestoyableObjects = sbomber->FindDestoyableGroundObjects();
        const double size = pBomb->GetWidth();
        const double size_2 = size / 2;
        for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
        {
            const double x1 = pBomb->GetX() - size_2;
            const double x2 = x1 + size;
            if (vecDestoyableObjects[i]->isInside(x1, x2))
            {
               sbomber->scoreChange(vecDestoyableObjects[i]);
               sbomber->DeleteStaticObj(vecDestoyableObjects[i]);
            }
        }
    }
};