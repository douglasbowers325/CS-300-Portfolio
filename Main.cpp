//============================================================================
// Douglas Bowers
// CS-300
// 7-2 Project Two
// 4/20/2024
//============================================================================


#include <algorithm>
#include <iostream>
#include <fstream> // enables reading and writing of files.
#include <sstream> // enables use of stringstream library
#include <vector> // enables use of vector based functions

// course structure
class Course {
public:
    int numPrerequisites;
    std::string courseName;
    std::string courseNumber;
    std::vector<std::string>prerequisites;
};

std::vector<Course> vector;
std::string userInput;

void loadVector(std::string fileName) {

    // string to read from file
    std::string courses;

    // reads text from file
    std::ifstream File(fileName);

    if (File.is_open()) {

        while (getline(File, courses)) {
            std::string temp;
            // pass in the string as a stream, passed into inputStream variable
            std::stringstream inputStream(courses);
            Course course;

            // skips cases where blank line is parsed
            if (courses == "") {
                continue;
            }

            // finds seperators and places in vector
            int end = courses.find(",");
            // assigns substring to number
            course.courseNumber = courses.substr(0, end);
            courses = courses.substr(end + 1);
            end = courses.find(",");

            // if there is no comma then course.courseName = courses
            if (end == std::string::npos) {

                course.courseName = courses;
            }
            else {
                course.courseName = courses.substr(0, end);
                courses = courses.substr(end + 1);

                int i = 0;

                while (courses != "") {
                    end = courses.find(",");

                    if (end != std::string::npos) {

                        temp = courses.substr(0, end);
                        course.prerequisites.push_back(temp);
                        courses = courses.substr(end + 1);
                    }
                    else {
                        course.prerequisites.push_back(courses);
                        break;
                    }
                }
            }
            // stores course into courseList
            vector.push_back(course);
        }

        // close file as it is not needed to remain open
        File.close();
    }
    else {
        // if file not found
        std::cout << "file not found." << std::endl;
    }

}

// sorts array in ascending order
bool compareCourses(Course c1, Course c2) {

    return (c1.courseNumber < c2.courseNumber);
}

// compares the courses 
bool isEqual(Course c) {

    // if userInput is found in vector
    return (c.courseNumber == userInput);
}
// main function
int main() {

    //declaration of int choice used for navigating menu
    int choice;
    //declaration of iterator within the vector
    std::vector<Course>::iterator it;

    std::cout << "Welcome to the course planner." << std::endl;
    do { // do while user does not choose option 9

        // displays menu
        std::cout << std::endl;
        std::cout << "1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit" << std::endl;

        // prompts user for input
        std::cout << "What would you like to do?";

        // assigns userInput to choice variable 
        std::cin >> choice;

        switch (choice) {
        case 1: {
            //load data structure
            std::string fileName;
            // call loadVector function
            loadVector("Course List.txt");
            //ensures vecotr only needs to be sorted once
            sort(vector.begin(), vector.end(), compareCourses);
            std::cout << "Course list loaded." << std::endl;
            break;
        }

        case 2: {
            std::cout << "Here is a sample schedule:\n" << std::endl;

            //print courses according vector size
            for (int i = 0; i < vector.size(); i++) {

                std::cout << vector[i].courseNumber << ", " << vector[i].courseName << std::endl;
            }
            break;
        }

        case 3: {
            // prompt user what course they want information about
            std::cout << "What course do you want to know about? ";

            // assigns value from cin to userInput variable
            std::cin >> userInput;

            //Implement std::transform to ensure all input is in upper case (removes case sensitivity)
            std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);

            // clears cin to avoid potential errors
            std::cin.clear();

            // iterator "it" used for sort and isEqual
            it = find_if(vector.begin(), vector.end(), isEqual);

            // use "it" for vector reference
            if (it != vector.end()) {

                std::cout << it->courseNumber << ", " << it->courseName << std::endl;
                std::cout << "Prerequisites: ";

                for (int i = 0; i < it->prerequisites.size(); i++) {
                    // prints prerequisites
                    std::cout << it->prerequisites[i];

                    // removes the comma after last prerequisite
                    if (i == it->prerequisites.size() - 1) {
                        std::cout << std::endl;
                    }
                    else {
                        // comma between prerequisites
                        std::cout << ", ";
                    }
                }
            }
            else {
                // error message displayed when course is not found
                std::cout << "Course not found." << std::endl;
            }
            break;
        }
        case 9: {
            //exits program
            std::cout << "Thank you for using the course planner!" << std::endl;
            break;
        }
              //when user enters invalid option
        default: {
            std::cout << choice << " is not a valid option." << std::endl;

            // clears cin to avoid overloading cin after choice is received
            std::cin.clear();
            // ignores any pending inputs
            std::cin.ignore(100, '\n');
        }
        }

    } while (choice != 9);  // loop continues until 9 is chosen

    return 0;
}