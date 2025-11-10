#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

class User
{
private:
    string name;
    string studentID;

    string trim(const string& str)
    {
        size_t first = str.find_first_not_of("\t\n\r");
        if(first == string::npos) return "";
        size_t last = str.find_last_not_of("\t\n\r");
        return str.substr(first, (last - first + 1));
    }

public:
    void inputInfo()
    {
        do {
            cout << "Nhập họ tên thí sinh:";
            getline(cin, name);
            name = trim(name);
            if (name.empty())
            {
                cout << "Họ tên không được để trống" << endl;
            }
        } while (name.empty());

        do {
            cout << "Nhập mã số sinh viên:";
            getline(cin, studentID);
            studentID = trim(studentID);
            if(studentID.empty())
            {
                cout << "Mã số sinh viên không được để trống" << endl;
            }
        } while (studentID.empty());
    }

    string getName() const 
    {
        return name;
    }

    string getID() const
    {
        return studentID;
    }
};