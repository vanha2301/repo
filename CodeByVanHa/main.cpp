#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <fstream>
#include <vector>
using namespace std;

string passworkSystem = "vanha2301";
// ngày giờ thời gian hiện tại.
string currentTime;
// file data lưu kế hoạch.
int markFileDataPlan[1000000][100];
bool markAnnouncementMoneyeveryday;
vector <string> fileDataPlan;
// Thông báo hệ thống, thông báo chương trình NOTE.
string thongBaoChuongTrinhNote = "%F0%9F%93%A2%3A%20%C4%90%C3%A2y%20l%C3%A0%20th%C3%B4ng%20b%C3%A1o%20t%E1%BB%AB%20h%E1%BB%87%20th%E1%BB%91ng%20th%C3%B4ng%20b%C3%A1o%20%C4%91%E1%BA%BFn%20t%E1%BB%AB%20ch%C6%B0%C6%A1ng%20tr%C3%ACnh%20GHI%20CH%C3%9A%0A";
// time Now
int dayNow, monthNow, yearNow, hourNow, minNow, secNow;
// số ngày còn lại khi sử dụng tiền.
int dayMoney;
string DocTinNhan() {
    std::string token = "7713713238:AAFrtM47YMZNQDmZk-xOvERLhmVCrftRmm4";  // Thay bằng token của bạn
    std::string command = "curl -s \"https://api.telegram.org/bot" + token + "/getUpdates\"";

    FILE* pipe = _popen(command.c_str(), "r");  // Dùng _popen trên Windows
    if (!pipe) return "Lỗi khi gọi API!";

    char buffer[1024];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;  // Đọc dữ liệu vào biến result
    }

    _pclose(pipe);  // Đóng pipe

    // Tìm tin nhắn cuối cùng (bằng cách tìm phần tử "text" cuối cùng)
    size_t lastTextPos = result.rfind("\"text\":\"");
    if (lastTextPos == std::string::npos) return "Không có tin nhắn nào!";

    lastTextPos += 8; // Nhảy qua `"text":"`
    size_t end = result.find("\"", lastTextPos); // Tìm dấu `"` đóng
    if (end == std::string::npos) return "Lỗi khi đọc tin nhắn!";

    return result.substr(lastTextPos, end - lastTextPos);
}

