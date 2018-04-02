#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <vector>
#include <float.h>
#include "Graph.h"
#include "math.h"

#define GV_WIDTH 457
#define GV_HEIGHT 424

//#define MIN_LON -9.014
//#define MAX_LON -6.515
//#define MIN_LAT 40.179
//#define MAX_LAT 41.878

#define MIN_LON -9.080
#define MAX_LON -6.575
#define MIN_LAT 40.147
#define MAX_LAT 41.900


class Link {
public:
	int edgeID, nodeID1, nodeID2;
	Link(int e, int n1, int n2) {
		edgeID = e;
		nodeID1 = n1;
		nodeID2 = n2;
	}
};


int resizeLat(long double lat);
int resizeLon(long double lon);




#endif /* SRC_UTILS_H_ */
