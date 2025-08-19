#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <set>
#include <iomanip>

#include "MyTemplates.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"

using namespace std;

vector<unique_ptr<Point2D>> allPoints2D;
vector<unique_ptr<Point3D>> allPoints3D;
vector<unique_ptr<Line2D>> allLines2D;
vector<unique_ptr<Line3D>> allLines3D;

string currentFilter = "Point2D";  // Default filter
string currentSortCriteria = "x-ordinate";  // Default sort
string currentSortOrder = "ASC";  // Default order

class menuSystem{
private:

public:
  // ~menuSystem() {
  //   safelyDeallocateMemory();
  // }

  void displayMenu(){
  cout << "Student ID: 8066590" << endl;
  cout << "Student Name: Bryan Lim Jun Jie" << endl;
  cout << "-------------------------------" << endl;
  cout << "Welcome to Assignment 3 program!" << endl;
  cout << "\n1)\tRead in data" << endl;
  cout << "2) \tSpecify filtering criteria (current : " << currentFilter << ")" << endl;
  cout << "3) \tSpecify sorting criteria (current : " << currentSortCriteria << ")" << endl;
  cout << "4) \tSpecify sorting order (current : " << currentSortOrder << ")" << endl;
  cout << "5)\tView data" << endl;
  cout << "6)\tStore data" << endl;
  cout << "7)\tExit program" << endl;
  cout << "Please enter choice: ";
  }

  int getUserChoice() {
    int choice;
    cin >>choice;
    return choice;

  }

  bool processMenuChoice(int choice) {
    switch (choice) {
      case 1: readData(); return true;
      case 2:setFilteringCriteria(); return true;
      case 3:setSortingCriteria(); return true;
      case 4:setSortingOrder(); return true;
      case 5:viewData(); return true;
      case 6: storeData(); return true;
      case 7:
        cout << "Thank you for using program" << endl;
        // safelyDeallocateMemory();
        return false;
      default:
        cout << "Please choose a number between 1-7" << endl;
        return false;
    }
  }

  void readData() {
    int count = 0;
    string fileName;
    cout << "\nPlease enter filename: ";
    cin >> fileName;
    cout << "\n";

    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << fileName << "'" << endl;
        return;  // Actually exit on error
    }

