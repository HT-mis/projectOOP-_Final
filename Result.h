#pragma once
#include <iostream>

using namespace std;

template <class T>
class Result 
{
private:
    int totalCorrect;
    int totalQuestions;
    T score;

public:

    Result(int correct, int total) 
    {
        this->totalCorrect = correct;
        this->totalQuestions = total;

        if (total > 0) 
        {
            double calculatedScore = (static_cast<double>(correct) / total) * 10.0;
            this->score = static_cast<T>(calculatedScore);
        }
        else 
        {
            this->score = static_cast<T>(0);
        }
    }

    void display() const 
    {
        cout << "Số câu đúng: " << totalCorrect << "/" << totalQuestions << endl;
        cout << "Điểm: " << score << endl;
    }

    //getter
    T getScore() const 
    {
        return score;
    }
    int getTotalCorrect() const 
    {
        return totalCorrect;
    }
    int getTotalQuestions() const 
    {
        return totalQuestions;
    }
};