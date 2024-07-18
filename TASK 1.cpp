#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>

using namespace std;

class Course {
public:
    string name;
    int credits;
    string grade;
    double grade_point;

    Course(string course_name, int course_credits, string course_grade)
        : name(course_name), credits(course_credits), grade(course_grade) {
        grade_point = calculate_grade_point();
    }

private:
    double calculate_grade_point() {
        unordered_map<string, double> grade_to_point = {
            {"A", 4.0},
            {"A-", 3.66},
            {"B+", 3.3},
            {"B", 3.0},
            {"B-", 2.7},
            {"C+", 2.3},
            {"C", 2.0},
            {"C-", 1.7},
            {"D+", 1.3},
            {"D", 1.0},
            {"D-", 0.7},
            {"F", 0.0}
        };
        return grade_to_point[grade];
    }
};

class Student {
public:
    void add_course(const Course& course) {
        courses.push_back(course);
    }

    double calculate_gpa() {
        int total_credits = 0;
        double total_grade_points = 0.0;

        for (const auto& course : courses) {
            total_credits += course.credits;
            total_grade_points += course.credits * course.grade_point;
        }

        if (total_credits == 0) {
            return 0.0;
        }
        return total_grade_points / total_credits;
    }

    void update_cumulative_gpa() {
        total_cumulative_credits = 0;
        cumulative_grade_points = 0.0;

        for (const auto& course : courses) {
            total_cumulative_credits += course.credits;
            cumulative_grade_points += course.credits * course.grade_point;
        }
    }

    double calculate_cgpa() {
        if (total_cumulative_credits == 0) {
            return 0.0;
        }
        return cumulative_grade_points / total_cumulative_credits;
    }

    void display_results() {
        cout << "Course Grades:" << endl;
        for (const auto& course : courses) {
            cout << "Course: " << course.name 
                 << ", Credits: " << course.credits 
                 << ", Grade: " << course.grade 
                 << ", Grade Points: " << course.grade_point 
                 << endl;
        }

        int total_credits = 0;
        double total_grade_points = 0.0;

        for (const auto& course : courses) {
            total_credits += course.credits;
            total_grade_points += course.credits * course.grade_point;
        }

        double gpa = calculate_gpa();
        update_cumulative_gpa();
        double cgpa = calculate_cgpa();

        cout << "\nTotal Credits: " << total_credits << endl;
        cout << "Total Grade Points: " << fixed << setprecision(2) << total_grade_points << endl;
        cout << "Semester GPA: " << fixed << setprecision(2) << gpa << endl;
        cout << "Cumulative GPA: " << fixed << setprecision(2) << cgpa << endl;
    }

private:
    vector<Course> courses;
    int total_cumulative_credits = 0;
    double cumulative_grade_points = 0.0;
};

int main() {
    Student student;
    int num_semesters;

    cout << "Enter the number of semesters you want to input grades for: ";
    cin >> num_semesters;
    cin.ignore();

    for (int sem = 1; sem <= num_semesters; ++sem) {
        cout << "\nSemester " << sem << ":" << endl;
        int num_courses;

        cout << "Enter the number of courses for semester " << sem << ": ";
        cin >> num_courses;
        cin.ignore();

        for (int i = 0; i < num_courses; ++i) {
            string name;
            int credits;
            string grade;

            cout << "Enter the course name: ";
            getline(cin, name);
            cout << "Enter the credits for " << name << ": ";
            cin >> credits;
            cout << "Enter the grade earned for " << name << ": ";
            cin >> grade;
            cin.ignore();

            unordered_map<string, double> valid_grades = {
                {"A", 4.0},
                {"A-", 3.66},
                {"B+", 3.3},
                {"B", 3.0},
                {"B-", 2.7},
                {"C+", 2.3},
                {"C", 2.0},
                {"C-", 1.7},
                {"D+", 1.3},
                {"D", 1.0},
                {"D-", 0.7},
                {"F", 0.0}
            };

            if (valid_grades.find(grade) == valid_grades.end()) {
                cout << "Invalid grade entered. Please enter a valid grade (A, A-, B+, B, B-, C+, C, C-, D+, D, D-, F)." << endl;
                --i;
                continue;
            }

            Course course(name, credits, grade);
            student.add_course(course);
        }

        
        cout << "\nResults for Semester " << sem << ":" << endl;
        student.display_results();

        
        student = Student();
    }

    return 0;
}
