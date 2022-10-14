#include "province.h"
#include <string>
#include <iostream>
using namespace std;

Province::Province() {
}

list<Road*> Province::getRoadList(){
  return listOfRoads;
}

list<City*> Province::getCityList(){
  return listOfCities;
}

int Province::getNumOfRoads(){
  return listOfRoads.size();
}

int Province::getNumOfCities(){
  return listOfCities.size();
}

void Province::addCity(City * city){
  listOfCities.push_back(city);
}

void Province::addRoad(Road * road){
  listOfRoads.push_back(road);
}
//find the city in the province with iterator, return iterator if find
City* Province::findCity(string city){
  list<City *>::iterator it;
  for(it = listOfCities.begin(); it != listOfCities.end(); it++){
    if((*it) -> getCityName().compare(city) == 0){
      return (*it);
    }
  }
  return NULL;
}
void Province::setCapital(City* city){
    capital = city;
}

City* Province::getCapital(){
  return capital;
}
