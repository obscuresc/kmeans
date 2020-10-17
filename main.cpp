#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <time.h>
#include <vector>

#define correctNumParams 3
#define numClusterMinimum 2
#define numDataPoints 240

// Point structure
struct Point {

	float x;
	float y;
	float z;
	
	int clusterID;
};

void kmeans(std::vector<Point>*, size_t);
void identify(std::vector<Point>*, std::vector<Point>*);
float OptEucDist(Point*, Point*);
void grabClusterIDs(std::vector<Point>*, std::vector<int>*);
bool differentClusterIDs(std::vector<Point>*, std::vector<int>*);


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

	// perform a k means algorithm
	kmeans(&data, numClusters);

	// multiple k means trials
	// auto 'k' determination

	return 0;

}


void kmeans(std::vector<Point>* data, size_t numClusters) {

	// randomise cluster selection from the given number of points
	srand(time(NULL));
	size_t randomIndex = 0;
	std::vector<Point> clusterPoints(numClusters);
	for(size_t i = 0; i < clusterPoints.size(); i++) {

		randomIndex = rand() % numDataPoints + 1;  
		clusterPoints.at(i) = data->at(randomIndex);
	}

	// buffer for checking whether cluster IDs change
	std::vector<int> clusterIDbuffer(data->size());
	identify(data, &clusterPoints);
	grabClusterIDs(data, &clusterIDbuffer);
	while(differentClusterIDs(data, &clusterIDbuffer)) {

		// compute new clusters() ***TODO***

		identify(data, &clusterPoints);
		grabClusterIDs(data, &clusterIDbuffer);
	}
}


float OptEucDist(Point* point1, Point* point2) {

	return pow(point1->x - point2->x, 2.0) + pow(point1->y - point2->y, 2.0) + pow(point1->z - point2->z, 2.0);

}

void identify(std::vector<Point>* data, std::vector<Point>* clusterPoints) {

	float minDist = std::numeric_limits<float>::max();
	float tempDist = 0;
	int closestClusterID = -1;
	for(size_t i = 0; i < data->size(); i++) {

		for(size_t j = 0; j < clusterPoints->size(); j++) {

			// check against all available clusters and find the closest
			tempDist = OptEucDist(&data->at(i), &clusterPoints->at(j));
			if(tempDist < minDist) {

				closestClusterID = j;
				minDist = tempDist;
			}

		}

		data->at(i).clusterID = closestClusterID;

	}
}



void grabClusterIDs(std::vector<Point>* data, std::vector<int>* clusterIDbuffer) {

	for(size_t i = 0; i < data->size(); i++)
		clusterIDbuffer->at(i) = data->at(i).clusterID;
}


bool differentClusterIDs(std::vector<Point>* data, std::vector<int>* clusterIDbuffer) {

	bool isDifferent = false;
	for(size_t i = 0; i < data->size(); i++) {

		isDifferent |= (data->at(i).clusterID == clusterIDbuffer->at(i));

	}

	return isDifferent;
}
