//Authors: Adam Princiotta, John Zhu
#include "province.h"
#include <string>

using namespace std;

//City in the Province 
City::City(string name, bool capital){
  cityName = name;
  isCapital = capital;
}

string City::getCityName(){
  return cityName;
}

bool City::getIsCapital(){
  return isCapital;
}

void City::addRoadToCity(Road * road){
  cityRoadList.push_back(road);
}

list<Road*> City::getCityRoadList(){
  return cityRoadList;
}
