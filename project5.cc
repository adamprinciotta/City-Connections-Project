//Authors: Adam Princiotta, John Zhu

#include <iostream>
#include <list>
#include <string>
#include "province.h"
#include <queue>
#include <set>
#include <map>
#include <stack>
using namespace std;

//Breadth First Search - returns BFS list of cities
//Takes in a province and makes a queue for cities, list for the final BFS and
//a set to store visited cities. Every time a new city is met, it is pushed onto
//the queue and then added to the visited cities set. Then the loop runs while
//the queue is not empty and takes the fron element and puts it on the BFS list.
//To see if a city is new, the road is taken and checks if the first city is the
//same as the the current city. If so, then the second city is used and vice versa.
list<City*> breadthFirstSearch(Province* p){
  queue<City*> cityQueue;
  list<City*> BFSCityList;
  set<City*> visitedCities;

  visitedCities.insert(p -> getCapital());
  cityQueue.push(p -> getCapital());
  City* currCity;

  while(!cityQueue.empty()){
    currCity = cityQueue.front();
    cityQueue.pop();

    BFSCityList.push_back(currCity);

    list<Road*>currCityRoadList = currCity -> getCityRoadList();
    list<Road*>::iterator i = currCityRoadList.begin();

    while(i != currCityRoadList.end()){
      Road* currRoad = * i;
      City* city1 = currRoad -> getCity1();
      City* city2 = currRoad -> getCity2();

      if((city1 -> getCityName()).compare(currCity -> getCityName()) == 0 && visitedCities.find(city2) == visitedCities.end()) {
        cityQueue.push(city2);
        visitedCities.insert(city2);
      }
      else if((city2 -> getCityName()).compare(currCity -> getCityName()) == 0 && visitedCities.find(city1) == visitedCities.end()){
        cityQueue.push(city1);
        visitedCities.insert(city1);
      }
      i++;
    }
  }

  return BFSCityList;

}


//Prints out the groups of cities that would be isolated if all bridge connections
//failed. Iterate through each city, and iterate through every road. Check if
//it is a bridge, if so then ignore it, otherwise store it in the queue and visited
//cities list. Nested iterators checking cities and their roads while keeping
//a queue of cities that need their roads checked and cities that have been visited.
void isolatedCities(Province * p){
  queue<City*> cityQueue;
  set<City*> visitedCities;

  list<City*> currCityList = p -> getCityList();

  City* currCity = p -> getCapital();

  cityQueue.push(currCity);
  cout << "Connected components in event of a major storm are" << endl;
  cout << "   If all bridges fail, the following towns would form an isolated group:" << endl;

  list<City*>::iterator cityItr = currCityList.begin();

  while(cityItr != currCityList.end()){
    if(visitedCities.find((*cityItr)) == visitedCities.end() && ((*cityItr) == p -> getCapital())){
      visitedCities.insert(*cityItr);
    }

    else if(visitedCities.find((*cityItr)) == visitedCities.end()){
      cout << "\n   If all bridges fail, the following towns would form an isolated group:" << endl;
      cityQueue.push(*cityItr);
      visitedCities.insert(*cityItr);
    }
      while(!cityQueue.empty()){
        currCity = cityQueue.front();
        cityQueue.pop();

        cout << "        " << currCity -> getCityName() << endl;

        list<Road*>currCityRoadList = currCity -> getCityRoadList();
        list<Road*>::iterator i = currCityRoadList.begin();

        while(i != currCityRoadList.end()){
          Road * currRoad = * i;
          if (!currRoad -> getIsBridge()){
            City* city1 = currRoad -> getCity1();
            City* city2 = currRoad -> getCity2();

            if((city1 -> getCityName()).compare(currCity -> getCityName()) == 0 && visitedCities.find(city2) == visitedCities.end()) {
              cityQueue.push(city2);
              visitedCities.insert(city2);
            }
            else if((city2 -> getCityName()).compare(currCity -> getCityName()) == 0 && visitedCities.find(city1) == visitedCities.end()){
              cityQueue.push(city1);
              visitedCities.insert(city1);
            }
          }
          i++;
        }
      }
    cityItr++;
  }
}

