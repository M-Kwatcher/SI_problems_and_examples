#include <iostream>
#include <string>
#include <vector>


class GradeBook{
    public:
        const std::vector<int>& getGrades() const {
            return grades;
        }

        void setGrades(const std::vector<int>& newGrades) {
            grades = newGrades;
        }

        const std::string& getInstructorName() const {
            return instructorName;
        }

        void setInstructorName(const std::string& newInstructorName) {
            instructorName = newInstructorName;
        }

        int getNumStudents() const {
            return numStudents;
        }

        void setNumStudents(int newNumStudents) {
            numStudents = newNumStudents;
        }

        void printGrades() const {
            for (int i = 0; i < grades.size()-1; i++){
                std::cout << grades[i] << " ";
            }
            std::cout << std::endl;
        }

    private:
        std::vector<int> grades{};
        std::string instructorName;
        int numStudents;
};
