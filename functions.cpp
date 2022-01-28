#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

// TODO Write this function
int energy(const Pixel *const*image, int col, int row, int width, int height)
{
  int xRRight = 0;
  int xGRight = 0;
  int xBRight = 0;

  int xRLeft = 0;
  int xGLeft = 0;
  int xBLeft = 0;

  int yRTop = 0;
  int yGTop = 0;
  int yBTop = 0;

  int yRBot = 0;
  int yGBot = 0;
  int yBBot = 0;



  int xREnergy = 0;
  int xGEnergy = 0;
  int xBEnergy = 0;
  int yREnergy = 0;
  int yGEnergy = 0;
  int yBEnergy = 0;
  int totEnergy = 0;

// initialize all the values

// if statement that if row == 0then changes right
// if statement if row == height - 1 then changes
// if statement col = 0 then changes
// if statement col = width then changes

  if(row == 0){  // change to more if/else statements to work for 1x3
    yRTop = image[col][height-1].r;
    yGTop =  image[col][height-1].g;
    yBTop = image[col][height-1].b;
  } else {
    yRTop = image[col][row-1].r;
    yGTop = image[col][row-1].g;
    yBTop = image[col][row-1].b;
  }
  

 if(row == height - 1) {
    yRBot = image[col][0].r;
    yGBot = image[col][0].g;
    yBBot =  image[col][0].b;
 } else{ 
    yRBot = image[col][row+1].r;
    yGBot = image[col][row+1].g;
    yBBot = image[col][row+1].b;
 }

  if(col == 0) { 
    xRLeft = image[width-1][row].r;
    xGLeft = image[width-1][row].g;
    xBLeft = image[width-1][row].b;
  }  else {
    xRLeft = image[col-1][row].r;
    xGLeft = image[col-1][row].g;
    xBLeft = image[col-1][row].b;
  }
  
if (col == width - 1) {
    xRRight = image[0][row].r;
    xGRight = image[0][row].g;
    xBRight = image[0][row].b;
} else {
    xRRight = image[col+1][row].r;
    xGRight = image[col+1][row].g;
    xBRight = image[col+1][row].b;
}

  yREnergy = yRTop - yRBot;
  yGEnergy = yGTop - yGBot;
  yBEnergy = yBTop - yBBot;
  xREnergy = xRRight - xRLeft;
  xGEnergy = xGRight - xGLeft;
  xBEnergy = xBRight - xBLeft;

  yREnergy *= yREnergy;
  yGEnergy *= yGEnergy;
  yBEnergy *= yBEnergy;
  xREnergy *= xREnergy;
  xGEnergy *= xGEnergy;
  xBEnergy *= xBEnergy;

  totEnergy = xREnergy + xGEnergy + xBEnergy + yREnergy + yGEnergy + yBEnergy;

  return totEnergy;
}

// TODO Write this function
int getVerticalSeam(const Pixel *const*image, int start_col, int width, int height, int* seam) // test for 1x3
{
  int currentEnergy = 0;
  int sumVertSeamEnergy = energy(image, start_col, 0, width, height);
  cout << sumVertSeamEnergy << ": ";
  seam[0] = start_col;
  for(int i = 1; i < height; i++) { 
    if(width == 1) {
      currentEnergy = energy(image, start_col, i, width, height);
      seam[i] = start_col;
    } else if (start_col == 0) {
      if(energy(image, start_col, i, width, height) <= energy(image, start_col+1, i,  width, height)){
        currentEnergy = energy(image, start_col, i, width, height);
        seam[i] = start_col;
      } else {
        currentEnergy = energy(image, start_col+1, i, width, height);
        seam[i] = start_col + 1;
        start_col = start_col + 1;
      }

    } else if(start_col == (width - 1)) {
        if(energy(image, start_col, i, width, height) <= energy(image, start_col-1, i, width, height)){
          currentEnergy = energy(image, start_col, i, width, height);
          seam[i] = start_col;
        } else {
          currentEnergy = energy(image,  start_col-1, i, width, height);
          seam[i] = start_col -1;
          start_col = start_col - 1;
        }   

    } else {
      int min = energy(image, start_col, i, width, height);
      seam[i] = start_col;
      for (int k = 0; k < 3; k++) {
        if (energy(image, (start_col +1 - k), i, width, height) < min) {
          min = energy(image, (start_col +1 - k), i, width, height);
          seam[i] = start_col +1 - k;
        }
      }
      start_col = seam[i];
      currentEnergy = min;
    }
    cout << currentEnergy << " ";
    sumVertSeamEnergy += currentEnergy;
  }

  return sumVertSeamEnergy;
}

// TODO Write this function
void removeVerticalSeam(Pixel **image, int& width, int height, int *verticalSeam)
{
  
  for(int i = 0; i < height; i++) {
    for (int k = verticalSeam[i]; k < (width - 1); k++) {
      image[k][i].r = image[k+1][i].r;
      image[k][i].g = image[k+1][i].g;
      image[k][i].b = image[k+1][i].b;
    }
  }
  
 
  width--;
}

