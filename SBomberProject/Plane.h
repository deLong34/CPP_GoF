#pragma once

#include "DynamicObject.h"

class Plane : public DynamicObject {
public:

    void Draw() const override;
    inline void ChangePlaneY(double dy) { yDirection += dy; }

    virtual void DrawBody() const;
    virtual void DrawWings() const;
    virtual void DrawTail() const;
private:

};

class ColorPlane : public Plane {
public:
    void DrawBody() const override {
        MyTools::SetColor(CC_Cyan);
        GotoXY(x, y);
        cout << "==========>";
    };
    void DrawWings() const override {
        MyTools::SetColor(CC_Blue);
        GotoXY(x + 3, y - 1);
        cout << "\\\\\\\\";
        MyTools::SetColor(CC_Green);
        GotoXY(x + 3, y + 1);
        cout << "////";
    };
    void DrawTail() const override {
        MyTools::SetColor(CC_LightCyan);
        GotoXY(x - 2, y - 1);
        cout << "===";
    };
};

class BigPlane : public Plane
{
public:
    void DrawBody() const override {
        GotoXY(x, y);
        cout << "=============>";
    };
    void DrawWings() const override {
        GotoXY(x + 3, y - 1);
        cout << "\\\\\\\\\\";
        GotoXY(x + 3, y + 1);
        cout << "//////";
    };
    void DrawTail() const override {
        GotoXY(x - 2, y - 1);
        cout << "=====";
    };
};

