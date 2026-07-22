#ifndef USER_INPUT_PARSER_H
#define USER_INPUT_PARSER_H

#include <string>
using namespace std;

class PassengerList;
class ShuttleList;

class UserInputParser {
public:
    bool parsePassengerInput(const string& rawInput, PassengerList& passengers, ShuttleList& shuttles) const;
    bool parseShuttleInput(const string& rawInput, PassengerList& passengers, ShuttleList& shuttles) const;
};

#endif
