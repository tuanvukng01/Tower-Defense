#include "path.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// Returns the success status of the last path reading operation.
bool path::readingSuccessfull(){
	return readingSuccess_;
}

// Adds a waypoint to the path, updating both the waypoint queue and the list of waypoints.
// Parameters:
//   - point: The 2D vector representing the waypoint to be added.
void path::addWaypoint(const sf::Vector2f& point) {
    waypoints_.push(point);
	wayPoints.push_back(point);
}

// Retrieves a copy of the waypoint queue.
// Returns:
//   A queue containing 2D vectors representing the waypoints in the path.
std::queue<sf::Vector2f> path::getWaypoints() const {
    return waypoints_;
}

const float path::width = 60.f;
// Creates unbuildable areas along the path based on waypoints and a specified width (defined above).
void path::makeUnBuildablePath()
{
	sf::FloatRect partofStreet;

	for (size_t i = 0; i < wayPoints.size() - 1; ++i)
	{
		sf::Vector2f vector;

		vector.x = wayPoints[i + 1].x - wayPoints[i].x;
		vector.y = wayPoints[i + 1].y - wayPoints[i].y;

		if ((vector.x >= 0.f) && (vector.y >= 0.f))
		{
			partofStreet.left = wayPoints[i].x - width / 2;
			partofStreet.top = wayPoints[i].y - width / 2;
			partofStreet.width = vector.x + width;
			partofStreet.height = vector.y + width;
		}
		else if ((vector.x < 0.f) || (vector.y < 0))
		{
			partofStreet.left = wayPoints[i + 1].x - width / 2;
			partofStreet.top = wayPoints[i + 1].y - width / 2;
			partofStreet.width = fabs(vector.x) + width;
			partofStreet.height = fabs(vector.y) + width;
		}

		unBuildable.push_back(partofStreet);
	}
	//wayPoints.clear(); // Commented out to preserve waypoints for potential future use.
}

// Reads path data from a file, populating the path's waypoints and updating the success status.
void path::readPath(){
	 std::ifstream file(src_);

    if(file.rdstate() & (file.failbit | file.badbit)){ // Checks for file opening failure
        readingSuccess_ = false;
        return;
    } 

    std::string line;

    std::getline(file,line); //disregards first line which is the formatting example

    while (std::getline(file,line))
    {
        
        char comma, oBrac, cBrac;
		sf::Vector2f coords;
		std::vector<sf::Vector2f> vec;

        std::istringstream iss(line);
	
		iss >> oBrac >> coords.x >> comma >> coords.y >> cBrac; //first entry with no comma before
        vec.push_back(coords);

		if (iss.fail() || iss.bad()){ //failure
            readingSuccess_ = false;
            return;
        }
     
	 	while (iss >> comma >> oBrac >> coords.x >> comma >> coords.y >> cBrac)
		{
			vec.push_back(coords);
		}
		

        if (iss.fail() && !iss.eof()) { // failure
            readingSuccess_ = false;
            return;
        }
        
		paths_.push_back(vec);
        readingSuccess_ = true;
    }
}