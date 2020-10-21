#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct discipline{
    std::string name;
    float mark;
};
struct student{
    std::string full_name;
    std::vector<discipline> results;
};
int main() {
    std::cout << "Enter count of students = ";
    unsigned int count_student;
    std::cin >> count_student;
    std::vector<student> vec(count_student);
    std::cout << "Enter count of disciplines = ";
    unsigned int count_disciplines;
    std::cin >> count_disciplines;
    std::vector<discipline> add(count_disciplines);
    std::cout << 1 << ". Discipline = ";
    std::cin.ignore();
    std::getline(std::cin, add[0].name);
    for (int j = 1; j < count_disciplines; ++j) {
        std::cout << j+1 << ". Discipline = ";
        std::getline(std::cin, add[j].name);
    }
    std::cout << std::endl;

    std::cout << 1 << ". Full name = ";
    std::getline(std::cin, vec[0].full_name);
    std::cout << "Enter marks:" << std::endl;
    for (int j = 0; j < count_disciplines; ++j) {
        std::cout << j + 1 << ". Discipline is " << add[j].name << std::endl;
        std::cout << "Enter mark = ";
        std::cin >> add[j].mark;
        vec[0].results.push_back(add[j]);
    }

    for (int i = 2; i <= count_student; ++i){
        std::cout << i << ". Full name = ";
        std::cin.ignore();
        std::getline(std::cin, vec[i-1].full_name);
        std::cout << "Enter marks:" << std::endl;
        for (int j = 0; j < count_disciplines; ++j) {
            std::cout << j+1 << ". Discipline is " << add[j].name << std::endl;
            std::cout << "Enter mark = ";
            std::cin >> add[j].mark;
            vec[i-1].results.push_back(add[j]);
        }
    }

    for (int i = 0; i < count_student-1; ++i) {
        for (int j = i+1; j < count_student; ++j) {
            if (vec[i].full_name > vec[j].full_name){
                std::swap(vec[i], vec[j]);
            }
        }
    }
    std::ofstream stream;
    stream.open("LR6.txt");
    for (int i = 0; i < count_student; ++i){
        stream << i+1 << ". " << vec[i].full_name << std::endl;
        for (int j = 0; j < count_disciplines; ++j) {
            stream << i+1 << "." << j+1 << ". " << vec[i].results[j].name << ' ' << vec[i].results[j].mark << std::endl;
        }
        stream << std::endl;
    }
    float value_marks;
    float max = -1;
    float max_at_all = -1;
    int best_discipline;
    for (int i = 0; i < count_disciplines; ++i) {
        value_marks = 0;
        max = -1;
        for (int j = 0; j < count_student; ++j) {
            value_marks += vec[j].results[i].mark;
            if (max < value_marks/count_student){
                max = value_marks/count_student;
            }
        }
        if (max_at_all < max){
            max_at_all = max;
            best_discipline = i;
        }
        stream << add[i].name << " middle mark is " << max << std::endl;
    }
    stream << "The best discipline is " << add[best_discipline].name << " with middle mark: " << max_at_all;
    stream.close();
    return 0;
}
