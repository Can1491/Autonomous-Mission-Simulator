#include "include/AutonomousVehicle.h"
#include "include/MissionPlanner.h"

#include <iostream>
#include <iomanip>
#include <vector>

int main() {

    std::cout << "========================================\n";
    std::cout << "       AUTONOMOUS MISSION SIMULATOR\n";
    std::cout << "========================================\n\n";

    Point start(0, 0);
    Point goal(9, 9);

    std::cout << "Baslangic konumu: ("
              << start.x << ", "
              << start.y << ")\n";

    std::cout << "Hedef konumu: ("
              << goal.x << ", "
              << goal.y << ")\n\n";

    // --------------------------------------------------
    // MISSION PLANNER
    // --------------------------------------------------

    std::cout << "Harita olusturuluyor...\n\n";

    MissionPlanner planner(10, 10);

    // Haritadaki engeller

    planner.addObstacle(Point(2, 2));
    planner.addObstacle(Point(3, 2));
    planner.addObstacle(Point(4, 2));

    planner.addObstacle(Point(5, 5));
    planner.addObstacle(Point(5, 6));
    planner.addObstacle(Point(5, 7));

    planner.printMap(start, goal);

    // --------------------------------------------------
    // PATH PLANNING
    // --------------------------------------------------

    std::cout << "\nRota hesaplaniyor...\n\n";

    std::vector<Point> path =
        planner.findPath(start, goal);

    if (path.empty()) {

        std::cout << "HATA: Hedefe ulasan rota bulunamadi!\n";

        return 1;
    }

    std::cout << "Rota bulundu!\n";

    std::cout << "Toplam adim: "
              << path.size() - 1
              << "\n\n";

    planner.printPath(path, start, goal);

    // --------------------------------------------------
    // PATH COORDINATES
    // --------------------------------------------------

    std::cout << "\nRota koordinatlari:\n";

    for (const Point& point : path) {

        std::cout << "("
                  << point.x
                  << ", "
                  << point.y
                  << ") ";
    }

    std::cout << "\n\n";

    std::cout << "GOREV BASARIYLA PLANLANDI!\n";

    // --------------------------------------------------
    // AUTONOMOUS VEHICLE
    // --------------------------------------------------

    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "            GOREV BASLIYOR\n";
    std::cout << "========================================\n";

    AutonomousVehicle vehicle(start);

    // Başlangıç noktası zaten telemetry'ye kaydedildi.
    // Bu nedenle rotadaki ilk noktayı atlıyoruz.

    for (std::size_t i = 1; i < path.size(); ++i) {

        vehicle.moveTo(path[i]);

        std::cout << "\n";
        std::cout << "----------------------------------------\n";

        std::cout << "ADIM "
                  << i
                  << " / "
                  << path.size() - 1
                  << "\n";

        std::cout << "ARAC DURUMU: "
                  << vehicle.getStatus()
                  << "\n";

        Point position = vehicle.getPosition();

        std::cout << "Konum    : ("
                  << position.x
                  << ", "
                  << position.y
                  << ")\n";

        std::cout << std::fixed
                  << std::setprecision(1);

        std::cout << "Hiz      : "
                  << vehicle.getSpeed()
                  << " km/h\n";

        std::cout << "Batarya  : "
                  << vehicle.getBattery()
                  << "%\n";

        std::cout << "Mesafe   : "
                  << vehicle.getDistance()
                  << " birim\n";

        std::cout << "Sicaklik : "
                  << vehicle.getTemperature()
                  << " C\n";

        std::cout << "Ivme     : "
                  << vehicle.getAcceleration()
                  << " m/s^2\n";
    }

    // --------------------------------------------------
    // MISSION COMPLETE
    // --------------------------------------------------

    vehicle.stop();

    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "           GOREV TAMAMLANDI!\n";
    std::cout << "========================================\n";

    std::cout << "Hedefe basariyla ulasildi.\n";

    // --------------------------------------------------
    // FINAL TELEMETRY
    // --------------------------------------------------

    vehicle.printTelemetry();

    // --------------------------------------------------
    // TELEMETRY HISTORY
    // --------------------------------------------------

    vehicle.printTelemetryHistory();

    // --------------------------------------------------
    // SAVE TELEMETRY
    // --------------------------------------------------

    vehicle.saveTelemetryToFile();

    // --------------------------------------------------
    // MISSION SUMMARY
    // --------------------------------------------------

    Point finalPosition = vehicle.getPosition();

    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "              GOREV OZETI\n";
    std::cout << "========================================\n";

    std::cout << "Baslangic     : ("
              << start.x
              << ", "
              << start.y
              << ")\n";

    std::cout << "Hedef         : ("
              << goal.x
              << ", "
              << goal.y
              << ")\n";

    std::cout << "Toplam Mesafe : "
              << vehicle.getDistance()
              << " birim\n";

    std::cout << "Kalan Batarya : "
              << vehicle.getBattery()
              << "%\n";

    std::cout << "Son Hiz       : "
              << vehicle.getSpeed()
              << " km/h\n";

    std::cout << "Sicaklik      : "
              << vehicle.getTemperature()
              << " C\n";

    std::cout << "Ivme          : "
              << vehicle.getAcceleration()
              << " m/s^2\n";

    std::cout << "Durum         : "
              << vehicle.getStatus()
              << "\n";

    std::cout << "Son Konum     : ("
              << finalPosition.x
              << ", "
              << finalPosition.y
              << ")\n";

    std::cout << "========================================\n";

    std::cout << "\nSimulator tamamlandi.\n";

    return 0;
}