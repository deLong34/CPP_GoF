
#include <conio.h>
#include <windows.h>

#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"

using namespace std;
using namespace MyTools;
extern FileLogger logger;
class SBomberImpl;

SBomber::SBomber() : sbomberImpl(new SBomberImpl())
    //: exitFlag(false),
    //startTime(0),
    //finishTime(0),
    //deltaTime(0),
    //passedTime(0),
    //fps(0),
    //bombsNumber(10),
    //score(0)
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");
    //WriteToLog(string(__FUNCTION__) + " was invoked");

    Plane* p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
   sbomberImpl->vecDynamicObj.push_back(p);

    LevelGUI* pGUI = new LevelGUI;
    pGUI->SetParam(sbomberImpl->passedTime, sbomberImpl->fps, sbomberImpl->bombsNumber, sbomberImpl->score);
    const uint16_t maxX = GetMaxX();
    const uint16_t maxY = GetMaxY(); 
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    sbomberImpl->vecStaticObj.push_back(pGUI);

    Ground* pGr = new Ground;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    sbomberImpl->vecStaticObj.push_back(pGr);

    Tank* pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    sbomberImpl->vecStaticObj.push_back(pTank);

    pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    sbomberImpl->vecStaticObj.push_back(pTank);

    House * pHouse = new House;
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    sbomberImpl->vecStaticObj.push_back(pHouse);

    /*
    Bomb* pBomb = new Bomb;
    pBomb->SetDirection(0.3, 1);
    pBomb->SetSpeed(2);
    pBomb->SetPos(51, 5);
    pBomb->SetSize(SMALL_CRATER_SIZE);
    vecDynamicObj.push_back(pBomb);
    */
}

SBomber::~SBomber()
{
    for (size_t i = 0; i < sbomberImpl->vecDynamicObj.size(); i++)
    {
        if (sbomberImpl->vecDynamicObj[i] != nullptr)
        {
            delete sbomberImpl->vecDynamicObj[i];
        }
    }

    for (size_t i = 0; i < sbomberImpl->vecStaticObj.size(); i++)
    {
        if (sbomberImpl->vecStaticObj[i] != nullptr)
        {
            delete sbomberImpl->vecStaticObj[i];
        }
    }
    delete sbomberImpl;
}

void SBomber::MoveObjects()
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < sbomberImpl->vecDynamicObj.size(); i++)
    {
        if (sbomberImpl->vecDynamicObj[i] != nullptr)
        {
            sbomberImpl->vecDynamicObj[i]->Move(sbomberImpl->deltaTime);
        }
    }
};

void SBomber::CheckObjects()
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");

    sbomberImpl->CheckPlaneAndLevelGUI();
    sbomberImpl->CheckBombsAndGround();
};

//void SBomber::CheckPlaneAndLevelGUI()
//{
//    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX())
//    {
//        exitFlag = true;
//    }
//}

//void SBomber::CheckBombsAndGround() 
//{
//    vector<Bomb*> vecBombs = FindAllBombs();
//    Ground* pGround = FindGround();
//    const double y = pGround->GetY();
//    for (size_t i = 0; i < vecBombs.size(); i++)
//    {
//        if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
//        {
//            pGround->AddCrater(vecBombs[i]->GetX());
//            CheckDestoyableObjects(vecBombs[i]);
//            DeleteDynamicObj(vecBombs[i]);
//        }
//    }
//
//}

//void SBomber::CheckDestoyableObjects(Bomb * pBomb)
//{
//    vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
//    const double size = pBomb->GetWidth();
//    const double size_2 = size / 2;
//    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
//    {
//        const double x1 = pBomb->GetX() - size_2;
//        const double x2 = x1 + size;
//        if (vecDestoyableObjects[i]->isInside(x1, x2))
//        {
//            score += vecDestoyableObjects[i]->GetScore();
//            DeleteStaticObj(vecDestoyableObjects[i]);
//        }
//    }
//}

//void SBomber::DeleteDynamicObj(DynamicObject* pObj)
//{
//    auto it = vecDynamicObj.begin();
//    for (; it != vecDynamicObj.end(); it++)
//    {
//        if (*it == pObj)
//        {
//            vecDynamicObj.erase(it);
//            break;
//        }
//    }
//}

