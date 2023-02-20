#pragma once

#include <stdint.h>
#include <string>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <time.h> 

#include <iostream>
#include <chrono>

namespace MyTools {

    // Палитра цветов от 0 до 15
    enum ConsoleColor
    {
        CC_Black = 0,
        CC_Blue,
        CC_Green,
        CC_Cyan,
        CC_Red,
        CC_Magenta,
        CC_Brown,
        CC_LightGray,
        CC_DarkGray,
        CC_LightBlue,
        CC_LightGreen,
        CC_LightCyan,
        CC_LightRed,
        CC_LightMagenta,
        CC_Yellow,
        CC_White
    };

	//=============================================================================================

	void ClrScr();

	void __fastcall GotoXY(double x, double y);

	uint16_t GetMaxX();

	uint16_t GetMaxY();

    void SetColor(ConsoleColor color);

	//=============================================================================================

	//void __fastcall OpenLogFile(const std::string& FN);

	//void CloseLogFile();

	//void __fastcall WriteToLog(const std::string& str);

	//void __fastcall WriteToLog(const std::string& str, int n);

	//void __fastcall WriteToLog(const std::string& str, double d);

	//=============================================================================================
    class FileLogger {
    private:
        ofstream logOut;
    public:
        FileLogger(const string& FN) {
            logOut.open(FN, ios_base::out);
        }

        ~FileLogger() {
            if (logOut.is_open())
            {
                logOut.close();
            }
        }

        string GetCurDateTime() {
            auto cur = std::chrono::system_clock::now();
            time_t time = std::chrono::system_clock::to_time_t(cur);
            char buf[64] = { 0 };
            ctime_s(buf, 64, &time);
            buf[strlen(buf) - 1] = '\0';
            return string(buf);
        }

        void __fastcall WriteToLog(const string& str) {
            if (logOut.is_open())
            {
                logOut << GetCurDateTime() << " - " << str << endl;
            }
        }

        void __fastcall WriteToLog(const string& str, int n) {
            if (logOut.is_open())
            {
                logOut << GetCurDateTime() << " - " << str << n << endl;
            }
        }

        void __fastcall WriteToLog(const string& str, double d) {
            if (logOut.is_open())
            {
                logOut << GetCurDateTime() << " - " << str << d << endl;
            }
        }
    };
};