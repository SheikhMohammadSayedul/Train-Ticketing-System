#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <conio.h> 
#ifdef _WIN32
    #include <windows.h>
    #include <io.h>  // For _isatty
    #include <fcntl.h> // For _setmode
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

using namespace std;

//.......................................graphics...............................................

//BOLD_TEXT
//\033[1mBold Text\033[0m

//COLOR_USING_SETCOLOR
// 0: Black
// 1: Blue
// 2: Green
// 3: Aqua
// 4: Red
// 5: Purple
// 6: Yellow
// 7: White (default)
// 8: Gray
// 9: Light Blue

//COLOR_USING_\033[
// Reset: \033[0m
// Red: \033[31m
// Green: \033[32m
// Yellow: \033[33m
// Blue: \033[34m
// Magenta: \033[35m
// Cyan: \033[36m
// White: \033[37m
int terminalWidth, terminalHeight;

void clearScreen() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}
bool isNumeric(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void getTerminalSize(int &width, int &height) {
    #ifdef _WIN32
        // Windows
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    #else
        // Unix/Linux
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        width = w.ws_col;
        height = w.ws_row;
    #endif
}
//for one line
void printCentered(const std::string& text) {
    getTerminalSize(terminalWidth, terminalHeight);
    int x = (terminalWidth - text.length()) / 2; // Horizontal position
    #ifdef _WIN32
        COORD coord;
        coord.X = x;
        coord.Y = terminalHeight / 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    #else
        std::cout << "\033[" << (terminalHeight / 2) << ";" << x << "H";  // Move cursor to (y, x)
    #endif
    std::cout << text << std::flush;
}
//for multiple lin/without hight;
void printCenteredText(const string& text) {
    if (text.size() >= terminalWidth) {
        cout << text << "\n";
        return;
    }
    int padding = floor((terminalWidth - text.size()) / 2.0);
    for (int i = 0; i < padding; i++)cout << ' ';
    cout <<"\033[1m"<< text<<"\033[0m";
}
void printCenteredTextMulti(const string& text,int x) {
    if (text.size() >= terminalWidth) {
        cout << text << "\n";
        return;
    }
    int padding = floor((terminalWidth-x)/2.0);
    for (int i = 0; i < padding; i++)cout << ' ';
    cout << text;
}

void goingBack(string s , int color) {
    setColor(color);
    printCentered("");
    
    for (int i = 0; i < 5; i++) {
        this_thread::sleep_for(chrono::milliseconds(700));
        cout << "\r";
        cout << string((terminalWidth - s.size()-2) / 2, ' ') << s;
        for (int j = 0; j <= i; j++) {
            std::cout << ".";
        }
        std::cout << std::flush;
    }
    setColor(7);
    std::cout << std::endl;
}
void loadingAnimation() {
    const char symbols[] = {'|', '/', '-', '\\'};
    int i = 0;
    setColor(2);
    printCentered("");
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < std::chrono::seconds(2)) {
        std::cout<<"\r"<< string((terminalWidth - 10) / 2, ' ') << "Loading... " << symbols[i % 4] << std::flush;
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout<<"\r"<< string((terminalWidth - 10) / 2, ' ') << "Loading... Done!" << std::endl;
    setColor(7);
}
void loadingAnimationOthers(string s) {
    const char symbols[] = {'|', '/', '-', '\\'};
    int i = 0;
    setColor(2);
    printCentered("");
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < std::chrono::seconds(2)) {
        std::cout<<"\r"<< string((terminalWidth - 10) / 2, ' ') << s << symbols[i % 4] << std::flush;
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout<<"\r"<< string((terminalWidth - 10) / 2, ' ') <<s<< " Done!" << std::endl;
    setColor(7);
}
    string getCurrentTime12HourFormat() {
    time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    int hour = localTime->tm_hour;
    std::string am_pm = (hour >= 12) ? "PM" : "AM";
    hour = (hour % 12 == 0) ? 12 : (hour % 12);
    std::ostringstream timeStream;
    timeStream << std::setw(2) << std::setfill('0') << hour << ":"
               << std::setw(2) << std::setfill('0') << localTime->tm_min << " "
               << am_pm;
    return timeStream.str();
}
void showTime()
{
    printCenteredTextMulti("\033[32m\033[1m                                                  ____________                                                  \n",112);
    printCenteredTextMulti("||=====||=====||=====||=====||=====||=====||=====||          ||=====||=====||=====||=====||=====||=====||=====||\n",112);
    string tempo="||     ||     ||     ||     ||     ||     ||     || \033[35m"+getCurrentTime12HourFormat()+"\033[32m ||     ||     ||     ||     ||     ||     ||     ||\n";
    printCenteredTextMulti(tempo,112);
    printCenteredTextMulti("\033[32m||=====||=====||=====||=====||=====||=====||=====||__________||=====||=====||=====||=====||=====||=====||=====||\n\n",112);

}
int fristAnimation() {
    string tempo;
    printf("\n\n");
    printCenteredTextMulti("          \033[32m\033[1m       ********************************************************       \n",96);
    printCenteredTextMulti("               ****************\033[31m00000000000000000000000000000\033[32m***************      \n",96);
    printCenteredTextMulti("          \033[32m   ****************************************************************   \n",96);
    printCenteredTextMulti("            **********\033[34m0000000000000000000000000000000000000000000000\033[32m**********   \n",96);
    printCenteredTextMulti("           ********\033[34m000000000000000000000000000000000000000000000000000\033[32m*********  \n",96);
    printCenteredTextMulti("           *******\033[34m000000000000000000000000000000000000000000000000000000\033[32m*******  \n",96);
    printCenteredTextMulti("          ******\033[36m                                                         \033[32m******* \n",96);
    printCenteredTextMulti("          ******\033[36m                                                         \033[32m********\n",96);
    printCenteredTextMulti("          ******\033[36m                                                         \033[32m********\n",96);
    printCenteredTextMulti("          ******\033[36m                                                         \033[32m********\n",96);
    printCenteredTextMulti("          ******\033[36m                                                         \033[32m********\n",96);
    printCenteredTextMulti("          \033[32m***********************************************************************\n",96);
    printCenteredTextMulti("          ******\033[34m00\033[32m***********\033[31m################################\033[32m***********\033[34m00\033[32m*******\n",96);
    printCenteredTextMulti("          ****\033[34m000000\033[32m**************************************************\033[34m000000\033[32m*****\n",96);
    printCenteredTextMulti("          ****\033[34m000000\033[32m**************************************************\033[34m000000\033[32m*****\n",96);
    printCenteredTextMulti("          ******\033[34m00\033[32m***********\033[31m################################\033[32m***********\033[34m00\033[32m*******\n",96);
    printCenteredTextMulti("          \033[32m***********************************************************************\n",96);
    printf("\n\n");
    //for(int i=0;i<(terminalHeight-20)/2;i++)cout<<"\n";
    printCenteredTextMulti("\033[32m\033[1m    ######         ### ###                         \n",84);
    printCenteredTextMulti("\033[32m    ###   ###      ###    ###                      \n",84);
    printCenteredTextMulti("\033[32m    ###    ###     ###      ###                    \n",84);
    printCenteredTextMulti("\033[32m    ###   ###      ###        ##                   \n",84);
    printCenteredTextMulti("\033[32m    ### ###        ###         #                   \n",84);
    printCenteredTextMulti("\033[32m    ###   ###      ###        ##                   \n",84);
    tempo="\033[32m    ###    ###     ###      ### \033[35m  =====         //\\     ======  ||                 \n";
    printCenteredTextMulti(tempo,84);
    tempo="\033[32m    ###  ###       ###    ###  \033[35m  ||    ))      //  \\      ||    ||                 \n";
    printCenteredTextMulti(tempo,84);
    printCenteredTextMulti("\033[32m    ######         ### ###    \033[35m    ======      //=====     ||    ||                 \n",84);
    tempo="                              \033[35m   ||     \\    //      \\    ||    ||                \n";
    printCenteredTextMulti(tempo,84);
    tempo="                              \033[35m   ||      \\  //        \\ ======  ||======          \n";
    printCenteredTextMulti(tempo,84);
    printf("\n\n\n");
    for(int i=0;i<(terminalWidth-86)/2;i++)cout<<' ';
    printf("\033[35m\033[1m______________________________________________________________________________________\n");
    setColor(2);
    for (int i = 0; i < 86; i++) {
        this_thread::sleep_for(chrono::milliseconds(70));
        cout<<'*';
        cout << "\r";
        for(int i=0;i<(terminalWidth-86)/2;i++)cout<<' ';
        for (int j = 0; j <= i; j++) {
            std::cout << "#";
        }
        std::cout << std::flush;
    }
    setColor(7);
    clearScreen();

return 0;
}
int welcomeAdmin(){
    clearScreen();
    setColor(7);
    printf("\n\n\n");
    printCenteredTextMulti("\033[1m     ##              ## #######  ##        ####     \033[32m####\033[37m     ###     ###  #######   \n",97);
    printCenteredTextMulti("      ##            ##  ##       ##       ##      \033[32m##    ##\033[37m   ## #   # ##  ##        \n",97);
    printCenteredTextMulti("       ##    ##    ##   ######   ##      ##      \033[32m##      ##\033[37m  ##  # #  ##  #######   \n",97);
    printCenteredTextMulti("        ## ##  ## ##    ##       ##       ##      \033[32m##    ##\033[37m   ##   #   ##  ##        \n",97);
    printCenteredTextMulti("         ##      ##     #######  #######   ####     \033[32m####\033[37m     ##       ##  #######    \n\n\n",97);


    setColor(8);
    printCenteredTextMulti("           ###         ### ###         #####              #####    #########  ####        ##     \n",97);
    printCenteredTextMulti("          ## ##        ###    ###      ###  ##          ##  ###       ###     ## ##       ##     \n",97);
    printCenteredTextMulti("         ##   ##       ###      ###    ###    ##      ##    ###       ###     ##  ##      ##     \n",97);
    printCenteredTextMulti("        ##     ##      ###        ##   ###      ##  ##      ###       ###     ##   ##     ##     \n",97);
    printCenteredTextMulti("       ## ##### ##     ###         #   ###        ##        ###       ###     ##    ##    ##     \n",97);
    printCenteredTextMulti("      ##         ##    ###        ##   ###                  ###       ###     ##     ##   ##     \n",97);
    printCenteredTextMulti("     ##           ##   ###      ###    ###                  ###       ###     ##      ##  ##     \n",97);
    printCenteredTextMulti("    ##             ##  ###    ###      ###                  ###       ###     ##       ## ##     \n",97);
    printCenteredTextMulti("   ##               ## ### ###         ###                  ###    #########  ##        ####     \n\n\n",97);

    for(int i=0;i<(terminalWidth-97)/2;i++)cout<<' ';
    printf("\033[35m_________________________________________________________________________________________________\n\t\t");
    setColor(2);
    for (int i = 0; i < 97; i++) {
        this_thread::sleep_for(chrono::milliseconds(70));
        cout<<'*';
        cout << "\r";
        for(int i=0;i<(terminalWidth-97)/2;i++)cout<<' ';
        for (int j = 0; j <= i; j++) {
            std::cout << "#";
        }
        std::cout << std::flush;
    }
    setColor(7);
    clearScreen();                                                                                
    return 0;
}
void welcomeUser(string s)
{
    clearScreen();
    setColor(7);
    printCenteredText("               ##              ## #######  ##        ####     \033[32m####\033[37m     ###     ###  #######   \n");
    printCenteredText("                ##            ##  ##       ##       ##      \033[32m##    ##\033[37m   ## #   # ##  ##        \n");
    printCenteredText("                 ##    ##    ##   ######   ##      ##      \033[32m##      ##\033[37m  ##  # #  ##  #######   \n");
    printCenteredText("                  ## ##  ## ##    ##       ##       ##      \033[32m##    ##\033[37m   ##   #   ##  ##        \n");
    printCenteredText("                    ##      ##     #######  #######   ####     \033[32m####\033[37m     ##       ##  #######   \n\n");


    setColor(2);
    s+="\n\n\n";
    printCenteredText(s);
}
//.......................................USER CLASS..............................................

class User {
public:
    string username, email, id, password;
    vector<string> trainInfo;

    void login();
    void signup();
    void forgetPassword();
    void writeToFile();
    void readFromFile();
    void updateFile();
};

vector<User> users; // Global users vector
string searchUsername; // Global searchUsername

//.....................................TRAIN CLASS....................................................

class Train {
public:
    string trainName, trainCode, trainSchedule;
    int ac=0, nonAc=0, chairCoach=0, acw = 0, nonAcw = 0, chairCoachw = 0;
    float acPrice=0, nonAcPrice=0, chairCoachPrice=0;

    vector<pair<int, string>> acWaitingList;
    vector<pair<int, string>> nonAcWaitingList;
    vector<pair<int, string>> chairCoachWaitingList;
    vector<pair<int, string>> acPassengerList;
    vector<pair<int, string>> nonAcPassengerList;
    vector<pair<int, string>> chairCoachPassengerList;
    void addTrain();
};

set<string> destination;
vector<pair<string, Train>> destinationTrain;
void userMenu();
//.....................................ADMIN......................................................

vector<pair<string,string>>admin;

void adminInformationToFile()
{
    ofstream file("E:\\project\\project\\adminInformation.txt", ios::out);
    if (!file) {
        cerr << "Error: File could not be opened or created!" << endl;
        return;
    }
    for(auto& it: admin)
    {
        file<<it.first<<'$'<<it.second<<'$'<<'\n';
    }
    file.close();
    return;
}
void fileToAdminInformation()
{
    ifstream file("E:\\project\\project\\adminInformation.txt", ios::in);
    if (!file) {
        cerr << "Error: File could not be opened or created!" << endl;
        return;
    }
    admin.clear();
    string line;
    while(getline(file, line))
    {
        istringstream ss(line);
        string f,s;
        getline(ss,f,'$');
        getline(ss,s,'$');
        admin.push_back(make_pair(f,s));
    }
    file.close();
    return;
}

void writeDestinationToFile()
{
    ofstream file("E:\\project\\project\\destinationData.txt", ios::out);
    if (!file) {
        cerr << "Error: File could not be opened or created!" << endl;
        return;
    }
    for(auto& it: destination)
    {
        file<<it<<'\n';
    }
    file.close();
    return;
}
void readFileToDestination()
{
    ifstream file("E:\\project\\project\\destinationData.txt", ios::in);
    if (!file) {
        cerr << "Error: File could not be opened or created!" << endl;
        return;
    }
    destination.clear();
    while(!file.eof())
    {
        string line;
        getline(file,line,'\n');
        if(line!="")destination.insert(line);
    }
    file.close();
    return;
}
void writeDestinationTrainToFile()
{
    ofstream file("E:\\project\\project\\destinationTrainData.txt", ios::out);
    if (!file) {
        cerr << "Error: File could not be opened or created!" << endl;
        return;
    }

    for (const auto& it : destinationTrain) {
        const std::string& destinationName = it.first; // Get the destination name
        const Train& train = it.second; // Get the Train object

        file << destinationName << '$'
             << train.trainName << '$'
             << train.trainCode << '$'
             << train.trainSchedule << '$'
             << train.ac << '$'
             << train.nonAc << '$'
             << train.chairCoach << '$'
             << train.acw << '$'
             << train.nonAcw << '$'
             << train.chairCoachw << '$'
             << train.acPrice << '$'
             << train.nonAcPrice << '$'
             << train.chairCoachPrice;

        file << '$' << train.acWaitingList.size();
        for (const auto& w : train.acWaitingList) {
            file << '$' << w.first << '$' << w.second;
        }

        file << '$' << train.nonAcWaitingList.size();
        for (const auto& w : train.nonAcWaitingList) {
            file << '$' << w.first << '$' << w.second;
        }

        file << '$' << train.chairCoachWaitingList.size();
        for (const auto& w : train.chairCoachWaitingList) {
            file << '$' << w.first << '$' << w.second;
        }
        file << '$' << train.acPassengerList.size();
        for (const auto& w : train.acPassengerList) {
            file << '$' << w.first << '$' << w.second;
        }

        file << '$' << train.nonAcPassengerList.size();
        for (const auto& w : train.nonAcPassengerList) {
            file << '$' << w.first << '$' << w.second;
        }

        file << '$' << train.chairCoachPassengerList.size();
        for (const auto& w : train.chairCoachPassengerList) {
            file << '$' << w.first << '$' << w.second;
        }

        file <<'$'<<'\n';
    }
    file.close();
    return;
}
void readDestinationTrainFromFile()
{
    ifstream file("E:\\project\\project\\destinationTrainData.txt", ios::in);
    if (!file) {
        cerr << "Error: File could not be opened or created!" << endl;
        return;
    }

    destinationTrain.clear();
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;

        Train train;
        string destinationName;

        getline(ss, destinationName, '$');
        getline(ss, train.trainName, '$');
        getline(ss, train.trainCode, '$');
        getline(ss, train.trainSchedule, '$');

        ss >> train.ac;
        ss.ignore(1, '$');
        ss >> train.nonAc;
        ss.ignore(1, '$');
        ss >> train.chairCoach;
        ss.ignore(1, '$');
        ss >> train.acw;
        ss.ignore(1, '$');
        ss >> train.nonAcw;
        ss.ignore(1, '$');
        ss >> train.chairCoachw;
        ss.ignore(1, '$');
        ss >> train.acPrice;
        ss.ignore(1, '$');
        ss >> train.nonAcPrice;
        ss.ignore(1, '$');
        ss >> train.chairCoachPrice;
        ss.ignore(1, '$');

        //Wating List
        int acListSize;
        ss >> acListSize;
        ss.ignore(1, '$');
        for (int i = 0; i < acListSize; ++i) {
            int pos;
            string name;
            ss >> pos;
            ss.ignore(1, '$');
            getline(ss, name, '$');
            train.acWaitingList.push_back(make_pair(pos, name));
        }

        int nonAcListSize;
        ss >> nonAcListSize;
        ss.ignore(1, '$');
        for (int i = 0; i < nonAcListSize; ++i) {
            int pos;
            string name;
            ss >> pos;
            ss.ignore(1, '$');
            getline(ss, name, '$');
            train.nonAcWaitingList.push_back(make_pair(pos, name));
        }

        int chairCoachListSize;
        ss >> chairCoachListSize;
        ss.ignore(1, '$');
        for (int i = 0; i < chairCoachListSize; ++i) {
            int pos;
            string name;
            ss >> pos;
            ss.ignore(1, '$');
            getline(ss, name, '$');
            train.chairCoachWaitingList.push_back(make_pair(pos, name));
        }

        //Passenger List
        int acPassengerListSize;
        ss >> acPassengerListSize;
        ss.ignore(1, '$');
        for (int i = 0; i < acPassengerListSize; ++i) {
            int pos;
            string name;
            ss >> pos;
            ss.ignore(1, '$');
            getline(ss, name, '$');
            train.acPassengerList.push_back(make_pair(pos, name));
        }

        int nonAcPassengerListSize;
        ss >> nonAcPassengerListSize;
        ss.ignore(1, '$');
        for (int i = 0; i < nonAcPassengerListSize; ++i) {
            int pos;
            string name;
            ss >> pos;
            ss.ignore(1, '$');
            getline(ss, name, '$');
            train.nonAcPassengerList.push_back(make_pair(pos, name));
        }

        int chairCoachPassengerListSize;
        ss >> chairCoachPassengerListSize;
        ss.ignore(1, '$');
        for (int i = 0; i < chairCoachPassengerListSize; ++i) {
            int pos;
            string name;
            ss >> pos;
            ss.ignore(1, '$');
            getline(ss, name, '$');
            train.chairCoachPassengerList.push_back(make_pair(pos, name));
        }
        // Add the train to the destinationTrain vector
        destinationTrain.push_back(make_pair(destinationName, train));
    }
    file.close();
}

