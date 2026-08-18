#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "Point.h"
#include <string>

struct Telemetry {

    Point position;

    double speed;
    double battery;
    double distance;
    double temperature;
    double acceleration;

    std::string status;
};

#endif