    // Clear existing data
    allPoints2D.clear();
    allPoints3D.clear();
    allLines2D.clear();
    allLines3D.clear();

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        try {
            size_t firstComma = line.find(',');
            string type = line.substr(0, firstComma);

            if (type == "Point2D") {
                auto coords = parseCoordinates(line);
                if (coords.size() == 2) {
                    allPoints2D.push_back(unique_ptr<Point2D>(new Point2D(coords[0], coords[1])));
                    count++;
                }
            }
            else if (type == "Point3D") {
                auto coords = parseCoordinates(line);
                if (coords.size() == 3) {
                    allPoints3D.push_back(unique_ptr<Point3D>(new Point3D(coords[0], coords[1], coords[2])));
                    count++;
                }
            }
            else if (type == "Line2D") {
                auto coords = parseCoordinates(line);
                if (coords.size() == 4) {  // [x1,y1], [x2,y2] = 4 coordinates
                    Point2D pt1(coords[0], coords[1]);
                    Point2D pt2(coords[2], coords[3]);
                    allLines2D.push_back(unique_ptr<Line2D>(new Line2D(pt1, pt2)));
                    count++;
                }
            }
            else if (type == "Line3D") {
                auto coords = parseCoordinates(line);
                if (coords.size() == 6) {  // [x1,y1,z1], [x2,y2,z2] = 6 coordinates
                    Point3D pt1(coords[0], coords[1], coords[2]);
                    Point3D pt2(coords[3], coords[4], coords[5]);
                    allLines3D.push_back(unique_ptr<Line3D>(new Line3D(pt1, pt2)));
                    count++;
                }
            }
        }
        catch (const exception& e) {
            cout << "Error parsing line: " << line << endl;
        }
        }

        file.close();

        // Remove duplicates
        removeDuplicates();

        cout << count << " records read successfully!" << endl;
        cout << "After removing duplicates:" << endl;
        cout << "- Point2D records: " << allPoints2D.size() << endl;
        cout << "- Point3D records: " << allPoints3D.size() << endl;
        cout << "- Line2D records: " << allLines2D.size() << endl;
        cout << "- Line3D records: " << allLines3D.size() << endl;
    }

    // Helper function
    vector<int> parseCoordinates(const string& line) {
        vector<int> coords;
        size_t start = line.find('[');

        while (start != string::npos) {
            size_t end = line.find(']', start);
            if (end == string::npos) break;

            string coordSection = line.substr(start + 1, end - start - 1);
            stringstream ss(coordSection);
            string token;

            while (getline(ss, token, ',')) {
                // Trim whitespace
                token.erase(0, token.find_first_not_of(" \t"));
                token.erase(token.find_last_not_of(" \t") + 1);

                if (!token.empty()) {
                    coords.push_back(stoi(token));
                }
            }

            start = line.find('[', end);
        }

        return coords;
    }

    // Remove Duplicates
    void removeDuplicates() {
        // Remove duplicates from Point2D
        sort(allPoints2D.begin(), allPoints2D.end(),
            [](const unique_ptr<Point2D>& a, const unique_ptr<Point2D>& b) {
                if (a->getX() != b->getX()) return a->getX() < b->getX();
                return a->getY() < b->getY();
            });

        auto newEnd2D = unique(allPoints2D.begin(), allPoints2D.end(),
            [](const unique_ptr<Point2D>& a, const unique_ptr<Point2D>& b) {
                return a->getX() == b->getX() && a->getY() == b->getY();
            });
        allPoints2D.erase(newEnd2D, allPoints2D.end());

        // Remove duplicates from Point3D
        sort(allPoints3D.begin(), allPoints3D.end(),
            [](const unique_ptr<Point3D>& a, const unique_ptr<Point3D>& b) {
                if (a->getX() != b->getX()) return a->getX() < b->getX();
                if (a->getY() != b->getY()) return a->getY() < b->getY();
                return a->getZ() < b->getZ();
            });

        auto newEnd3D = unique(allPoints3D.begin(), allPoints3D.end(),
            [](const unique_ptr<Point3D>& a, const unique_ptr<Point3D>& b) {
                return a->getX() == b->getX() && a->getY() == b->getY() && a->getZ() == b->getZ();
            });
        allPoints3D.erase(newEnd3D, allPoints3D.end());

        // Remove duplicates from Line2D
        sort(allLines2D.begin(), allLines2D.end(),
            [](const unique_ptr<Line2D>& a, const unique_ptr<Line2D>& b) {
                // Compare Point1 first
                if (a->getPt1().getX() != b->getPt1().getX()) return a->getPt1().getX() < b->getPt1().getX();
                if (a->getPt1().getY() != b->getPt1().getY()) return a->getPt1().getY() < b->getPt1().getY();
                // If Point1 is equal, compare Point2
                if (a->getPt2().getX() != b->getPt2().getX()) return a->getPt2().getX() < b->getPt2().getX();
                return a->getPt2().getY() < b->getPt2().getY();
            });

        auto newEndLine2D = unique(allLines2D.begin(), allLines2D.end(),
            [](const unique_ptr<Line2D>& a, const unique_ptr<Line2D>& b) {
                return (a->getPt1().getX() == b->getPt1().getX() &&
                        a->getPt1().getY() == b->getPt1().getY() &&
                        a->getPt2().getX() == b->getPt2().getX() &&
                        a->getPt2().getY() == b->getPt2().getY());
            });
        allLines2D.erase(newEndLine2D, allLines2D.end());

        // Remove duplicates from Line3D
        sort(allLines3D.begin(), allLines3D.end(),
            [](const unique_ptr<Line3D>& a, const unique_ptr<Line3D>& b) {
                // Compare Point1 first
                if (a->getPt1().getX() != b->getPt1().getX()) return a->getPt1().getX() < b->getPt1().getX();
                if (a->getPt1().getY() != b->getPt1().getY()) return a->getPt1().getY() < b->getPt1().getY();
                if (a->getPt1().getZ() != b->getPt1().getZ()) return a->getPt1().getZ() < b->getPt1().getZ();
                // If Point1 is equal, compare Point2
                if (a->getPt2().getX() != b->getPt2().getX()) return a->getPt2().getX() < b->getPt2().getX();
                if (a->getPt2().getY() != b->getPt2().getY()) return a->getPt2().getY() < b->getPt2().getY();
                return a->getPt2().getZ() < b->getPt2().getZ();
            });

        auto newEndLine3D = unique(allLines3D.begin(), allLines3D.end(),
            [](const unique_ptr<Line3D>& a, const unique_ptr<Line3D>& b) {
                return (a->getPt1().getX() == b->getPt1().getX() &&
                        a->getPt1().getY() == b->getPt1().getY() &&
                        a->getPt1().getZ() == b->getPt1().getZ() &&
                        a->getPt2().getX() == b->getPt2().getX() &&
                        a->getPt2().getY() == b->getPt2().getY() &&
                        a->getPt2().getZ() == b->getPt2().getZ());
            });
        allLines3D.erase(newEndLine3D, allLines3D.end());
    }

    void setFilteringCriteria() {
      cout << "\n[ Specifying filtering criteria (current : " << currentFilter << ") ]" << endl;
      cout << "\na)\tPoint2D records" << endl;
      cout << "b)\tPoint3D records" << endl;
      cout << "c)\tLine2D records" << endl;
      cout << "d)\tLine3D records" << endl;
      cout << "\nPlease enter your criteria (a - d) : ";

      char choice;
      cin >> choice;

      string newFilter;
      switch(choice) {
          case 'a':
          case 'A':
              newFilter = "Point2D";
              break;
          case 'b':
          case 'B':
              newFilter = "Point3D";
              break;
          case 'c':
          case 'C':
              newFilter = "Line2D";
              break;
          case 'd':
          case 'D':
              newFilter = "Line3D";
              break;
          default:
              cout << "Invalid choice! Please enter a, b, c, or d." << endl;
              return;
      }

      currentFilter = newFilter;
      cout << "Filter criteria successfully set to '" << currentFilter << "'!" << endl;

      // Reset sorting criteria to default for the new filter type
      // resetSortingCriteriaForFilter();
  }

    void setSortingCriteria() {
        cout << "\n[ Specifying sorting criteria (current : " << currentSortCriteria << ") ]" << endl;

        if (currentFilter == "Point2D") {
            cout << "\na)\tX ordinate value\t(default)" << endl;
            cout << "b)\tY ordinate value" << endl;
            cout << "c)\tDist. Fr Origin value" << endl;
        }
        else if (currentFilter == "Point3D") {
            cout << "\na)\tX ordinate value\t(default)" << endl;
            cout << "b)\tY ordinate value" << endl;
            cout << "c)\tZ ordinate value" << endl;
            cout << "d)\tDist. Fr Origin value" << endl;
        }
        else if (currentFilter == "Line2D") {
            cout << "\na)\tPt. 1's (x, y) values\t(default)" << endl;
            cout << "b)\tPt. 2's (x, y) values" << endl;
            cout << "c)\tLength value" << endl;
        }
        else if (currentFilter == "Line3D") {
            cout << "\na)\tPt. 1's (x, y) values\t(default)" << endl;
            cout << "b)\tPt. 2's (x, y) values" << endl;
            cout << "c)\tLength value" << endl;
        }

        cout << "\nPlease enter your criteria (a - c) : ";

        char choice;
        cin >> choice;

        string newCriteria;
        if (currentFilter == "Point2D") {
            switch(choice) {
                case 'a': case 'A': newCriteria = "x-ordinate"; break;
                case 'b': case 'B': newCriteria = "y-ordinate"; break;
                case 'c': case 'C': newCriteria = "distFrOrigin"; break;
                default:
                    cout << "Invalid choice!" << endl;
                    return;
            }
        }
        else if (currentFilter == "Point3D") {
            switch(choice) {
                case 'a': case 'A': newCriteria = "x-ordinate"; break;
                case 'b': case 'B': newCriteria = "y-ordinate"; break;
                case 'c': case 'C': newCriteria = "z-ordinate"; break;
                case 'd': case 'D': newCriteria = "distFrOrigin"; break;
                default:
                    cout << "Invalid choice!" << endl;
                    return;
            }
        }
        else if (currentFilter == "Line2D" || currentFilter == "Line3D") {
            switch(choice) {
                case 'a': case 'A': newCriteria = "Pt. 1"; break;
                case 'b': case 'B': newCriteria = "Pt. 2"; break;
                case 'c': case 'C': newCriteria = "Length"; break;
                default:
                    cout << "Invalid choice!" << endl;
                    return;
            }
        }

        currentSortCriteria = newCriteria;
        cout << "Sorting criteria successfully set to '" << currentSortCriteria << "'!" << endl;
    }

    void setSortingOrder() {
      cout << "\n[ Specifying sorting order (current : " << currentSortOrder << ") ]" << endl;
      cout << "\na)\tASC (Ascending order)" << endl;
      cout << "b)\tDSC (Descending order)" << endl;
      cout << "\nPlease enter your criteria (a - b) : ";

      char choice;
      cin >> choice;

      string newOrder;
      switch(choice) {
          case 'a': case 'A':
              newOrder = "ASC";
              break;
          case 'b': case 'B':
              newOrder = "DSC";
              break;
          default:
              cout << "Invalid choice!" << endl;
              return;
      }

      currentSortOrder = newOrder;
      cout << "Sorting order successfully set to '" << currentSortOrder << "'!" << endl;
  }

