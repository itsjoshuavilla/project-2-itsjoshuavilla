#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//  Base Class 
class Student {
protected:
    string first_name;
    string last_name;
    double gpa;
    int grad_year;
    string grad_semester;
    int enroll_year;
    string enroll_semester;
    string level; // "Undergraduate" or "Graduate"

public:
    // Default constructor
    Student() {
        first_name = "Unknown";
        last_name = "Unknown";
        gpa = 0.0;
        grad_year = 0;
        grad_semester = "N/A";
        enroll_year = 0;
        enroll_semester = "N/A";
        level = "Undergraduate";
    }

    // Destructor
    virtual ~Student() {}

    // Setters
    void setName(const string &first, const string &last) {
        first_name = first;
        last_name = last;
    }

    void setGPA(double g) { gpa = g; }
    void setGradInfo(int year, const string &semester) {
        grad_year = year;
        grad_semester = semester;
    }
    void setEnrollInfo(int year, const string &semester) {
        enroll_year = year;
        enroll_semester = semester;
    }
    void setLevel(const string &lvl) { level = lvl; }

    // Getters
    string getName() const { return first_name + " " + last_name; }
    double getGPA() const { return gpa; }
    int getGradYear() const { return grad_year; }
    string getGradSemester() const { return grad_semester; }
    int getEnrollYear() const { return enroll_year; }
    string getEnrollSemester() const { return enroll_semester; }
    string getLevel() const { return level; }

    // Virtual print function for file output
    virtual void printInfo(ofstream &outfile) const {
        outfile << "Name: " << getName() << endl;
        outfile << "GPA: " << gpa << endl;
        outfile << "Level: " << level << endl;
        outfile << "Enrolled: " << enroll_semester << " " << enroll_year << endl;
        outfile << "Graduation: " << grad_semester << " " << grad_year << endl;
    }
};

// Derived Class: Art Student 
class Art_Student : public Student {
private:
    string art_emphasis; // Art Studio, Art History, Art Education

public:
    Art_Student() : Student() {
        art_emphasis = "Art Studio";
    }

    void setArtEmphasis(const string &emph) { art_emphasis = emph; }
    string getArtEmphasis() const { return art_emphasis; }

    void printInfo(ofstream &outfile) const override {
        outfile << "=== Art Student ===" << endl;
        Student::printInfo(outfile);
        outfile << "Emphasis: " << art_emphasis << endl;
        outfile << "--------------------" << endl;
    }
};

// Derived Class: Physics Student 
class Physics_Student : public Student {
private:
    string concentration; // Biophysics, Earth and Planetary Sciences

public:
    Physics_Student() : Student() {
        concentration = "Biophysics";
    }

    void setConcentration(const string &conc) { concentration = conc; }
    string getConcentration() const { return concentration; }

    void printInfo(ofstream &outfile) const override {
        outfile << "=== Physics Student ===" << endl;
        Student::printInfo(outfile);
        outfile << "Concentration: " << concentration << endl;
        outfile << "--------------------" << endl;
    }
};

// ---------------- Main 
int main() {
    vector<Art_Student *> art_students;
    vector<Physics_Student *> physics_students;

    // Create and populate Art Students
    for (int i = 0; i < 5; i++) {
        Art_Student *a = new Art_Student();
        a->setName("ArtFirst" + to_string(i+1), "ArtLast" + to_string(i+1));
        a->setGPA(3.0 + 0.1 * i);
        a->setGradInfo(2026, "Spring");
        a->setEnrollInfo(2022, "Fall");
        a->setLevel("Undergraduate");
        if (i % 3 == 0) a->setArtEmphasis("Art Studio");
        else if (i % 3 == 1) a->setArtEmphasis("Art History");
        else a->setArtEmphasis("Art Education");
        art_students.push_back(a);
    }

    // Create and populate Physics Students
    for (int i = 0; i < 5; i++) {
        Physics_Student *p = new Physics_Student();
        p->setName("PhysFirst" + to_string(i+1), "PhysLast" + to_string(i+1));
        p->setGPA(3.5 + 0.05 * i);
        p->setGradInfo(2027, "Fall");
        p->setEnrollInfo(2023, "Spring");
        p->setLevel("Graduate");
        if (i % 2 == 0) p->setConcentration("Biophysics");
        else p->setConcentration("Earth and Planetary Sciences");
        physics_students.push_back(p);
    }

    // Write to file
    ofstream outfile("student_info.dat");
    if (!outfile) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }

    outfile << "===== STUDENT INFORMATION =====" << endl << endl;

    for (auto a : art_students) a->printInfo(outfile);
    for (auto p : physics_students) p->printInfo(outfile);

    outfile.close();
    cout << "Student data written to 'student_info.dat'" << endl;

    // Clean up
    for (auto a : art_students) delete a;
    for (auto p : physics_students) delete p;

    return 0;
}
