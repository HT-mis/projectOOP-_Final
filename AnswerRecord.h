#pragma once
#include <iostream>
using namespace std;

class AnswerRecord
{
private:
    int questionID;
    int chosenAnswer;
    bool skipped;

public:
    AnswerRecord(int qID)
    {
        questionID = qID;
        chosenAnswer = -1;
        skipped = false;
    }

    void markAnswer(int option)
    {
        if(option >= 0 && option <= 3)
        {
            chosenAnswer = option;
            skipped = false;
        }
        else
        {
            cout << "Lựa chọn không hợp lệ. Phải là 0 - 3" << endl;
        }
    }

    void markSkip()
    {
        skipped = true;
    }

    bool isAnswer() const
    {
        return(chosenAnswer != -1 && !skipped);
    }

    bool isSkipped() const
    {
        return skipped;
    }

    int getAnswer() const
    {
        return chosenAnswer;
    }

    int getQuestionID() const
    {
        return questionID;
    }
};