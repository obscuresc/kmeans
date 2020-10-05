#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

#define correctNumParams 3
#define numClusterMinimum 2
#define numDataPoints 240

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

	// function guard
	if(argc != correctNumParams) return -1;
	int numClusters = atoi(argv[2]);
	if(numClusters < numClusterMinimum) return -1;

	// open file given by command line
	std::fstream dataFile;
	char * fileName = argv[1];
	dataFile.open(fileName);
	if(!dataFile.good()) return -1;

	// load data assuming only 240 per specification
	std::string line;
	std::getline(dataFile, line);
	std::cout << line << std::endl;	

	// decide if PPM structure
	bool isPPM = (line.at(0) == 'P');
	std::vector<Point> data(numDataPoints);

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
	srand(time(NULL));
	size_t randomIndex = 0;
	std::vector<Point> clusters(numClusters);
	for(int i = 0; i < clusters.size(); i++) {

		randomIndex = rand() % numDataPoints + 1;  
		clusters.at(i) = data.at(randomIndex);
	}

	// perform a k means algorithm
		// need vector of cluster allocation per point
		// k means ends when vector of allocation remains the same

	// multiple k means trials
	// auto 'k' determination

	return 0;

}