//Returns true if the city is an articulation point. Uses the same method as the
//BFS search from earlier however the city list is called and the given city
//is deleted then making new list a city smaller. Then the BFS is run and if the
//same number of cities is found, then it is not an articulation point. If the
//number is not equal, then it is an articulation point.
bool articulationPointsAux(Province * p, City * delCity){
  queue<City*> cityQueue;
  list<City*> BFSCityList;
  set<City*> visitedCities;

  list<City*> newCityList = p -> getCityList();
  newCityList.remove(delCity);

  //If the city to delete is not the capital and there is something else to delete
  if(delCity != p -> getCapital() && newCityList.size() > 0){
    visitedCities.insert(p -> getCapital());
    cityQueue.push(p -> getCapital());
  }
  //If the city is the captial and there is another city to replace it
  else if(newCityList.size() > 0){
    list<City*>::iterator firstCity = newCityList.begin();
    visitedCities.insert(*firstCity);
    cityQueue.push(*firstCity);
  }

  City* currCity;
  while(!cityQueue.empty()){
    currCity = cityQueue.front();
    cityQueue.pop();

    BFSCityList.push_back(currCity);

    list<Road*>currCityRoadList = currCity -> getCityRoadList();
    list<Road*>::iterator i = currCityRoadList.begin();

    while(i != currCityRoadList.end()){
      Road* currRoad = * i;
      City* city1 = currRoad -> getCity1();
      City* city2 = currRoad -> getCity2();

      if((city1 -> getCityName()).compare(currCity -> getCityName()) == 0 && visitedCities.find(city2) == visitedCities.end() && city2 != delCity) {
        cityQueue.push(city2);
        visitedCities.insert(city2);
      }
      else if((city2 -> getCityName()).compare(currCity -> getCityName()) == 0 && visitedCities.find(city1) == visitedCities.end() && city1 != delCity){
        cityQueue.push(city1);
        visitedCities.insert(city1);
      }
      i++;
    }
  }

  if(visitedCities.size() == newCityList.size()){
    return false;
  }
  return true;
}

//Prints out the cities that are articulation points so that if they are destroyed,
//then the province will be split into different sections. If no such cities
//exist then it prints none. This function iterates throug the cities to delete
//and sends them to an auxilary function
void articulationPoints(Province * p){
  list<City*> currCityList = p -> getCityList();
  list<City*> artPoints;
  bool isArtPoint;
  City* currCity = p -> getCapital();
  list<City*>::iterator cityItr = currCityList.begin();

  while(cityItr != currCityList.end()){
    isArtPoint = articulationPointsAux(p, *cityItr);
    if(isArtPoint){
      artPoints.push_back(*cityItr);
    }
    cityItr++;
  }

  if(artPoints.size() > 0){
    list<City*>::iterator artPointItr = artPoints.begin();
    while(artPointItr != artPoints.end()){
      cout << "    " << (*artPointItr) -> getCityName() << endl;
      artPointItr++;
    }
  }

  else{
    cout << "    (None)" << endl;
  }

}

