#include "calc_core.h"

static String currentInput = "";
static float firstNumber = 0;
static float secondNumber = 0;
static char currentOperator = 0;
static bool isResultDisplayed = false;

void calc_init(){
    calc_reset();
};

// Hàm reset máy tính (dùng cho nút BOOT)
void calc_reset(){
    currentInput = "";
    firstNumber = 0;
    secondNumber = 0;
    currentOperator = 0;
    isResultDisplayed = false;
    Serial.println("\n[Calc] System Ready. Waiting for input...");
};

// Hàm nhận tín hiệu đầu vào từ phím (đây là nơi chứa State Machine)
void calc_process_input(char key){

    // 1. Xử lý logic khi vừa hiển thị kết quả xong mà nhập số mới -> Reset
    if (isResultDisplayed && ((key >= '0' && key <= '9') || key == '.')) {
        currentInput = "";
        firstNumber = 0;
        currentOperator = 0;
        isResultDisplayed = false;
        Serial.println("\n[Calc] New calculation started.");
    }

    // 2. Nhóm phím SỐ và CHẤM
    if ((key >= '0' && key <= '9') || key == '.') {
        if (key == '.' && currentInput.indexOf('.') != -1) {
            return; // Đã có dấu chấm rồi thì thôi
        }
        currentInput += key;
        Serial.print(key); // Hiển thị số đang nhập
    }

    else if (key == '+' || key == '-' || key == '*' || key == '/') {
        if (isResultDisplayed){
            Serial.print(firstNumber);
        }

        if (currentInput.length() > 0) {
            firstNumber = currentInput.toFloat(); // Lưu số cũ
            currentOperator = key;                // Lưu phép tính
            currentInput = "";                    // Xóa để nhập số mới
            isResultDisplayed = false;
            
            Serial.print(" ");
            Serial.print(currentOperator);
            Serial.print(" ");
        }
    } 
    // 4. Phím BẰNG (=)
    else if (key == '=') {
        if (currentInput.length() > 0 && currentOperator != 0) {
            secondNumber = currentInput.toFloat();
            float result = 0;
            bool error = false;

            switch (currentOperator) {
                case '+': result = firstNumber + secondNumber; break;
                case '-': result = firstNumber - secondNumber; break;
                case '*': result = firstNumber * secondNumber; break;
                case '/': 
                    if (secondNumber == 0) error = true;
                    else result = firstNumber / secondNumber; 
                    break;
            }

            Serial.print(" = ");
            if (error) {
                Serial.println("Error");
            } else {
                Serial.println(result);
                firstNumber = result;
                currentInput = String(result); 
            }
            isResultDisplayed = true; // Đánh dấu đã xong
        }
    }

};


