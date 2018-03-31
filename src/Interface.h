#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

#include "RoadNetwork.h"
#include <set>

class Interface {
private:
	RoadNetwork* roadnetwork;
	unsigned long long sourceID;
	unsigned long long destinyID;
public:
	Interface();
	virtual ~Interface();
	unsigned long long getDestinyId() const;
	void setDestinyId(int destinyId);
	unsigned long long getSourceId() const;
	void setSourceId(int sourceId);

	void roadsBlocked();
	void calculatePath();

};

#endif /* SRC_INTERFACE_H_ */
