#pragma once

class GameObject {
public:

    GameObject() : x(0.0), y(0.0), width(0) { }

    virtual void Draw() const = 0;

    virtual inline void SetPos(double nx, double ny) = 0;

    virtual inline double GetY() const = 0;
    virtual inline double GetX() const = 0;

    virtual inline void SetWidth(uint16_t widthN) = 0;
    virtual inline uint16_t GetWidth() const = 0;
    inline double GetYi() const { return y; }

protected:

    double x, y;
    uint16_t width;
};