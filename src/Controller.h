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
    Controller(Graph graph1);

    vector<Stop> stopDB; //!< Airports data base
    vector<Line> linesDB;
    Graph graph;
public:
    vector<Stop> readEachLineFile0(string code);
    vector<Stop> readEachLineFile1(string code);
    // Constructors
    /** @brief  Default constructor.*/
    Controller();
    /** @brief  Default destructor.*/
    ~Controller();
    // Gets
    /** @brief  Returns the Airports data base.*/
    vector<Stop> getStops();

    /** @brief  Returns the Airports data base.*/
    vector<Line> getLines();


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

    string getDirections(Stop origin, Stop destination);
};

#endif //PROJ1_CONTROLLER_H
