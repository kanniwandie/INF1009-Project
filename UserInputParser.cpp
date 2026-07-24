/**
 * @file UserInputParser.cpp
 * @brief Implements user input parsing for passenger and shuttle data entry.
 * @author Melia Kek Xin Hui
 */

#include "UserInputParser.h"
#include "FileLoader.h"
#include "Passenger.h"
#include "ShuttleVehicle.h"

bool UserInputParser::parsePassengerInput(const string& rawInput, PassengerList& passengers, ShuttleList& shuttles) const {
    PassengerParser parser;
    return parser.parse(rawInput, passengers, shuttles);
}

bool UserInputParser::parseShuttleInput(const string& rawInput, PassengerList& passengers, ShuttleList& shuttles) const {
    ShuttleParser parser;
    return parser.parse(rawInput, passengers, shuttles);
}
