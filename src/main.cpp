#include <iostream>
#include <string>
#include "menu.h"
#include "Interface.h"

using namespace std;
int main()
{
	//menu();
	//RoadNetwork* test = new RoadNetwork();
	//test->readOSM();
	//test->convertToGV();
	Interface* test = new Interface();
	test->roadsBlocked();
	return 0;
}
