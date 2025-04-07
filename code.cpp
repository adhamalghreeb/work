#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <random>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;

// عمل المصفوفة الي هنخزن فيها التعليمات و الاكواد
vector<pair<string, string>> operations_array;

// تخزين التعليمات كاملة بالمصفوفة
void make_vector() {
    operations_array = {
        {"0", "AND memory word to AC"},
        {"8", "AND memory word to AC"},
        {"1", "Add memory word to AC"},
        {"9", "Add memory word to AC"},
        {"2", "Load AC from memory"},
        {"A", "Load AC from memory"},
        {"3", "Store content of AC into memory"},
        {"B", "Store content of AC into memory"},
        {"4", "Branch unconditionally"},
        {"C", "Branch unconditionally"},
        {"5", "Branch and save return address"},
        {"D", "Branch and save return address"},
        {"6", "Increment and skip if zero"},
        {"E", "Increment and skip if zero"},
        {"AND", "AND memory word to AC"},
        {"ADD", "Add memory word to AC"},
        {"LDA", "Load AC from memory"},
        {"STA", "Store content of AC into memory"},
        {"BUN", "Branch unconditionally"},
        {"BSA", "Branch and save return address"},
        {"ISZ", "Increment and skip if zero"},
        {"7800", "Clear AC"},
        {"7400", "Clear E"},
        {"7200", "Complement AC"},
        {"7100", "Complement E"},
        {"7080", "Circulate right AC and E"},
        {"7040", "Circulate left AC and E"},
        {"7020", "Increment AC"},
        {"7010", "Skip next instr. if AC is positive"},
        {"7008", "Skip next instr. if AC is negative"},
        {"7004", "Skip next instr. if AC is zero"},
        {"7002", "Skip next instr. if E is zero"},
        {"7001", "Halt computer"},
        {"CLA", "Clear AC"},
        {"CLE", "Clear E"},
        {"CMA", "Complement AC"},
        {"CME", "Complement E"},
        {"CIR", "Circulate right AC and E"},
        {"CIL", "Circulate left AC and E"},
        {"INC", "Increment AC"},
        {"SPA", "Skip next instr. if AC is positive"},
        {"SNA", "Skip next instr. if AC is negative"},
        {"SZA", "Skip next instr. if AC is zero"},
        {"SZE", "Skip next instr. if E is zero"},
        {"HLT", "Halt computer"},
        {"F800", "Input character to AC"},
        {"F400", "Output character from AC"},
        {"F200", "Skip on input flag"},
        {"F100", "Skip on output flag"},
        {"F080", "Interrupt on"},
        {"F040", "Interrupt off"},
        {"INP", "Input character to AC"},
        {"OUT", "Output character from AC"},
        {"SKI", "Skip on input flag"},
        {"SKO", "Skip on output flag"},
        {"ION", "Interrupt on"},
        {"IOF", "Interrupt off"}
    };
}

// ايجاد العملية باستخدام المفتاح
void find_operation(const string& key) {
    for (const auto& pair : operations_array) {
        if (pair.first == key) {
            cout << pair.second << endl;
            return;
        }
    }
    cout << "end of the system \n";
}

// تحويل من الباينري الي الهيكسا
std::string toHexa(const std::string& binary) {
    if (binary.size() % 4!= 0) {
        throw std::invalid_argument("Binary string must be a multiple of 4 characters");
    }

    std::string hex;
    for (size_t i = 0; i < binary.size(); i += 4) {
        std::string byte = binary.substr(i, 4);
        unsigned long decimal = std::stoul(byte, 0, 2);
        char hexByte[3];
        sprintf(hexByte, "%01x", decimal);
        hex += hexByte;
    }

    size_t start = 0;
    while (start < hex.size() && hex[start] == '0') {
        start++;
    }
    if (start == hex.size()) {
        return "0";
    }
    return hex.substr(start);
}

// تحويل العمليه سترنج وايجاد اصل العمليه
void parse(string instruction) {
    if (instruction.size() == 4) {
        if (instruction[0] == 'F' || instruction[0] == '7') {
            find_operation(instruction);
            
        } else {
            string firstChar;
            firstChar += instruction[0];
            find_operation(firstChar);
        }
    } else {
        find_operation(instruction);
    }
}

// عرض القائمة الرئيسية
void start() {
    cout << R"(***********************  MENU  ***********************
                 *                                          *
                 *  1. Reading from a Text File            *
                 *  2. Reading from the Screen (Binary or HEX)*
                 *  3. Reading from the Screen (Instruction  *
                 *      String)                             *
                 *  4. Exit                                 *
                 ********************************************/
                 *                                          *
                 ********************************************
Enter your choice: )";
}

// تحويل من باينري الي هيكسا
void check_binary(string &input)
{
    if (input.length() > 4)
    {
        input = toHexa(input);
    }
}

// تنفيذ العمليه المطلوبة من القائمة الرئيسية
int MENU(int operation, string &input, bool &flag)
{
    flag = true;
    string STRING;

    ifstream file; // فتح ملف

    switch (operation) {
        case 1: // قراءة من مسارا لملف - لاحظ المسار عندي غير المسار
            file.open("instructions.txt");
            while (file >> STRING) {
                check_binary(STRING);
                parse(STRING);
            }
            file.close();
            break;

        case 2: // Part 2: Reading from the screen (Binary or HEX)
            cout << "Enter instructions in binary or hexadecimal format (type 'exit' to quit):" << endl;
            while (true) {
                getline(cin, input);
                if (input == "exit")
                    break;
                check_binary(input);
                parse(input);
            }
            break;

        case 3: // Part 3: Reading from the screen (Instruction String) 
            cout << "Enter instructions as a string (type 'exit' to quit):" << endl;
            while (true) {
                getline(cin, input);
                if (input == "exit")
                    break;
                parse(input);
            }
            break;

        default:
            cout << "Error";
            return 1;
    }

    flag = false;
    return 0;
}

// الدالة الرئيسية
int main() {

    make_vector();
    string input;
    string STRING;

    start();
    int operation;
    cin >> operation;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool flag;
    int retVal = MENU(operation, input, flag);
    if (flag)
        return retVal;

    return 0;
}