/*
 BTree.h - declarations for the class .
 */

#ifndef PROVINCE_H
#define PROVINCE_H
#include <list>
#include <string>
using namespace std;

//class Province;
class City;
class Road;

class Province
{
    public:

    //constructor
    Province();


    //get the list for road
    list<Road*> getRoadList();
    //get the list for city
    list<City*> getCityList();

    //get the number of roads in province
    int getNumOfRoads();
    //get the number of cities in province
    int getNumOfCities();
    //Set captial
    void setCapital(City* city);
    //Get captial in city list
    City* getCapital();

    //add city in city list
    void addCity(City * city);
    //find citt in list
    City* findCity(string city);
    //add road in road list
    void addRoad(Road *road);

    //Destructor
    ~Province();

    private:
    City* capital;
    list<City*> listOfCities;
    list<Road*> listOfRoads;

};

//Each city in the province
class City
{
    public:

    //constructor
    City(string name, bool capital);
    //Get city name
    string getCityName();
    //true if city is captial
    bool getIsCapital();

    //add road in list
    void addRoadToCity(Road* road);
    //return road list for this city
    list<Road*> getCityRoadList();

    private:
    string cityName;
    bool isCapital;
    list<Road*> cityRoadList;
};

//Each road in the province
class Road
{
    public:

    //constructor
    Road(City* cityOne, City* cityTwo, bool bridge, int roadDistance);

    //Get city on one end of the road
    City* getCity1();
    //Get the city on the other side of the road
    City* getCity2();
    //true if road is bridge
    bool getIsBridge();
    //Get distance for road
    int getDistance();

    private:
    City* city1;
    City* city2;
    bool isBridge;
    int distance;
};
//This is use in priority_queue, helped by Sam
struct WeightOrder {

 bool operator()(Road* startRoad, Road* endRoad) {
    return endRoad -> getDistance() < startRoad -> getDistance();
  };
};
#endif
