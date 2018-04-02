#include <iostream>
#include "Utils.h"


int resizeLat(long double lat) {
	return (GV_HEIGHT - (round(GV_HEIGHT / (MAX_LAT - MIN_LAT) * (lat - MIN_LAT))));
}

int resizeLon(long double lon) {
	return (round(GV_WIDTH / (MAX_LON - MIN_LON) * (lon - MIN_LON)));
}


