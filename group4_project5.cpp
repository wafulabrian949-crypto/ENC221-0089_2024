#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <limits>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

// ======================================================
// 1. Basic Geometry Classes
// ======================================================

class Point2D {
public:
    double x, y;

    Point2D(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

    bool operator==(const Point2D& other) const {
        return fabs(x - other.x) < 1e-9 &&
               fabs(y - other.y) < 1e-9;
    }
};

class ContourLine {
public:
    double level;
    vector<Point2D> points;

    ContourLine(double lvl = 0) : level(lvl) {}
};

// ======================================================
// 2. Survey Point Class
// ======================================================

class SurveyPoint3D {
private:
    double x, y, elevation;

public:
    SurveyPoint3D(double x_, double y_, double e_)
        : x(x_), y(y_), elevation(e_) {}

    double getX() const { return x; }
    double getY() const { return y; }
    double getElevation() const { return elevation; }
};

// ======================================================
// 3. GridCell Class
// ======================================================

class GridCell {
private:
    double x, y, elevation;

public:
    GridCell(double x_ = 0, double y_ = 0)
        : x(x_), y(y_), elevation(0) {}

    void setElevation(double e) { elevation = e; }

    double getX() const { return x; }
    double getY() const { return y; }
    double getElevation() const { return elevation; }
};

// ======================================================
// 4. DEM Generator (IDW Interpolation)
// ======================================================

class DEMGenerator {
private:
    vector<SurveyPoint3D> surveyPoints;
    vector<vector<GridCell>> grid;
    int rows, cols;
    double cellSize;

    double interpolateIDW(double x, double y, double power = 2.0) {
        double numerator = 0;
        double denominator = 0;

        for (const auto& pt : surveyPoints) {
            double dx = x - pt.getX();
            double dy = y - pt.getY();
            double distance = sqrt(dx * dx + dy * dy);

            if (distance < 1e-10)
                return pt.getElevation();

            double weight = 1.0 / pow(distance, power);
            numerator += weight * pt.getElevation();
            denominator += weight;
        }

        return numerator / denominator;
    }

public:
    DEMGenerator(const vector<SurveyPoint3D>& pts,
                 int r, int c, double cs)
        : surveyPoints(pts), rows(r), cols(c), cellSize(cs) {

        grid.resize(rows, vector<GridCell>(cols));

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                grid[i][j] = GridCell(j * cellSize,
                                      i * cellSize);
    }

    void generateDEM() {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                grid[i][j].setElevation(
                    interpolateIDW(grid[i][j].getX(),
                                   grid[i][j].getY()));
    }

    vector<vector<GridCell>>& getGrid() {
        return grid;
    }
};

// ======================================================
// 5. Contour Generator (Marching Squares)
// ======================================================

class ContourGenerator {
private:
    const vector<vector<GridCell>>& grid;
    int rows, cols;

    Point2D interpolatePoint(double x1, double y1, double e1,
                             double x2, double y2, double e2,
                             double level) {

        double t = (level - e1) / (e2 - e1);
        t = max(0.0, min(1.0, t));

        return Point2D(
            x1 + t * (x2 - x1),
            y1 + t * (y2 - y1)
        );
    }

    const vector<pair<int, int>>& getEdges(int caseIndex) {
        static const vector<vector<pair<int, int>>> lookup = {
            {}, {{0,3}}, {{0,1}}, {{1,3}},
            {{1,2}}, {{0,2},{1,3}}, {{0,2}}, {{2,3}},
            {{2,3}}, {{0,2}}, {{0,3},{1,2}}, {{1,2}},
            {{1,3}}, {{0,1}}, {{0,3}}, {}
        };
        return lookup[caseIndex];
    }

    Point2D getEdgePoint(int i, int j, int edge, double level) {

        const auto& TL = grid[i][j];
        const auto& TR = grid[i][j+1];
        const auto& BL = grid[i+1][j];
        const auto& BR = grid[i+1][j+1];

        switch(edge) {
        case 0: return interpolatePoint(
            TL.getX(), TL.getY(), TL.getElevation(),
            TR.getX(), TR.getY(), TR.getElevation(),
            level);

        case 1: return interpolatePoint(
            TR.getX(), TR.getY(), TR.getElevation(),
            BR.getX(), BR.getY(), BR.getElevation(),
            level);

        case 2: return interpolatePoint(
            BR.getX(), BR.getY(), BR.getElevation(),
            BL.getX(), BL.getY(), BL.getElevation(),
            level);

        case 3: return interpolatePoint(
            BL.getX(), BL.getY(), BL.getElevation(),
            TL.getX(), TL.getY(), TL.getElevation(),
            level);
        }

        return Point2D();
    }

public:
    ContourGenerator(const vector<vector<GridCell>>& g)
        : grid(g) {
        rows = grid.size();
        cols = grid[0].size();
    }

    vector<ContourLine> generateContours(double interval) {

        vector<ContourLine> contours;

        double minElev = numeric_limits<double>::max();
        double maxElev = numeric_limits<double>::lowest();

        for (const auto& row : grid)
            for (const auto& cell : row) {
                minElev = min(minElev, cell.getElevation());
                maxElev = max(maxElev, cell.getElevation());
            }

        for (double level = minElev;
             level <= maxElev;
             level += interval) {

            ContourLine line(level);

            for (int i = 0; i < rows-1; ++i)
                for (int j = 0; j < cols-1; ++j) {

                    double eTL = grid[i][j].getElevation();
                    double eTR = grid[i][j+1].getElevation();
                    double eBL = grid[i+1][j].getElevation();
                    double eBR = grid[i+1][j+1].getElevation();

                    int caseIndex = 0;
                    if (eTL >= level) caseIndex |= 1;
                    if (eTR >= level) caseIndex |= 2;
                    if (eBR >= level) caseIndex |= 4;
                    if (eBL >= level) caseIndex |= 8;

                    const auto& edges = getEdges(caseIndex);

                    for (const auto& ep : edges) {
                        Point2D p1 = getEdgePoint(i,j,ep.first,level);
                        Point2D p2 = getEdgePoint(i,j,ep.second,level);

                        line.points.push_back(p1);
                        line.points.push_back(p2);
                    }
                }

            if (!line.points.empty())
                contours.push_back(line);
        }

        return contours;
    }

    void exportToCSV(const vector<ContourLine>& contours,
                     const string& filename) {

        ofstream file(filename);

        file << "Level,X,Y\n";

        for (const auto& c : contours)
            for (const auto& p : c.points)
                file << c.level << ","
                     << p.x << ","
                     << p.y << "\n";

        file.close();
    }
};

// ======================================================
// 6. MAIN
// ======================================================

int main() {

    vector<SurveyPoint3D> surveyPoints = {
        {0,0,50}, {0,100,60},
        {100,0,70}, {100,100,80},
        {50,50,120}
    };

    DEMGenerator dem(surveyPoints, 50, 50, 2.0);
    dem.generateDEM();

    ContourGenerator contourGen(dem.getGrid());

    auto contours = contourGen.generateContours(10.0);

    contourGen.exportToCSV(contours, "contours.csv");

    cout << "DEM and Contours generated successfully.\n";

    return 0;
}
