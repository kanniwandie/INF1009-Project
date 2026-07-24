/**
 * @file UserInputParser.h
 * @brief Adapts menu input into the parser layer for passenger and shuttle data.
 * @author Melia Kek Xin Hui
 */
#ifndef USER_INPUT_PARSER_H
#define USER_INPUT_PARSER_H

#include <string>
using namespace std;

class PassengerList;
class ShuttleList;

/**
 * @brief Converts user-entered menu tokens into structured passenger or shuttle records.
 * @author Melia Kek Xin Hui
 */
class UserInputParser {
public:
    bool parsePassengerInput(const string& rawInput, PassengerList& passengers, ShuttleList& shuttles) const;
    bool parseShuttleInput(const string& rawInput, PassengerList& passengers, ShuttleList& shuttles) const;
};

#endif
