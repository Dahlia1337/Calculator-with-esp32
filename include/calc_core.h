#if !defined(CALC_CORE_H)
#define CALC_CORE_H

#include "global.h"

// Hàm khởi tạo các biến tính toán
void calc_init();

// Hàm nhận tín hiệu đầu vào từ phím (đây là nơi chứa State Machine)
void calc_process_input(char key);

// Hàm reset máy tính (dùng cho nút BOOT)
void calc_reset();

#endif // CALC_CORE_H
