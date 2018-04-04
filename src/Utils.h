#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <vector>
#include <float.h>
#include "Graph.h"
#include "math.h"

#define GV_WIDTH 1157
#define GV_HEIGHT 2405

#define MIN_LON -9.5691
#define MAX_LON -6.3940
#define MIN_LAT 36.8554
#define MAX_LAT 41.9411


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
