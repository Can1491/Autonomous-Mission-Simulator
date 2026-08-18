#ifndef AUTONOMOUS_VEHICLE_H
#define AUTONOMOUS_VEHICLE_H

#include "Point.h"
#include "Telemetry.h"

#include <string>
#include <vector>

class AutonomousVehicle {

private:

    Point position;

    double speed;
    double battery;
    double totalDistance;

    double temperature;
    double acceleration;

    std::string status;

    std::vector<Telemetry> telemetryLog;

    void updateTelemetry();

public:

    AutonomousVehicle(Point start);

    void moveTo(Point newPosition);

    void stop();

    Point getPosition() const;

    double getSpeed() const;

    double getBattery() const;

    double getDistance() const;

    double getTemperature() const;

    double getAcceleration() const;

    std::string getStatus() const;

    void printTelemetry() const;

    void printTelemetryHistory() const;

    void saveTelemetryToFile() const;
};

#endif