#pragma once

#include <stdint.h>
#include<vector>
#include "GameObject.h"

class LevelGUI : public GameObject {
public:

    LevelGUI() : bombsNumber(0), score(0), passedTime(0), fps(0), height(0) { }

    void __fastcall SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew);
    
    void __fastcall SetHeight(uint16_t heightN) { height = heightN; };
    
    inline uint16_t GetFinishX() const { return finishX; }
    inline void SetFinishX(uint16_t finishXN) { finishX = finishXN; }

    void Draw() const override;
    //-----1.1----//
    void sendMessage(std::string _massage) {
        message.push_back(_massage);
    }
    std::string getMessage() {
        if (message.size() != 0) {
            std::string mess = message.back();
            message.pop_back();
            return mess;
        }
        else
        {  return "Ìíå íå÷åãî ñêàçàòü!";   }
    }
private:
    std::clock_t tStart = std::clock();
    uint16_t height;
    uint16_t finishX = 109;
    uint64_t passedTime, fps;
    uint16_t bombsNumber;
    int16_t score;
    //-----1.1-----//
    std::vector<std::string> message;
};

class Mediator {
private:
    LevelGUI* levelGUI;

public:
    Mediator() {};
    Mediator(LevelGUI* levelGUI) : levelGUI(levelGUI) {};
    void SendMessage1() { levelGUI->sendMassage("ÓóóóóÓÓÓÓ"); }
    void SendMessage2() { levelGUI->sendMassage("ÍèÍàÄà!"); }
    void SendMessage3() { levelGUI->sendMassage("Íå Æóææè!"); }
    void SendMessage4() { levelGUI->sendMassage("äûğ-Äûğ-Äûğ"); }
    void SendMessage5() { levelGUI->sendMassage("Ïèó-Ïèó"); }
};

