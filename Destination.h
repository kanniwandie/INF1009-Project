/**
 * @file Destination.h
 * @brief Declares the destination value object used by entities.
 * @author Chen Xiyuan
 */
#ifndef DESTINATION_H
#define DESTINATION_H

#include <string>
using namespace std;

/**
 * @brief Value object that represents a destination name and its validation rules.
 * @author Chen Xiyuan
 */
class Destination {
private:
    string value;

public:
    Destination(const string& initialValue = "");

    void setValue(const string& newValue);
    bool isValid() const;
    string toString() const;

    operator string() const;
};

#endif
