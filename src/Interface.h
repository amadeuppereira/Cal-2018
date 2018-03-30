#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

#include "RoadNetwork.h"
#include <set>

class Interface {
private:
	RoadNetwork* roadnetwork;
public:
	Interface();
	virtual ~Interface();

	void roadsBlocked();

};

#endif /* SRC_INTERFACE_H_ */
