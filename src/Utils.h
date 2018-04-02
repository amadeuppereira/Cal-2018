#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <vector>
#include <float.h>
#include "Graph.h"
#include "math.h"

#define GV_WIDTH 520
#define GV_HEIGHT 515

#define MIN_LAT 40.65633
#define MAX_LAT 40.66051
#define MIN_LON -7.91586
#define MAX_LON -7.91030

//#define MIN_LAT 40.65466
//#define MAX_LAT 40.67395
//#define MIN_LON -7.919028
//#define MAX_LON -7.886086


class Link {
public:
	int edgeID, nodeID1, nodeID2;
	Link(int e, int n1, int n2) {
		edgeID = e;
		nodeID1 = n1;
		nodeID2 = n2;
	}
};

struct LimitCoords
{
	double maxLat;
	double minLat;
	double maxLong;
	double minLong;
};

/**
 * Stores in a LimitCoords struct the max coordinate values of map graph g
 */
LimitCoords getLimitCoords(Graph<int> g);
int resizeLat(double lat, LimitCoords l, float windowH);
int resizeLong(double lon, LimitCoords l, float windowW);


//int resizeLat(double lat);
//int resizeLong(double lon);


//int getGV_X();
//int getGV_Y();


#endif /* SRC_UTILS_H_ */