void viewData() {
    cout << "\n[ View data ... ]" << endl;
    cout << "filtering criteria : " << currentFilter << endl;
    cout << "sorting criteria : " << currentSortCriteria << endl;
    cout << "sorting order : " << currentSortOrder << endl;
    cout << endl;

    if (currentFilter == "Point2D") {
        if (allPoints2D.empty()) {
            cout << "No Point2D records available. Please read in data first." << endl;
            return;
        }

        // Create a copy for sorting without affecting original data
        vector<Point2D*> sortedPoints;
        for (auto& point : allPoints2D) {
            sortedPoints.push_back(point.get());
        }

        // Sort based on current criteria
        sortPoint2DData(sortedPoints);

        // Display header
        cout << "Point2D" << endl;
        cout << "   X      Y    Dist. Fr Origin" << endl;
        cout << "- - - - - - - - - - - - - - - -" << endl;

        // Display data
        for (auto* point : sortedPoints) {
            cout << "[" << setw(4) << point->getX() << ", "
                 << setw(4) << point->getY() << "]   "
                 << fixed << setprecision(3) << point->getScalarValue() << endl;
        }
    }
    else if (currentFilter == "Point3D") {
        if (allPoints3D.empty()) {
            cout << "No Point3D records available. Please read in data first." << endl;
            return;
        }

        vector<Point3D*> sortedPoints;
        for (auto& point : allPoints3D) {
            sortedPoints.push_back(point.get());
        }

        sortPoint3DData(sortedPoints);

        cout << "Point3D" << endl;
        cout << "   X      Y      Z    Dist. Fr Origin" << endl;
        cout << "- - - - - - - - - - - - - - - - - - -" << endl;

        for (auto* point : sortedPoints) {
            cout << "[" << setw(4) << point->getX() << ", "
                 << setw(4) << point->getY() << ", "
                 << setw(4) << point->getZ() << "]   "
                 << fixed << setprecision(3) << point->getScalarValue() << endl;
        }
    }
    else if (currentFilter == "Line2D") {
        if (allLines2D.empty()) {
            cout << "No Line2D records available. Please read in data first." << endl;
            return;
        }

        vector<Line2D*> sortedLines;
        for (auto& line : allLines2D) {
            sortedLines.push_back(line.get());
        }

        sortLine2DData(sortedLines);

        cout << "Line2D" << endl;
        cout << " P1-X  P1-Y      P2-X  P2-Y   Length" << endl;
        cout << "- - - - - - - - - - - - - - - - - -" << endl;

        for (auto* line : sortedLines) {
            cout << "[" << setw(4) << line->getPt1().getX() << ", "
                 << setw(4) << line->getPt1().getY() << "]   "
                 << "[" << setw(4) << line->getPt2().getX() << ", "
                 << setw(4) << line->getPt2().getY() << "]   "
                 << fixed << setprecision(3) << line->getScalarValue() << endl;
        }
    }
    else if (currentFilter == "Line3D") {
        if (allLines3D.empty()) {
            cout << "No Line3D records available. Please read in data first." << endl;
            return;
        }

        vector<Line3D*> sortedLines;
        for (auto& line : allLines3D) {
            sortedLines.push_back(line.get());
        }

        sortLine3DData(sortedLines);

        cout << "Line3D" << endl;
        cout << " P1-X  P1-Y  P1-Z     P2-X  P2-Y  P2-Z    Length" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

        for (auto* line : sortedLines) {
            cout << "[" << setw(4) << line->getPt1().getX() << ", "
                 << setw(4) << line->getPt1().getY() << ", "
                 << setw(4) << line->getPt1().getZ() << "]   "
                 << "[" << setw(4) << line->getPt2().getX() << ", "
                 << setw(4) << line->getPt2().getY() << ", "
                 << setw(4) << line->getPt2().getZ() << "]   "
                 << fixed << setprecision(3) << line->getScalarValue() << endl;
        }
    }

    cout << "\nPress any key to go back to main menu ..." << endl;
}

    void sortPoint2DData(vector<Point2D*>& points) {
    // We need to work with the original unique_ptr containers for template functions
    // So we'll sort the original container and then rebuild the pointer vector

    if (currentSortCriteria == "x-ordinate") {
        if (currentSortOrder == "ASC") {
            sort(allPoints2D.begin(), allPoints2D.end(), compareXAsc<Point2D>);
        } else {
            sort(allPoints2D.begin(), allPoints2D.end(), compareXDsc<Point2D>);
        }
    }
    else if (currentSortCriteria == "y-ordinate") {
        if (currentSortOrder == "ASC") {
            sort(allPoints2D.begin(), allPoints2D.end(), compareYAsc<Point2D>);
        } else {
            sort(allPoints2D.begin(), allPoints2D.end(), compareYDsc<Point2D>);
        }
    }
    else if (currentSortCriteria == "distFrOrigin") {
        if (currentSortOrder == "ASC") {
            sort(allPoints2D.begin(), allPoints2D.end(), compareDistAsc<Point2D>);
        } else {
            sort(allPoints2D.begin(), allPoints2D.end(), compareDistDsc<Point2D>);
        }
    }

    // Rebuild the pointer vector to match the sorted order
    points.clear();
    for (auto& point : allPoints2D) {
        points.push_back(point.get());
    }
    }

    void sortPoint3DData(vector<Point3D*>& points) {
        if (currentSortCriteria == "x-ordinate") {
            if (currentSortOrder == "ASC") {
                sort(allPoints3D.begin(), allPoints3D.end(), compareXAsc<Point3D>);
            } else {
                sort(allPoints3D.begin(), allPoints3D.end(), compareXDsc<Point3D>);
            }
        }
        else if (currentSortCriteria == "y-ordinate") {
            if (currentSortOrder == "ASC") {
                sort(allPoints3D.begin(), allPoints3D.end(), compareYAsc<Point3D>);
            } else {
                sort(allPoints3D.begin(), allPoints3D.end(), compareYDsc<Point3D>);
            }
        }
        else if (currentSortCriteria == "z-ordinate") {
            if (currentSortOrder == "ASC") {
                sort(allPoints3D.begin(), allPoints3D.end(), compareZAsc<Point3D>);
            } else {
                sort(allPoints3D.begin(), allPoints3D.end(), compareZDsc<Point3D>);
            }
        }
        else if (currentSortCriteria == "distFrOrigin") {
            if (currentSortOrder == "ASC") {
                sort(allPoints3D.begin(), allPoints3D.end(), compareDistAsc<Point3D>);
            } else {
                sort(allPoints3D.begin(), allPoints3D.end(), compareDistDsc<Point3D>);
            }
        }

        // Rebuild the pointer vector to match the sorted order
        points.clear();
        for (auto& point : allPoints3D) {
            points.push_back(point.get());
        }
    }

    void sortLine2DData(vector<Line2D*>& lines) {
        if (currentSortCriteria == "Pt. 1") {
            // For lexicographic sorting (X then Y), we need custom lambda since templates only sort by X
            sort(allLines2D.begin(), allLines2D.end(), [this](const unique_ptr<Line2D>& a, const unique_ptr<Line2D>& b) {
                if (a->getPt1().getX() != b->getPt1().getX()) {
                    return currentSortOrder == "ASC" ? a->getPt1().getX() < b->getPt1().getX()
                                                    : a->getPt1().getX() > b->getPt1().getX();
                }
                return currentSortOrder == "ASC" ? a->getPt1().getY() < b->getPt1().getY()
                                                : a->getPt1().getY() > b->getPt1().getY();
            });
        }
        else if (currentSortCriteria == "Pt. 2") {
            sort(allLines2D.begin(), allLines2D.end(), [this](const unique_ptr<Line2D>& a, const unique_ptr<Line2D>& b) {
                if (a->getPt2().getX() != b->getPt2().getX()) {
                    return currentSortOrder == "ASC" ? a->getPt2().getX() < b->getPt2().getX()
                                                    : a->getPt2().getX() > b->getPt2().getX();
                }
                return currentSortOrder == "ASC" ? a->getPt2().getY() < b->getPt2().getY()
                                                : a->getPt2().getY() > b->getPt2().getY();
            });
        }
        else if (currentSortCriteria == "Length") {
            if (currentSortOrder == "ASC") {
                sort(allLines2D.begin(), allLines2D.end(), compareDistAsc<Line2D>);
            } else {
                sort(allLines2D.begin(), allLines2D.end(), compareDistDsc<Line2D>);
            }
        }

        // Rebuild the pointer vector to match the sorted order
        lines.clear();
        for (auto& line : allLines2D) {
            lines.push_back(line.get());
        }
    }

    void sortLine3DData(vector<Line3D*>& lines) {
        if (currentSortCriteria == "Pt. 1") {
            // For lexicographic sorting (X then Y), we need custom lambda since templates only sort by X
            sort(allLines3D.begin(), allLines3D.end(), [this](const unique_ptr<Line3D>& a, const unique_ptr<Line3D>& b) {
                if (a->getPt1().getX() != b->getPt1().getX()) {
                    return currentSortOrder == "ASC" ? a->getPt1().getX() < b->getPt1().getX()
                                                    : a->getPt1().getX() > b->getPt1().getX();
                }
                return currentSortOrder == "ASC" ? a->getPt1().getY() < b->getPt1().getY()
                                                : a->getPt1().getY() > b->getPt1().getY();
            });
        }
        else if (currentSortCriteria == "Pt. 2") {
            sort(allLines3D.begin(), allLines3D.end(), [this](const unique_ptr<Line3D>& a, const unique_ptr<Line3D>& b) {
                if (a->getPt2().getX() != b->getPt2().getX()) {
                    return currentSortOrder == "ASC" ? a->getPt2().getX() < b->getPt2().getX()
                                                    : a->getPt2().getX() > b->getPt2().getX();
                }
                return currentSortOrder == "ASC" ? a->getPt2().getY() < b->getPt2().getY()
                                                : a->getPt2().getY() > b->getPt2().getY();
            });
        }
        else if (currentSortCriteria == "Length") {
            if (currentSortOrder == "ASC") {
                sort(allLines3D.begin(), allLines3D.end(), compareDistAsc<Line3D>);
            } else {
                sort(allLines3D.begin(), allLines3D.end(), compareDistDsc<Line3D>);
            }
        }

        // Rebuild the pointer vector to match the sorted order
        lines.clear();
        for (auto& line : allLines3D) {
            lines.push_back(line.get());
        }
    }

    void storeData() {
    string fileName;
    cout << "\nPlease enter filename : ";
    cin >> fileName;

    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not create file '" << fileName << "'" << endl;
        return;
    }

    int recordsWritten = 0;

    if (currentFilter == "Point2D") {
        if (allPoints2D.empty()) {
            cout << "No Point2D records available to store." << endl;
            file.close();
            return;
        }

        // Create a copy for sorting without affecting original data
        vector<Point2D*> sortedPoints;
        for (auto& point : allPoints2D) {
            sortedPoints.push_back(point.get());
        }

        // Sort based on current criteria
        sortPoint2DData(sortedPoints);

        // Write header
        file << "Point2D" << endl;
        file << "   X      Y    Dist. Fr Origin" << endl;
        file << "- - - - - - - - - - - - - - - -" << endl;

        // Write data with exact format: [  value,   value]   value
        for (auto* point : sortedPoints) {
            file << "[" << setw(4) << point->getX() << ", "
                 << setw(4) << point->getY() << "]   "
                 << fixed << setprecision(3) << point->getScalarValue() << endl;
            recordsWritten++;
        }
    }
    else if (currentFilter == "Point3D") {
        if (allPoints3D.empty()) {
            cout << "No Point3D records available to store." << endl;
            file.close();
            return;
        }

        vector<Point3D*> sortedPoints;
        for (auto& point : allPoints3D) {
            sortedPoints.push_back(point.get());
        }

        sortPoint3DData(sortedPoints);

        // Write header
        file << "Point3D" << endl;
        file << "   X      Y      Z    Dist. Fr Origin" << endl;
        file << "- - - - - - - - - - - - - - - - - - -" << endl;

        // Write data
        for (auto* point : sortedPoints) {
            file << "[" << setw(4) << point->getX() << ", "
                 << setw(4) << point->getY() << ", "
                 << setw(4) << point->getZ() << "]   "
                 << fixed << setprecision(3) << point->getScalarValue() << endl;
            recordsWritten++;
        }
    }
    else if (currentFilter == "Line2D") {
        if (allLines2D.empty()) {
            cout << "No Line2D records available to store." << endl;
            file.close();
            return;
        }

        vector<Line2D*> sortedLines;
        for (auto& line : allLines2D) {
            sortedLines.push_back(line.get());
        }

        sortLine2DData(sortedLines);

        // Write header
        file << "Line2D" << endl;
        file << " P1-X  P1-Y      P2-X  P2-Y   Length" << endl;
        file << "- - - - - - - - - - - - - - - - - -" << endl;

        // Write data
        for (auto* line : sortedLines) {
            file << "[" << setw(4) << line->getPt1().getX() << ", "
                 << setw(4) << line->getPt1().getY() << "]   "
                 << "[" << setw(4) << line->getPt2().getX() << ", "
                 << setw(4) << line->getPt2().getY() << "]   "
                 << fixed << setprecision(3) << line->getScalarValue() << endl;
            recordsWritten++;
        }
    }
    else if (currentFilter == "Line3D") {
        if (allLines3D.empty()) {
            cout << "No Line3D records available to store." << endl;
            file.close();
            return;
        }

        vector<Line3D*> sortedLines;
        for (auto& line : allLines3D) {
            sortedLines.push_back(line.get());
        }

        sortLine3DData(sortedLines);

        // Write header
        file << "Line3D" << endl;
        file << " P1-X  P1-Y  P1-Z     P2-X  P2-Y  P2-Z    Length" << endl;
        file << "- - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

        // Write data
        for (auto* line : sortedLines) {
            file << "[" << setw(4) << line->getPt1().getX() << ", "
                 << setw(4) << line->getPt1().getY() << ", "
                 << setw(4) << line->getPt1().getZ() << "]   "
                 << "[" << setw(4) << line->getPt2().getX() << ", "
                 << setw(4) << line->getPt2().getY() << ", "
                 << setw(4) << line->getPt2().getZ() << "]   "
                 << fixed << setprecision(3) << line->getScalarValue() << endl;
            recordsWritten++;
        }
    }

    file.close();

    cout << recordsWritten << " records output successfully!" << endl;
    cout << "\nGoing back to main menu ..." << endl;
}

  void run() {
    bool continueRunning = true;
    while (continueRunning) {
      displayMenu();
      int choice = getUserChoice();
      continueRunning = processMenuChoice(choice);
      if (continueRunning) {
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        cout << "\n" << endl;
      }
    }
  }
};

// int main(){
//   menuSystem menu;
//   menu.run();
// }