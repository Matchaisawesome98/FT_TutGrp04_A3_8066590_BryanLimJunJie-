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
      case 5:
        //viewData();
        return true;
      case 6:
        // storeData();
        return true;
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

    // Duplicate removal function
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
    }

  // void viewData() {
  //   if (points2D.empty()) {
  //     cout << "No data available. Please read in data first." << endl;
  //     return;
  //   }
  //
  //   cout << "\nDisplaying " << points2D.size() << " Point2D records:" << endl;
  //   cout << "===============================================" << endl;
  //   for (size_t i = 0; i < points2D.size(); i++) {
  //     cout << "[" << (i + 1) << "] " << points2D[i] << endl;
  //   }
  // }

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

int main(){
  menuSystem menu;
  menu.run();
  // Point2D p1(3, 2);
  // Point2D p2(5, 2);
  //
  // cout << "Point 1: (" << p1.getX() << ", " << p1.getY() << ")" << endl;
  // cout << "Point 2: (" << p2.getX() << ", " << p2.getY() << ")" << endl;
  //
  // return 0;
}