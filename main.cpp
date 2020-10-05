#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Point {

	float x;
	float y;
	float z;
	
	size_t clusterID;
};

// Optimised Euclidean Distance (no sqrt) from cluster point
float OptEucDist(Point* point, Point* cluster) {

	return pow(point->x - cluster->x, 2.0) + pow(point->y - cluster->y, 2.0) + pow(point->z - cluster->z, 2.0);

}

int main(int argc, char *argv[]) {

	// open file given by command line
	std::fstream dataFile;
	char * fileName = argv[1];
	dataFile.open(fileName);

	// load data assuming only 240 per specification
	// ignore first line as is currently not used
	std::string line;
	std::getline(dataFile, line);
	std::vector<Point> data(240);

	Point tempPoint;
	std::getline(dataFile, line);
	while(!dataFile.eof()) {
	
		// tokenise to ordinates
		// load ordinates to point
		// load vector with new point	
		std::getline(dataFile, line);
	}	

	// randomise cluster selection from the given number of points
	// perform a k means algorithm
	// multiple k means trials
	// auto 'k' determination

	return 0;

}
