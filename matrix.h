#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;
#include <string>
using namespace std;
#include <vector>
using namespace std;
#include <stdlib.h>
#include <algorithm>

class Matrix
{
public:
    Matrix();
    int length;
    int width;
  public:
    Matrix(int l, int w){
      length = l;
      width = w;
    }
    vector<vector<int>> setup(){
      for (int i = 0; i < length; i ++){
        vector<int> blank;
        for (int w = 0; w < width; w ++){
          if (bombinit()){
            blank.push_back(1);
          }
          else{
            blank.push_back(0);
          }
        }
        positions.push_back(blank);
      }
     return positions;
    }
    private:
      vector<vector<int>> positions;
      bool bombinit(){ //decides if a square is a bomb or not. Called from setup
        int checker = rand() % 100 + 1;
        if (checker <= 1){
          return true;
        }
        else{
          return false;
        }
      }
  };

#endif // MATRIX_H