//void SBomber::DeleteStaticObj(GameObject* pObj)
//{
//    auto it = vecStaticObj.begin();
//    for (; it != vecStaticObj.end(); it++)
//    {
//        if (*it == pObj)
//        {
//            vecStaticObj.erase(it);
//            break;
//        }
//    }
//}

//vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const
//{
//    vector<DestroyableGroundObject*> vec;
//    Tank* pTank;
//    House* pHouse;
//    for (size_t i = 0; i < vecStaticObj.size(); i++)
//    {
//        pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
//        if (pTank != nullptr)
//        {
//            vec.push_back(pTank);
//            continue;
//        }
//
//        pHouse = dynamic_cast<House*>(vecStaticObj[i]);
//        if (pHouse != nullptr)
//        {
//            vec.push_back(pHouse);
//            continue;
//        }
//    }
//
//    return vec;
//}

//Ground* SBomber::FindGround() const
//{
//    Ground* pGround;
//
//    for (size_t i = 0; i < vecStaticObj.size(); i++)
//    {
//        pGround = dynamic_cast<Ground *>(vecStaticObj[i]);
//        if (pGround != nullptr)
//        {
//            return pGround;
//        }
//    }
//
//    return nullptr;
//}

//vector<Bomb*> SBomber::FindAllBombs() const
//{
//    vector<Bomb*> vecBombs;
//
//    for (size_t i = 0; i < vecDynamicObj.size(); i++)
//    {
//        Bomb* pBomb = dynamic_cast<Bomb*>(vecDynamicObj[i]);
//        if (pBomb != nullptr)
//        {
//            vecBombs.push_back(pBomb);
//        }
//    }
//
//    return vecBombs;
//}

//Plane* SBomber::FindPlane() const
//{
//    for (size_t i = 0; i < vecDynamicObj.size(); i++)
//    {
//        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
//        if (p != nullptr)
//        {
//            return p;
//        }
//    }
//
//    return nullptr;
//}

//LevelGUI* SBomber::FindLevelGUI() const
//{
//    for (size_t i = 0; i < vecStaticObj.size(); i++)
//    {
//        LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
//        if (p != nullptr)
//        {
//            return p;
//        }
//    }
//
//    return nullptr;
//}

void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224)
    {
        c = _getch();
    }

    logger.WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {

    case 27: // esc
        sbomberImpl->exitFlag = true;
        break;

    case 72: // up
        sbomberImpl->FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
        sbomberImpl->FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
        sbomberImpl->DropBomb();
        break;

    case 'B':
        sbomberImpl->DropBomb();
        break;

    default:
        break;
    }
}

void SBomber::DrawFrame()
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < sbomberImpl->vecDynamicObj.size(); i++)
    {
        if (sbomberImpl->vecDynamicObj[i] != nullptr)
        {
            sbomberImpl->vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < sbomberImpl->vecStaticObj.size(); i++)
    {
        if (sbomberImpl->vecStaticObj[i] != nullptr)
        {
            sbomberImpl->vecStaticObj[i]->Draw();
        }
    }

    GotoXY(0, 0);
    sbomberImpl->fps++;

    sbomberImpl->FindLevelGUI()->SetParam(sbomberImpl->passedTime, sbomberImpl->fps, sbomberImpl->bombsNumber, sbomberImpl->score);
}

void SBomber::TimeStart()
{
    logger.WriteToLog(string(__FUNCTION__) + " was invoked");
    sbomberImpl->startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    sbomberImpl->finishTime = GetTickCount64();
    sbomberImpl->deltaTime = uint16_t(sbomberImpl->finishTime - sbomberImpl->startTime);
    sbomberImpl->passedTime += sbomberImpl->deltaTime;

    logger.WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)sbomberImpl->deltaTime);
}

//void SBomber::DropBomb()
//{
//    if (bombsNumber > 0)
//    {
//        logger.WriteToLog(string(__FUNCTION__) + " was invoked");
//
//        Plane* pPlane = FindPlane();
//        double x = pPlane->GetX() + 4;
//        double y = pPlane->GetY() + 2;
//
//        Bomb* pBomb = new Bomb;
//        pBomb->SetDirection(0.3, 1);
//        pBomb->SetSpeed(2);
//        pBomb->SetPos(x, y);
//        pBomb->SetWidth(SMALL_CRATER_SIZE);
//
//        vecDynamicObj.push_back(pBomb);
//        bombsNumber--;
//        score -= Bomb::BombCost;
//    }
//}
