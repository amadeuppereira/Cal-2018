#include "RoadNetwork.h"

RoadNetwork::RoadNetwork() {
	// TODO Auto-generated constructor stub

}

RoadNetwork::~RoadNetwork() {
	// TODO Auto-generated destructor stub
}

int RoadNetwork::getDestinyId() const {
	return destinyID;
}

void RoadNetwork::setDestinyId(int destinyId) {
	destinyID = destinyId;
}

int RoadNetwork::getSourceId() const {
	return sourceID;
}

void RoadNetwork::setSourceId(int sourceId) {
	sourceID = sourceId;
}
