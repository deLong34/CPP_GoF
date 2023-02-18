
#include <iostream>

#include "Tank.h"
#include "MyTools.h"

#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace MyTools;

bool Tank::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}

void Tank::Draw() const
{
	MyTools::SetColor(CC_Brown);
	GotoXY(x, y - 3);
	cout << "    #####";
	GotoXY(x-2, y - 2);
	cout << "#######   #";
	GotoXY(x, y - 1);
	cout << "    #####";
	GotoXY(x,y);
	cout << " ###########";
	//---1.1---//
	srand(time(NULL));
	int num = rand() % 5;
	if (num == 1) { mediator.SendMessage1(); }
	if (num == 2) { mediator.SendMessage2(); }
	if (num == 3) { mediator.SendMessage3(); }
	if (num == 4) { mediator.SendMessage4(); }
	else { mediator.SendMessage5(); }
}