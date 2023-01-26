#pragma once

#include <stdint.h>
#include <string>
using namespace std;

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
    class FileLoggerSingletone
    {
    private:
        FileLoggerSingletone() {}
        FileLoggerSingletone(FileLoggerSingletone& other) = delete;
        FileLoggerSingletone& operator =(const FileLoggerSingletone&) = delete;
        static FileLoggerSingletone* theInstance;
    public:
        static FileLoggerSingletone* getInstance()
        {
            if (theInstance == nullptr) {
                theInstance = new FileLoggerSingletone();
            }
            return theInstance;
        }
        void __fastcall OpenLogFile(const string& FN);
        void CloseLogFile();
        string GetCurDateTime();
        void __fastcall WriteToLog(const string& str);
        void __fastcall WriteToLog(const string& str, int n);
        void __fastcall WriteToLog(const string& str, double d);
    };
	//=============================================================================================
    //Задание 2*
    class ILogger
    {
        public:
        virtual void __fastcall WriteToLog(const string& str) = 0;
        virtual void __fastcall WriteToLog(const string& str, int n) = 0;
        virtual void __fastcall WriteToLog(const string& str, double d) = 0;
    };

    class LoggerSigletone : ILogger
    {
    private:
        FileLoggerSingletone* FLS;
        int cnt = 1;
        bool CheckAccess() const {
            return true;
        }
        void LogChange();

    public:
        LoggerSigletone(FileLoggerSingletone* FLS) : FLS(FLS) {}
        virtual void __fastcall WriteToLog(const string& str) override {
            if (CheckAccess())
            {
                LogChange();
                FLS->WriteToLog(str);
            }
        }
        virtual void __fastcall WriteToLog(const string& str, int n) override {
            if (CheckAccess())
            {
                LogChange();
                FLS->WriteToLog(str, n);
            }
        }
        virtual void __fastcall WriteToLog(const string& str, double d) override {
            if (CheckAccess())
            {
                LogChange();
                FLS->WriteToLog(str, d);
            }
        }
        FileLoggerSingletone* getInstance() {
            return  FLS->getInstance();
        }
    }; 
};