void ThongBao(std::string data) {
    std::string token = "7713713238:AAFrtM47YMZNQDmZk-xOvERLhmVCrftRmm4";  // Thay bằng token của bạn
    std::string chat_id = "7352518467";  // Thay bằng Chat ID của bạn
    std::string message = data;

    std::string command = "curl -s -X POST \"https://api.telegram.org/bot" + token +
        "/sendMessage\" -d \"chat_id=" + chat_id +
        "&text=" + message + "\" > nul 2>&1";

    system(command.c_str());  // Gửi thông báo
}
void setupTimeNow() {
    std::time_t now = std::time(nullptr);
    tm localTime;
    localtime_s(&localTime, &now);
    std::ostringstream timeStream;
    timeStream << std::setw(2) << std::setfill('0') << localTime.tm_mday << "/"
        << std::setw(2) << std::setfill('0') << (localTime.tm_mon + 1) << "/"
        << (localTime.tm_year + 1900) << " "
        << std::setw(2) << std::setfill('0') << localTime.tm_hour << ":"
        << std::setw(2) << std::setfill('0') << localTime.tm_min << ":"
        << std::setw(2) << std::setfill('0') << localTime.tm_sec;
    currentTime = timeStream.str();
    dayNow = std::stoi(currentTime.substr(0, 2));
    monthNow = std::stoi(currentTime.substr(3, 2));
    yearNow = std::stoi(currentTime.substr(6, 4));
    hourNow = std::stoi(currentTime.substr(11, 2));
    minNow = std::stoi(currentTime.substr(14, 2));
    secNow = std::stoi(currentTime.substr(17, 2));
}
void CinFileData() {
    //cin file data 
    ifstream cinFile("fileData.txt");
    string subject;
    while (getline(cinFile, subject)) {
        fileDataPlan.push_back(subject);
    }
    cinFile.close();
}
void OutFileData() {
    string time, title, text;
    ofstream outFile("fileData.txt", ios::app);

    cout << "Nhap Thoi Gian: ";
    getline(cin, time);
    outFile << time << endl;

    cout << "Nhap chu de: ";
    getline(cin, title);
    outFile << title << endl;

    cout << "Nhap noi dung: ";
    getline(cin, text);
    outFile << text << endl;
    outFile.close();
    system("cls");

    ThongBao("#############################################");
    ThongBao(thongBaoChuongTrinhNote);
    ThongBao("Ban vua cap nhat danh sach va them du lieu.");
    string tmp;
    setupTimeNow();
    tmp = "Thoi gian cap nhat la: " + currentTime;
    ThongBao(tmp);

    tmp = "Time: " + time;
    ThongBao(tmp);

    tmp = "Chu de: " + title;
    ThongBao(tmp);

    tmp = "Noi dung: " + text;
    ThongBao(tmp);

}
void updateFileData() {
    CinFileData();
    setupTimeNow();
    if (hourNow == 0 && minNow == 0 && secNow == 0) {
        ThongBao("Da cap nhat fileDataPlan");
    }
    ofstream data("fileData.txt");
    string dataNow;
    for (int i = 0; i < fileDataPlan.size(); i += 3) {
        dataNow = fileDataPlan[i];
        if (dayNow <= stoi(dataNow.substr(0, 2)) && monthNow <= stoi(dataNow.substr(3, 2)) && yearNow <= stoi(dataNow.substr(6, 4))) {
            data << fileDataPlan[i] << endl;
            data << fileDataPlan[i + 1] << endl;
            data << fileDataPlan[i + 2] << endl;
        }
    }
    data.close();
    CinFileData();

}
void TBFileDataPlan() {
    cout << "Dang chay ham TBFileDataPlan" << endl;
    system("cls");
    //CinFileData();
    setupTimeNow();
    string dataNow;
    for (int i = 0; i < fileDataPlan.size(); i += 3) {
        setupTimeNow();
        dataNow = fileDataPlan[i];
        int timeHour_Min_SecNow, timeHour_Min_SecPlan;
        timeHour_Min_SecNow = hourNow * 3600 + minNow * 60 + secNow;
        timeHour_Min_SecPlan = stoi(dataNow.substr(11, 2)) * 3600 + stoi(dataNow.substr(14, 2)) * 60 + stoi(dataNow.substr(17, 2));
        //cout << "loi o day";
        if (dayNow == stoi(dataNow.substr(0, 2)) && monthNow == stoi(dataNow.substr(3, 2)) && yearNow == stoi(dataNow.substr(6, 4)) && timeHour_Min_SecNow >= timeHour_Min_SecPlan && markFileDataPlan[i][0] == 1) {
            //cout << "loi o day";
            markFileDataPlan[i][0] = 0;
            string tmp;
            ThongBao("####################################");
            ThongBao(thongBaoChuongTrinhNote);
            tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
            ThongBao(tmp);

            tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
            ThongBao(tmp);

            tmp = "%F0%9F%97%9FText%3A%20" + fileDataPlan[i + 2];
            ThongBao(tmp);

        }
        // Thong bao truoc 15 phut.
        if (dayNow == stoi(dataNow.substr(0, 2)) && monthNow == stoi(dataNow.substr(3, 2)) && yearNow == stoi(dataNow.substr(6, 4)) && timeHour_Min_SecNow >= (timeHour_Min_SecPlan - 900) && markFileDataPlan[i][1] == 1) {
            markFileDataPlan[i][1] = 0;
            string tmp;
           ThongBao("####################################");
           ThongBao(thongBaoChuongTrinhNote);
           //📝:Bạn chỉ còn 15 phút với nội dung.
           ThongBao("%F0%9F%94%90%3AB%E1%BA%A1n%20%C4%91%C3%A3%20nh%E1%BA%ADp%20sai%20m%E1%BA%ADt%20kh%E1%BA%A9u%2C%20xin%20vui%20l%C3%B2ng%20nh%E1%BA%ADp%20l%E1%BA%A1i.");
           tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
           ThongBao(tmp);

           tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
           ThongBao(tmp);

           tmp = "%F0%9F%97%9FText%3A%20" + fileDataPlan[i + 2];
           ThongBao(tmp);


        }
        // Thông báo trước 30 phút.
        if (dayNow == stoi(dataNow.substr(0, 2)) && monthNow == stoi(dataNow.substr(3, 2)) && yearNow == stoi(dataNow.substr(6, 4)) && timeHour_Min_SecNow >= (timeHour_Min_SecPlan - 1800) && markFileDataPlan[i][2] == 1) {
            markFileDataPlan[i][2] = 0;
            string tmp;
           ThongBao("####################################");
           ThongBao(thongBaoChuongTrinhNote);
           //📝:Bạn chỉ còn 30 phút với nội dung.
           ThongBao("%F0%9F%93%9D%3AB%E1%BA%A1n%20ch%E1%BB%89%20c%C3%B2n%2030%20ph%C3%BAt%20v%E1%BB%9Bi%20n%E1%BB%99i%20dung.%0A");
           tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
           ThongBao(tmp);

           tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
           ThongBao(tmp);

           tmp = "%F0%9F%97%9FText%3A%20" + fileDataPlan[i + 2];
           ThongBao(tmp);


        }
        // Thông báo trước 1 tiếng.
        if (dayNow == stoi(dataNow.substr(0, 2)) && monthNow == stoi(dataNow.substr(3, 2)) && yearNow == stoi(dataNow.substr(6, 4)) && timeHour_Min_SecNow >= (timeHour_Min_SecPlan - 3600) && markFileDataPlan[i][3] == 1) {
            markFileDataPlan[i][3] = 0;
            string tmp;
           ThongBao("####################################");
           ThongBao(thongBaoChuongTrinhNote);
           //📝:Bạn chỉ còn 1 tiếng với nội dung.
           ThongBao("%F0%9F%93%9D%3AB%E1%BA%A1n%20ch%E1%BB%89%20c%C3%B2n%201%20ti%E1%BA%BFng%20v%E1%BB%9Bi%20n%E1%BB%99i%20dung.%0A.");
           tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
           ThongBao(tmp);

           tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
           ThongBao(tmp);

           tmp = "%F0%9F%97%9FText%3A%20" + fileDataPlan[i + 2];
           ThongBao(tmp);


        }
        // Thông báo trước 3 tiếng.
        if (dayNow == stoi(dataNow.substr(0, 2)) && monthNow == stoi(dataNow.substr(3, 2)) && yearNow == stoi(dataNow.substr(6, 4)) && timeHour_Min_SecNow >= (timeHour_Min_SecPlan - 3600 * 3) && markFileDataPlan[i][4] == 1) {
            markFileDataPlan[i][4] = 0;
            string tmp;
           ThongBao("####################################");
           ThongBao(thongBaoChuongTrinhNote);
           //📝:Bạn chỉ còn 3 tiếng với nội dung.
           ThongBao("%F0%9F%93%9D%3AB%E1%BA%A1n%20ch%E1%BB%89%20c%C3%B2n%203%20ti%E1%BA%BFng%20v%E1%BB%9Bi%20n%E1%BB%99i%20dung.%0A.");
           tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
           ThongBao(tmp);

           tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
           ThongBao(tmp);

           tmp = "%F0%9F%97%9FText%3A%20" + fileDataPlan[i + 2];
           ThongBao(tmp);

        }
        // Thông báo trước 1 ngày.
        if (dayNow == (stoi(dataNow.substr(0, 2)) - 1) && monthNow == stoi(dataNow.substr(3, 2)) && yearNow == stoi(dataNow.substr(6, 4)) && timeHour_Min_SecNow >= (timeHour_Min_SecPlan) && markFileDataPlan[i][5] == 1) {
            markFileDataPlan[i][5] = 0;
            string tmp;
           ThongBao("####################################");
           ThongBao(thongBaoChuongTrinhNote);
           //📝:Bạn chỉ còn 1day với nội dung.
           ThongBao("%F0%9F%93%9D%3AB%E1%BA%A1n%20ch%E1%BB%89%20c%C3%B2n%201%20ng%C3%A0y%20v%E1%BB%9Bi%20n%E1%BB%99i%20dung.%0A.");
           tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
           ThongBao(tmp);

           tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
           ThongBao(tmp);

           tmp = "%F0%9F%97%9FText%3A%20" + fileDataPlan[i + 2];
           ThongBao(tmp);

        }

    }
}
void TongBaoNote(){
    string tinNhanNew;
    tinNhanNew = DocTinNhan();
    TBFileDataPlan();
    //tính năng truy cập vào ghi chú note.
    if (tinNhanNew == "&note") {
        cout << "send message";
        system("cls");
        ThongBao("#############################");
        // thông báo hệ thống. chương trình note.
        ThongBao(thongBaoChuongTrinhNote);
        ThongBao("%F0%9F%94%90%3A%20Vui%20l%C3%B2ng%20nh%E1%BA%ADp%20m%E1%BA%ADt%20kh%E1%BA%A9u%20%C4%91%E1%BB%83%20ti%E1%BA%BFn%20h%C3%A0nh%20%C4%91%C4%83ng%20nh%E1%BA%ADp%20v%C3%A0o%20ch%C6%B0%C6%A1ng%20tr%C3%ACnh%20GHI%20CH%C3%9A");
        Sleep(7000);
        tinNhanNew = DocTinNhan();
        if (tinNhanNew == passworkSystem) {
            ThongBao("%C4%90ang%20ti%E1%BA%BFn%20h%C3%A0nh%20%C4%91%C4%83ng%20nh%E1%BA%ADp...");
            ThongBao("----25%");
            ThongBao("--------50%");
            ThongBao("------------75%");
            ThongBao("----------------100%");
            ThongBao("Xin%20ch%C3%A0o%20admin.%20Ch%C3%A0o%20m%E1%BB%ABng%20b%E1%BA%A1n%20%C4%91%C3%A3%20quay%20tr%E1%BB%9F%20l%E1%BA%A1i.");
            ThongBao("returnmain: thoat ra khoi MUC GHI CHU");
            ThongBao("show: in ra ghi chu hien tai con");
            bool flagShowNoteNow = true;
            while (true) {
                //system("cls");
                TBFileDataPlan();
                setupTimeNow();
                tinNhanNew = DocTinNhan();

                // trở về thời điểm ban đầu.
                if (tinNhanNew == "&returnmain") {
                    ThongBao("Ban da thoat khoi MUC GHI CHU");
                    return;
                }
                if (tinNhanNew == "&show" && flagShowNoteNow == true) {
                    flagShowNoteNow = false;
                    setupTimeNow();
                    string dataNow;
                    bool flag = false;
                    for (int i = 0; i < fileDataPlan.size(); i += 3) {
                        dataNow = fileDataPlan[i];
                        
                        if (dayNow <= stoi(dataNow.substr(0, 2)) && monthNow <= stoi(dataNow.substr(3, 2)) && yearNow <= stoi(dataNow.substr(6, 4)) && flagShowNoteNow == false) {
                            flag = true;
                            string tmp;

                            tmp = "%E2%8C%9ATime%3A%20 " + fileDataPlan[i];
                            ThongBao(tmp);

                            tmp = "%F0%9F%93%98Title%3A%20" + fileDataPlan[i + 1];
                            ThongBao(tmp);

                            tmp = "%F0%9F%97%9FTitle%3A%20" + fileDataPlan[i + 2];
                            ThongBao(tmp);
                        }
                    }
                    if (flag == false) {
                        ThongBao("Khong co thong tin nao.");
                    }

                }
            }
        }
        else {
            //🔐:Bạn đã nhập sai mật khẩu, xin vui lòng nhập lại.
            ThongBao("%F0%9F%94%90%3AB%E1%BA%A1n%20%C4%91%C3%A3%20nh%E1%BA%ADp%20sai%20m%E1%BA%ADt%20kh%E1%BA%A9u%2C%20xin%20vui%20l%C3%B2ng%20nh%E1%BA%ADp%20l%E1%BA%A1i.");
        }
    }
}

