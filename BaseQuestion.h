#pragma once
#include <iostream>
#include <string>

using namespace std;

class BaseQuestion 
{
protected:
    int id;
    string content;

public:
    BaseQuestion(int id, const string& content) 
    {
        this->id = id;
        this->content = content;
    }

    //ham thuan ao
    virtual void display() const = 0;
    virtual bool checkAnswer(int option) const = 0;
    virtual ~BaseQuestion() = default;

    //getter
    int getID() const 
    {
        return id;
    }
    string getContent() const 
    {
        return content;
    }
};