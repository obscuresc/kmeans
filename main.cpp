#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <time.h>
#include <vector>

#ifdef DEBUG
	#define LOG(x) std::cout << x << std::endl;
#else
	#define LOG(x) 
#endif // DEBUG


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
void computeNewClusters(std::vector<Point>*, std::vector<Point>*);
void grabClusterIDs(std::vector<Point>*, std::vector<int>*);
bool differentClusterIDs(std::vector<Point>*, std::vector<int>*);
void printVecPoints(std::vector<Point>*);


int main(int argc, char *argv[]) {

	// function guards
	if(argc != correctNumParams) {

		std::cout << "Incorrect number of arguments" << std::endl;
		return -1;
	}

	int numClusters = atoi(argv[2]);
	if(numClusters < numClusterMinimum) {
		
		std::cout << "Invalid number of clusters" << std::endl;
		return -1;
	}

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

	LOG("Starting kmeans");

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

	printVecPoints(data);

	grabClusterIDs(data, &clusterIDbuffer);
	while(differentClusterIDs(data, &clusterIDbuffer)) {

		LOG("New iteration of kmeans");

		computeNewClusters(data, &clusterPoints);
		identify(data, &clusterPoints);
		grabClusterIDs(data, &clusterIDbuffer);
	}
}


float OptEucDist(Point* point1, Point* point2) {

	LOG("OptEucDist");
	std::cout << "Point1: (" << point1->x << "," << point1->y << "," << point1->z << ")" << std::endl;
	std::cout << "Point2: (" << point2->x << "," << point2->y << "," << point2->z << ")" << std::endl;
	return pow(point1->x - point2->x, 2.0) + pow(point1->y - point2->y, 2.0) + pow(point1->z - point2->z, 2.0);

}


void computeNewClusters(std::vector<Point>* data, std::vector<Point>* clusterPoints) {

	LOG("Starting computeNewClusters");

	std::vector<int> numOfPointsInCluster(clusterPoints->size(), 0);

	// sum ordinates of each points that are part of the cluster 
	for(size_t i = 0; i < data->size(); i++) {

		clusterPoints->at(data->at(i).clusterID).x += data->at(i).x;
		clusterPoints->at(data->at(i).clusterID).y += data->at(i).y;
		clusterPoints->at(data->at(i).clusterID).z += data->at(i).z;
		numOfPointsInCluster.at(data->at(i).clusterID)++;

	}

	// calculate average using the number of points within the cluster
	for(size_t i = 0; i < clusterPoints->size(); i++) {

		clusterPoints->at(i).x /= numOfPointsInCluster.at(i);
		clusterPoints->at(i).y /= numOfPointsInCluster.at(i);
		clusterPoints->at(i).z /= numOfPointsInCluster.at(i);
	}

}


void identify(std::vector<Point>* data, std::vector<Point>* clusterPoints) {

	LOG("New identify call");

	float minDist = std::numeric_limits<float>::max();
	float tempDist = 0;
	int closestClusterID = -1;
	for(size_t i = 0; i < data->size(); i++) {

		LOG("Point identify");
		std::cout << "(" << data->at(i).x << "," << data->at(i).y << ",";
		std::cout << data->at(i).z << ")" << std::endl;

		for(size_t j = 0; j < clusterPoints->size(); j++) {

			std::cout << "Cluster Point: " << "(" << clusterPoints->at(j).x;
			std::cout << "," << clusterPoints->at(j).y << ",";
			std::cout << clusterPoints->at(j).z << std::endl;

			// check against all available clusters and find the closest
			tempDist = OptEucDist(&(data->at(i)), &clusterPoints->at(j));
			std::cout << "Distance between: " << tempDist << std::endl;

			if(tempDist < minDist) {

				closestClusterID = j;
				minDist = tempDist;
			}

		#ifdef DEBUG
			LOG("HALTED");
			std::getc(stdin);
		#endif // DEBUG

		}

		data->at(i).clusterID = closestClusterID;
		#ifdef DEBUG
			LOG("HALTED");
			std::getc(stdin);
		#endif // DEBUG

	}
}



void grabClusterIDs(std::vector<Point>* data, std::vector<int>* clusterIDbuffer) {

	LOG("Grabbing cluster IDs");

	for(size_t i = 0; i < data->size(); i++)
		clusterIDbuffer->at(i) = data->at(i).clusterID;
}


bool differentClusterIDs(std::vector<Point>* data, std::vector<int>* clusterIDbuffer) {

	LOG("Determined if IDs have changed");

	bool isDifferent = false;
	for(size_t i = 0; i < data->size(); i++) {

		isDifferent |= (data->at(i).clusterID != clusterIDbuffer->at(i));

	}

	#ifdef DEBUG
		LOG("HALTED");
		std::getc(stdin);
	#endif // DEBUG

	return isDifferent;
}


void printVecPoints(std::vector<Point>* input) {

	for(size_t i = 0; i < input->size(); i++) {
		
		std::cout << "Point: (" << input->at(i).x;
	   	std::cout << "," << input->at(i).y << ","; 
		std::cout << input->at(i).z << ")";
		std::cout << " clusterID: " << input->at(i).clusterID << std::endl;
	}
}
