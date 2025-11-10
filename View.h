#pragma once
#include<iostream>
#include<string>

//
#include "BaseQuestion.h"
#include "AnswerRecord.h"
#include "User.h"
#include "Result.h"


using namespace std;

class View {
public:
//	Hang--------------------------------------------------------------------------------------
	View() {}
	void displayWelcome(){
		cout << "--------------------------------------------" << endl;
	 	cout << "\t CHUONG TRINH THI TRAC NGHIEM" << endl;
		cout << "--------------------------------------------" << endl;
    	cout << "\t NOTE: Ban co the chon trả loi hoac skip sang cau tiep theo"<<endl;
    	cout << "\t Chuc ban hoan thanh tot bai trac nghiem!" << endl;
		cout << "--------------------------------------------" << endl;
	} //hien thi chao mung, HDSD
	void displayHeader(int current, int total, int timeLeft){
		int minutes = timeLeft / 60; //phut
		int seconds = timeLeft % 60; //giay
	
		string minStr = (minutes < 10 ? "0" : "") + to_string(minutes);
		string secStr = (seconds < 10 ? "0" : "") + to_string(seconds);

		cout  << current + 1 << "|" << total
		<< " | \t Thời gian còn lại: "
		<< minStr << ":" << secStr << endl;
	}//so cau ht, tong , thoi gian con lai
	void displayQuestion(const BaseQuestion&question){
		question.display();
	}//hien thi ques
	void displayQuestionStatus(const AnswerRecord& record){
		  //skip
    	if (record.isSkipped()) {
        	cout << "Trang thai: Đa skip" << std::endl;
    	}
    //tra loi
    	else if (record.isAnswer()) {
        	char choice = 'a' + record.getAnswer();
        	cout << "Trang thai: Đa tra loi (" << choice << ")" << std::endl;
    	}
    //chua chon
    	else {
        	cout << "Trang thai: Chua tra loi" << std::endl;
    	}
	}//trang thai cau hoi hien tai

	//ket qua cuoi cung
	void displayResult(const User& user, const Result<double>& result, const string& startTime, const string& totalTime){
		cout << "--------------------------------------------" << endl;
    	cout << "\t KET QUA BAI THI" << endl;
    	cout << "Ho ten: " << user.getName() << endl;
    	cout << "Ma sinh vien: " << user.getID() << endl;
    	cout << "Thoi gian bat đau: " << startTime << endl;
    	cout << "Tong thoi gian lam bai: " << totalTime << endl;
    	result.display();
    	cout << "--------------------------------------------" << endl;
	}
	void displayMenu(){
		cout << "Lựa chọn: N (Next), P (Previous), S (Skip), J (Jump)\n	a/b/c/d (Chọn đáp án), Q (Submit)" << endl;
	}//hien thi chon thao tac
	void displayPrompt(const string& message){
		cout << message;
	}//nhac nhap ten
	void displayError(const string& error){
		cout << "[31m" << error << "[0m" << endl; 
	}//thong bao loi



	/// Hoanh -------------------------------------------------------------------------------------------------///
	///  
	char getUserChoice(){
		while (true) {
		std::string s;
		if (!std::getline(std::cin, s)) continue;
		if (s.empty()) continue;
		char c = std::toupper(s[0]);
		std::string valid = "NPJSQABCD";
		if (valid.find(c) != std::string::npos) return c;
		displayError("Lua chon khong hop le!");
		displayPrompt("Nhap lai: ");
	}
	}
	bool confirmSubmit(){
		while (true) {
		std::string s;
		displayPrompt("Ban co chac muon nop bai? (Y/N): ");
		if (!std::getline(std::cin, s)) continue;
		if (s.empty()) continue;
		char c = std::toupper(s[0]);
		if (c == 'Y') return true;
		if (c == 'N') return false;
		displayError("Nhap Y hoac N!");
	}

	}
	int inputQuestionNumber(int totalQuestions){
		while (true) {
		displayPrompt("Nhap so thu tu cau (1-" +
			std::to_string(totalQuestions) + "): ");
		std::string s;
		if (!std::getline(std::cin, s)) continue;
		try {
			int v = std::stoi(s);
			if (v >= 1 && v <= totalQuestions) return v - 1;
		}
		catch (...) {}
		displayError("So khong hop le!");
	}
	}
	std::string inputName(){
		std::string s;
		if (!std::getline(std::cin, s)) s = "";
		// trim
		auto l = s.find_first_not_of(" \t\n\r\f\v");
		if (l == std::string::npos) return "";
		auto r = s.find_last_not_of(" \t\n\r\f\v");
		return s.substr(l, r - l + 1);
	}
	std::string inputStudentID(){
		std::string s;
		if (!std::getline(std::cin, s)) s = "";
		auto l = s.find_first_not_of(" \t\n\r\f\v");
		if (l == std::string::npos) return "";
		auto r = s.find_last_not_of(" \t\n\r\f\v");
		return s.substr(l, r - l + 1);
	}
	int charToOptionIndex(char choice){
		choice = std::toupper(choice);
		if (choice >= 'A' && choice <= 'D') return choice - 'A';
		return -1;
	}
};



