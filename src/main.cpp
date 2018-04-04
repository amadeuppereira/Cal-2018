#include <iostream>
#include <string>
#include "menu.h"
#include "Interface.h"
#include "Utils.h"

using namespace std;
int main()
{
	//menu();

	Interface i = Interface();
	i.convertToGV();
	i.updateMap();

	i.roadsBlocked();
	i.updateMap();

	i.calculatePath();
	cin.get();
	i.updateMap();


	cin.get();

	return 0;
}
