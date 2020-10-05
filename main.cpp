#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define headerSampleSize 20

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

int main(int argc, char const *argv[]) {

	// open file given by command line
	std::fstream dataFile;
	char * fileName = &argv[2];
	dataFile.open(fileName);

	// load data assuming only 241 per specification
	std::string line;
	dataFile.getline(line);
	std::cout << line << std::endl;
	std::vector<Point> data(241);
	
	return 0;

}
