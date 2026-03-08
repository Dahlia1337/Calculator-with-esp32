#include "task_wifi.h"
#include <WiFi.h>
#include <Preferences.h>


void task_wifi(void *parameter) {
    Preferences preferences;

    // 1. Mở không gian nhớ có tên "wifi" ở chế độ Đọc (true = Read Only)
    preferences.begin("wifi", true);
    String ssid = preferences.getString("ssid", "");
    String pass = preferences.getString("pass", "");
    preferences.end();

    Serial.println("[WiFi] Đang khởi động mạng...");

    // 2. Logic kiểm tra và kết nối
    bool connected = false;

    if (ssid != "") {
        Serial.printf("[WiFi] Tìm thấy WiFi đã lưu: %s\n", ssid.c_str());
        Serial.println("[WiFi] Đang thử kết nối (STA Mode)...");
        
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid.c_str(), pass.c_str());

        // Chờ kết nối trong khoảng 10 giây (20 lần * 500ms)
        int attempts = 0;
        while (WiFi.status() != WL_CONNECTED && attempts < 20) {
            Serial.print(".");
            vTaskDelay(500 / portTICK_PERIOD_MS); // Không dùng delay() trong FreeRTOS
            attempts++;
        }
        Serial.println();

        if (WiFi.status() == WL_CONNECTED) {
            connected = true;
            Serial.print("[WiFi] KẾT NỐI THÀNH CÔNG! Địa chỉ IP: ");
            Serial.println(WiFi.localIP());
        } else {
            Serial.println("[WiFi] Kết nối thất bại (Sai pass hoặc không có mạng).");
        }
    } else {
        Serial.println("[WiFi] Không có WiFi nào được lưu trong bộ nhớ.");
    }

    // 3. Nếu kết nối thất bại hoặc không có SSID, chuyển sang phát WiFi (AP Mode)
    if (!connected) {
        Serial.println("[WiFi] Đang chuyển sang chế độ Trạm phát (AP Mode)...");
        WiFi.mode(WIFI_AP);
        
        // Tên WiFi mà ESP32 phát ra (Mật khẩu là 12345678)
        WiFi.softAP("ESP32_Calculator_Setup", "12345678");
        
        Serial.print("[WiFi] ĐÃ PHÁT WIFI! Tên: ESP32_Calculator_Setup - Pass: 12345678\n");
        Serial.print("[WiFi] Truy cập IP cấu hình: ");
        Serial.println(WiFi.softAPIP());
    }

    // 4. Vòng lặp duy trì mạng (Auto Reconnect)
    while (1) {
        // Nếu đang ở chế độ bắt WiFi (STA) mà bị rớt mạng
        if (WiFi.getMode() == WIFI_STA && WiFi.status() != WL_CONNECTED) {
            Serial.println("[WiFi] Mất kết nối! Đang thử kết nối lại...");
            WiFi.disconnect();
            WiFi.reconnect();
            vTaskDelay(5000 / portTICK_PERIOD_MS); // Chờ 5s trước khi check lại
        }
        
        // Nghỉ ngơi 10 giây rồi mới kiểm tra lại để nhường CPU cho tính toán
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}