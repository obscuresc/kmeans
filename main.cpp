#include <iostream>
#include <fstream>
#include <string>

#define headerSampleSize 20

struct Point {

    std::vector<float> ord;

  Point::Point(size_t dim) {

    ord.resize(dim);

  }

};

int main(int argc, char const *argv[]) {

  // open file given by command line
  std::fstream dataFile;
  char * fileName = &argv[2];
  dataFile.open(fileName);

  // ignore header line if required
  bool headerLineExists = FALSE;
  char headerSample[headerSampleSize];
  dataFile.getline(headerSample, headerSampleSize, ',');
  try {

    // no header line exists
    float numHeaderSample = std::stof(str(headerSample));

    // line pointer will remain at the start of the file
  }
  catch (int e)
  {
    // move line pointer to second line in the file
    headerLineExists = TRUE;

  }

  // reset file stream
  dataFile.close();
  dataFile.open(fileName);

  // move line if required
  if headerLineExists {

    // don't care about the header line at the moment
    dataFile.getLine();

  }

  // create and load vector of points
  std::vector<Point> data;
  char * ordinates;
  std::string line;
  while not eof {

    // convert line to point
    dataFile.getLine(line);
    ordinates = strtok(line, ',');

    // for number of ordinates
    // allocate ordinates to point

    // append point to vector, might be slow but don't know data size prior
    data.push()
  }




  return 0;
}
