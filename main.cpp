#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct discipline{
    discipline(const string& new_name, const float& new_mark) {
        name = new_name;
        mark = new_mark;
    }
    string name;
    float mark = 0;
};

struct student{
    student(const string& new_full_name, string& new_res, vector<discipline> new_results) {
        full_name = new_full_name;
        int size = new_res.length();
        for (int i = 0; i < size; ++i) {
            if (new_res[i] == ',') {
                new_res.erase(i, 1);
            }
        }
        int count = 0;
        for (const char& new_mark : new_res) {
            new_results[count].mark = static_cast<int>(new_mark) - 48;
            ++count;
        }
        results = new_results;
    }
    string full_name;
    vector<discipline> results;
};

ostream& operator<<(ostream& output, const student& stud) {
    output << stud.full_name << endl;
    for (const discipline& i : stud.results) {
        output << "- " << i.name << ' ' << i.mark << endl;
    }
    return output;
}

void binary_input_base (const string& name_input, int& count_stud, int& count_dis, vector<student>& students,
                 vector<discipline>& disciplines) {
    ifstream input(name_input, ios::binary);
    if (input) {
        string line;
        line.resize(1);
        string count;
        while (line != " ") {
            input.read(line.data(), 1);
            count += line;
        }
        count.erase(count.size() - 1, 1);
        count_dis = stoi(count);
        while (line != "\n") {
            input.read(line.data(), 1);
        }
        line.resize(1);
        count.clear();
        string dis;
        for (int i = 0; i < count_dis; ++i) {
            dis.clear();
            input.read(line.data(), 1);
            while (line != "\n") {
                if ((line != "\n") && (line != "\r")) {
                    dis += line;
                }
                input.read(line.data(), 1);
            }
            disciplines.emplace_back(discipline(dis, 0));
        }
        while (line != " ") {
            input.read(line.data(), 1);
            if (line != " ") {
                count += line;
            }
        }
        count_stud = stoi(count);
        while (line != "\n") {
            input.read(line.data(), 1);
        }
        line.resize(1);
        count.clear();
        string stud, res;
        for (int i = 0; i < count_stud; ++i) {
            stud.clear();
            res.clear();
            input.read(line.data(), 1);
            while (line != "{") {
                if (line != "{") {
                    stud += line;
                }
                input.read(line.data(), 1);
            }
            stud.erase(stud.size() - 1, 1);
            while (line != "\n") {
                input.read(line.data(), 1);
                if ((line != "}") && (line != "\n") && (line != "\r")) {
                    res += line;
                }
            }
            student new_stud(stud, res, disciplines);
            students.emplace_back(new_stud);
        }
        input.close();
    } else {
        return;
    }
}

void binary_output_base(const string& name, const vector<student>& students, const vector<discipline>& disciplines) {
    ofstream output(name);
    string new_line = "\n";
    for (const auto& i : students) {
        output.write(i.full_name.c_str(), i.full_name.length());
        string space = " ";
        output.write(new_line.c_str(), 1);
        for (const discipline& j : i.results) {
            string dash = "- ";
            output.write(dash.c_str(), 2);
            output.write(j.name.c_str(), j.name.length());
            output.write(space.c_str(), 1);
            float mark = j.mark;
            string new_mark = to_string(mark);
            output.write(new_mark.c_str(), 1);
            output.write(new_line.c_str(), 1);
        }
    }
    string help_str;
    float max_at_all = -1;
    int best_discipline;
    for (int i = 0; i < disciplines.size(); ++i) {
        float value_marks = 0;
        float max = 0;
        for (int j = 0; j < students.size(); ++j) {
            value_marks += students[j].results[i].mark;
            if (max < value_marks/students.size()){
                max = value_marks/students.size();
            }
        }
        if (max_at_all < max){
            max_at_all = max;
            best_discipline = i;
        }
        help_str = "middle mark is ";
        output.write(disciplines[i].name.c_str(), disciplines[i].name.length());
        output.write(help_str.c_str(), help_str.length());
        string new_max = to_string(max);
        output.write(new_max.c_str(), new_max.length());
        output.write(new_line.c_str(), 1);
    }
    help_str = "The best discipline is ";
    output.write(help_str.c_str(), help_str.length());
    output.write(disciplines[best_discipline].name.c_str(), disciplines[best_discipline].name.length());
    help_str = " with middle mark: ";
    string new_max_at_all = to_string(max_at_all);
    output.write(help_str.c_str(), help_str.length());
    output.write(new_max_at_all.c_str(), new_max_at_all.length());
    output.close();
}

void input_base (const string& name_input, int& count_stud, int& count_dis, vector<student>& students,
                 vector<discipline>& disciplines) {
    ifstream input(name_input);
    if (input) {
        string line;
        input >> count_dis;
        getline(input, line);
        for (int i = 0; i < count_dis; ++i) {
            getline(input, line);
            disciplines.emplace_back(discipline(line, 0));
        }
        input >> count_stud;
        getline(input, line);
        for (int i = 0; i < count_stud; ++i) {
            getline(input, line);
            string name = line.substr(0, line.find('{') - 1);
            string res = line.substr(line.find('{') + 1, line.find('}') - line.find('{') - 1);
            student new_stud(name, res, disciplines);
            students.emplace_back(new_stud);
        }
        input.close();
    } else {
        return;
    }
}

void output_base(const string& name, const vector<student>& students, const vector<discipline>& disciplines) {
    ofstream output(name);
    for (const auto& i : students) {
        output << i;
    }
    float max_at_all = -1;
    int best_discipline;
    for (int i = 0; i < disciplines.size(); ++i) {
        float value_marks = 0;
        float max = 0;
        for (int j = 0; j < students.size(); ++j) {
            value_marks += students[j].results[i].mark;
            if (max < value_marks/students.size()){
                max = value_marks/students.size();
            }
        }
        if (max_at_all < max){
            max_at_all = max;
            best_discipline = i;
        }
        output << disciplines[i].name << " middle mark is " << max << std::endl;
    }
    output << "The best discipline is " << disciplines[best_discipline].name << " with middle mark: " << max_at_all;
    output.close();
}

int main() {
    string name;
    cout << "Enter mode:\n1)Text\n2)Binary\n";
    char mode;
    cin >> mode;
    if (mode == '1') {
        cout << "Enter name of input file :"; //O:\\Albert_Files\\LR6\\input.txt
        cin.ignore();
        getline(cin, name);
        int count_of_students, count_disciplines;
        vector<student> students;
        vector<discipline> disciplines;
        input_base(name, count_of_students, count_disciplines, students, disciplines);
        sort(students.begin(), students.end(), [](const student& first, const student& second) {
            return first.full_name < second.full_name;
        });
        cout << "Enter name of output file :";
        getline(cin, name);
        output_base(name, students, disciplines);
    } else if (mode == '2') {
        cout << "Enter name of input file :";
        cin.ignore();
        getline(cin, name);
        int count_of_students, count_disciplines;
        vector<student> students;
        vector<discipline> disciplines;
        binary_input_base(name, count_of_students, count_disciplines, students, disciplines);
        sort(students.begin(), students.end(), [](const student& first, const student& second) {
            return first.full_name < second.full_name;
        });
        cout << "Enter name of output file :";
        getline(cin, name);
        binary_output_base(name, students, disciplines);
    } else {
        cout << "Enter 1 or 2!!!";
        return 0;
    }
}
