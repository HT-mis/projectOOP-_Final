#pragma once
#include "BaseQuestion.h" 
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class MultipleChoiceQuestion : public BaseQuestion 
{
private:
    vector<string> options;
    int correctIndex;

public:
    MultipleChoiceQuestion(int id, string content, vector<string> opts, int correct)
        : BaseQuestion(id, content)// gôi ham tao cua BaseQuestion
    {
        this->correctIndex = correct;
        
        this->options = opts;
    
    }

    //Override các ham ao
    void display() const override 
    {
        cout << "Câu " << id << ": " << content << endl;
        char optionChar = 'A';
        for (int i = 0; i < 4; ++i) 
        {
            cout << "  " << optionChar << ". " << options[i] << endl;
            optionChar++;
        }
    }

    bool checkAnswer(int option) const override 
    {
        return option == correctIndex;
    }
};