//The method for road upgrading, and use kruskal's algorithm (Minimum spanning tree).
//Use priotity queue, and put road with distance in priority queue.
//Got some help by Sam
void roadUpgrading(Province* p){
  //Use maps to store the two cities and use that to find distance
  map<City*,City*> cityMap;
  //Use vector to store the road for update
  vector<Road*> spanningTree;

  //Use province to get all cities and roads, and iterates them
  list<City*> listOfCities = p -> getCityList();
  list<Road*> listOfRoads = p ->getRoadList();
  list<City*>:: iterator cityIterator =listOfCities.begin();
  list<Road*>:: iterator roadIterator =listOfRoads.begin();

  //Creates a priority queue pq to store vector and weight order of road of the
  //class Road in Province head file , and initializes the queue to be empty
  priority_queue<Road*, vector<Road*>, WeightOrder> PriorityQueue;

  //Use loop to go through eacg city
  while(cityIterator != listOfCities.end()){
    cityMap[*cityIterator]=*cityIterator;
    cityIterator++;
  }
  //Use loop to go through each road and put road in the queue
  while(roadIterator !=listOfRoads.end() ){
    PriorityQueue.push(*roadIterator);
    roadIterator++;
  }

  //Use loop to find what road need add to the vector
  while(spanningTree.size()<listOfCities.size()-1){
    //get the top element
    Road* road=PriorityQueue.top();
    //then delete
    PriorityQueue.pop();

    //Get first and second element from city
    City* first = road->getCity2();
    City* second = road->getCity1();

    //check if the first element is not equal the first element in map
    while(first != cityMap[first]){
      first = cityMap[first];
    }
    //check if the second element is not equal the second element in map
    while(second != cityMap[second]){
      second =cityMap[second];
    }
    //if they are not equal, change the second element become first element,
    //and  put road in to vector
    if (first != second){
      cityMap[second] = first;
      spanningTree.push_back(road);
    }
  }
  //display information with vector
  for (int count = 0; count < spanningTree.size(); count++ ) {
    cout << "    " << spanningTree[count] -> getCity2()-> getCityName() << " to " << spanningTree[count] -> getCity1() -> getCityName() << endl;
  }
}

//Takes in the file input and stores them into provinces, cities and roads.
//Then calls a breadth first search method and prints out the order along with
//the adjacent cities, their distance and if they are connected by a bride or not.
//Then calls isolatedCities method and articulationPoints method.
void readAndPrint(){
  Province * p;
    p = new Province();
    int numOfCities;
    int numOfRoads;
    City * c;

    cin >> numOfCities >> numOfRoads;

    for(int i = 0; i < numOfCities; i++){
      string cityName;
      cin >> cityName;
      if(i == 0){
        City * c = new City(cityName, true);
        p -> setCapital(c);
        p -> addCity(c);
      }
      else{
        City * c = new City(cityName, false);
        p -> addCity(c);
      }
    }

    for(int i = 0; i < numOfRoads;i++){
      string road1;
      string road2;
      string bridge;
      bool hasBridge = false;
      int distance;

      cin >> road1 >> road2 >> bridge >> distance;

      if(bridge == "B"){
        hasBridge = true;
      }
      City * city1 = p -> findCity(road1);
      City * city2 = p -> findCity(road2);
      Road * r = new Road(city1, city2, hasBridge, distance);
      p -> addRoad(r);
      city1 -> addRoadToCity(r);
      city2 -> addRoadToCity(r);
    }
    int listSize = p -> getNumOfCities();
    list<City*> BFSCityList = breadthFirstSearch(p);

    list<City *>::iterator it;

    for(it = BFSCityList.begin(); it != BFSCityList.end(); it++){
      City * currCity = * it;
      cout << currCity -> getCityName() << endl;

      list<Road *> roadList = currCity -> getCityRoadList();
      list<Road *>::iterator roadIt;
      for (roadIt = roadList.begin(); roadIt != roadList.end(); roadIt++){
        Road * r = * roadIt;
        City * city1 = r -> getCity1();
        City * city2 = r -> getCity2();
        int distance = r -> getDistance();

        if((city1 -> getCityName()).compare(currCity -> getCityName()) == 0) {
          cout << "\t" << city2 -> getCityName() << " " << distance << " mi ";
        }
        else if((city2 -> getCityName()).compare(currCity -> getCityName()) == 0){
          cout << "\t" << city1 -> getCityName() << " " << distance << " mi ";
        }
        if(r -> getIsBridge()){
          cout << "via bridge";
        }
        cout << endl;
      }
    }

    cout<<"\nThe road upgrading goal can be achieved at minimal cost by upgrading:"<<endl;
    roadUpgrading(p);
    cout << endl;
    isolatedCities(p);
    cout << "\nObliterating any of the following would result in the province becoming disconnected: " << endl;
    articulationPoints(p);

    cout << "\n\n------------------------------------------------------------------";
}

int main()
{

  while(true){
    char c;
    cin >> c;
    if(cin.eof()){
        break;
      }
      else{
        cin.unget();
        cout << "The input data is:" << endl << endl;
        readAndPrint();
        cout << endl << endl;
      }
  }

}
