#pragma once

#include "DynamicObject.h"

class Plane : public DynamicObject {
public:
    //
    inline void SetPos(double nx, double ny) { x = nx; y = ny; }
    inline double GetY() const { return y; }
    inline double GetX() const { return x; }
    inline void SetWidth(uint16_t widthN) { width = widthN; }
    inline uint16_t GetWidth() const { return width; }
    //
    void Draw() const override;

    inline void ChangePlaneY(double dy) { yDirection += dy; }

private:

};

