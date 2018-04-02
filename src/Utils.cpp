#include <iostream>
#include "Utils.h"


LimitCoords getLimitCoords(Graph<int> g) {
	LimitCoords l;

//Initializes minimum value with highest possible
	double minLat = FLT_MAX;
	double minLong = FLT_MAX;

	double maxLat = -FLT_MAX;
	double maxLong = -FLT_MAX;

	vector<Vertex<int> *> vertex = g.getVertexSet();
	for (int i = 0; i < g.getNumVertex(); i++) {
		if (vertex[i]->getLatitude() < minLat)
			minLat = vertex[i]->getLatitude();

		if (vertex[i]->getLongitude() < minLong)
			minLong = vertex[i]->getLongitude();

		if (vertex[i]->getLatitude() > maxLat)
			maxLat = vertex[i]->getLatitude();

		if (vertex[i]->getLongitude() > maxLong)
			maxLong = vertex[i]->getLongitude();
	}

	l.maxLat = maxLat;
	l.maxLong = maxLong;
	l.minLat = minLat;
	l.minLong = minLong;

	return l;
}

int resizeLat(double lat, LimitCoords l, float windowH) {

	return ((lat - l.minLat)/(l.maxLat-l.minLat)*windowH);

//	return (windowH
//			- (round(windowH / (l.maxLat - l.minLat) * (lat - l.minLat))));
}

int resizeLong(double lon, LimitCoords l, float windowW) {

	return ((lon - l.minLong)/(l.maxLong-l.minLong)*windowW);

	//return (round(windowW / (l.maxLong - l.minLong) * (lon - l.minLong)));
}

//int resizeLat(double lat) {
//
//	int ret = (lat - MIN_LAT)/(MAX_LAT - MIN_LAT) * (GV_HEIGHT - 0);
//
//	return ret;
//}
//
//int resizeLong(double lon) {
//
//	int ret = (lon - MIN_LON)/(MAX_LON - MIN_LON) * (GV_WIDTH - 0);
//
//	return ret;
//}
