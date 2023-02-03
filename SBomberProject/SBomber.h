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

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();
    //-----1-----///
    void __fastcall DeleteDynamicObj(DynamicObject* pBomb);
    void __fastcall DeleteStaticObj(GameObject* pObj);
    void DropBomb();
    std::vector<Bomb*> FindAllBombs() const;

private:

    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Bomb* pBomb);

   // void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
   //  void __fastcall DeleteStaticObj(GameObject* pObj);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
   // std::vector<Bomb*> FindAllBombs() const;

   // void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};

// void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
class Command
{
protected:
    SBomber* sbomber;
public:
    virtual void __fastcall Execute() = 0;   
};

//
class DeleteDynamicObjCommand : public Command
{
private:
    DynamicObject* pBomb;
    DynamicObject& vecDynamicObj;
public:
    DeleteDynamicObjCommand(DynamicObject* pObj, DynamicObject& vecDynamicObj) : pBomb(pObj), vecDynamicObj(vecDynamicObj) {};
    void Execute () override{
        sbomber->DeleteDynamicObj(pBomb);
   }
};

//
class DeleteStaticObjCommand : public Command
{
private:
    GameObject* pObj;
    GameObject& vecStaticObj;
public:
    DeleteStaticObjCommand(GameObject* pObj, GameObject& vecStaticObj) : pObj(pObj), vecStaticObj(vecStaticObj) {};
    void Execute() override {
        sbomber->DeleteStaticObj(pObj);
    }
};

//
class DropBombCommand : public Command
{
private:
    const Plane* plane;
    DynamicObject& vecDynamicObj;
    //const Bomb& bomb = SBomber::FindAllBombs();
    const Bomb& bomb = SBomber::FindAllBombs();
public:
    DropBombCommand(Plane* plane, DynamicObject& vecDynamicObj, const Bomb& bomb) :plane(plane), vecDynamicObj(vecDynamicObj), bomb(bomb) {};
    void Execute() override {
        sbomber->DropBomb();
    }
};

//
class Invocer
{
private:
    SBomber bomber;
    Command* pCommand;
public:
    Invocer(): pCommand(nullptr){}
    Invocer(Command* pCommand) : pCommand(pCommand) {}
    virtual ~Invocer() {}

    void DeleteDynamicObj(DynamicObject* pObj, DynamicObject& vecDynamicObj) {
        pCommand = new DeleteDynamicObjCommand(pObj, vecDynamicObj);
        pCommand->Execute();
    }

    void DeleteStaticObj(GameObject* pObj, GameObject& vecStaticObj) {
        pCommand = new DeleteStaticObjCommand(pObj, vecStaticObj);
        pCommand->Execute();
    }

    void DropBomb(Plane* plane, DynamicObject& vecDynamicObj, const Bomb& bomb) {
        pCommand = new  DropBombCommand(plane, vecDynamicObj, bomb);
        pCommand->Execute();
    }

};

