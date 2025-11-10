#pragma once

#include <iostream>
#include <ctime>
#include <chrono>
#include <string>     
#include <sstream>    
#include <iomanip>    

using namespace std::chrono;
using namespace std;

class Timer
{
private:
    steady_clock::time_point start_time;
    time_point<system_clock> m_systemStartTime;
    steady_clock::time_point m_stopTime; 
    bool m_isRunning = false;            

public:
    Timer() = default;
    // danh dau thoi gian bat dau
    void start() {
        start_time = steady_clock::now();
        m_systemStartTime = system_clock::now();
        m_isRunning = true; 
        cout << "Thoi gian bat dau!" << endl;
    }
    // dung khi submit
    bool stop() {
        if (!m_isRunning) {
            std::cout << "Canh bao: Timer chua chay hoac da dung roi." << std::endl;
            return false;
        }
        m_stopTime = steady_clock::now();
        m_isRunning = false;
        std::cout << "Thoi gian ket thuc va da duoc luu!" << std::endl;
        return true;
    }
    // dong ho bam gio
    chrono::seconds getRemainingTime(minutes ExamDuration) const {
        if (!m_isRunning) return seconds(0);

        auto elapsed = steady_clock::now() - start_time;
        
        seconds remaining = duration_cast<seconds>(ExamDuration) 
                            - duration_cast<seconds>(elapsed);
        
        if (remaining.count() < 0) {
            return seconds(0);
        }
        return remaining;
    }
    // kiem tra xem con thoi giankhong
    bool isTimeUp(minutes ExamDuration) const {
        return getRemainingTime(ExamDuration).count() <= 0;
    }
    // thoi gian bat dau de hien thi sau cuoi
   string getStartTime() const {
    
    // 1. Chuyển kiểu time_point (C++ mới) sang time_t (C cũ)
    // Đây là bước bắt buộc
     time_t start_time_t = system_clock::to_time_t(m_systemStartTime);

    // 2. Lấy struct tm (cấu trúc có giờ, phút, giây) từ time_t
    // Dùng localtime để lấy giờ địa phương
    tm* local_time = localtime(&start_time_t);

    // 3. Tạo một buffer (mảng char) để chứa chuỗi kết quả
    // "HH:MM" là 5 ký tự, cộng 1 ký tự null '\0' -> cần 6.
    // Lấy 10 cho an toàn.
    char buffer[10];

    // 4. Định dạng thời gian vào buffer
    // strftime = "String Format Time"
    // "%H" = Giờ (24h)
    // "%M" = Phút
    strftime(buffer, sizeof(buffer), "%H:%M", local_time);

    // 5. Chuyển mảng char đó thành một std::string và trả về
    return string(buffer);
}
    // tong thoi gian lam bai
    seconds getTotalElapsed() const {
        if (!m_isRunning) {
            return duration_cast<seconds>(m_stopTime - start_time);
        }
        return duration_cast<seconds>(steady_clock::now() - start_time);
    }
};