void markFileData(){
    
    for(int i = 0; i < fileDataPlan.size(); i+=3){
        markFileDataPlan[i][0] = 1;
        markFileDataPlan[i][1] = 1;
        markFileDataPlan[i][2] = 1;
        markFileDataPlan[i][3] = 1;
        markFileDataPlan[i][4] = 1;
        markFileDataPlan[i][5] = 1;
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////

int moneyNow = 0;
// so tien cua ngay hom do.
int moneyDay;
void cinVarMoneyNowInFileMoneyNow(){
    TBFileDataPlan();
    setupTimeNow();
        cout << "Chạy hàm cinVarMoneyNowInFileMoneyNow" << endl;
        ifstream in("moneyNow.txt");
        in >> moneyNow;
        in.close();
}
void ThongBaoMoney(std::string data) {
    std::string token = "7962421342:AAGvgmJmoKPAjOPu4NDTjTo24YMQgdiNqc0";  // Thay bằng token của bạn
    std::string chat_id = "7352518467";  // Thay bằng Chat ID của bạn
    std::string message = data;

    std::string command = "curl -s -X POST \"https://api.telegram.org/bot" + token +
        "/sendMessage\" -d \"chat_id=" + chat_id +
        "&text=" + message + "\" > nul 2>&1";

    system(command.c_str());  // Gửi thông báo
}
string DocTinNhanMoney() {
    std::string token = "7962421342:AAGvgmJmoKPAjOPu4NDTjTo24YMQgdiNqc0";  // Thay bằng token của bạn
    std::string command = "curl -s \"https://api.telegram.org/bot" + token + "/getUpdates\"";

    FILE* pipe = _popen(command.c_str(), "r");  // Dùng _popen trên Windows
    if (!pipe) return "Lỗi khi gọi API!";

    char buffer[1024];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;  // Đọc dữ liệu vào biến result
    }

    _pclose(pipe);  // Đóng pipe

    // Tìm tin nhắn cuối cùng (bằng cách tìm phần tử "text" cuối cùng)
    size_t lastTextPos = result.rfind("\"text\":\"");
    if (lastTextPos == std::string::npos) return "Không có tin nhắn nào!";

    lastTextPos += 8; // Nhảy qua `"text":"`
    size_t end = result.find("\"", lastTextPos); // Tìm dấu `"` đóng
    if (end == std::string::npos) return "Lỗi khi đọc tin nhắn!";

    return result.substr(lastTextPos, end - lastTextPos);
}
void XuLyTinNhanMoney(){
    TBFileDataPlan();
    string messages = DocTinNhanMoney();
    if(messages == "&Money"){
        while(true){
            TBFileDataPlan();
            //💵Bạn đã truy cập vào chương trình Money by coder vanha.
            ThongBaoMoney("%F0%9F%92%B5B%E1%BA%A1n%20%C4%91%C3%A3%20truy%20c%E1%BA%ADp%20v%C3%A0o%20ch%C6%B0%C6%A1ng%20tr%C3%ACnh%20Money%20by%20coder%20vanha.");
            //🔑Xin vui lòng nhập mật khẩu để truy cập vào hệ thống.
            ThongBaoMoney("%F0%9F%94%91Xin%20vui%20l%C3%B2ng%20nh%E1%BA%ADp%20m%E1%BA%ADt%20kh%E1%BA%A9u%20%C4%91%E1%BB%83%20truy%20c%E1%BA%ADp%20v%C3%A0o%20h%E1%BB%87%20th%E1%BB%91ng.");
            Sleep(7000);
            messages = DocTinNhanMoney();
            if( messages == passworkSystem){
                //Đang truy cập vào hệ tống
                ThongBaoMoney("%C4%90ang%20truy%20c%E1%BA%ADp%20v%C3%A0o%20h%E1%BB%87%20t%E1%BB%91ng");
                ThongBaoMoney("----25%");
                ThongBaoMoney("--------50%");
                ThongBaoMoney("------------75%");
                ThongBaoMoney("----------------100%");
                //Bạn đã đăng nhập vào chương trình thành công.
                ThongBaoMoney("B%E1%BA%A1n%20%C4%91%C3%A3%20%C4%91%C4%83ng%20nh%E1%BA%ADp%20v%C3%A0o%20ch%C6%B0%C6%A1ng%20tr%C3%ACnh%20th%C3%A0nh%20c%C3%B4ng.");
                int checkPlayFirst = 1;
                int checkPlaySecond = 1;
                while(true){
                    cout << "Dang chay while sau khi dang nhap thanh cong";
                    if(checkPlayFirst == 1 || (checkPlaySecond == 1) ){
                        // Ở đây bạn có thể sử dụng các lệnh.
                        ThongBaoMoney("%E1%BB%9E%20%C4%91%C3%A2y%20b%E1%BA%A1n%20c%C3%B3%20th%E1%BB%83%20s%E1%BB%AD%20d%E1%BB%A5ng%20c%C3%A1ch%20l%E1%BB%87nh.");
                        ThongBaoMoney("PlusMoney");
                        ThongBaoMoney("UseMoney");
                        ThongBaoMoney("returnmain");
                    }
                    checkPlayFirst = 0;
                    checkPlaySecond = 0;
                    TBFileDataPlan();
                    messages = DocTinNhanMoney();
                    if(messages == "PlusMoney"){
                        ThongBaoMoney("Truy cap vao PlusMoney");
                        //💵số tiền hiện tại của bạn là: + 
                        string tmp;
                        tmp = "%F0%9F%92%B5s%E1%BB%91%20ti%E1%BB%81n%20hi%E1%BB%87n%20t%E1%BA%A1i%20c%E1%BB%A7a%20b%E1%BA%A1n%20l%C3%A0%3A" + to_string(moneyNow);
                        ThongBaoMoney(tmp);
                        ofstream out("moneyNow.txt");
                        while(true){
                            TBFileDataPlan();
                            messages = DocTinNhanMoney();
                            char c = messages[0];
                            // Kiểm tra thử xem nó có phải là số nguyên hay không.
                            if(48 - static_cast <int> (c) >= - 9 && 48 - static_cast <int> (c) <= 0){
                                //💵Đã cập nhật thành công:
                                ThongBaoMoney("%F0%9F%92%B5%C4%90%C3%A3%20c%E1%BA%ADp%20nh%E1%BA%ADt%20th%C3%A0nh%20c%C3%B4ng%3A");
                                moneyNow += stoi(messages);
                                out << moneyNow;
                                //💵Số tiền sau khi được cập nhật là:
                                tmp = "%F0%9F%92%B5S%E1%BB%91%20ti%E1%BB%81n%20sau%20khi%20%C4%91%C6%B0%E1%BB%A3c%20c%E1%BA%ADp%20nh%E1%BA%ADt%20l%C3%A0%3A" + to_string(moneyNow);
                                ThongBaoMoney(tmp);
                                out.close();
                                checkPlaySecond = 1;
                                break;
                            }

                        }
                            
                    }

                    if(messages == "returnmain"){
                        //Đã thoát khỏi chương trình Money thành công.
                        ThongBaoMoney("%C4%90%C3%A3%20tho%C3%A1t%20kh%E1%BB%8Fi%20ch%C6%B0%C6%A1ng%20tr%C3%ACnh%20Money%20th%C3%A0nh%20c%C3%B4ng.");
                        return;
                    }

                    if(messages == "UseMoney"){
                        cout << "message == UseMoney da truy cap vao do" << endl;
                         //💵Vui lòng nhập số tiền bạn đã sử dụng: 
                         ThongBaoMoney("%F0%9F%92%B5Vui%20l%C3%B2ng%20nh%E1%BA%ADp%20s%E1%BB%91%20ti%E1%BB%81n%20b%E1%BA%A1n%20%C4%91%C3%A3%20s%E1%BB%AD%20d%E1%BB%A5ng%3A%20");
                        while(true){
                            if(checkPlaySecond == 1 ){
                                break;
                            }
                            messages = DocTinNhanMoney();
                            char c = messages[0];
                            if(48 - static_cast <int> (c) >= - 9 && 48 - static_cast <int> (c) <= 0){
                                ofstream outFIleHistoryOfUseMoney("HistoryOfUseMoney.txt", ios::app);
                                cout << "da vao khu vuc tru tien" << endl;
                                moneyDay -= stoi(messages);
                                moneyNow -= stoi(messages);
                                setupTimeNow();
                                outFIleHistoryOfUseMoney << currentTime << endl;
                                outFIleHistoryOfUseMoney << messages << endl;

                                //cập nhật số tiền sau khi sử dụng.
                                ofstream out("moneyNow.txt");
                                out << moneyNow;
                                out.close();
                                cinVarMoneyNowInFileMoneyNow();
                                //💵Vui lòng gửi nội dung mà bạn đã sử dụng.
                                ThongBaoMoney("%F0%9F%92%B5Vui%20l%C3%B2ng%20g%E1%BB%ADi%20n%E1%BB%99i%20dung%20m%C3%A0%20b%E1%BA%A1n%20%C4%91%C3%A3%20s%E1%BB%AD%20d%E1%BB%A5ng.");
                                string messagesAfter = messages;
                                while(true){
                                    messages = DocTinNhanMoney();
                                    if(messages != messagesAfter){
                                        outFIleHistoryOfUseMoney << messages << endl;
                                        //💵Đã cập nhật thành công.
                                        ThongBaoMoney("%F0%9F%92%B5%C4%90%C3%A3%20c%E1%BA%ADp%20nh%E1%BA%ADt%20th%C3%A0nh%20c%C3%B4ng.");
                                        checkPlaySecond = 1;
                                        //💵Số tiền trong ngày còn được phép sử dụng là.
                                        string tmp;
                                        tmp = "%F0%9F%92%B5S%E1%BB%91%20ti%E1%BB%81n%20trong%20ng%C3%A0y%20c%C3%B2n%20%C4%91%C6%B0%E1%BB%A3c%20ph%C3%A9p%20s%E1%BB%AD%20d%E1%BB%A5ng%20l%C3%A0" + to_string(moneyDay);
                                        ThongBaoMoney(tmp);
                                        
                                        
                                        break;
                                    }
                                }
                            }
                            else{
                                //💵Vui lòng gửi lại số tiền bạn đã gửi, có thể bạn đã gửi kí tự: 
                                ThongBaoMoney("%F0%9F%92%B5Vui%20l%C3%B2ng%20g%E1%BB%ADi%20l%E1%BA%A1i%20s%E1%BB%91%20ti%E1%BB%81n%20b%E1%BA%A1n%20%C4%91%C3%A3%20g%E1%BB%ADi%2C%20c%C3%B3%20th%E1%BB%83%20b%E1%BA%A1n%20%C4%91%C3%A3%20g%E1%BB%ADi%20k%C3%AD%20t%E1%BB%B1%3A%20");
                                Sleep(4000);
                            }

                        }
                    }
                    
                }

            }
            else{
                //🔴Sai mật khẩu xin vui lòng nhập lại.
                ThongBaoMoney("%F0%9F%94%B4Sai%20m%E1%BA%ADt%20kh%E1%BA%A9u%20xin%20vui%20l%C3%B2ng%20nh%E1%BA%ADp%20l%E1%BA%A1i.");
            }
        }
            
    }
    
}
void announcementMoneyeveryday(){
    if(hourNow >= 5){
        markAnnouncementMoneyeveryday = true;
    }
    TBFileDataPlan();
    setupTimeNow();
    int announcementEveryday = moneyNow / dayMoney;
    string tmp; vector <string> A;
    if(hourNow >= 6 && minNow == 36 && secNow == 0 && markAnnouncementMoneyeveryday == true){
        moneyDay = moneyNow / dayMoney + -30000;
        markAnnouncementMoneyeveryday = false;
        ThongBaoMoney("/////////////////////////////////////////////////");
        ifstream in("HistoryOfUseMoney.txt");
        string cinTmp;
        while(getline(in, cinTmp)){
            A.push_back(cinTmp);
        }
        in.close();
        int moneyDayAfter;
        for(int i = 0; i < A.size(); i+=3){
            if(dayNow - 1 == stoi(A[i].substr(0, 2)) ){
                //ThongBaoMoney(A[i]);
                moneyDayAfter += stoi(A[i + 1]);
            }
        }
        //💵Số tiền ngày hôm trước mà bạn sử dụng là: 
        tmp = "%F0%9F%92%B5S%E1%BB%91%20ti%E1%BB%81n%20ng%C3%A0y%20h%C3%B4m%20tr%C6%B0%E1%BB%9Bc%20m%C3%A0%20b%E1%BA%A1n%20s%E1%BB%AD%20d%E1%BB%A5ng%20l%C3%A0%3A%20" + to_string(moneyDayAfter);
        ThongBaoMoney(tmp);
        
        //💵Tổng kết: 
        tmp = "%F0%9F%92%B5T%E1%BB%95ng%20k%E1%BA%BFt%3A%20" + to_string(moneyNow/dayMoney - moneyDayAfter);
        ThongBaoMoney(tmp);
        ///////////
        tmp = "%F0%9F%92%B5S%E1%BB%91%20ti%E1%BB%81n%20h%C3%B4m%20nay%20b%E1%BA%A1n%20%C4%91%C6%B0%E1%BB%A3c%20ph%C3%A9p%20s%E1%BB%AD%20d%E1%BB%A5ng%20l%C3%A0%3A%20" + to_string(announcementEveryday);
        ThongBaoMoney(tmp);
    }
}

int main() {


    // lưu fileData.
    CinFileData();
    markFileData();
    //updateFileData();
    
    while (true) {
        dayMoney = 28 - dayNow;
        CinFileData();
        cinVarMoneyNowInFileMoneyNow();
        TBFileDataPlan();
        TongBaoNote();
        XuLyTinNhanMoney();
        announcementMoneyeveryday();

    }

    return 0;
}
