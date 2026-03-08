#include "task_calc.h"
#include "global.h"
#include "calc_core.h"

void task_calculator(void *parameter) {
    // Khởi tạo máy trạng thái tính toán
    calc_init();
    
    char receivedKey;

    while (1) {
        // Kiểm tra nút Clear (BOOT button)
        if (clear_requested) {
            calc_reset();
            clear_requested = false;
        }

        // Đợi nhận thư từ Queue (Chờ tối đa portMAX_DELAY - nghĩa là chờ mãi mãi đến khi có thư)
        if (xQueueReceive(keyQueue, &receivedKey, portMAX_DELAY) == pdPASS) {
            Serial.print("[Calc Task] Nhận được phím: ");
            Serial.println(receivedKey);
            
            // Nếu nhận được phím 'C' từ Web (Nút Clear trên Web)
            if (receivedKey == 'C' || receivedKey == 'c') {
                calc_reset();
            } else {
                // Đưa vào logic tính toán
                calc_process_input(receivedKey);
            }
        }
    }
}