void Train :: addTrain()
{
    clearScreen();
    showTime();
    cout<<"\033[31mPress # to go Back."<<endl;
    setColor(2); 
    printCenteredTextMulti("\033[1mEnter Train Name: ",36);
    setColor(5);
    getline(cin,trainName);
    if(trainName=="#"){
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    setColor(2);
    printCenteredTextMulti("\033[1mEnter Train Code: ",36);
    setColor(5);
    getline(cin,trainCode);
    if(trainCode=="#"){
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    setColor(2);
    printCenteredTextMulti("\033[1mEnter Train Schedule: ",36);
    setColor(5);
    getline(cin,trainSchedule);
    if(trainSchedule=="#"){
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    setColor(2);
    printCenteredTextMulti("\033[1mEnter Train AC Seat: ",36);
    string tempo;
    setColor(5);
    getline(cin,tempo);
    if(!isNumeric(tempo)){
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    ac=stoi(tempo);
    setColor(2);
    printCenteredTextMulti("\033[1mEnter Train NON-AC Seat: ",36);
    setColor(5);
    getline(cin,tempo);
    if(!isNumeric(tempo)){
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    nonAc=stoi(tempo);
    setColor(2);
    printCenteredTextMulti("\033[1mEnter Train Chair-Coach Seat: ",36);
    setColor(5);
    getline(cin,tempo);
    if(!isNumeric(tempo)){
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    chairCoach=stoi(tempo);
    setColor(2);
    printCenteredTextMulti("\033[1mEnter Train AC Seat Price: ",36);
    setColor(5);
    getline(cin,tempo);
    if(!isNumeric(tempo)){
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    acPrice=stof(tempo);
    setColor(2);
    printCenteredTextMulti("\033[1mEnter Train NON-AC Seat Price: ",36);
    setColor(5);
    getline(cin,tempo);
    if(!isNumeric(tempo)){
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    nonAcPrice=stof(tempo);
    setColor(2);
    printCenteredTextMulti("\033[1mEnter Train Chair-Coach Seat Price: ",36);
    setColor(5);
    getline(cin,tempo);
    if(!isNumeric(tempo)){
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    chairCoachPrice=stof(tempo);
    string des;
    int H=1,G;
    clearScreen();
    showTime();
    printCenteredTextMulti("\033[1mAvailable Route for the Train: \n",32);
    setColor(2);
    for(auto it: destination){
        string temP=to_string(H)+". "+it+'\n';
        printCenteredTextMulti(temP,32);
        H++;
    }
    setColor(5);
    printCenteredTextMulti("\033[1mEnter Your Desire Route No: ",32);
    scanf("%d%*c",&G);
    H=1;
    for(auto it: destination){
        if(H==G){
            des=it;
            break;
        }
        H++;
    }
    clearScreen();
    setColor(2);
    loadingAnimationOthers("Train Adding.....");
    setColor(5);
    printCenteredText("\033[32mPress any key!\n");
    cin.ignore();
    cin.ignore();
    destinationTrain.push_back(make_pair(des,*this));
    clearScreen();
    goingBack("going back",4);
    clearScreen();
    writeDestinationTrainToFile();
    return;
}

void adminManue()
{
    char choice;
    do{
    clearScreen();
    showTime();
    printf("\n\n");
    printCenteredTextMulti("\033[1m\033[32mThis is admin manue:\n",30);
    printCenteredTextMulti("press \033[35m1\033[32m to see Train details. \n",30);
    printCenteredTextMulti("Press \033[35m2\033[32m to see user details.\n",30);
    printCenteredTextMulti("Press \033[31many\033[32m to Logout.\n",30);
    printCenteredTextMulti("Enter Your choice: ",30);

    scanf("%c%*c",&choice);
    // if(choice=='#'){
    //     goingBack("Going Back",4);
    //     return;
    // }
    switch(choice)
    {
        case '1':{
            char ch;
            do{
            clearScreen();
            cout<<"\033[31mPress # To Go Back."<<endl;
            showTime();
            int i=1;
            printCenteredTextMulti("\033[1m\033[34m-----------------------------------------------------------------------------------------------------------------------------------------------\n",143);
            for(int is=(terminalWidth-143)/2;is>0;is--)cout<<' ';
            printf("|\033[35m Train No\033[34m | \033[35m       Train Name   \033[34m    |  \033[35m   Train Code \033[34m   | \033[35m   Train Schedule  \033[34m |  \033[35m  AC seat/Price \033[34m  | \033[35m Non AC seat/Price \033[34m| \033[35m Chair Coach/Price\033[34m |\n");
            printCenteredTextMulti("\033[34m-----------------------------------------------------------------------------------------------------------------------------------------------\n",143);
            for (auto &it : destinationTrain){
                for(int is=(terminalWidth-143)/2;is>0;is--)cout<<' ';
                printf("\033[34m| \033[32m   %d.  \033[34m  |  \033[32m   %s", i, it.second.trainName.c_str());
                for (int j = it.second.trainName.size(); j < 20; j++) printf(" ");
                printf("\033[34m|    \033[32m    %s     \033[34m   |   \033[32m   %s   \033[34m    |   \033[32m  %d/%.2f", it.second.trainCode.c_str(), it.second.trainSchedule.c_str(), it.second.ac, it.second.acPrice);
                for(int k=int(log10(it.second.ac))+int(log10(it.second.acPrice))+6;k<15;k++)printf(" ");
                printf("\033[34m|  \033[32m   %d/%.2f",it.second.nonAc,it.second.nonAcPrice);
                for(int k=int(log10(it.second.nonAc))+int(log10(it.second.nonAcPrice))+6;k<15;k++)printf(" ");
                printf("\033[34m|  \033[32m   %d/%.2f",it.second.chairCoach,it.second.chairCoachPrice);
                for(int k=int(log10(it.second.chairCoach))+int(log10(it.second.chairCoachPrice))+6;k<15;k++)printf(" ");
                printf("\033[34m|\n");
                for(int is=(terminalWidth-143)/2;is>0;is--)cout<<' ';
                printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
                i++;
            }

            printCenteredTextMulti("\033[35mDo you want any change: \n",40);
            printCenteredTextMulti("\033[32mPress \033[35m1\033[32m to Add Train.\n",40);
            printCenteredTextMulti("Press \033[35m2\033[32m to Delet Train.\n",40);
            printCenteredTextMulti("Press \033[35m3\033[32m to Updet Train Schedule.\n",40);
            printCenteredTextMulti("Press \033[35m4\033[32m to Updet Train Route.\n",40);
            printCenteredTextMulti("Press \033[35m5\033[32m to Updet Route.\n",40);
            printCenteredTextMulti("Press \033[35m6\033[32m to Updet Ticket Price.\n",40);
            printCenteredTextMulti("Press \033[35m7\033[32m to Updet passenger capacity.\n",40);
            printCenteredTextMulti("Press \033[35m8\033[32m to Updet passenger List.\n",40);
            printCenteredTextMulti("Press \033[35m9\033[32m to See Wating List.\n",40);
            printCenteredTextMulti("\033[32mEnter Your Choice: \033[36m",40);
            scanf("%c%*c",&ch);
            if(ch=='#'){
                clearScreen();
                goingBack("going back",4);
                clearScreen();
                break;
            }
            switch (ch){
            case '1':{
                    Train obj; 
                    clearScreen();
                    loadingAnimation();
                    obj.addTrain();
                    break;
                }
            case '2':{
                    cout<<endl;
                    printCenteredTextMulti("\033[35mWhich Train You want to Delet: ",40);
                    int trainno;
                    string tempo;
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                    }
                    trainno=stoi(tempo);
                    string trname=destinationTrain[trainno-1].first;
                    for(auto& it:users){
                        int i=0;
                        for(auto& its: it.trainInfo){
                            string temp;
                            istringstream ss (its);
                            getline(ss,temp,'$');
                            if(temp==trname){
                                it.trainInfo.erase(it.trainInfo.begin()+i);
                            }
                            else{
                                i++;
                            }
                        }
                    }
                    destinationTrain.erase(destinationTrain.begin()+(trainno-1));
                    writeDestinationTrainToFile();
                    User obj;
                    obj.updateFile();
                    clearScreen();
                    loadingAnimationOthers("\033[31mTrain Deleting.....");
                    setColor(5);
                    printCenteredText("\033[35mPress any key!");
                    cin.ignore();
                    cin.ignore();
                    clearScreen();
                    goingBack("going back",4);
                    clearScreen();
                    writeDestinationTrainToFile();
                    writeDestinationToFile();
                    User obj1;
                     obj1.updateFile();
                    break;
                }
            case '3':{
                cout<<endl;
                    printCenteredTextMulti("\033[35mWhich Train Schedule you want to updet: ",40);
                    int trainno;
                    string tempo;
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                    }
                    trainno=stoi(tempo);
                    string temp;
                    printCenteredTextMulti("\033[32mEnter New Schedule:\033[35m ",40);
                    getline(cin,temp);
                    destinationTrain[trainno-1].second.trainSchedule=temp;
                    clearScreen();
                    loadingAnimationOthers("\033[32mSchedule Updeting.....");
                    setColor(5);
                    printCenteredText("\033[35mPress any key!");
                    cin.ignore();
                    cin.ignore();
                    clearScreen();
                    goingBack("going back",4);
                    clearScreen();
                    writeDestinationTrainToFile();
                    writeDestinationToFile();
                    User obj1;
                    obj1.updateFile();
                    clearScreen();
                    break;
                }
            case '4':{
                cout<<endl;
                    printCenteredTextMulti("\033[35mWhich Train Route you want to updet: ",36);
                    int trainno,H=0,G;
                    string tempo;
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                    }
                    trainno=stoi(tempo);
                    string temp;
                    clearScreen();
                    cout<<"\033[31mPress # To Go Back."<<endl;
                    printCenteredTextMulti("\033[32mAvailable Route for the Trains: \n",36);
                    for(auto it: destination){
                        string temP=to_string(H)+". "+it+'\n';
                        if(H!=0)printCenteredTextMulti(temP,32);
                        H++;
                    }
                    printCenteredTextMulti("\033[35mWhich Route you Prefer: \033[35m",36);
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                    }
                    G=stoi(tempo);
                    H=1;
                    for(auto it: destination){
                        if(H==G){
                            destinationTrain[trainno-1].first=it;
                        }
                        H++;
                    }
                    loadingAnimationOthers("\033[32mTrain Route Updeting.....");
                    setColor(5);
                    printCenteredText("\033[35mPress any key!");
                    cin.ignore();
                    cin.ignore();
                    clearScreen();
                    goingBack("going back",4);
                    clearScreen();
                    writeDestinationTrainToFile();
                    writeDestinationToFile();
                    User obj;
                    obj.updateFile();
                    break;
                }
            case '5':{
                    int H=0,G;
                    clearScreen();
                    cout<<"\033[31mPress # To Go Back."<<endl;
                    showTime();
                    printCenteredTextMulti("\033[32mAvailable Route for the Trains: \n",36);
                    for(auto it: destination){
                        string temP=to_string(H+1)+". "+it+'\n';
                        printCenteredTextMulti(temP,32);
                        H++;
                    }
                    printCenteredTextMulti("Press \033[35m1\033[32m to Add Route.\n",36);
                    printCenteredTextMulti("Press \033[35m2\033[32m to Delet Route.\n",36);
                    printCenteredTextMulti("Press \033[35many\033[32m to Go Back.\n\n",36);
                    printCenteredTextMulti("Enter your Choice: ",36);
                    string tempo;
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                    }
                    G=stoi(tempo);
                    if(G==1){
                        printCenteredTextMulti("Enter New Route: ",36);
                        string newRoute;
                        getline(cin,newRoute);
                        if(newRoute=="#"){
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                        }
                        destination.insert(newRoute);
                    }else if(G==2){

                        printCenteredTextMulti("\033[35mWhich Route You Want to Delet?\033[36m",36);
                        int wr;
                        getline(cin,tempo);
                        if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                        }
                        wr=stoi(tempo);
                        H=1;
                        for(auto it: destination)//delet route from destination{
                            if(H==wr){
                                int H1=0;
                                for(auto its: destinationTrain)//delet trains in that route
                                {
                                    if(its.first==it){
                                        string trname=it;
                                        for(auto& itt:users)//delet who have tickets
                                        {
                                            int ik=0;
                                            for(auto& itf: itt.trainInfo){
                                                string temp;
                                                istringstream ss (itf);
                                                getline(ss,temp,'$');
                                                if(temp==trname){
                                                    itt.trainInfo.erase(itt.trainInfo.begin()+ik);
                                                }
                                                ik++;
                                            }
                                        }
                                        destinationTrain.erase(destinationTrain.begin()+(H1-1));
                                    }else{
                                        H1++;
                                    }
                                }
                                destination.erase(it);
                                break;
                            }else{
                                H++;
                            }
                    }else{
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                    }
                clearScreen();
                loadingAnimationOthers("Route Updating.....");
                clearScreen();
                printCenteredText("\033[35mPress Any key!");
                cin.ignore();
                cin.ignore();
                clearScreen();
                goingBack("going back",4);
                clearScreen();
                writeDestinationTrainToFile();
                writeDestinationToFile();
                User obj;
                obj.updateFile();
                break;
                }
            case '6':
                {
                    int no;
                    do{
                        cout<<endl;
                    printCenteredTextMulti("\033[35mWhich Train Ticket Price you want to updet: \033[32m",46);
                    int trainno,newP;
                    string tempo;
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        return;
                    }
                    trainno=stoi(tempo);
                    clearScreen();
                    cout<<"\033[31Press # To Go Back."<<endl;
                    showTime();
                    printCenteredTextMulti("Which Seat :\n\n",46);
                    printCenteredTextMulti("Press \033[35m1\033[32m For Updeting AC Ticket Price.\n",46);
                    printCenteredTextMulti("Press \033[35m2\033[32m For Updeting Non-AC Ticket Price.\n",46);
                    printCenteredTextMulti("Press \033[35m3\033[32m For Updeting Chair-Coach Ticket Price.\n",46);
                    printCenteredTextMulti("Press \033[35many\033[32m For Back\n\n",46);
                    printCenteredTextMulti("Enter Your Choice: ",46);
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        return;
                    }
                    no=stoi(tempo);
                    switch (no){
                    case 1:{
                            setColor(2);
                            cout<<endl;
                            printCenteredTextMulti("Enter New Price: ",46);
                            getline(cin,tempo);
                            if(!isNumeric(tempo)){
                                clearScreen();
                                goingBack("going back",4);
                                clearScreen();
                            break;
                            }
                            newP=stoi(tempo);
                            destinationTrain[trainno-1].second.acPrice=newP;
                            clearScreen();
                            loadingAnimationOthers("Train Ticket Price Updeting...");
                            setColor(5);
                            printCenteredText("Press any key To Back.");
                            cin.ignore();
                            cin.ignore();
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            writeDestinationTrainToFile();
                            break;
                        }
                    case 2:{
                            setColor(2);
                            cout<<endl;
                            printCenteredTextMulti("Enter New Price: ",46);
                            getline(cin,tempo);
                            if(!isNumeric(tempo)){
                                clearScreen();
                                goingBack("going back",4);
                                clearScreen();
                            break;
                            }
                            newP=stoi(tempo);
                            destinationTrain[trainno-1].second.nonAcPrice=newP;
                            clearScreen();
                            loadingAnimationOthers("Train Ticket Price Updeting...");
                            setColor(5);
                            printCenteredText("Press any key To Back.");
                            cin.ignore();
                            cin.ignore();
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            writeDestinationTrainToFile();
                            break;
                        }
                    case 3:{
                            setColor(2);
                            cout<<endl;
                            printCenteredTextMulti("Enter New Price: ",46);
                            getline(cin,tempo);
                            if(!isNumeric(tempo)){
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            break;
                            }
                            newP=stoi(tempo);
                            destinationTrain[trainno-1].second.chairCoachPrice=newP;
                            clearScreen();
                            loadingAnimationOthers("Train Ticket Price Updeting...");
                            setColor(5);
                            printCenteredText("Press any key To Back.");
                            cin.ignore();
                            cin.ignore();
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            writeDestinationTrainToFile();
                            break;
                        }
                    default:
                        break;
                    }
                    }while(no==1||no==2||no==3);
                    break;
                }
            case '7':{
                    int no;
                    do{
                    setColor(2);
                    cout<<endl;
                    printCenteredTextMulti("\033[0mWhich Train Passenger capacity you want to updet: ",52);
                    int trainno,newP;
                    string tempo;
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                    }
                    trainno=stoi(tempo);
                    clearScreen();
                    cout<<"\033[31mPress # To Go Back!\033[32m"<<endl;
                    showTime();
                    printCenteredTextMulti("Which Seat :\n\n",52);
                    printCenteredTextMulti("Press \033[35m1\033[32m For Updeting AC Seat Capacity.\n",52);
                    printCenteredTextMulti("Press \033[35m2\033[32m For Updeting Non-AC Seat Capacity.\n",52);
                    printCenteredTextMulti("Press \033[35m3\033[32m For Updeting Chair-Coach Seat Capacity.\n",52);
                    printCenteredTextMulti("Press \033[35many\033[32m For Back.\n",52);
                    printCenteredTextMulti("Enter Your Choice: ",52);
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("Going Back",4);
                        clearScreen();
                        break;
                    }
                    no=stoi(tempo);
                    switch (no)
                    {
                    case 1:
                        {
                            setColor(2);
                            cout<<endl;
                            printCenteredTextMulti("Enter New Capacity: ",52);
                            setColor(6);
                            getline(cin,tempo);
                            setColor(2);
                            if(!isNumeric(tempo)){
                                clearScreen();
                                goingBack("going back",4);
                                clearScreen();
                                break;
                            }
                            newP=stoi(tempo);
                            destinationTrain[trainno-1].second.ac=newP;
                            clearScreen();
                            loadingAnimationOthers("AC Seat Capacity Updeting...");
                            printCenteredText("Press any key To Back.");
                            cin.ignore();
                            cin.ignore();
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            writeDestinationTrainToFile();
                            break;
                        }
                    case 2:{
                            setColor(2);
                            cout<<endl;
                            printCenteredTextMulti("Enter New Capacity: ",52);
                            setColor(6);
                            getline(cin,tempo);
                            setColor(2);
                            if(!isNumeric(tempo)){
                                clearScreen();
                                goingBack("going back",4);
                                clearScreen();
                                break;
                            }
                            newP=stoi(tempo);
                            destinationTrain[trainno-1].second.nonAc=newP;
                            loadingAnimationOthers("Non-AC Seat Capacity Updeting...");
                            printCenteredText("Press any key To Back.");
                            cin.ignore();
                            cin.ignore();
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            writeDestinationTrainToFile();
                            break;
                        }
                    case 3:{
                            setColor(2);
                            cout<<endl;
                            printCenteredTextMulti("Enter New Capacity: ",52);
                            setColor(6);
                            getline(cin,tempo);
                            if(!isNumeric(tempo)){
                                clearScreen();
                                goingBack("going back",4);
                                clearScreen();
                                return;
                            }
                            newP=stoi(tempo);
                            setColor(2);
                            destinationTrain[trainno-1].second.chairCoach=newP;
                            loadingAnimationOthers("Chair-coach Seat Capacity Updeting...");
                            printCenteredText("Press any key To Back.");
                            cin.ignore();
                            cin.ignore();
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            writeDestinationTrainToFile();
                            break;
                        }
                    default:
                        break;
                    }
                    }while(no==1||no==2||no==3);
                    break;
                }
                case '8':{
                    int trainno,no;
                    do{
                    cout<<endl;
                    printCenteredTextMulti("\033[32mWhich Train Passenger List you want to updet (Press # for none): ",56);
                    string tempo;
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                    }
                    trainno=stoi(tempo);
                    clearScreen();
                    cout<<"\033[31mPress # To Go Back.\033[32m"<<endl;
                    showTime();
                    printCenteredTextMulti("Which Seat :\n\n",56);
                    printCenteredTextMulti("\tPress \033[35m1\033[32m For See AC Seat Passenger List.\n",56);
                    printCenteredTextMulti("\tPress \033[35m2\033[32m For See Non-AC Seat Passenger List.\n",56);
                    printCenteredTextMulti("\tPress \033[35m3\033[32m For See Chair-Coach Seat Passenger List.\n",56);
                    printCenteredTextMulti("\tPress \033[35many\033[32m For Back\n",56);
                    printCenteredTextMulti("\tEnter Your Choice: ",56);
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                    }
                    no=stoi(tempo);
                    switch (no)
                    {
                    case 1:{
                            loadingAnimation();
                            clearScreen();
                            cout<<"\033[31mPress # To Go Back.\033[32m"<<endl;
                            showTime();
                            setColor(5);
                            printCenteredTextMulti("Here is the Passenger List:\n",27);
                            int k=1;
                            setColor(2);
                            for(const auto& it:destinationTrain[trainno-1].second.acPassengerList){
                                tempo="\033[0m\033[32m"+to_string(k)+" : "+it.second+" - "+to_string(it.first)+" Ticket\n";
                                printCenteredTextMulti(tempo,18);
                                k++;
                            }
                            printf("\n\n");
                            printCenteredTextMulti("\033[32mPress \033[35m1\033[32m to Cencel a Passenger Ticket.\n",38);
                            int am=1;
                            getline(cin,tempo);
                            if(tempo!="1")
                            {
                                clearScreen();
                                goingBack("going back",4);
                                clearScreen();
                                break;
                            }
                            printCenteredTextMulti("Which Passenger Ticket You want to cencel:",38);
                            getline(cin,tempo);
                            if(!isNumeric(tempo))
                            {
                                clearScreen();
                                goingBack("going back",4);
                                clearScreen();
                                break;
                            }
                            am=stoi(tempo);
                            k=1;
                            for(const auto& it:destinationTrain[trainno-1].second.acPassengerList){
                                if(k==am){
                                    destinationTrain[trainno-1].second.ac+=destinationTrain[trainno-1].second.acPassengerList[k-1].first;
                                    for(auto& its: users){
                                        if(its.username==destinationTrain[trainno-1].second.acPassengerList[k-1].second){
                                            int kaje_lagbe=0;
                                            for(const auto& itt: its.trainInfo){
                                                string temp1;
                                                istringstream ss (itt);
                                                getline(ss,temp1,'$');
                                                if(temp1==destinationTrain[trainno-1].second.trainName){
                                                    its.trainInfo.erase(its.trainInfo.begin()+kaje_lagbe);
                                                    break;
                                                }else{
                                                    kaje_lagbe++;
                                                }
                                            }
                                        }
                                    }
                                    destinationTrain[trainno-1].second.acPassengerList.erase(destinationTrain[trainno-1].second.acPassengerList.begin()+(k-1));
                                }
                                k++;
                            }
                            clearScreen();
                            loadingAnimationOthers("Passenger Deleting.....");
                            printCenteredTextMulti("Press any key!\n",38);
                            getline(cin,tempo);
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            break;
                        }
                    case 2:
                        {
                            loadingAnimation();
                            clearScreen();
                            cout<<"\033[31mPress # To Go Back.\033[32m"<<endl;
                            showTime();
                            setColor(5);
                            printCenteredText("Here is the Passenger List:\n");
                            int k=1;
                            setColor(2);
                            for(const auto& it:destinationTrain[trainno-1].second.nonAcPassengerList){
                                tempo=to_string(k)+" : "+it.second+" - "+to_string(it.first)+" Ticket\n";
                                printCenteredText(tempo);
                                k++;
                            }
                            printf("\n\n");
                            printCenteredTextMulti("Press 1 to Cencel a Passenger Ticket.\n",38);
                            int am=1;
                            getline(cin,tempo);
                            if(tempo!="1")
                            {
                                clearScreen();
                                goingBack("going back",4);
                                clearScreen();
                                break;
                            }
                            printCenteredTextMulti("Which Passenger Ticket You want to cencel:",38);
                            getline(cin,tempo);
                            if(!isNumeric(tempo))
                            {
                                clearScreen();
                                goingBack("going back",4);
                                clearScreen();
                                break;
                            }
                            am=stoi(tempo);
                            k=1;
                            for(const auto& it:destinationTrain[trainno-1].second.nonAcPassengerList){
                                if(k==am){
                                    destinationTrain[trainno-1].second.nonAc+=destinationTrain[trainno-1].second.nonAcPassengerList[k-1].first;
                                    for(auto& its: users){
                                        if(its.username==destinationTrain[trainno-1].second.nonAcPassengerList[k-1].second){
                                            int kaje_lagbe=0;
                                            for(const auto& itt: its.trainInfo){
                                                string temp1;
                                                istringstream ss (itt);
                                                getline(ss,temp1,'$');
                                                if(temp1==destinationTrain[trainno-1].second.trainName){
                                                    its.trainInfo.erase(its.trainInfo.begin()+kaje_lagbe);
                                                    break;
                                                }else{
                                                    kaje_lagbe++;
                                                }
                                            }
                                        }
                                    }
                                    destinationTrain[trainno-1].second.nonAcPassengerList.erase(destinationTrain[trainno-1].second.nonAcPassengerList.begin()+(k-1));
                                }
                                k++;
                            }
                            clearScreen();
                            loadingAnimationOthers("Passenger Deleting.....");
                            printCenteredTextMulti("Press any key!\n",38);
                            getline(cin,tempo);
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            break;
                        }
                    case 3:
                        {
                            loadingAnimation();
                            clearScreen();
                            cout<<"\033[31mPress # To Go Back.\033[32m"<<endl;
                            showTime();
                            setColor(5);
                            printCenteredText("Here is the Passenger List:\n");
                            int k=1;
                            setColor(2);
                            for(const auto& it:destinationTrain[trainno-1].second.chairCoachPassengerList){
                                tempo=to_string(k)+" : "+it.second+" - "+to_string(it.first)+" Ticket\n";
                                printCenteredText(tempo);
                                k++;
                            }
                            printf("\n\n");
                            printCenteredTextMulti("Press 1 to Cencel a Passenger Ticket.\n",38);
                            int am=1;
                            getline(cin,tempo);
                            if(tempo!="1")
                            {
                                clearScreen();
                                goingBack("going back",4);
                                clearScreen();
                                break;
                            }
                            printCenteredTextMulti("Which Passenger Ticket You want to cencel:",38);
                            getline(cin,tempo);
                            if(!isNumeric(tempo))
                            {
                                clearScreen();
                                goingBack("going back",4);
                                clearScreen();
                                break;
                            }
                            am=stoi(tempo);
                            k=1;
                            for(const auto& it:destinationTrain[trainno-1].second.chairCoachPassengerList){
                                if(k==am){
                                    destinationTrain[trainno-1].second.chairCoach+=destinationTrain[trainno-1].second.chairCoachPassengerList[k-1].first;
                                    for(auto& its: users){
                                        if(its.username==destinationTrain[trainno-1].second.chairCoachPassengerList[k-1].second){
                                            int kaje_lagbe=0;
                                            for(const auto& itt: its.trainInfo){
                                                string temp1;
                                                istringstream ss (itt);
                                                getline(ss,temp1,'$');
                                                if(temp1==destinationTrain[trainno-1].second.trainName){
                                                    its.trainInfo.erase(its.trainInfo.begin()+kaje_lagbe);
                                                    break;
                                                }else{
                                                    kaje_lagbe++;
                                                }
                                            }
                                        }
                                    }
                                    destinationTrain[trainno-1].second.chairCoachPassengerList.erase(destinationTrain[trainno-1].second.chairCoachPassengerList.begin()+(k-1));
                                }
                                k++;
                            }
                            clearScreen();
                            loadingAnimationOthers("Passenger Deleting.....");
                            printCenteredTextMulti("Press any key!\n",38);
                            getline(cin,tempo);
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            break;
                        }
                    default:
                        clearScreen();
                        goingBack("going Back",5);
                        clearScreen();
                        break;
                    }
                    }while(no==1||no==2||no==3);
                    break;
                }
            case '9':{
                    int trainno,no;
                    do{
                        loadingAnimation();
                    cout<<"\033[31mPress # To Go Back.\033[32m"<<endl;
                    cout<<endl;
                    printCenteredTextMulti("Which Train Passenger List you want to See: ",56);
                    string tempo;
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("Going Back",4);
                        clearScreen();
                        break;
                    }
                    trainno=stoi(tempo);
                    printCenteredTextMulti("\033[32mWhich Seat :\n\n",56);
                    printCenteredTextMulti("\033[32m\tPress\033[35m 1 \033[32mFor See AC Seat Passenger wating List.\n",56);
                    printCenteredTextMulti("\033[32m\tPress \033[35m2 For See Non-AC Seat Passenger wating List.\n",56);
                    printCenteredTextMulti("\033[32m\tPress \033[35m3 For See Chair-Coach Seat Passenger wating List.\n",56);
                    printCenteredTextMulti("\033[32m\tPress \033[35many\033[32m For Back\n",56);
                    printCenteredTextMulti("\033[32m\tEnter Your Choice: ",56);
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                        clearScreen();
                        goingBack("Going Back",4);
                        clearScreen();
                        break;
                    }
                    no=stoi(tempo);
                    switch (no)
                    {
                    case 1:{
                            int k=1;
                            clearScreen();
                            showTime();
                            setColor(5);
                            for(const auto& it:destinationTrain[trainno-1].second.acWaitingList)
                            {
                                tempo=to_string(k)+" : "+it.second+'-'+to_string(it.first)+" Ticket\n";
                                printCenteredText(tempo);
                            }
                            setColor(9);
                            cout<<endl;
                            printCenteredText("This is the wating List till now.\n");
                            cout<<"\033[31mPress Any Key To Go Back!"<<endl;
                            cin.ignore();
                            cin.ignore();
                            clearScreen();
                            goingBack("going Back",5);
                            clearScreen();
                            break;
                        }
                    case 2:{
                            int k=1;
                            clearScreen();
                            showTime();
                            setColor(5);
                            for(const auto& it:destinationTrain[trainno-1].second.nonAcWaitingList){
                                tempo=to_string(k)+" : "+it.second+'-'+to_string(it.first)+" Ticket\n";
                                printCenteredText(tempo);
                            }
                            setColor(9);
                            printCenteredText("This is the wating List till now.\n");
                            cout<<"\033[31mPress Any Key To Go Back!"<<endl;
                            cin.ignore();
                            cin.ignore();
                            clearScreen();
                            goingBack("going Back",5);
                            clearScreen();
                            break;
                        }
                    case 3:{
                            int k=1;
                            clearScreen();
                            showTime();
                            setColor(5);
                            for(const auto& it:destinationTrain[trainno-1].second.chairCoachWaitingList){
                                tempo=to_string(k)+" : "+it.second+'-'+to_string(it.first)+" Ticket\n";
                                printCenteredText(tempo);
                            }
                            setColor(9);
                            printCenteredText("This is the wating List till now.\n");
                            cout<<"\033[31mPress Any Key To Go Back!"<<endl;
                            cin.ignore();
                            cin.ignore();
                            clearScreen();
                            goingBack("going Back",5);
                            clearScreen();
                            break;
                        }
                    default:
                        clearScreen();
                        goingBack("going Back",5);
                        clearScreen();
                        break;
                    }
                    }while(no==1||no==2||no==3);
                    break;
                }
            default:
                clearScreen();
                goingBack("going Back",5);
                clearScreen();
                break;
            }
            }while(ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7');
            break;
        }
        case '2':{
            char ch;
            int w;
            do{
            loadingAnimation();
            clearScreen();
            cout<<"\033[31mPress # To Go Back."<<endl;
            showTime();
            printCenteredTextMulti("\033[1m\033[35mHere is All User Details.\n",25);
            printCenteredTextMulti("\033[1m\033[34m-------------------------------------------------------------------------------------\n",85);
            printCenteredTextMulti("\033[34m|\033[35m User No \033[34m|    \033[35m     Username        \033[34m |   \033[35m    ID     \033[34m   |       \033[35m     Email       \033[34m    |\n",85);
            printCenteredTextMulti("\033[34m-------------------------------------------------------------------------------------\n",85);
            int k=1;
            for(const auto& it: users)
            {
                for(int is=(terminalWidth-85)/2;is>0;is--)cout<<' ';
                printf("\033[34m|  \033[32m  %d  \033[34m  |    \033[32m   %s",k,it.username.c_str());
                for(int i=it.username.size();i<19;i++)printf(" ");
                printf("\033[34m|  \033[32m  %s",it.id.c_str());
                for(int k=it.id.size();k<13;k++)printf(" ");
                printf("\033[34m|     \033[32m  %s",it.email.c_str());
                for(int i=it.email.size();i<=20;i++)printf(" ");
                printf("\033[34m|\n");
                for(int is=(terminalWidth-85)/2;is>0;is--)cout<<' ';
                printf("-------------------------------------------------------------------------------------\n");
                k++;
            }
            printCenteredTextMulti("\033[32mDo You want to go farther more?\n\n",58);
            printCenteredTextMulti("\tPress \033[35m1\033[32m to See User Security Information.\n",58);
            printCenteredTextMulti("\tPress \033[35m2\033[32m to See User Ticket Reservation Information.\n",58);
            printCenteredTextMulti("\tPress \033[35m3\033[32m for Delet User.\n",58);
            printCenteredTextMulti("\tPress \033[35m4\033[32m to Promote a User As Admin.\n",58);
            printCenteredTextMulti("\tPress \033[35m5\033[32m to See Admins.\n",58);
            printCenteredTextMulti("\tPress \033[35many\033[32m to back.\n",58);
            cout<<endl;
            printCenteredTextMulti("Enter Your Choice:",58);
            scanf("%c%*c",&ch);
            if(ch=='#')
            {
                clearScreen();
                goingBack("going back",4);
                clearScreen();
                break;
            }

            switch (ch)
            {
            case '1':
                {
                    setColor(2);
                    printCenteredTextMulti("\033[32mWhich User Security Information you Want to see:",58);
                    setColor(5);
                    string tempo;
                    getline(cin,tempo);
                    if(!isNumeric(tempo))
                    {
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                    }
                    w=stoi(tempo);
                    tempo="\033[32m\033[1mUser Passeord is:\033[35m "+ users[w-1].password;
                    clearScreen();
                    printCenteredText(tempo);
                    printCenteredText("\033[31mPress any key!");
                    cin.ignore();
                    cin.ignore();
                    clearScreen();
                    goingBack("going back",4);
                    clearScreen();
                    break;
                }
            case '2':
                {
                    //cout<<"\033[31mPress # To Go Back."<<endl;
                    setColor(2);
                    printCenteredTextMulti("\033[1mWhich User Ticket Reservation Information you Want to see:",58);
                    cout<<endl;
                    setColor(5);
                    string tempo;
                    getline(cin,tempo);
                    if(!isNumeric(tempo))
                    {
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                    }
                    clearScreen();
                    cout<<"\033[31mPress # to go Back!"<<endl;
                    setColor(2);
                    showTime();
                    w=stoi(tempo);
                    printCenteredTextMulti("Here is The User Ticket Reservation Information.\n\n",48);
                    string trname,trcode,seat,wating,seatname,trsc,perTicketprice,ct;
                    printCenteredTextMulti("\033[1m\033[34m-------------------------------------------------------------------------------------------------------------------------------------------------------\n",147);
                    for(int is=(terminalWidth-147)/2;is>0;is--)cout<<' ';
                    printf("\033[34m|\033[35m Train No\033[34m |  \033[35m      Train Name    \033[34m   |  \033[35m  Train Code \033[34m  |   \033[35m  Train Schedule   \033[34m  |   \033[35m   Seat/Price   \033[34m   |  \033[35m  Total Price \033[34m   |    \033[35m   Boking time       \033[34m |\n");
                    printCenteredTextMulti("-------------------------------------------------------------------------------------------------------------------------------------------------------\n",147);
                    for(int i=0;i<users[w-1].trainInfo.size();i++)
                    {
                        istringstream ss(users[w-1].trainInfo[i]);

                        getline(ss,trname,'*');
                        getline(ss,trcode,'*');
                        getline(ss,seat,'*');
                        getline(ss,wating,'*');
                        getline(ss,seatname,'*');
                        getline(ss,trsc,'*');
                        getline(ss,perTicketprice,'*');
                        getline(ss,ct);
                        for(int is=(terminalWidth-147)/2;is>0;is--)cout<<' ';
                        printf("\033[34m|   \033[32m  %d   \033[34m |  \033[32m   %s",i+1,trname.c_str());
                        for(int j=trname.size();j<20;j++)printf(" ");
                        printf("\033[34m|    \033[32m   %s    \033[34m   |  \033[32m     %s    \033[34m     |   \033[32m  %s\033[33m/\033[32m%s",trcode.c_str(),trsc.c_str(),seat.c_str(),perTicketprice.c_str());
                        for(int k=seat.size()+perTicketprice.size();k<16;k++)printf(" ");
                        printf("\033[34m|   \033[32m  %.2f",stof(seat)*stoi(perTicketprice));
                        string sa=to_string(stoi(seat)*stoi(perTicketprice));
                        for(int k=sa.size();k<11;k++)printf(" ");
                        printf("\033[34m|\033[32m %s \033[34m|\n",ct.c_str());
                        for(int is=(terminalWidth-147)/2;is>0;is--)cout<<' ';
                        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                    }
                    printCenteredTextMulti("\033[31mPress any Key!",20);
                    cin.ignore();
                    cin.ignore();
                    clearScreen();
                    goingBack("going back",4);
                    clearScreen();
                    break;
                }
            case '3':
                {
                    setColor(2);
                    printCenteredTextMulti("\033[32mWhich User You want to Delet: ",58);
                    setColor(5);
                    string tempo;
                    getline(cin,tempo);
                    if(!isNumeric(tempo))
                    {
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                    }
                    w=stoi(tempo);
                    users.erase(users.begin()+(w-1));
                    User oj;
                    oj.updateFile();
                    clearScreen();
                    loadingAnimationOthers("User Deleting......");
                    cout<<endl;
                    setColor(2);
                    printCenteredText("Press Any key!\n");
                    cin.ignore();
                    cin.ignore();
                    clearScreen();
                    goingBack("going back",4);
                    clearScreen();
                    break;
                }
            case '4':
                {
                    setColor(2);
                    printCenteredTextMulti("\033[32mWhich User You Want As An Admin.",58);
                    setColor(5);
                    string tempo;
                    getline(cin,tempo);
                    if(!isNumeric(tempo))
                    {
                        clearScreen();
                        goingBack("going back",4);
                        clearScreen();
                        break;
                    }
                    w=stoi(tempo);
                    admin.push_back(make_pair(users[w-1].username,users[w-1].password));
                    adminInformationToFile();
                    clearScreen();
                    loadingAnimationOthers("Admin Adding......");
                    cout<<endl;
                    setColor(2);
                    clearScreen();
                    printCenteredText("Press Any key!\n");
                    cin.ignore();
                    cin.ignore();
                    clearScreen();
                    goingBack("going back",4);
                    clearScreen();
                    break;
                }
            case '5':
                {
                    loadingAnimation();
                    clearScreen();
                    showTime();
                    setColor(5);
                    printCenteredTextMulti("This is Admin Panel.\n",30);
                    setColor(2);
                    for(int i=0;i<admin.size();i++)
                    {
                        string tempo;
                        tempo=to_string(i+1)+admin[i].first;
                        printCenteredTextMulti(tempo,25);
                    }
                    setColor(2);
                    printCenteredText("Press Any key to go back!\n");
                    cin.ignore();
                    cin.ignore();
                    clearScreen();
                    goingBack("going back",4);
                    clearScreen();
                    break;
                }
            default:
                clearScreen();
                goingBack("going back",4);
                clearScreen();
            }
            }while(ch==1||ch==2||ch==3||ch==4||ch==5);
            break;
        }
        default:
        {
            clearScreen();
            goingBack("loging out",4);
            clearScreen();
            break;
        }
    }
    }while(choice=='1'||choice=='2');
    return;
}

