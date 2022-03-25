#include <iostream>
#include <iomanip>
#include <list>
#include <fstream>
#include <stdlib.h>

// maximum number of characters for name
#define MAX_CHAR 40

using namespace std;

// Course class
class Course{
    public:
        string courseId;
        int grade;
        float credits;

        Course(string c, int g, float cr){
            courseId = c;
            grade = g;
            credits = cr;
        }

        float getCredits(){
            return credits;
        }

        int getGrade(){
            return grade;
        }
};

// Compare predicate for list of courses
bool compare_courseid(const Course & a, const Course & b){
    return a.courseId < b.courseId;
}

// Student class
class Student{
    private:
        string name;
        list<Course> courses;

    public:
        Student(string n){
            name = n;
        }

        void addCourse(Course c){
            courses.push_back(c);
        }
        
        bool deleteCourse(string id){
            list<Course>::iterator ptr;

            for (ptr = courses.begin(); ptr != courses.end(); ptr++){
                if((*ptr).courseId == id){
                    courses.erase(ptr);
                    return true;
                }
            }
            return false;
        }

        bool updateCourse(string id, int g){
            list<Course>::iterator ptr;
            for (ptr = courses.begin(); ptr != courses.end(); ptr++){
                if((*ptr).courseId == id){
                    (*ptr).grade = g;
                    return true;
                }
            }
            return false;
        }

        void displayCourses(){
            if(courses.empty() == 0){
                list<Course>::iterator ptr;
                for (ptr = courses.begin(); ptr != courses.end(); ptr++){
                    cout << (*ptr).courseId << ": " << (*ptr).getGrade() << " " << (*ptr).getCredits() << endl;
                }
            } else{
                cout << "\n-- No courses exist --" << endl;
            }
        }

        void computeGpa(){
            float result = 0;
            float value = 0;

            list<Course>::iterator ptr;

            for (ptr = courses.begin(); ptr != courses.end(); ptr++){
                int grade = (*ptr).getGrade();
                float gradePoints = 0;
                if(grade >= 90 && grade <= 100 )
                    gradePoints = 4.0;
                else if(grade >= 85 && grade <= 89)
                    gradePoints = 3.8;
                else if(grade >= 80 && grade <= 84)
                    gradePoints = 3.6;
                else if(grade >= 75 && grade <= 79)
                    gradePoints = 3.3;
                else if(grade >= 70 && grade <= 74)
                    gradePoints = 3.0;
                else if(grade >= 65 && grade <= 69)
                    gradePoints = 2.5;
                else if(grade >= 60 && grade <= 64)
                    gradePoints = 2.0;
                else if(grade >= 55 && grade <= 59)
                    gradePoints = 1.5;
                else if(grade >= 50 && grade <= 54)
                    gradePoints = 1.0;
                else
                    gradePoints = 0.0;
                result += (gradePoints * (*ptr).getCredits());
                value += (*ptr).getCredits();
            }

            if(result != 0)
                result = result / value;

            cout << setprecision(2) << result << " GPA" << endl;
        }

        void writeToFile(){
            ofstream MyFile("output.txt");
            MyFile << name;
            if(courses.size() > 0){
                list<Course>::iterator ptr;
                for (ptr = courses.begin(); ptr != courses.end(); ptr++)
                {
                    MyFile << (*ptr).courseId << ": " << (*ptr).getGrade() << " " << (*ptr).getCredits() << endl;
                }
            }
            MyFile.close();
        }

        bool courseExists(string id){
            list<Course>::iterator ptr;
            for (ptr = courses.begin(); ptr != courses.end(); ptr++)
            {
                if((*ptr).courseId == id)
                    return true;
            }
            return false;
        }

        void menu(){
            int userChoice;
            string courseId;
            int grade;
            float credit;
            while(1){
                cout << "-------------------------------\n\n";
                cout << "Course Management System\n\n";
                cout << "-------------------------------\n";
                cout << "1.Insert a Course\n";
                cout << "2.Delete a course by ID\n";
                cout << "3.Update a course grade\n";
                cout << "4.Sort your courses\n";
                cout << "5.View all of your courses\n";
                cout << "6.Compute your GPA\n";
                cout << "7.Save your courses to a file\n";
                cout << "8.Exit \nEnter your choice : ";
                
                cin >> userChoice;

                switch(userChoice){
                    case 1:
                        cout << "Insert a Course\nEnter course id: ";
                        cin >> courseId;
                        while(courseExists(courseId)){
                            cout << "this course exists! enter new id: " << endl;
                            cin >> courseId;
                        }
                        cout << "Enter grade: ";
                        cin >> grade;
                        cout << "Enter credit: ";
                        cin >> credit;
                        addCourse(Course(courseId, grade, credit));
                        cout << "--Course added--" << endl;
                        break;
                    case 2:
                        cout << "Delete Course\nEnter course id: ";
                        cin >> courseId;
                        while(!courseExists(courseId)){
                            cout << "enter valid id: " << endl;
                            cin >> courseId;
                        }
                        deleteCourse(courseId);
                        cout << "--Course successfully deleted--" << endl;
                        break;
                    case 3:
                        cout << "Update Course Grade\nEnter course id: ";
                        cin >> courseId;
                        while(!courseExists(courseId)){
                            cout << "enter valid id:  " << endl;
                            cin >> courseId;
                        }
                        cout << "Enter new grade: ";
                        cin >> grade;
                        updateCourse(courseId, grade);
                        cout << "--Course successfully updated--" << endl;

                        break;
                    case 4:
                        cout << "--Courses sorted--" << endl;
                        courses.sort(compare_courseid);
                        break;
                    case 5:
                        cout << "\nVIEW ALL YOUR COURSES\n";
                        displayCourses();
                        break;
                    case 6:
                        cout << "-- Accumulative GPA computed --" << endl;
                        computeGpa();
                        break;
                    case 7:
                        cout << "\n-- Data saved to file--" << endl;
                        writeToFile();
                        break;
                    case 8:
                        // exit
                        exit(1);
                    default:
                        cout << "Invalid option" << endl;
                }

            }
        }
};

// Entry point of program
int main(int argc, char** argv){

    char str[MAX_CHAR];
    cout << "Enter your name: ";
    fgets(str, MAX_CHAR, stdin);
    cout << str << endl;
    
    Student *s = new Student(str);
    s->menu();
    delete s;

    return 0;
}