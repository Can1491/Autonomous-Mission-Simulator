#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// ============================================================
// NOKTA / KOORDİNAT
// ============================================================

struct Point {
    int x;
    int y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// ============================================================
// TELEMETRİ VERİSİ
// ============================================================

struct Telemetry {
    Point position;
    double speed;
    double battery;
    double distance;
    double temperature;
    double acceleration;
    string status;
};

// ============================================================
// OTONOM ARAÇ
// ============================================================

class AutonomousVehicle {

private:

    Point position;

    double speed;
    double battery;
    double totalDistance;

    double temperature;
    double acceleration;

    string status;

    vector<Telemetry> telemetryLog;

public:

    AutonomousVehicle(Point start) {

        position = start;

        speed = 0.0;
        battery = 100.0;
        totalDistance = 0.0;

        temperature = 25.0;
        acceleration = 0.0;

        status = "READY";

        updateTelemetry();
    }

    // --------------------------------------------------------
    // TELEMETRİ KAYDET
    // --------------------------------------------------------

    void updateTelemetry() {

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

    // --------------------------------------------------------
    // ARACI HAREKET ETTİR
    // --------------------------------------------------------

    void moveTo(Point newPosition) {

        position = newPosition;

        speed = 40.0;

        acceleration = 2.5;

        totalDistance += 1.0;

        battery -= 2.0;

        if (battery < 0.0) {
            battery = 0.0;
        }

        // Basit sıcaklık simülasyonu
        temperature += 0.3;

        status = "ACTIVE";

        updateTelemetry();
    }

    // --------------------------------------------------------
    // ARACI DURDUR
    // --------------------------------------------------------

    void stop() {

        speed = 0.0;
        acceleration = 0.0;

        status = "COMPLETED";

        updateTelemetry();
    }

    // --------------------------------------------------------
    // GETTERLAR
    // --------------------------------------------------------

    Point getPosition() const {
        return position;
    }

    double getSpeed() const {
        return speed;
    }

    double getBattery() const {
        return battery;
    }

    double getDistance() const {
        return totalDistance;
    }

    double getTemperature() const {
        return temperature;
    }

    double getAcceleration() const {
        return acceleration;
    }

    string getStatus() const {
        return status;
    }

    // --------------------------------------------------------
    // ANLIK TELEMETRİ
    // --------------------------------------------------------

    void printTelemetry() const {

        cout << "\n";
        cout << "========================================\n";
        cout << "             TELEMETRI\n";
        cout << "========================================\n";

        cout << fixed << setprecision(1);

        cout << "Durum       : "
             << status << endl;

        cout << "Konum       : ("
             << position.x
             << ", "
             << position.y
             << ")" << endl;

        cout << "Hiz         : "
             << speed
             << " km/h" << endl;

        cout << "Batarya     : "
             << battery
             << "%" << endl;

        cout << "Mesafe      : "
             << totalDistance
             << " birim" << endl;

        cout << "Sicaklik    : "
             << temperature
             << " C" << endl;

        cout << "Ivme        : "
             << acceleration
             << " m/s^2" << endl;

        cout << "========================================\n";
    }

    // --------------------------------------------------------
    // TELEMETRİ GEÇMİŞİ
    // --------------------------------------------------------

    void printTelemetryHistory() const {

        cout << "\n";
        cout << "========================================\n";
        cout << "          TELEMETRI GECMISI\n";
        cout << "========================================\n";

        for (size_t i = 0; i < telemetryLog.size(); i++) {

            const Telemetry& t = telemetryLog[i];

            cout << fixed << setprecision(1);

            cout << "[" << i + 1 << "] ";

            cout << "Konum: ("
                 << t.position.x
                 << ", "
                 << t.position.y
                 << ") | ";

            cout << "Hiz: "
                 << t.speed
                 << " km/h | ";

            cout << "Batarya: "
                 << t.battery
                 << "% | ";

            cout << "Mesafe: "
                 << t.distance
                 << " | ";

            cout << "Sicaklik: "
                 << t.temperature
                 << " C | ";

            cout << "Ivme: "
                 << t.acceleration
                 << " m/s^2 | ";

            cout << "Durum: "
                 << t.status
                 << endl;
        }
    }

    // --------------------------------------------------------
    // TELEMETRİYİ DOSYAYA KAYDET
    // --------------------------------------------------------

    void saveTelemetryToFile() const {

        ofstream file("telemetry.log");

        if (!file.is_open()) {

            cout << "\nTelemetry dosyasi olusturulamadi!\n";

            return;
        }

        file << "AUTONOMOUS MISSION SIMULATOR\n";
        file << "TELEMETRY LOG\n";
        file << "========================================\n\n";

        for (size_t i = 0; i < telemetryLog.size(); i++) {

            const Telemetry& t = telemetryLog[i];

            file << fixed << setprecision(1);

            file << "Step: "
                 << i + 1
                 << "\n";

            file << "Position: ("
                 << t.position.x
                 << ", "
                 << t.position.y
                 << ")\n";

            file << "Speed: "
                 << t.speed
                 << " km/h\n";

            file << "Battery: "
                 << t.battery
                 << "%\n";

            file << "Distance: "
                 << t.distance
                 << " units\n";

            file << "Temperature: "
                 << t.temperature
                 << " C\n";

            file << "Acceleration: "
                 << t.acceleration
                 << " m/s^2\n";

            file << "Status: "
                 << t.status
                 << "\n";

            file << "----------------------------------------\n";
        }

        file.close();

        cout << "\nTelemetry verileri "
             << "telemetry.log dosyasina kaydedildi.\n";
    }
};

// ============================================================
// HARİTA AYARLARI
// ============================================================

const int WIDTH = 10;
const int HEIGHT = 10;

// ============================================================
// HARİTA OLUŞTUR
// ============================================================

vector<vector<int>> createMap() {

    vector<vector<int>> grid(
        HEIGHT,
        vector<int>(WIDTH, 0)
    );

    // Engel grubu 1
    grid[2][2] = 1;
    grid[2][3] = 1;
    grid[2][4] = 1;

    // Engel grubu 2
    grid[5][5] = 1;
    grid[6][5] = 1;
    grid[7][5] = 1;

    return grid;
}

// ============================================================
// HARİTA YAZDIR
// ============================================================

void printMap(
    const vector<vector<int>>& grid,
    Point start,
    Point goal,
    Point vehicle,
    const vector<Point>& path = {}
) {

    vector<vector<char>> display(
        HEIGHT,
        vector<char>(WIDTH, '.')
    );

    // Engeller
    for (int y = 0; y < HEIGHT; y++) {

        for (int x = 0; x < WIDTH; x++) {

            if (grid[y][x] == 1) {

                display[y][x] = '#';
            }
        }
    }

    // Rota
    for (const Point& p : path) {

        if (!(p == start) && !(p == goal)) {

            display[p.y][p.x] = '*';
        }
    }

    display[start.y][start.x] = 'S';

    display[goal.y][goal.x] = 'G';

    display[vehicle.y][vehicle.x] = 'A';

    cout << "\n";

    for (int y = 0; y < HEIGHT; y++) {

        for (int x = 0; x < WIDTH; x++) {

            cout << display[y][x] << " ";
        }

        cout << endl;
    }
}

// ============================================================
// GEÇERLİ HÜCRE KONTROLÜ
// ============================================================

bool isValid(
    int x,
    int y,
    const vector<vector<int>>& grid
) {

    if (x < 0 || x >= WIDTH) {

        return false;
    }

    if (y < 0 || y >= HEIGHT) {

        return false;
    }

    if (grid[y][x] == 1) {

        return false;
    }

    return true;
}

// ============================================================
// BFS ROTA HESAPLAMA
// ============================================================

vector<Point> findPath(
    const vector<vector<int>>& grid,
    Point start,
    Point goal
) {

    queue<Point> q;

    vector<vector<bool>> visited(
        HEIGHT,
        vector<bool>(WIDTH, false)
    );

    vector<vector<Point>> parent(
        HEIGHT,
        vector<Point>(
            WIDTH,
            {-1, -1}
        )
    );

    q.push(start);

    visited[start.y][start.x] = true;

    int dx[] = {
        1,
        -1,
        0,
        0
    };

    int dy[] = {
        0,
        0,
        1,
        -1
    };

    while (!q.empty()) {

        Point current = q.front();

        q.pop();

        if (current == goal) {

            break;
        }

        for (int i = 0; i < 4; i++) {

            int nx =
                current.x + dx[i];

            int ny =
                current.y + dy[i];

            if (!isValid(nx, ny, grid)) {

                continue;
            }

            if (visited[ny][nx]) {

                continue;
            }

            visited[ny][nx] = true;

            parent[ny][nx] = current;

            q.push({nx, ny});
        }
    }

    // Rota bulunamadı
    if (!visited[goal.y][goal.x]) {

        return {};
    }

    vector<Point> path;

    Point current = goal;

    while (!(current == start)) {

        path.push_back(current);

        current =
            parent[current.y][current.x];
    }

    path.push_back(start);

    // Başlangıçtan hedefe doğru sırala
    reverse(
        path.begin(),
        path.end()
    );

    return path;
}

// ============================================================
// ROTA KOORDİNATLARINI YAZDIR
// ============================================================

void printPath(
    const vector<Point>& path
) {

    cout << "\nRota koordinatlari:\n";

    for (const Point& p : path) {

        cout << "("
             << p.x
             << ", "
             << p.y
             << ") ";
    }

    cout << "\n";
}

// ============================================================
// GÖREV ÖZETİ
// ============================================================

void printMissionSummary(
    const AutonomousVehicle& vehicle,
    Point start,
    Point goal
) {

    cout << "\n";
    cout << "========================================\n";
    cout << "              GOREV OZETI\n";
    cout << "========================================\n";

    cout << "Baslangic     : ("
         << start.x
         << ", "
         << start.y
         << ")\n";

    cout << "Hedef         : ("
         << goal.x
         << ", "
         << goal.y
         << ")\n";

    cout << fixed << setprecision(1);

    cout << "Toplam Mesafe : "
         << vehicle.getDistance()
         << " birim\n";

    cout << "Kalan Batarya : "
         << vehicle.getBattery()
         << "%\n";

    cout << "Son Hiz       : "
         << vehicle.getSpeed()
         << " km/h\n";

    cout << "Sicaklik      : "
         << vehicle.getTemperature()
         << " C\n";

    cout << "Ivme          : "
         << vehicle.getAcceleration()
         << " m/s^2\n";

    cout << "Durum         : "
         << vehicle.getStatus()
         << "\n";

    cout << "========================================\n";
}

// ============================================================
// MAIN
// ============================================================

int main() {

    cout << "========================================\n";
    cout << "       AUTONOMOUS MISSION SIMULATOR\n";
    cout << "========================================\n";

    // --------------------------------------------------------
    // GÖREV TANIMI
    // --------------------------------------------------------

    Point start = {0, 0};

    Point goal = {9, 9};

    // --------------------------------------------------------
    // HARİTA
    // --------------------------------------------------------

    vector<vector<int>> grid =
        createMap();

    AutonomousVehicle vehicle(start);

    cout << "\nBaslangic konumu: ("
         << start.x
         << ", "
         << start.y
         << ")\n";

    cout << "Hedef konumu: ("
         << goal.x
         << ", "
         << goal.y
         << ")\n";

    cout << "\nHarita olusturuluyor...\n";

    printMap(
        grid,
        start,
        goal,
        vehicle.getPosition()
    );

    // --------------------------------------------------------
    // ROTA HESAPLAMA
    // --------------------------------------------------------

    cout << "\nRota hesaplaniyor...\n";

    vector<Point> path =
        findPath(
            grid,
            start,
            goal
        );

    if (path.empty()) {

        cout << "\nHATA!\n";
        cout << "Hedefe ulasan rota bulunamadi.\n";

        return 1;
    }

    cout << "\nRota bulundu!\n";

    cout << "Toplam adim: "
         << path.size() - 1
         << "\n";

    printMap(
        grid,
        start,
        goal,
        start,
        path
    );

    printPath(path);

    cout << "\nGOREV BASARIYLA PLANLANDI!\n";

    // --------------------------------------------------------
    // GÖREV BAŞLANGICI
    // --------------------------------------------------------

    cout << "\n";
    cout << "========================================\n";
    cout << "            GOREV BASLIYOR\n";
    cout << "========================================\n";

    // --------------------------------------------------------
    // ARAÇ HAREKETİ
    // --------------------------------------------------------

    for (size_t i = 1; i < path.size(); i++) {

        vehicle.moveTo(path[i]);

        cout << "\n----------------------------------------\n";

        cout << "ADIM "
             << i
             << " / "
             << path.size() - 1
             << "\n";

        cout << "ARAC DURUMU: "
             << vehicle.getStatus()
             << "\n";

        cout << "Konum    : ("
             << vehicle.getPosition().x
             << ", "
             << vehicle.getPosition().y
             << ")\n";

        cout << fixed << setprecision(1);

        cout << "Hiz      : "
             << vehicle.getSpeed()
             << " km/h\n";

        cout << "Batarya  : "
             << vehicle.getBattery()
             << "%\n";

        cout << "Mesafe   : "
             << vehicle.getDistance()
             << " birim\n";

        cout << "Sicaklik : "
             << vehicle.getTemperature()
             << " C\n";

        cout << "Ivme     : "
             << vehicle.getAcceleration()
             << " m/s^2\n";

        // ----------------------------------------------------
        // BATARYA KONTROLÜ
        // ----------------------------------------------------

        if (vehicle.getBattery() <= 20.0) {

            cout << "\n";
            cout << "!!! UYARI: BATARYA DUSUK !!!\n";
        }
    }

    // --------------------------------------------------------
    // GÖREV TAMAMLAMA
    // --------------------------------------------------------

    vehicle.stop();

    cout << "\n";
    cout << "========================================\n";
    cout << "           GOREV TAMAMLANDI!\n";
    cout << "========================================\n";

    cout << "Hedefe basariyla ulasildi.\n";

    // --------------------------------------------------------
    // SON TELEMETRİ
    // --------------------------------------------------------

    vehicle.printTelemetry();

    // --------------------------------------------------------
    // TELEMETRİ GEÇMİŞİ
    // --------------------------------------------------------

    vehicle.printTelemetryHistory();

    // --------------------------------------------------------
    // TELEMETRİ DOSYASI
    // --------------------------------------------------------

    vehicle.saveTelemetryToFile();

    // --------------------------------------------------------
    // GÖREV ÖZETİ
    // --------------------------------------------------------

    printMissionSummary(
        vehicle,
        start,
        goal
    );

    cout << "\n";
    cout << "Simulator tamamlandi.\n";

    return 0;
}