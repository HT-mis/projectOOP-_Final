#pragma once
#include"MultipleChoiceQuestion.h"
#include"User.h"
#include"AnswerRecord.h"
#include"FileManager.h"
#include"View.h"
#include"Timer.h"
class Quiz
{
private:
    vector<MultipleChoiceQuestion*>questions;// lưu câu hỏi
    vector<AnswerRecord*> answers; // lưu câu trả lời .
    int index; // só thứ tự
    User user; // người làm bài
    View view; // trình bày
    Timer time; // thời gian
    minutes examDuration; // thời gian thi
    string resultFile;
    bool isRunning;
public:
    Quiz(const string& fileName, const string& result)
        :resultFile(result), isRunning(false),index(0)
    {
        int examDuration = 0;
        questions = FileManager::loadQuestion(fileName,examDuration);
        this->examDuration =  minutes( examDuration);
        for(auto* q: questions){
            answers.push_back(new AnswerRecord(q->getID()));
        }
        index = 0;
    }
    ~Quiz(){
        for(auto* q: questions){
            delete q;
        }
        for (auto* a: answers){
            delete a;
        }
    }
    void start(){
        view.displayWelcome();// hiển thị chào mừng
        user.inputInfo(); // lưu thông tin thí sinh
        time.start(); // tính giờ
        isRunning = true; //set cờ hiệu
        processloop(); // hàm chạy vòng lặp hiện câu hỏi.
    }
private:
    void maps(int newIndex){
        if(newIndex >=questions.size()){ // tăng số thứ tự trong câu 
            index = 0;
        }else if(newIndex < 0){
            index = -1;
        }else{
            index = newIndex;
        }
    }
    void handleSubmit(){
        time.stop();
        isRunning = false;
        int correctCount = 0;
        for(int i = 0; i < questions.size(); i++){
            if(questions[i]->checkAnswer(answers[i]->getAnswer())){ // chấm điểm.
                correctCount ++;
            }
        }
        Result<double> result(correctCount, questions.size());
        long long totalMinute = time.getTotalElapsed().count();
        long long minute = totalMinute / 60;
        long long second = totalMinute % 60;
        string totalM = to_string(minute) +":" +to_string(second);
        
        view.displayResult(user,result,time.getStartTime(),totalM);
        FileManager::saveResult(resultFile,user.getName(),user.getID(),result.getScore());
    }
    // xóa màn hình 
    void clearScreen()
    {
    #ifdef _WIN32
    // Nếu là Windows (Win32/Win64)
        std::system("cls");
    #else
    // Nếu là hệ thống POSIX (Linux, macOS)
        std::system("clear");
    #endif
    }
    void processloop(){
        while (isRunning)   
        {
            if(time.isTimeUp(examDuration)){
                cout<<"Het gio!"<<endl;
                handleSubmit();
                break;
            }
            clearScreen();
            auto currentQuestion = questions[index];    // lấy câu hỏi theo index.
            auto currentAnswer = answers[index]; // lấy câu trả lời theo index. auto là tự xác định kiểu dữ liệu
            int timeLeftSec = time.getRemainingTime(examDuration).count();// thời gian đếm ngược.
            view.displayHeader(index,questions.size(), timeLeftSec);// hiển thị câu hỏi 1/size, thời gian còn lại.
            view.displayQuestion(*currentQuestion);// hiển thị câu hỏi
            view.displayQuestionStatus(*currentAnswer);// trạng thái câu hỏi .
            view.displayMenu(); // hiển thị menu chọn next pre..
            char choice = view.getUserChoice();
            // lựa chọn
            switch (choice)
            {
            case 'A':
                answers[index]->markAnswer(view.charToOptionIndex(choice));
                break;
            case 'B':
                answers[index]->markAnswer(view.charToOptionIndex(choice));
                break;
            case 'C':
                answers[index]->markAnswer(view.charToOptionIndex(choice));
                break;
            case 'D':
                answers[index]->markAnswer(view.charToOptionIndex(choice));
                break;
            case 'N':
                maps(index +1);
                break;
            case 'P':
                maps(index - 1);
                break;
            case 'S':
                answers[index]->markSkip();
                maps(index + 1);
                break;
            case 'J':
                {   
                int num = view.inputQuestionNumber(questions.size());
                maps(num);
                break;
                }
            case 'Q':
                if(view.confirmSubmit()){
                    handleSubmit();
                }
                break;  
        }
        
    }
    
}
};
