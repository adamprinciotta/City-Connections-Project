#include "province.h"
#include <string>

using namespace std;
//Road in the Province
Road::Road(City* cityOne, City* cityTwo, bool bridge, int roadDistance){
  city1 = cityOne;
  city2 = cityTwo;
  isBridge = bridge;
  distance = roadDistance;
}

City* Road::getCity1(){
  return city1;
}

City* Road::getCity2(){
  return city2;
}

bool Road::getIsBridge(){
  return isBridge;
}

int Road::getDistance(){
  return distance;
}

