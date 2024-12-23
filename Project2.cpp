#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

// Course structure to hold course details
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// Function to split a string by a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to load courses from a file into a hash table
unordered_map<string, Course> loadCourses(const string& fileName) {
    unordered_map<string, Course> courses;
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return courses;
    }

    string line;
    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() < 2) {
            cout << "Error: Invalid line format in file." << endl;
            continue;
        }

        Course course;
        course.courseNumber = tokens[0];
        course.name = tokens[1];
        for (size_t i = 2; i < tokens.size(); ++i) {
            course.prerequisites.push_back(tokens[i]);
        }

        courses[course.courseNumber] = course;
    }

    file.close();
    return courses;
}

// Function to print a sorted list of all courses
void printCourseList(const unordered_map<string, Course>& courses) {
    vector<string> courseKeys;
    for (const auto& pair : courses) {
        courseKeys.push_back(pair.first);
    }

    sort(courseKeys.begin(), courseKeys.end());

    cout << "\nHere is a sample schedule:\n";
    for (const string& key : courseKeys) {
        const Course& course = courses.at(key);
        cout << course.courseNumber << ", " << course.name << endl;
    }
}

// Function to print information about a specific course
void printCourseInfo(const unordered_map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);
    if (it == courses.end()) {
        cout << "Course " << courseNumber << " not found." << endl;
        return;
    }

    const Course& course = it->second;
    cout << course.courseNumber << ", " << course.name << endl;
    if (course.prerequisites.empty()) {
        cout << "No prerequisites." << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// Main program menu
void displayMenu() {
    cout << "\n1. Load Data Structure.\n";
    cout << "2. Print Course List.\n";
    cout << "3. Print Course.\n";
    cout << "9. Exit.\n";
    cout << "What would you like to do? ";
}

int main() {
    unordered_map<string, Course> courses;
    bool dataLoaded = false;

    while (true) {
        displayMenu();

        int choice;
        cin >> choice;
        cin.ignore(); // Ignore leftover newline

        switch (choice) {
        case 1: {
            string fileName;
            cout << "Enter the file name: ";
            getline(cin, fileName);
            courses = loadCourses(fileName);
            if (!courses.empty()) {
                dataLoaded = true;
                cout << "Data loaded successfully." << endl;
            }
            break;
        }
        case 2: {
            if (!dataLoaded) {
                cout << "Error: No data loaded. Please load data first." << endl;
            }
            else {
                printCourseList(courses);
            }
            break;
        }
        case 3: {
            if (!dataLoaded) {
                cout << "Error: No data loaded. Please load data first." << endl;
            }
            else {
                string courseNumber;
                cout << "Enter course number: ";
                getline(cin, courseNumber);
                printCourseInfo(courses, courseNumber);
            }
            break;
        }
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            return 0;
        default:
            cout << "Invalid option. Try again." << endl;
        }
    }
}
