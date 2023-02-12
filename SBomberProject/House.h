 #pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
public:
	bool __fastcall isInside(double x1, double x2) const override;
	inline uint16_t GetScore() const override { return score; }
	void Draw() const override;

private:
	char look[7][14];
	const uint16_t score = 40;
};


//HouseBuilder///////////////////////////
class HouseBuilder  {
protected:
	House* house = nullptr;
	char look[7][14];
public:
	virtual void createWall() {};
	virtual void createRoof() {};
	virtual void createPipe() {};
	virtual void createWindow() {};

	virtual void createHouse() {};
	virtual ~HouseBuilder() { delete house; }

	House* house() { return house; }
	
};

//HouseBuilderA////Первый тип дома .............
class HouseBuilderA : public HouseBuilder {
	void createHouse() override {
		house = new House;
	};
	void createWall() override{
		for (size_t i = 0; i < 12; i++) { look[i][0] = '#';	}
		for (size_t i = 0; i < 12; i++)	{ look[i][3] = '#'; }
		for (size_t j = 1; j < 3; j++)	{ look[0][j] = '#';	}
		for (size_t j = 1; j < 3; j++)	{ look[11][j] = '#'; }
	};
	void createRoof() override {
	look[1][4] = '#'; look[2][4] = '#'; look[3][5] = '#'; look[4][5] = '#'; look[5][6] = '#'; look[6][6] = '#';
	look[7][5] = '#'; look[8][5] = '#'; look[9][4] = '#'; look[10][4] = '#';
	};
	void createPipe() override {
		look[1][5] = 'H'; look[1][6] = 'H'; look[2][5] = 'H'; look[2][6] = 'H';
	};
	void createWindow() override {
		look[3][1] = 'O'; look[4][1] = 'O'; look[3][2] = 'O'; look[4][2] = 'O';
	};
};

//HouseBuilderB ////  Второй тип дома
class HouseBuilderB : public HouseBuilder {
	void createHouse() override {
		house = new House;
	};
	void createWall() override {
		for (size_t i = 0; i < 12; i++) { look[i][0] = '#'; }
		for (size_t i = 0; i < 12; i++) { look[i][3] = '#'; }
		for (size_t j = 1; j < 3; j++) { look[0][j] = '#'; }
		for (size_t j = 1; j < 3; j++) { look[11][j] = '#'; }
	};
	void createRoof() override {
		look[1][4] = '^'; look[2][4] = '^'; look[3][5] = '^'; look[4][5] = '^'; look[5][6] = '^'; look[6][6] = '^';
		look[7][5] = '^'; look[8][5] = '^'; look[9][4] = '^'; look[10][4] = '^';
	};
	//void createPipe() override {
	//	look[1][5] = 'H'; look[1][6] = 'H'; look[2][5] = 'H'; look[2][6] = 'H';
	//};
	void createWindow() override {
		look[3][1] = 'W'; look[4][1] = 'W'; look[3][2] = 'W'; look[4][2] = 'W';
		look[3][3] = 'W'; look[4][3] = 'W';
	};
};

//
class HouseDirector {
public:
	House* construct(HouseBuilder& builder) {
		builder.createHouse(); //создаем объект дома
		builder.createPipe(); //создаем элементы дома (заполняем массив)
		builder.createRoof();
		builder.createWall();
		builder.createWindow();
	}
};