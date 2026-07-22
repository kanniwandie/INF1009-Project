#ifndef DESTINATION_H
#define DESTINATION_H

#include <string>
using namespace std;

// Author: [Your Name]
class Destination {
private:
    string value;

public:
    Destination(const string& value = "");

    void setValue(const string& newValue);
    bool isValid() const;
    string toString() const;

    operator string() const;
};

#endif
