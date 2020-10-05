#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Point structure
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
	std::string line;
	std::getline(dataFile, line);
	
	// decide if PPM structure
	bool isPPM = (line.at(0) == 'P');
	std::vector<Point> data(240);

	Point tempPoint;
	std::string xString;
	std::string yString;
	std::string zString;

	if(isPPM) {

		while(dataFile >> xString >> yString >> zString) {

			tempPoint.x = stof(xString);
			tempPoint.y = stof(yString);
			tempPoint.z = stof(yString);
		
			data.push_back(tempPoint);	
		}
	}

	else {

		while(dataFile >> xString >> yString) {

			tempPoint.x = stof(xString);
			tempPoint.y = stof(yString);
		
			data.push_back(tempPoint);	
		}
		
	}
	// randomise cluster selection from the given number of points
	// perform a k means algorithm
	// multiple k means trials
	// auto 'k' determination

	return 0;

}