// TODO Write this function for extra credit
int getHorizontalSeam(const Pixel *const*image, int start_row, int width, int height, int* seam)
{
  if(image == nullptr) { ; }
  if(start_row == 0) { ; }
  if(width== 0) { ; }
  if(height == 0) { ; }
  if(seam == nullptr) { ; }
  return 0;
}

// TODO Write this function for extra credit
void removeHorizontalSeam(Pixel **image, int width, int& height, int *horizontalSeam)
{
  if(image == nullptr) { ; }
  if(width== 0) { ; }
  if(height == 0) { ; }
  if(horizontalSeam == nullptr) { ; }
  
}

int *findMinVerticalSeam(const Pixel *const*image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first col (index 0)
  int *minSeam = new int[height]{0};
  int minDist = getVerticalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[height ]{0};
  int candidateDistance = -1; // invalid distance

  // start at second col (index 1) since we initialized with first col (index 0)
  for (int col = 1; col < width; ++col)
  {
    candidateDistance = getVerticalSeam(image, col, width, height, candidateSeam);

    if (candidateDistance < minDist)
    { // new min
      //  swap min & candidate
      minDist = candidateDistance;
      int* temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

  // clean up 
  delete [] candidateSeam;

  return minSeam;
}

int *findMinHorizontalSeam(const Pixel *const*image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first row (index 0)
  int *minSeam = new int[width]{0};
  int minDistance = getHorizontalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[width]{0};
  int candidateDistance = -1; // invalid distance

  // start at second row (index 1) since we initialized with first row (index 0)
  for (int row = 1; row < height; ++row)
  {
    candidateDistance = getHorizontalSeam(image, row, width, height, candidateSeam);

    if (candidateDistance < minDistance)
    { // new minimum
      //  swap min and candidate seams
      minDistance = candidateDistance;
      int* temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

    // clean up 
  delete [] candidateSeam;

  return minSeam;
}

Pixel **createImage(int width, int height)
{
  cout << "Start createImage... " << endl;

  // Create a one dimensional array on the heap of pointers to Pixels
  //    that has width elements (i.e. the number of columns)
  Pixel **image = new Pixel *[width] {}; // initializes to nullptr

  for (int col = 0; col < width; ++col)
  { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    try
    {
      image[col] = new Pixel[height];
    }
    catch (std::bad_alloc &e)
    {
      // clean up already allocated arrays
      for (int i = 0; i < col; ++i)
      {
        delete[] image[i];
      }
      delete[] image;
      // rethrow
      throw e;
    }
  }

  // initialize cells
  // cout << "Initializing cells..." << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = {0, 0, 0};
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel **image, int width)
{
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i = 0; i < width; ++i)
  {
    delete[] image[i];
  }
  delete[] image;
  image = nullptr;
  cout << "End deleteImage..." << endl;
}

bool isValidColor(int colorVal)
{
  if (colorVal < 0 || colorVal > 255)
  {
    return false;
  }
  return true;
}

Pixel ** loadImage(string filename, int &width, int &height)
{
  cout << "Start loadImage..." << endl;
  // remove
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw std::invalid_argument("Failed to open input file (" + filename + ")");
  }

  string type;
  ifs >> type; // should be P3
  if (toupper(type.at(0)) != 'P' || type.at(1) != '3')
  {
    throw std::domain_error("Not PPM type P3 (" + type + ")");
  }
  ifs >> width;
  // cout << "w and h: " << w << " " << h << endl;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for width");
  }
  if (width <= 0)
  {
    ostringstream oss;
    oss << "Width in file must be greater than 0 (" << width << ")";
    throw std::domain_error(oss.str());
  }

  ifs >> height;
  if (ifs.fail())
  {
    cout << "Read non-integer value for height" << endl;
  }
  if (height <= 0)
  {
    ostringstream oss;
    oss << "Height in file must be greater than 0 (" << height << ")";
    throw std::domain_error(oss.str());
  }

  int colorMax = 0;
  ifs >> colorMax;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for max color value");
  }
  if (colorMax != 255)
  {
    ostringstream oss;
    oss << "Max color value must be 255 (" << colorMax << ")";
    throw std::domain_error(oss.str());
  }

  // load image throws exceptions but we will let them pass through
  Pixel **image = createImage(width, height);

  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "Pixel(" << col << ", " << row << ")" << endl;
      ifs >> image[col][row].r;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for red");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for red (" << image[col][row].r << ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].g;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for green");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for green (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].b;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for blue");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for blue (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }
    }
  }
  cout << "End loadImage..." << endl;
  return image;
}

void outputImage(string filename, const Pixel *const *image, int width, int height)
{
  cout << "Start outputImage..." << endl;
  // remove code
  // declare/define and open output file stream with filename
  ofstream ofs(filename);
  // ensure file is open
  if (!ofs.is_open())
  {
    throw std::invalid_argument("Error: failed to open output file - " + filename);
  }
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << 255 << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      ofs << image[col][row].r << " ";
      ofs << image[col][row].g << " ";
      ofs << image[col][row].b << " ";
    }
    ofs << endl;
  }
  cout << "End outputImage..." << endl;
}