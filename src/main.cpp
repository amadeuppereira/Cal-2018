#include <iostream>
#include <string>
#include "RoadNetwork.h"
#include "menu.h"

using namespace std;
int main()
{
	//menu();
	RoadNetwork* test = new RoadNetwork();
	test->readOSM();
	return 0;
}
