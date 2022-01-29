// ****************************************************************************************************
// ******************************************* CONTROLLER_H__ *****************************************
// ****************************************************************************************************

#ifndef PROJ1_CONTROLLER_H
#define PROJ1_CONTROLLER_H


#include "Line.h"
#include "Graph.h"
#include <vector>
#include <string>

class Controller{
private:
    vector<Stop> stopDB; //!< Airports data base
    vector<Line> linesDB;
    Graph graph;
    string userName;
    int maxWalingDistance=10000;
    int walkingFactor;
public:
    // Constructors
    /** @brief  Default constructor.*/
    Controller();
    /** @brief  Default destructor.*/
    ~Controller();
    Graph& getGraph() {return graph;}
    // Gets
    /** @brief  Returns the Airports data base.*/
    vector<Stop>& getStops();

    string getUsername();

    /** @brief  Returns the Airports data base.*/
    vector<Line> getLines();
    void readStops();
    void readLines();
    bool readUserData();
    void extractStopsFromLines();
    int getIndexStop(string code);
    vector<Stop>& getStopDB();


    // Finds
    /** @brief  Returns an Airport based on \p ID.*/
    Stop& findStop(string code);

    Line& findLine(string code);


    // Exists
    /** @brief  Checks for the existence of an Airport based on \p ID.*/
    bool existsStop(string code);


    // Adds
    /** @brief  Adds a new Passenger created with \p name.*/
    void addStop(string code, string name, string zone, float latitude, float longitude);


    // Removes
    /** @brief  Removes an Airport based on \p ID.*/
    bool removeStop(string code);


    // Specified Gets
    /** @brief  Returns the next available flight number (the smallest value not used).*/
    Stop getClosestStop(double lat1, double lon1);


    //Write
    /** @brief  Writes the .txt files upon Save&Quit*/
    void writeFiles();

    void createGraphLines();
    static double haversine(double lat1, double lon1,
                            double lat2, double lon2);

    string getDirections(string origin, string destination, int type = 0);

    void setUsername(string username);
    void setWalkingFac(int walkF);
    void setMaxWalkDist(int maxWD);

    void addEdgesInWalkingDistance();

    vector<int> getStopsNearCoords(double longitude, double latitude, double distance);
};

#endif //PROJ1_CONTROLLER_H
