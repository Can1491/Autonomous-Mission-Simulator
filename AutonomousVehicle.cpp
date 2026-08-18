#include "include/AutonomousVehicle.h"

#include <iostream>
#include <iomanip>
#include <fstream>

AutonomousVehicle::AutonomousVehicle(Point start)
    : position(start),
      speed(0.0),
      battery(100.0),
      totalDistance(0.0),
      temperature(25.0),
      acceleration(0.0),
      status("READY") {

    updateTelemetry();
}

void AutonomousVehicle::updateTelemetry() {

    Telemetry data;

    data.position = position;
    data.speed = speed;
    data.battery = battery;
    data.distance = totalDistance;
    data.temperature = temperature;
    data.acceleration = acceleration;
    data.status = status;

    telemetryLog.push_back(data);
}

void AutonomousVehicle::moveTo(Point newPosition) {

    position = newPosition;

    speed = 40.0;
    acceleration = 2.5;

    totalDistance += 1.0;

    battery -= 2.0;

    if (battery < 0.0) {
        battery = 0.0;
    }

    temperature += 0.3;

    status = "ACTIVE";

    updateTelemetry();
}

void AutonomousVehicle::stop() {

    speed = 0.0;
    acceleration = 0.0;

    status = "COMPLETED";

    updateTelemetry();
}

Point AutonomousVehicle::getPosition() const {
    return position;
}

double AutonomousVehicle::getSpeed() const {
    return speed;
}

double AutonomousVehicle::getBattery() const {
    return battery;
}

double AutonomousVehicle::getDistance() const {
    return totalDistance;
}

double AutonomousVehicle::getTemperature() const {
    return temperature;
}

double AutonomousVehicle::getAcceleration() const {
    return acceleration;
}

std::string AutonomousVehicle::getStatus() const {
    return status;
}

void AutonomousVehicle::printTelemetry() const {

    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "             TELEMETRI\n";
    std::cout << "========================================\n";

    std::cout << std::fixed << std::setprecision(1);

    std::cout << "Durum       : "
              << status << std::endl;

    std::cout << "Konum       : ("
              << position.x
              << ", "
              << position.y
              << ")" << std::endl;

    std::cout << "Hiz         : "
              << speed
              << " km/h" << std::endl;

    std::cout << "Batarya     : "
              << battery
              << "%" << std::endl;

    std::cout << "Mesafe      : "
              << totalDistance
              << " birim" << std::endl;

    std::cout << "Sicaklik    : "
              << temperature
              << " C" << std::endl;

    std::cout << "Ivme        : "
              << acceleration
              << " m/s^2" << std::endl;

    std::cout << "========================================\n";
}

void AutonomousVehicle::printTelemetryHistory() const {

    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "          TELEMETRI GECMISI\n";
    std::cout << "========================================\n";

    for (std::size_t i = 0; i < telemetryLog.size(); ++i) {

        const Telemetry& data = telemetryLog[i];

        std::cout << std::fixed << std::setprecision(1);

        std::cout << "["
                  << i + 1
                  << "] ";

        std::cout << "Konum: ("
                  << data.position.x
                  << ", "
                  << data.position.y
                  << ") | ";

        std::cout << "Hiz: "
                  << data.speed
                  << " km/h | ";

        std::cout << "Batarya: "
                  << data.battery
                  << "% | ";

        std::cout << "Mesafe: "
                  << data.distance
                  << " | ";

        std::cout << "Sicaklik: "
                  << data.temperature
                  << " C | ";

        std::cout << "Ivme: "
                  << data.acceleration
                  << " m/s^2 | ";

        std::cout << "Durum: "
                  << data.status
                  << std::endl;
    }

    std::cout << "========================================\n";
}

void AutonomousVehicle::saveTelemetryToFile() const {

    std::ofstream file("telemetry.log");

    if (!file.is_open()) {

        std::cout << "\nTelemetry dosyasi olusturulamadi!\n";

        return;
    }

    file << "========================================\n";
    file << "          TELEMETRY LOG\n";
    file << "========================================\n\n";

    for (std::size_t i = 0; i < telemetryLog.size(); ++i) {

        const Telemetry& data = telemetryLog[i];

        file << std::fixed << std::setprecision(1);

        file << "["
             << i + 1
             << "] ";

        file << "Konum: ("
             << data.position.x
             << ", "
             << data.position.y
             << ") | ";

        file << "Hiz: "
             << data.speed
             << " km/h | ";

        file << "Batarya: "
             << data.battery
             << "% | ";

        file << "Mesafe: "
             << data.distance
             << " | ";

        file << "Sicaklik: "
             << data.temperature
             << " C | ";

        file << "Ivme: "
             << data.acceleration
             << " m/s^2 | ";

        file << "Durum: "
             << data.status
             << "\n";
    }

    file << "\n========================================\n";

    file.close();

    std::cout << "\nTelemetry verileri telemetry.log dosyasina kaydedildi.\n";
}