//.....................................LOGIN OR SIGNUP...............................................

void User::signup() {
    clearScreen();
    loadingAnimation();
    clearScreen();
    cout<<"\033[31mPress # to go back!"<<endl;
    showTime();
    printf("\033[1m");
    setColor(9);
    printCenteredTextMulti("Enter Username: ",22);
    setColor(8);
    getline(cin, username);
    if(username=="#"){
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    setColor(9);
    printCenteredTextMulti("Enter Email Address: ",22);
    setColor(8);
    getline(cin, email);
    if(email=="#"){
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    setColor(9);
    printCenteredTextMulti("Enter ID: ",22);
    setColor(8);
    getline(cin, id);
    if(id=="#"){
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    printCenteredTextMulti("\033[31mN.B:\033[32m Password Should Contain Capital,Small,Special,Numeric Charecter.\n",22);
    int A = 0, B = 0, C = 0, D = 0;
    printCenteredTextMulti("\033[32m\033[1mEnter Password: \033[0m",22);
    while (true) {
        char ch = _getch();
        if (ch == '\r') break;
        password += ch;
        cout << '*';

        A = B = C = D = 0;
        for (char c : password) {
            if (c >= 'A' && c <= 'Z') A = 1;
            else if (c >= 'a' && c <= 'z') B = 1;
            else if (c >= '0' && c <= '9') C = 1;
            else D = 1;
        }
        printf("\033[2K\r");
        for(int ami=0;ami<(terminalWidth-22)/2;ami++)printf(" ");
        cout << "\033[32mEnter Password: ";
        if (A + B + C + D < 3) {
            cout << "\033[34m" << password << "\033[1m  (weak)\033[8D\033[0m";
        } else if (A + B + C + D < 4) {
            cout << "\033[33m" << password << "\033[1m  (moderate)\033[12D\033[0m";
        } else {
            cout << "\033[31m" << password << "\033[1m  (strong)\033[10D\033[0m";
        }
        std::cout << std::flush;
    }
    clearScreen();
    for(int ami=0;ami<(terminalHeight-2)/2;ami++)printf("\n");
    printCenteredTextMulti("\033[32mPassword accepted.\n",30);
    printCenteredTextMulti("\033[35mPress any key to back.\n",30);
    cin.ignore();
    cin.ignore();
    clearScreen();
    goingBack("Going Back",5);
    clearScreen();
    users.push_back(*this);
    updateFile();
    return;
}

void User::login() {
    char key;
    do{
        clearScreen();
        loadingAnimation();
        clearScreen();
        showTime();
        setColor(9);
        string searchPassword;
        printCenteredTextMulti("Enter Username: ",20);
        setColor(8);
        getline(cin, searchUsername);
        setColor(9);
        printCenteredTextMulti("Enter Password: ",20);
        setColor(8);
        getline(cin, searchPassword);

        for(auto& it:admin){
            if(it.first==searchUsername && it.second==searchPassword){
                clearScreen();
                welcomeAdmin();
                adminManue();
                return;
            }
        }

        for (auto &it : users) {
            if (searchUsername == it.username && searchPassword == it.password) {
                clearScreen();
                goingBack("Login Successful",2);
                clearScreen();
                userMenu();
                return;
            }
        }
        setColor(4);
        printCenteredTextMulti("\033[35mIncorrect username or password.\n",31);
        key=0;
        printCenteredTextMulti("\033[33mPress 1 To Retry.\n",17);
        printCenteredTextMulti("\033[31mPress any key to Exit.\n",22);
        scanf("%d%*c",&key);
        if(key==1)
        {
            clearScreen();
            loadingAnimation();
            clearScreen();
        }
        else 
        {
            clearScreen();
            goingBack("Exiting",4);
            clearScreen();
        }

    }while(key=='1');
    clearScreen();
    return;
}

void User::forgetPassword() {
    int key;
    do{
        clearScreen();
        loadingAnimation();
        clearScreen();
        string searchUsername, searchEmail, searchId;
        cout<<"\033[31mPress # to go back!"<<endl;
        cout<<"\n\n\n";
        setColor(5);
        printCenteredTextMulti("Enter Your Username: ",25);
        setColor(2);
        getline(cin, searchUsername);
        if(searchUsername=="#"){
            clearScreen();
            goingBack("going back",4);
        }
        setColor(5);
        printCenteredTextMulti("Enter Your Email: ",25);
        setColor(2);
        getline(cin, searchEmail);
        if(searchEmail=="#"){
            clearScreen();
            goingBack("going back",4);
        }
        setColor(5);
        printCenteredTextMulti("Enter Your ID: ",25);
        setColor(2);
        getline(cin, searchId);
        if(searchId=="#"){
            clearScreen();
            goingBack("going back",4);
        }

        for (auto &it : users) {
            if (it.username == searchUsername && it.email == searchEmail && it.id == searchId) {
                string tempo="Your Password is: "+it.password ;
                printCenteredTextMulti(tempo,25);
                cout<<endl;
                printCenteredTextMulti("Press any key!",15);
                cin.ignore();
                cin.ignore();
                clearScreen();
                goingBack("going back",2);
                clearScreen();
                return;
            }
        }
        clearScreen();
        printCenteredTextMulti("\033[31mWrong Information.\n",18);
        key=0;
        printCenteredTextMulti("\033[33mPress 1 To Retry.\n",18);
        printCenteredTextMulti("\033[35mPress any key to Exit.\n",18);
        scanf("%d",&key);
        if(key==1)loadingAnimation();
        else goingBack("Exiting",4);
        clearScreen();
    }while(key==1);
}

void User::writeToFile() {
    ofstream file("E:\\project\\project\\loginData.txt", ios::app);
    if (!file) {
        cerr << "Error: File could not be opened or created!" << endl;
        return;
    }
    file << username << '$' << email << '$' << id << '$' << password << '$' << trainInfo.size();
    for (auto &it : trainInfo) {
        file << '$' << it;
    }
    file <<'$'<<'\n';
    file.close();
}

void User::updateFile() {
    ofstream file("E:\\project\\project\\loginData.txt", ios::out);
    if (!file) {
        cerr << "Error: File could not be opened or created!" << endl;
        return;
    }
    for (auto &its : users) {
        file << its.username << '$' << its.email << '$' << its.id << '$' << its.password << '$' << its.trainInfo.size();
        for (auto &it : its.trainInfo) {
            file << '$' << it;
        }
        file <<'$'<<'\n';
    }

    file.close();
}

void User::readFromFile() {
    ifstream file("E:\\project\\project\\loginData.txt", ios::in);
    if (!file) {
        cerr << "Error: File could not be opened!" << endl;
        return;
    }

    while (!file.eof()) {
        User tempUser;
        string line;
        getline(file, line);

        if (line.empty()) continue;

        istringstream ss(line);
        getline(ss, tempUser.username, '$');
        getline(ss, tempUser.email, '$');
        getline(ss, tempUser.id, '$');
        getline(ss, tempUser.password, '$');

        int trainInfoSize;
        ss >> trainInfoSize;
        ss.ignore(); // Ignore delimiter

        for (int i = 0; i < trainInfoSize; i++) {
            string temp;
            getline(ss, temp, '$');
            tempUser.trainInfo.push_back(temp);
        }

        users.push_back(tempUser);
    }

    file.close();
}

int signupOrLogin() {
    char choice;
    User obj;
    do{
    showTime();
    printf("\n\n\n");
    setColor(5);
    printf("\033[1m");
    printCenteredTextMulti( "\033[1m  _   _      _ _                           \n",20);
    printCenteredTextMulti( "\033[1m | | | | ___| | | ___                      \n",20);
    printCenteredTextMulti( "\033[1m | |_| |/ _ \\ | |/ _ \\                    \n",20);
    printCenteredTextMulti( "\033[1m |  _  |  __/ | | (_) |                    \n",20);
    printCenteredTextMulti( "\033[1m |_| |_|\\___|_|_|\\___/                    \n",20);
    setColor(8);
    printCenteredTextMulti("\033[1m \033[1mWelcome to BD Railway.....                 \n\n",20);
    printCenteredTextMulti("\033[1m \033[32mPress \033[35m1\033[0m for Login\n",20);
    printCenteredTextMulti("\033[1m \033[32mPress \033[35m2\033[0m for Signup\n",20);
    printCenteredTextMulti("\033[1m \033[32mPress \033[35m3\033[0m for Forget Password\n",20);
    printCenteredTextMulti("\033[1m \033[32mPress \033[31many\033[0m key for \033[31mExit.\n\n",20);
    printCenteredTextMulti("\033[1m \033[32mEnter Your Choice: ",20);
    scanf("%c%*c",&choice);

        switch (choice) {
        case '1':{
                obj.login();
                break;
            }

        case '2':
            {
                obj.signup();
                break;
            }

        case '3':
            {
                obj.forgetPassword();
                break;
            }
        default:
            {
                clearScreen();
                goingBack("Exiting",4);
                clearScreen();
                break;
            }
        }
    }while(choice=='1'||choice=='2'||choice=='3');
    return 0;
}

//...................................User Manue.....................................................

void printTicket(string name,string route,string classs, string ticket,string price,string schedule,string passname)
{
    string tempo;
    printCenteredTextMulti("\033[1m\033[32m|==============================================================|        \n",64);
    printCenteredTextMulti("|O                                                            O|        \n",64);
    printCenteredTextMulti("|O                  BANGLADESH RAILWAY                        O|        \n",64);
    printCenteredTextMulti("|O                                                            O|        \n",64);
    for(int is=(terminalWidth-64)/2;is>0;is--)cout<<' ';
    tempo="|O    Train Name: "+name;
    cout<<tempo;
    for(int i=name.size();i<44;i++)printf(" ");
    printf("o|\n");
    //printf("|O    Train Name:                                             O|        \n");
    for(int is=(terminalWidth-64)/2;is>0;is--)cout<<' ';
    tempo="|O    Route: "+route;
    cout<<tempo;
    for(int i=route.size();i<49;i++)printf(" ");
    printf("o|\n");
    //printf("|O    Route:                                                  O|        \n");
    for(int is=(terminalWidth-64)/2;is>0;is--)cout<<' ';
    tempo="|O    Class: "+classs;
    cout<<tempo;
    for(int i=classs.size();i<49;i++)printf(" ");
    printf("o|\n");
    //printf("|O    Class:                                                  O|        \n");
    for(int is=(terminalWidth-64)/2;is>0;is--)cout<<' ';
    tempo="|O    Ticket: "+ticket;
    cout<<tempo;
    for(int i=ticket.size();i<48;i++)printf(" ");
    printf("o|\n");
    //printf("|O    Ticket:                                                 O|        \n");
    for(int is=(terminalWidth-64)/2;is>0;is--)cout<<' ';
    tempo="|O    Price: "+price;
    cout<<tempo;
    for(int i=price.size();i<49;i++)printf(" ");
    printf("o|\n");
    //printf("|O    Price:                                                  O|        \n");
    for(int is=(terminalWidth-64)/2;is>0;is--)cout<<' ';
    tempo="|O    Train Schedule: "+schedule;
    cout<<tempo;
    for(int i=schedule.size();i<40;i++)printf(" ");
    printf("o|\n");
    //printf("|O    Train Schedule:                                         O|        \n");
    for(int is=(terminalWidth-64)/2;is>0;is--)cout<<' ';
    tempo="|O    Passenger Name: "+passname;
    cout<<tempo;
    for(int i=passname.size();i<40;i++)printf(" ");
    printf("o|\n");
    //printf("|O    Passenger Name:                                         O|        \n");
    printCenteredTextMulti("|O                                                            O|        \n",64);
    printCenteredTextMulti("|O                        THANK YOU                           O|        \n",64);
    printCenteredTextMulti("|O                                                            O|        \n",64);
    printCenteredTextMulti("|==============================================================|        \n",64) ;

}

void bookTicket() {
    int choice;
    string tempo;
    int i=1;
    clearScreen();
    cout<<"\033[31mPress # to go Back!"<<endl;
    showTime();
    setColor(2);
    cout<<endl;
    printCenteredTextMulti("\033[1mThis is Our Train Routes: \n\n",30);
    for(const auto& it:destination){
        tempo="\tPress \033[35m"+to_string(i)+"\033[32m for "+it.c_str()+"\n";
        printCenteredTextMulti(tempo,30);
        i++;
    }
    cout<<endl;
    printCenteredTextMulti("Enter your Destination: ",30);
    getline(cin,tempo);
    if(!isNumeric(tempo))
    {
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    choice=stoi(tempo);
    auto it=next(destination.begin(),choice-1);
    string temp = *it;
    setColor(5);
    printf("\n\n");
    printCenteredText("The trains in this route:\n");
    i = 1;
    printCenteredTextMulti("\033[1m\033[34m-----------------------------------------------------------------------------------------------------------------------------------------------\n",143);
    for(int is=(terminalWidth-143)/2;is>0;is--)cout<<' ';
    printf("|\033[35m Train No\033[34m | \033[35m       Train Name   \033[34m    |  \033[35m   Train Code \033[34m   | \033[35m   Train Schedule  \033[34m |  \033[35m  AC seat/Price \033[34m  | \033[35m Non AC seat/Price \033[34m| \033[35m Chair Coach/Price\033[34m |\n");
    printCenteredTextMulti("\033[34m-----------------------------------------------------------------------------------------------------------------------------------------------\n",143);
    for (auto &it : destinationTrain) {
        if (temp == it.first) {
            for(int is=(terminalWidth-143)/2;is>0;is--)cout<<' ';
                printf("\033[34m| \033[32m   %d.  \033[34m  |  \033[32m   %s", i, it.second.trainName.c_str());
                for (int j = it.second.trainName.size(); j < 20; j++) printf(" ");
                printf("\033[34m|    \033[32m    %s     \033[34m   |   \033[32m   %s   \033[34m    |   \033[32m  %d/%.2f", it.second.trainCode.c_str(), it.second.trainSchedule.c_str(), it.second.ac, it.second.acPrice);
                for(int k=int(log10(it.second.ac))+int(log10(it.second.acPrice))+6;k<15;k++)printf(" ");
                printf("\033[34m|  \033[32m   %d/%.2f",it.second.nonAc,it.second.nonAcPrice);
                for(int k=int(log10(it.second.nonAc))+int(log10(it.second.nonAcPrice))+6;k<15;k++)printf(" ");
                printf("\033[34m|  \033[32m   %d/%.2f",it.second.chairCoach,it.second.chairCoachPrice);
                for(int k=int(log10(it.second.chairCoach))+int(log10(it.second.chairCoachPrice))+6;k<15;k++)printf(" ");
                printf("\033[34m|\n");
                for(int is=(terminalWidth-143)/2;is>0;is--)cout<<' ';
                printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n");
                i++;
        }
    }
    printCenteredTextMulti("Enter your desired train no.: ",30);
    getline(cin,tempo);
    if(!isNumeric(tempo)){
        clearScreen();
        goingBack("going back",4);
        clearScreen();
        return;
    }
    choice=stoi(tempo);
    i = 1;
    for (auto &it : destinationTrain) {
        if (temp == it.first) {
            if (i == choice) {
                int amount;
                clearScreen();
                loadingAnimation();
                clearScreen();
                cout<<"\033[31mPress # to go back!"<<endl;
                showTime();
                cout<<endl;
                printCenteredTextMulti("\033[34mChoose your category:\n",40);
                cout<<endl;
                tempo="\033[32mPress \033[35m1\033[32m for Available AC seat/price: "+to_string(it.second.ac)+"\033[34m/\033[32m"+to_string((int)it.second.acPrice)+".00\n";
                printCenteredTextMulti(tempo,40);
                tempo="\033[32mPress \033[35m2\033[32m for Available Non AC seat/price: "+to_string(it.second.nonAc)+"\033[34m/\033[32m"+to_string((int)it.second.nonAcPrice)+".00\n";
                printCenteredTextMulti(tempo,40);
                tempo="\033[32mPress \033[35m3\033[32m for Available ChairCoach seat/price: "+to_string(it.second.chairCoach)+"\033[34m/\033[32m"+to_string((int)it.second.chairCoachPrice)+".00\n";
                printCenteredTextMulti(tempo,40);
                printCenteredTextMulti("Press any to go back.\n\n",40);
                printCenteredTextMulti("Enter your choice: ",40);
                string tempo;
                getline(cin,tempo);
                if(!isNumeric(tempo)){
                    clearScreen();
                    goingBack("going back",4);
                    clearScreen();
                    return;
                }
                int choic=stoi(tempo);
                time_t ct = time(0);
                string currentTime = ctime(&ct);
                if (choic == 1) {
                    if (it.second.ac == 0) {
                        clearScreen();
                        cout<<"\033[31mPress # to go back"<<endl;
                        showTime();
                        printCenteredTextMulti("\033[31m\033[1mSorry sir!!!\n",12);
                        printCenteredTextMulti("\033[33mhere is no ticket available for now.\n",35);
                        printCenteredTextMulti("\033[32mBut you can give your name in the waiting list.\n\n",47);
                        printCenteredTextMulti("\033[32mDo you want to be in wating list?\n",40);
                        printCenteredTextMulti("Press \033[35m1 \033[32mYes\n",40);
                        printCenteredTextMulti("Press \033[35m2\033[32m No\n",40);
                        printCenteredTextMulti("\033[32mEnter your choice: ",40);
                        char hq;
                        scanf("%c%*c",&hq);
                        if(hq!='1'){
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            return;
                        }
                    }
                    printCenteredTextMulti("\033[32mHow many tickets do you want to book: ",40);
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                    clearScreen();
                    goingBack("going back",4);
                    clearScreen();
                    return;
                    }
                    amount=stoi(tempo);
                    if (it.second.ac >= amount) {
                        it.second.ac -= amount;
                        for (auto &ut : users) {
                            if (ut.username == searchUsername) {
                                ut.trainInfo.push_back(it.second.trainName + '*' + it.second.trainCode + '*' + to_string(amount) + '*' + '0' + "*Ac*" + it.second.trainSchedule + '*' + to_string(int(it.second.acPrice)) + '*' + currentTime);
                                it.second.acPassengerList.push_back(make_pair(amount, searchUsername));
                                break;
                            }
                        }
                        clearScreen();
                        loadingAnimationOthers("Booking Ticket...");
                        clearScreen();
                        printTicket(it.second.trainName,it.first,"AC",to_string(amount),to_string(amount*it.second.acPrice),it.second.trainSchedule,searchUsername);
                        writeDestinationTrainToFile();
                        adminInformationToFile();
                        User obj;
                        obj.updateFile();
                        printCenteredTextMulti("Press any Key To Go Back.\n",25);
                        cin.ignore();
                        cin.ignore();
                        clearScreen();
                        goingBack("going back",2);
                        clearScreen();
                        return;

                    } else {
                        char hc;
                        clearScreen();
                        cout<<"\033[31mPress # to go back"<<endl;
                        showTime();
                        printCenteredTextMulti("\033[31m\033[1mSorry sir!!!\n",12);
                        printCenteredTextMulti("\033[33mhere is not ticket available for now.\n",35);
                        tempo="\033[32mYou can buy \033[35m"+to_string(it.second.ac)+"\033[32m ticket for now.\n\n";
                        printCenteredTextMulti(tempo,47);
                        tempo="\tPress \033[35m1 \033[32mto buy \033[35m"+to_string(it.second.ac)+"\033[32m Ticket.\n";
                        printCenteredTextMulti(tempo,47);
                        tempo="\tPress \033[35m1 \033[32mto buy \033[35m"+to_string(it.second.ac)+"\033[32m Ticket and Other in wating list.\n\n";
                        printCenteredTextMulti(tempo,47);
                        printCenteredTextMulti("\033[32mEnter your choice: ",40);
                        scanf("%c%*c",&hc);
                        if(hc!='1'||hc!='2'){
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            return;
                        }
                        if(hc=='1')
                        {
                            for (auto &ut : users) {
                                if (ut.username == searchUsername) {
                                it.second.acPassengerList.push_back(make_pair(it.second.ac, searchUsername));
                                ut.trainInfo.push_back(it.second.trainName + '*' + it.second.trainCode + '*' + to_string(it.second.ac) + '*' + '0' + "*Ac*" + it.second.trainSchedule + '*' + to_string(int(it.second.acPrice)) + '*' + currentTime);
                                break;
                                }
                            }
                            it.second.ac = 0;
                            clearScreen();
                            loadingAnimation();
                            clearScreen();
                            printCenteredTextMulti("\033[35mThis is your ticket:\n\n",20);
                            printTicket(it.second.trainName,it.first,"AC",to_string(it.second.ac),to_string(it.second.ac*it.second.acPrice),it.second.trainSchedule,searchUsername);
                        }
                        else if(hc=='2')
                        {
                            amount -= it.second.ac;
                            it.second.acWaitingList.push_back(make_pair(amount, searchUsername));
                            for (auto &ut : users) {
                                if (ut.username == searchUsername) {
                                    it.second.acPassengerList.push_back(make_pair(it.second.ac, searchUsername));
                                    ut.trainInfo.push_back(it.second.trainName + '*' + it.second.trainCode + '*' + to_string(it.second.ac) + '*' + to_string(amount) + "*Ac*" + it.second.trainSchedule + '*' + to_string(int(it.second.acPrice)) + '*' + currentTime);
                                    break;
                                }
                            }
                        it.second.ac = 0;
                        clearScreen();
                        loadingAnimation();
                        clearScreen();
                        printCenteredTextMulti("\033[35mThis is your ticket:\n\n",20);
                        printTicket(it.second.trainName,it.first,"AC",to_string(it.second.ac),to_string(it.second.ac*it.second.acPrice),it.second.trainSchedule,searchUsername);
                        }else{
                            clearScreen();
                            return;
                        }
                        writeDestinationTrainToFile();
                        adminInformationToFile();
                        User obj;
                        obj.updateFile();
                        printCenteredTextMulti("Press any Key To Go Back.\n",25);
                        cin.ignore();
                        cin.ignore();
                        clearScreen();
                        goingBack("going back",2);
                        clearScreen();
                        return;
                    }
                }
                else if (choic == 2) {
                    if (it.second.nonAc == 0) {
                        clearScreen();
                        cout<<"\033[31mPress # to go back"<<endl;
                        showTime();
                        printCenteredTextMulti("\033[31m\033[1mSorry sir!!!\n",12);
                        printCenteredTextMulti("\033[33mhere is no ticket available for now.\n",35);
                        printCenteredTextMulti("\033[32mBut you can give your name in the waiting list.\n\n",47);
                        printCenteredTextMulti("\033[32mDo you want to be in wating list?\n",40);
                        printCenteredTextMulti("Press \033[35m1 \033[32mYes\n",40);
                        printCenteredTextMulti("Press \033[35m2\033[32m No\n",40);
                        printCenteredTextMulti("\033[32mEnter your choice: ",40);
                        char hq;
                        scanf("%c%*c",&hq);
                        if(hq!='1'){
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            return;
                        }
                    }
                    printCenteredTextMulti("\033[32mHow many tickets do you want to book: ",40);
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                    clearScreen();
                    goingBack("going back",4);
                    clearScreen();
                    return;
                    }
                    amount=stoi(tempo);
                    if (it.second.nonAc >= amount) {
                        it.second.nonAc -= amount;
                        for (auto &ut : users) {
                            if (ut.username == searchUsername) {
                                it.second.acPassengerList.push_back(make_pair(amount, searchUsername));
                                ut.trainInfo.push_back(it.second.trainName + '*' + it.second.trainCode + '*' + to_string(amount) + '*' + '0' + "*NonAc*" + it.second.trainSchedule + '*' + to_string(int(it.second.nonAcPrice)) + '*' + currentTime);
                                break;
                            }
                        }
                        clearScreen();
                        loadingAnimationOthers("Booking Ticket...");
                        clearScreen();
                        printTicket(it.second.trainName,it.first,"Non-Ac",to_string(amount),to_string(amount*it.second.nonAcPrice),it.second.trainSchedule,searchUsername);
                        writeDestinationTrainToFile();
                        adminInformationToFile();
                        User obj;
                        obj.updateFile();
                        printCenteredTextMulti("Press any Key To Go Back.\n",25);
                        cin.ignore();
                        cin.ignore();
                        clearScreen();
                        goingBack("going back",2);
                        clearScreen();
                        return;
                    } else {
                        char hc;
                        clearScreen();
                        cout<<"\033[31mPress # to go back"<<endl;
                        showTime();
                        printCenteredTextMulti("\033[31m\033[1mSorry sir!!!\n",12);
                        printCenteredTextMulti("\033[33mhere is not ticket available for now.\n",35);
                        tempo="\033[32mYou can buy \033[35m"+to_string(it.second.ac)+"\033[32m ticket for now.\n\n";
                        printCenteredTextMulti(tempo,47);
                        tempo="\tPress \033[35m1 \033[32mto buy \033[35m"+to_string(it.second.ac)+"\033[32m Ticket.\n";
                        printCenteredTextMulti(tempo,47);
                        tempo="\tPress \033[35m1 \033[32mto buy \033[35m"+to_string(it.second.ac)+"\033[32m Ticket and Other in wating list.\n\n";
                        printCenteredTextMulti(tempo,47);
                        printCenteredTextMulti("\033[32mEnter your choice: ",40);
                        scanf("%c%*c",&hc);
                        if(hc!='1'|| hc!='2'){
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            return;
                        }
                        if(hc=='1')
                        {
                            for (auto &ut : users) {
                            if (ut.username == searchUsername) {
                                it.second.acPassengerList.push_back(make_pair(it.second.nonAc, searchUsername));
                                ut.trainInfo.push_back(it.second.trainName + '*' + it.second.trainCode + '*' + to_string(it.second.nonAc) + '*' + '0' + "*NonAc*" + it.second.trainSchedule + '*' + to_string(int(it.second.nonAcPrice)) + '*' + currentTime);
                                break;
                            }
                            }
                            it.second.nonAc = 0;
                            clearScreen();
                            loadingAnimation();
                            clearScreen();
                            printCenteredTextMulti("\033[35mThis is your ticket:\n\n",20);
                            printTicket(it.second.trainName,it.first,"Non-Ac",to_string(it.second.nonAc),to_string(it.second.nonAc*it.second.nonAcPrice),it.second.trainSchedule,searchUsername);
                        }
                        else if(hc=='2')
                        {
                            amount -= it.second.nonAc;
                            it.second.nonAcWaitingList.push_back(make_pair(amount, searchUsername));
                            for (auto &ut : users) {
                                if (ut.username == searchUsername) {
                                    it.second.acPassengerList.push_back(make_pair(it.second.nonAc, searchUsername));
                                    ut.trainInfo.push_back(it.second.trainName + '*' + it.second.trainCode + '*' + to_string(it.second.nonAc) + '*' + to_string(amount)+ "*NonAc*" + it.second.trainSchedule + '*' + to_string(int(it.second.nonAcPrice)) + '*' + currentTime);
                                    break;
                                }
                        }
                        it.second.nonAc = 0;
                        clearScreen();
                        loadingAnimation();
                        clearScreen();
                        printCenteredTextMulti("\033[35mThis is your ticket:\n\n",20);
                        printTicket(it.second.trainName,it.first,"Non-Ac",to_string(it.second.nonAc),to_string(it.second.nonAc*it.second.nonAcPrice),it.second.trainSchedule,searchUsername);
                        }
                        else 
                        {
                            clearScreen();
                            return;
                        }
                        writeDestinationTrainToFile();
                        adminInformationToFile();
                        User obj;
                        obj.updateFile();
                        printCenteredTextMulti("Press any Key To Go Back.\n",25);
                        cin.ignore();
                        cin.ignore();
                        clearScreen();
                        goingBack("going back",2);
                        clearScreen();
                        return;
                    }
                }
                else if (choic == 3) 
                {
                    if(it.second.chairCoach==0)
                    {
                        clearScreen();
                        cout<<"\033[31mPress # to go back"<<endl;
                        showTime();
                        printCenteredTextMulti("\033[31m\033[1mSorry sir!!!\n",12);
                        printCenteredTextMulti("\033[33mhere is no ticket available for now.\n",35);
                        printCenteredTextMulti("\033[32mBut you can give your name in the waiting list.\n\n",47);
                        printCenteredTextMulti("\033[32mDo you want to be in wating list?\n",40);
                        printCenteredTextMulti("Press \033[35m1 \033[32mYes\n",40);
                        printCenteredTextMulti("Press \033[35m2\033[32m No\n",40);
                        printCenteredTextMulti("\033[32mEnter your choice: ",40);
                        char hq;
                        scanf("%c%*c",&hq);
                        if(hq!='1'){
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            return;
                        }
                    }
                    printCenteredTextMulti("\033[32mHow many tickets do you want to book: ",40);
                    getline(cin,tempo);
                    if(!isNumeric(tempo)){
                    clearScreen();
                    goingBack("going back",4);
                    clearScreen();
                    return;
                    }
                    amount=stoi(tempo);
                    if (it.second.chairCoach >= amount) 
                    {
                        it.second.chairCoach -= amount;
                        for (auto &ut : users) 
                        {
                            if (ut.username == searchUsername) {
                                it.second.acPassengerList.push_back(make_pair(amount, searchUsername));
                                ut.trainInfo.push_back(it.second.trainName + '*' + it.second.trainCode + '*' + to_string(amount) + '*' + '0' + "*ChairCoach*" + it.second.trainSchedule + '*' + to_string(int(it.second.chairCoachPrice)) + '*' + currentTime);
                                break;
                            }
                        }
                        clearScreen();
                        loadingAnimationOthers("Booking Ticket...");
                        clearScreen();
                        printTicket(it.second.trainName,it.first,"ChairCoach",to_string(amount),to_string(amount*it.second.chairCoachPrice),it.second.trainSchedule,searchUsername);
                        writeDestinationTrainToFile();
                        adminInformationToFile();
                        User obj;
                        obj.updateFile();
                        printCenteredTextMulti("Press any Key To Go Back.\n",25);
                        cin.ignore();
                        cin.ignore();
                        clearScreen();
                        goingBack("going back",2);
                        clearScreen();
                        return;
                    } else {
                        char hc;
                        clearScreen();
                        cout<<"\033[31mPress # to go back"<<endl;
                        showTime();
                        printCenteredTextMulti("\033[31m\033[1mSorry sir!!!\n",12);
                        printCenteredTextMulti("\033[33mhere is not ticket available for now.\n",35);
                        tempo="\033[32mYou can buy \033[35m"+to_string(it.second.ac)+"\033[32m ticket for now.\n\n";
                        printCenteredTextMulti(tempo,47);
                        tempo="\tPress \033[35m1 \033[32mto buy \033[35m"+to_string(it.second.ac)+"\033[32m Ticket.\n";
                        printCenteredTextMulti(tempo,47);
                        tempo="\tPress \033[35m1 \033[32mto buy \033[35m"+to_string(it.second.ac)+"\033[32m Ticket and Other in wating list.\n\n";
                        printCenteredTextMulti(tempo,47);
                        printCenteredTextMulti("\033[32mEnter your choice: ",40);
                        scanf("%c%*c",&hc);
                        if(hc!='1'|| hc!='2'){
                            clearScreen();
                            goingBack("going back",4);
                            clearScreen();
                            return;
                        }
                        if(hc=='1')
                        {
                            for (auto &ut : users){
                                if (ut.username == searchUsername){
                                    it.second.acPassengerList.push_back(make_pair(it.second.chairCoach, searchUsername));
                                    ut.trainInfo.push_back(it.second.trainName + '*' + it.second.trainCode + '*' + to_string(it.second.chairCoach) + '*' + '0' + "*ChairCoach*" + it.second.trainSchedule + '*' + to_string(int(it.second.chairCoachPrice)) + '*' + currentTime);
                                    break;
                                }
                            }
                            it.second.chairCoach = 0;
                            clearScreen();
                            loadingAnimation();
                            clearScreen();
                            printCenteredTextMulti("\033[35mThis is your ticket:\n\n",20);
                            printTicket(it.second.trainName,it.first,"Non-Ac",to_string(it.second.chairCoach),to_string(it.second.chairCoach*it.second.chairCoachPrice),it.second.trainSchedule,searchUsername);
                        }
                        else if(hc=='2')
                        {
                            amount -= it.second.chairCoach;
                            it.second.chairCoachWaitingList.push_back(make_pair(amount, searchUsername));
                            for (auto &ut : users)
                            {
                                if (ut.username == searchUsername)
                                {
                                    it.second.acPassengerList.push_back(make_pair(it.second.chairCoach, searchUsername));
                                    ut.trainInfo.push_back(it.second.trainName + '*' + it.second.trainCode + '*' + to_string(it.second.chairCoach) + '*' + to_string(amount) + "*ChairCoach*" + it.second.trainSchedule + '*' + to_string(int(it.second.chairCoachPrice)) + '*' + currentTime);
                                }
                            }
                            it.second.chairCoach = 0;
                            clearScreen();
                            loadingAnimation();
                            clearScreen();
                            printCenteredTextMulti("\033[35mThis is your ticket:\n\n",20);
                            printTicket(it.second.trainName,it.first,"Non-Ac",to_string(it.second.chairCoach),to_string(it.second.chairCoach*it.second.chairCoachPrice),it.second.trainSchedule,searchUsername);
                        }
                        else 
                        {
                            clearScreen();
                            return;
                        }
                        writeDestinationTrainToFile();
                        adminInformationToFile();
                        User obj;
                        obj.updateFile();
                        printCenteredTextMulti("Press any Key To Go Back.\n",25);
                        cin.ignore();
                        cin.ignore();
                        clearScreen();
                        goingBack("going back",2);
                        clearScreen();
                    }
                }else{
                    return;
                }
            }
            i++;
        }
    }
}
void userProfile()
{
    char choice;
    do{
    clearScreen();
    showTime();
    printCenteredTextMulti("Welcome,,,,In your Profile!\n",27);
    for(auto& it: users)
    {
        if(it.username==searchUsername)
        {
            setColor(6);
            string tempo="Your Name: "+searchUsername+"\n";
            setColor(8);
            printCenteredTextMulti(tempo,45);
            setColor(6);
            tempo="Your Email Address: "+it.email+"\n";
            setColor(8);
            printCenteredTextMulti(tempo,45);
            setColor(6);
            tempo="Your ID: "+it.id+"\n";
            setColor(8);
            printCenteredTextMulti(tempo,45);
            setColor(6);
            tempo="Your Password: "+it.password+"\n";
            setColor(8);
            printCenteredTextMulti(tempo,45);
            cout<<endl;
            printCenteredTextMulti("\033[35m\033[1mTrain & Ticket Information You Have Reserved:\n\n",45);
            string trname,trcode,seat,wating,seatname,trsc,perTicketprice,ct;
            printCenteredTextMulti("\033[1m\033[34m-------------------------------------------------------------------------------------------------------------------------------------------------------\n",147);
            for(int is=(terminalWidth-147)/2;is>0;is--)cout<<' ';
            printf("\033[34m|\033[35m Train No\033[34m |  \033[35m      Train Name    \033[34m   |  \033[35m  Train Code \033[34m  |   \033[35m  Train Schedule   \033[34m  |   \033[35m   Seat/Price   \033[34m   |  \033[35m  Total Price \033[34m   |    \033[35m   Boking time      \033[34m  |\n");
            printCenteredTextMulti("-------------------------------------------------------------------------------------------------------------------------------------------------------\n",147);

            for(int i=0;i<it.trainInfo.size();i++)
            {
                istringstream ss(it.trainInfo[i]);
                getline(ss,trname,'*');
                getline(ss,trcode,'*');
                getline(ss,seat,'*');
                getline(ss,wating,'*');
                getline(ss,seatname,'*');
                getline(ss,trsc,'*');
                getline(ss,perTicketprice,'*');
                getline(ss,ct);
                for(int is=(terminalWidth-147)/2;is>0;is--)cout<<' ';
                printf("\033[34m|   \033[32m  %d   \033[34m |  \033[32m   %s",i+1,trname.c_str());
                for(int j=trname.size();j<20;j++)printf(" ");
                printf("\033[34m|    \033[32m   %s    \033[34m   |  \033[32m     %s    \033[34m     |   \033[32m  %s\033[33m/\033[32m%s",trcode.c_str(),trsc.c_str(),seat.c_str(),perTicketprice.c_str());
                for(int k=seat.size()+perTicketprice.size();k<16;k++)printf(" ");
                printf("\033[34m|   \033[32m  %.2f",stof(seat)*stoi(perTicketprice));
                string sa=to_string(stoi(seat)*stoi(perTicketprice));
                for(int k=sa.size();k<11;k++)printf(" ");
                printf("\033[34m|\033[32m %s \033[34m|\n",ct.c_str());
                for(int is=(terminalWidth-147)/2;is>0;is--)cout<<' ';
                printf("-------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
            printf("\n\n\n");
            printCenteredTextMulti("\033[32mPress \033[35m1\033[32m to Cencel a Train.\n",26);
            printCenteredTextMulti("Press \033[35m2\033[32m to change Password.\n",26);
            printCenteredTextMulti("Press \033[35many\033[32m to Back.\n\n",26);

            printCenteredTextMulti("\033[32mEnter your Choice: ",26);
            scanf("%c%*c",&choice);
            switch(choice){
            case '1':
                {
                    int is;
                    printf("\n\n");
                    printCenteredTextMulti("Which train you want to cencel: ",26);
                    scanf("%d%*c",&is);
                    istringstream ss(it.trainInfo[is-1]);
                    getline(ss,trname,'$');
                    getline(ss,trcode,'$');
                    getline(ss,seat,'$');
                    getline(ss,seatname,'$');
                    it.trainInfo.erase(it.trainInfo.begin()+(is-1));

                    string tempname,tempseat,tempseatname,tempwating;
                    int updetseat=stoi(seat);
                    for(int i=0;i<destinationTrain.size();i++){
                        if(destinationTrain[i].second.trainName==trname){
                            
                            if(seatname=="Ac"){
                                int tumi=0;
                                for(auto ami: destinationTrain[i].second.acPassengerList){
                                    if(ami.second==searchUsername){
                                        destinationTrain[i].second.acPassengerList.erase(destinationTrain[i].second.acPassengerList.begin()+tumi);
                                    }
                                    tumi++;
                                }
                                for(int j=0;j<destinationTrain[i].second.acWaitingList.size();j++){
                                    if(updetseat==0){
                                        break;
                                    }
                                    if(destinationTrain[i].second.acWaitingList[j].first<=updetseat){
                                        for(int ut=0;ut<users.size();ut++){
                                            for(int uts=0;uts<users[ut].trainInfo.size();uts++){
                                                istringstream st(users[ut].trainInfo[uts]);
                                                getline(st,tempname,'$');
                                                getline(st,trcode,'$');
                                                getline(st,tempseat,'$');
                                                getline(st,tempwating,'$');
                                                getline(st,tempseatname,'$');
                                                getline(st,trsc,'$');
                                                getline(st,perTicketprice,'$');
                                                getline(st,ct,'$');
                                                tempseat=to_string(destinationTrain[i].second.acWaitingList[j].first+stoi(tempseat));
                                                tempwating='0';
                                                users[ut].trainInfo[uts]=(tempname+'$'+trcode+'$'+tempseat+'$'+tempwating+'$'+tempseatname+'$'+trsc+'$'+perTicketprice+'$'+ct+'$');
                                                updetseat-=destinationTrain[i].second.acWaitingList[j].first;
                                            }
                                        }
                                    }else{
                                        for(int ut=0;ut<users.size();ut++){
                                            for(int uts=0;uts<users[ut].trainInfo.size();uts++){
                                                istringstream st(users[ut].trainInfo[uts]);
                                                getline(st,tempname,'$');
                                                getline(st,trcode,'$');
                                                getline(st,tempseat,'$');
                                                getline(st,tempwating,'$');
                                                getline(st,tempseatname,'$');
                                                getline(st,trsc,'$');
                                                getline(st,perTicketprice,'$');
                                                getline(st,ct,'$');
                                                tempseat=to_string(stoi(tempseat)+updetseat);
                                                tempwating=to_string(destinationTrain[i].second.acWaitingList[j].first-updetseat);
                                                users[ut].trainInfo[uts]=(tempname+'$'+trcode+'$'+tempseat+'$'+tempwating+'$'+tempseatname+'$'+trsc+'$'+perTicketprice+'$'+ct+'$');
                                                updetseat=0;
                                            }
                                        }
                                    }
                                }
                                destinationTrain[i].second.ac+=updetseat;
                            }else if(seatname=="NonAc"){
                                int tumi=0;
                                for(auto ami: destinationTrain[i].second.nonAcPassengerList){
                                    if(ami.second==searchUsername){
                                        destinationTrain[i].second.nonAcPassengerList.erase(destinationTrain[i].second.nonAcPassengerList.begin()+tumi);
                                    }
                                    tumi++;
                                }
                                for(int j=0;j<destinationTrain[i].second.nonAcWaitingList.size();j++){
                                    if(updetseat==0){
                                        break;
                                    }
                                    if(destinationTrain[i].second.nonAcWaitingList[j].first<=updetseat){
                                        for(int ut=0;ut<users.size();ut++){
                                            for(int uts=0;uts<users[ut].trainInfo.size();uts++){
                                                istringstream st(users[ut].trainInfo[uts]);
                                                getline(st,tempname,'$');
                                                getline(st,trcode,'$');
                                                getline(st,tempseat,'$');
                                                getline(st,tempwating,'$');
                                                getline(st,tempseatname,'$');
                                                getline(st,trsc,'$');
                                                getline(st,perTicketprice,'$');
                                                getline(st,ct,'$');
                                                tempseat=to_string(destinationTrain[i].second.nonAcWaitingList[j].first+stoi(tempseat));
                                                tempwating='0';
                                                users[ut].trainInfo[uts]=(tempname+'$'+trcode+'$'+tempseat+'$'+tempwating+'$'+tempseatname+'$'+trsc+'$'+perTicketprice+'$'+ct+'$');
                                                updetseat-=destinationTrain[i].second.nonAcWaitingList[j].first;
                                            }
                                        }
                                    }else{
                                        for(int ut=0;ut<users.size();ut++){
                                            for(int uts=0;uts<users[ut].trainInfo.size();uts++){
                                                istringstream st(users[ut].trainInfo[uts]);
                                                getline(st,tempname,'$');
                                                getline(st,trcode,'$');
                                                getline(st,tempseat,'$');
                                                getline(st,tempwating,'$');
                                                getline(st,tempseatname,'$');
                                                getline(st,trsc,'$');
                                                getline(st,perTicketprice,'$');
                                                getline(st,ct,'$');
                                                tempseat=to_string(stoi(tempseat)+updetseat);
                                                tempwating=to_string(destinationTrain[i].second.nonAcWaitingList[j].first-updetseat);
                                                users[ut].trainInfo[uts]=(tempname+'$'+trcode+'$'+tempseat+'$'+tempwating+'$'+tempseatname+'$'+trsc+'$'+perTicketprice+'$'+ct+'$');
                                                updetseat=0;
                                            }
                                        }
                                    }
                                }
                                destinationTrain[i].second.nonAc+=updetseat;
                            }else{
                                int tumi=0;
                                for(auto ami: destinationTrain[i].second.chairCoachPassengerList){
                                    if(ami.second==searchUsername){
                                        destinationTrain[i].second.chairCoachPassengerList.erase(destinationTrain[i].second.chairCoachPassengerList.begin()+tumi);
                                    }
                                    tumi++;
                                }
                                for(int j=0;j<destinationTrain[i].second.chairCoachWaitingList.size();j++){
                                    if(updetseat==0){
                                        break;
                                    }
                                    if(destinationTrain[i].second.chairCoachWaitingList[j].first<=updetseat){
                                        for(int ut=0;ut<users.size();ut++){
                                            for(int uts=0;uts<users[ut].trainInfo.size();uts++){
                                                istringstream st(users[ut].trainInfo[uts]);
                                                getline(st,tempname,'$');
                                                getline(st,trcode,'$');
                                                getline(st,tempseat,'$');
                                                getline(st,tempwating,'$');
                                                getline(st,tempseatname,'$');
                                                getline(st,trsc,'$');
                                                getline(st,perTicketprice,'$');
                                                getline(st,ct,'$');
                                                tempseat=to_string(destinationTrain[i].second.chairCoachWaitingList[j].first+stoi(tempseat));
                                                tempwating='0';
                                                users[ut].trainInfo[uts]=(tempname+'$'+trcode+'$'+tempseat+'$'+tempwating+'$'+tempseatname+'$'+trsc+'$'+perTicketprice+'$'+ct+'$');
                                                updetseat-=destinationTrain[i].second.chairCoachWaitingList[j].first;
                                            }
                                        }
                                    }else{
                                        for(int ut=0;ut<users.size();ut++){
                                            for(int uts=0;uts<users[ut].trainInfo.size();uts++){
                                                istringstream st(users[ut].trainInfo[uts]);
                                                getline(st,tempname,'$');
                                                getline(st,trcode,'$');
                                                getline(st,tempseat,'$');
                                                getline(st,tempwating,'$');
                                                getline(st,tempseatname,'$');
                                                getline(st,trsc,'$');
                                                getline(st,perTicketprice,'$');
                                                getline(st,ct,'$');
                                                tempseat=to_string(stoi(tempseat)+updetseat);
                                                tempwating=to_string(destinationTrain[i].second.chairCoachWaitingList[j].first-updetseat);
                                                users[ut].trainInfo[uts]=(tempname+'$'+trcode+'$'+tempseat+'$'+tempwating+'$'+tempseatname+'$'+trsc+'$'+perTicketprice+'$'+ct+'$');
                                                updetseat=0;
                                            }
                                        }
                                    }
                                }
                                destinationTrain[i].second.chairCoach+=updetseat;
                            }

                            break;
                        }
                    }
                    clearScreen();
                    loadingAnimationOthers("Train Cenceling....");
                    clearScreen();
                }
                break;
            case '2':
                for(auto& it: users)
                {
                    if(it.username==searchUsername){
                        string temp,password;
                        clearScreen();
                        cout<<"\033[31mPress # to go back!"<<endl;
                        showTime();
                        printf("\n");
                        printCenteredTextMulti("\033[31mN.B:\033[32m Password Should Contain Capital,Small,Special,Numeric Charecter.\n",22);
                        int A = 0, B = 0, C = 0, D = 0;
                        printCenteredTextMulti("\033[32m\033[1mEnter Password: \033[0m",22);
                        while (true) {
                            char ch = _getch();
                            if (ch == '\r') break;
                            password += ch;
                            cout << '*';

                            A = B = C = D = 0;
                            for (char c : password) {
                            if (c >= 'A' && c <= 'Z') A = 1;
                            else if (c >= 'a' && c <= 'z') B = 1;
                            else if (c >= '0' && c <= '9') C = 1;
                            else D = 1;
                            }
                            printf("\033[2K\r");
                            for(int ami=0;ami<(terminalWidth-22)/2;ami++)printf(" ");
                            cout << "\033[32mEnter Password: ";
                            if (A + B + C + D < 3) {
                            cout << "\033[34m" << password << "\033[1m  (weak)\033[8D\033[0m";
                            } else if (A + B + C + D < 4) {
                            cout << "\033[33m" << password << "\033[1m  (moderate)\033[12D\033[0m";
                            } else {
                            cout << "\033[31m" << password << "\033[1m  (strong)\033[10D\033[0m";
                            }
                            std::cout << std::flush;
                        }
                        clearScreen();
                        for(int ami=0;ami<(terminalHeight-2)/2;ami++)printf("\n");
                        printCenteredTextMulti("\033[32mPassword accepted.",18);
                        printCenteredTextMulti("\033[35mPress any key to back.",22);
                        cin.ignore();
                        cin.ignore();
                        it.password=password;
                        clearScreen();
                        loadingAnimationOthers("Password Updating....");
                        clearScreen();
                        break;
                    }
                }
                break;
            default:
                break;
            }
            break;
        }
    }
    }while(choice=='1'||choice=='2');
    clearScreen();
}
void userMenu() {
    char choice;
    do {
        clearScreen();
        welcomeUser(searchUsername);
        printCenteredTextMulti("\033[32m\033[1mPress \033[35m1\033[32m to Book Ticket       \n",30);
        printCenteredTextMulti("\033[32m\033[1mPress \033[35m2\033[32m to See Your Profile. \n",30);
        printCenteredTextMulti("\033[32m\033[1mPress \033[35many\033[32m to Log Out           \n",30);
        printCenteredTextMulti("\033[32m\033[1mEnter your choice: ",30);
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case '1':
        {
            clearScreen();
            loadingAnimation();
            bookTicket();
            break;
        }
        case '2':
        {
            clearScreen();
            loadingAnimation();
            userProfile();
            break;
        }
        default:
        {
            writeDestinationTrainToFile();
            adminInformationToFile();
            writeDestinationToFile();
            User obj;
            obj.updateFile();
            clearScreen();
            goingBack("Logging out",4);
            return;
        }
        }
    } while (choice == '1'|| choice=='2');
}

//....................................MAIN FUNCTION................................................

int startMain() {
    
    User user;
    user.readFromFile();
    fileToAdminInformation();
    readFileToDestination();
    readDestinationTrainFromFile();
    getTerminalSize(terminalWidth, terminalHeight);
    fristAnimation();
    signupOrLogin();
    return 0;
}
int main()
{
    startMain();
    return 0;
}
