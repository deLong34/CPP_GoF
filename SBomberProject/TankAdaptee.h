#pragma once
#include <iostream>
#include "MyTools.h"
#include "DestroyableGroundObject.h"

using namespace MyTools;
using namespace std;

class TankAdaptee {
public:

    TankAdaptee() : x(0.0), y(0.0), width(0) { }

    void Paint();
    bool __fastcall isInRange(double x1, double x2) const;

    inline uint16_t GetScore() const { return score; }

    inline void SetPos(double nx, double ny) { x = nx; y = ny; }
    inline double GetY() const { return y; }
    inline double GetX() const { return x; }
    inline void SetWidth(uint16_t widthN) { width = widthN; }
    inline uint16_t GetWidth() const { return width; }

protected:

    double x, y;
    uint16_t width;
    const uint16_t score = 30;
};

void TankAdaptee::Paint() {
    MyTools::SetColor(CC_Brown);
    GotoXY(x, y - 3);
    cout << "    #####";
    GotoXY(x - 2, y - 2);
    cout << "#######   #";
    GotoXY(x, y - 1);
    cout << "    #####";
    GotoXY(x, y);
    cout << " ###########";
}
bool __fastcall TankAdaptee::isInRange(double x1, double x2) const {
    const double XBeg = x + 2;
    const double XEnd = x + width - 1;
    if (x1 < XBeg && x2 > XEnd) {
        return true; }
    if (x1 > XBeg && x1 < XEnd) {
        return true; }
    if (x2 > XBeg && x2 < XEnd) {
        return true; }
    return false;
}

//----2-----//////
class TankAdapter : public DestroyableGroundObject {
private:
    TankAdaptee* tank;
public:
    inline void SetPos(double nx, double ny) override { tank->SetPos(nx, ny); }
    inline double GetY() const override { tank->GetY(); }
    inline double GetX() const override { tank->GetX(); }
    inline void SetWidth(uint16_t widthN) override { tank->SetWidth(width); }
    inline uint16_t GetWidth() const override { tank->GetWidth(); }

    void Draw() const override {
        tank->Paint();
    }

    bool __fastcall isInside(double x1, double x2) const override {
        tank->isInRange(x1, x2);
    }
    inline uint16_t GetScore() const { tank->GetScore(); }
};