#include "Quiz.h" // Nhúng file class Quiz của bạn
#include <iostream>

using namespace std;

int main()
{
    try
    {
        // === CÀI ĐẶT BÀI THI ===

        // 1. Tên file chứa câu hỏi
        string questionFile = "questions.txt"; 


        // 2 Tên file để lưu kết quả
        string resultFile = "results.txt";

        
        cout << "Dang khoi tao bai thi..." << endl;
        Quiz quiz(questionFile,resultFile);

        // === BẮT ĐẦU THI ===
        quiz.start();

        cout << "\nCam on ban da hoan thanh bai thi!" << endl;
    }
    catch (const exception& e)
    {
        // Bắt lỗi chung, ví dụ như không tìm thấy file
        cerr << "Loi: " << e.what() << endl;
    }
    catch (...)
    {
        // Bắt các lỗi không xác định
        cerr << "Da xay ra loi khong xac dinh!" << endl;
    }

    // Dừng màn hình console lại để xem kết quả (nếu cần)
    cout << "Nhan Enter de thoat..." << endl;
    cin.get(); // Đợi người dùng nhấn Enter
    
    return 0;
}