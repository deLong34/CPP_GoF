#pragma once
#include <conio.h>
#include <windows.h>
#include <stdint.h>
#include <time.h> 

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <stdint.h>

#include "GameObject.h"

class DynamicObject : public GameObject 
{
public:

    DynamicObject() : speed(0.0), xDirction(0.0), yDirection(0) { }

    inline void SetSpeed(double sp) { speed = sp; }
    inline void SetDirection(double dx, double dy) { xDirction = dx; yDirection = dy; }
  
    virtual void Move(uint16_t time) { x += xDirction * speed * time * 0.001; y += yDirection * speed * time * 0.001; };
    //-----1-----//
    double GetSpeed() { return speed; }
    pair <double, double> GetDirection() {
        return std::make_pair(xDirction, yDirection);
    }
    //
protected:

    double speed;
    double xDirction, yDirection;

};

class  IVisitor
{
public:
    virtual void log(Bomb* b) = 0;
    virtual void log(Plane* p) = 0;
};

class LogVisitor : public IVisitor {
public:
    void log(Bomb* b) override {
        MyTools::WriteToLog("Bomb position = ", b->GetDirection(), b->GetSpeed());
    }
    void log(Plane* p) override {
        MyTools::WriteToLog("Plane position = ", p->GetDirection(), p->GetSpeed());
    }

private:
    ofstream logOut;
};
 