#pragma once

#include <vector>
#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "MyTools.h"
#include "SBomber.h"
#include "House.h"

using namespace std;
using namespace MyTools;
extern FileLogger logger;

class SBomberImpl {
private:
public:
    SBomberImpl() : exitFlag(false), startTime(0), finishTime(0), deltaTime(0), passedTime(0), fps(0), bombsNumber(10),
        score(0) {}
    void CheckPlaneAndLevelGUI(); //
    void CheckBombsAndGround();//
    void __fastcall CheckDestoyableObjects(Bomb* pBomb);//
    void __fastcall DeleteDynamicObj(DynamicObject* pBomb);//
    void __fastcall DeleteStaticObj(GameObject* pObj);//
    Ground* FindGround() const;//
    Plane* FindPlane() const;//
    LevelGUI* FindLevelGUI() const;//
    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    bool exitFlag;
    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;//
    std::vector<Bomb*> FindAllBombs() const;//
};

void SBomberImpl::CheckPlaneAndLevelGUI()
{
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX())
    {
        exitFlag = true;
    }
}

void SBomberImpl::CheckBombsAndGround()
{
    vector<Bomb*> vecBombs = FindAllBombs();
    Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
    {
        if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);
            DeleteDynamicObj(vecBombs[i]);
        }
    }

}

void SBomberImpl::CheckDestoyableObjects(Bomb* pBomb)
{
    vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
    {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2))
        {
            score += vecDestoyableObjects[i]->GetScore();
            DeleteStaticObj(vecDestoyableObjects[i]);
        }
    }
}

void SBomberImpl::DeleteDynamicObj(DynamicObject* pObj)
{
    auto it = vecDynamicObj.begin();
    for (; it != vecDynamicObj.end(); it++)
    {
        if (*it == pObj)
        {
            vecDynamicObj.erase(it);
            break;
        }
    }
}

void SBomberImpl::DeleteStaticObj(GameObject* pObj)
{
    auto it = vecStaticObj.begin();
    for (; it != vecStaticObj.end(); it++)
    {
        if (*it == pObj)
        {
            vecStaticObj.erase(it);
            break;
        }
    }
}

vector<DestroyableGroundObject*> SBomberImpl::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    House* pHouse;
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
        if (pTank != nullptr)
        {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House*>(vecStaticObj[i]);
        if (pHouse != nullptr)
        {
            vec.push_back(pHouse);
            continue;
        }
    }

    return vec;
}

Ground* SBomberImpl::FindGround() const
{
    Ground* pGround;

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pGround = dynamic_cast<Ground*>(vecStaticObj[i]);
        if (pGround != nullptr)
        {
            return pGround;
        }
    }

    return nullptr;
}

vector<Bomb*> SBomberImpl::FindAllBombs() const
{
    vector<Bomb*> vecBombs;

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Bomb* pBomb = dynamic_cast<Bomb*>(vecDynamicObj[i]);
        if (pBomb != nullptr)
        {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}

Plane* SBomberImpl::FindPlane() const
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

LevelGUI* SBomberImpl::FindLevelGUI() const
{
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

//void SBomber::ProcessKBHit()
//{
//    int c = _getch();
//
//    if (c == 224)
//    {
//        c = _getch();
//    }
//
//    logger.WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);
//
//    switch (c) {
//
//    case 27: // esc
//        exitFlag = true;
//        break;
//
//    case 72: // up
//        FindPlane()->ChangePlaneY(-0.25);
//        break;
//
//    case 80: // down
//        FindPlane()->ChangePlaneY(0.25);
//        break;
//
//    case 'b':
//        DropBomb();
//        break;
//
//    case 'B':
//        DropBomb();
//        break;
//
//    default:
//        break;
//    }
//}
//
//void SBomber::DrawFrame()
//{
//    logger.WriteToLog(string(__FUNCTION__) + " was invoked");
//
//    for (size_t i = 0; i < vecDynamicObj.size(); i++)
//    {
//        if (vecDynamicObj[i] != nullptr)
//        {
//            vecDynamicObj[i]->Draw();
//        }
//    }
//
//    for (size_t i = 0; i < vecStaticObj.size(); i++)
//    {
//        if (vecStaticObj[i] != nullptr)
//        {
//            vecStaticObj[i]->Draw();
//        }
//    }
//
//    GotoXY(0, 0);
//    fps++;
//
//    FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
//}
//
//void SBomber::TimeStart()
//{
//    logger.WriteToLog(string(__FUNCTION__) + " was invoked");
//    startTime = GetTickCount64();
//}
//
//void SBomber::TimeFinish()
//{
//    finishTime = GetTickCount64();
//    deltaTime = uint16_t(finishTime - startTime);
//    passedTime += deltaTime;
//
//    logger.WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
//}

void SBomberImpl::DropBomb()
{
    if (bombsNumber > 0)
    {
        logger.WriteToLog(string(__FUNCTION__) + " was invoked");

        Plane* pPlane = FindPlane();
        double x = pPlane->GetX() + 4;
        double y = pPlane->GetY() + 2;

        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(2);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(SMALL_CRATER_SIZE);

        vecDynamicObj.push_back(pBomb);
        bombsNumber--;
        score -= Bomb::BombCost;
    }

}