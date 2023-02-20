#pragma once

#include <vector>
#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "SBomberImpl.h"

class SBomber
{
private:
    //-----7.2-----//
   
    SBomberImpl* sbomberImpl;
public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return sbomberImpl->exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

private:
    //-----7.2-----//
    class SBomberImpl;
    SBomberImpl* sbomberImpl;
    //--------------------
    //void CheckPlaneAndLevelGUI();
    //void CheckBombsAndGround();
    //void __fastcall CheckDestoyableObjects(Bomb* pBomb);
    //void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    //void __fastcall DeleteStaticObj(GameObject* pObj);
    //Ground * FindGround() const;
    //Plane * FindPlane() const;
    //LevelGUI * FindLevelGUI() const;
    //std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    //std::vector<Bomb*> FindAllBombs() const;
    //void DropBomb();
    //std::vector<DynamicObject*> vecDynamicObj;
    //std::vector<GameObject*> vecStaticObj;
    //
    //bool exitFlag;

    //uint64_t startTime, finishTime, passedTime;
    //uint16_t bombsNumber, deltaTime, fps;
    //int16_t score;
};