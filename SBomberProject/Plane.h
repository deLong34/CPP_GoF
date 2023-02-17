#pragma once

#include "DynamicObject.h"

class Plane : public DynamicObject {
public:

    void Draw() const override;

    inline void ChangePlaneY(double dy) { yDirection += dy; }

    //
    void __fastcall Accept(const IVisitor& v)
    {
        v.log(*this);
    }


private:

};

