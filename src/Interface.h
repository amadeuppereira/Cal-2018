#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

#include "RoadNetwork.h"
#include <set>
#include <unistd.h>

class Interface {
private:
	RoadNetwork* roadnetwork;
public:
	Interface();
	virtual ~Interface();
	void convertToGV();
	unsigned long long getDestinyId() const;
	void setDestinyId(int destinyId);
	unsigned long long getSourceId() const;
	void setSourceId(int sourceId);
	void roadsBlocked();
	void calculatePath();
	void showMap();
	void updateMap();
	void closeMapWindow();
	void getAllCarsPath();
	void removeCar();
	void returnMenu();
	void returnMenu2();
};

#endif /* SRC_INTERFACE_H_ */
