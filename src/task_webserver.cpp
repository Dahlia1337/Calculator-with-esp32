#include "task_webserver.h"
#include <ESPmDNS.h>

AsyncWebServer server(80);

Preferences preferences;

void task_webserver(void *parameter) {
    // 1. Khởi động LittleFS để đọc file HTML
    if(!LittleFS.begin(true)){
        Serial.println("Lỗi Mount LittleFS!");
        vTaskDelete(NULL); // Dừng task nếu lỗi
    }

    // --- ĐỊNH TUYẾN CÁC ĐƯỜNG DẪN (ROUTING) ---

    // 2. Khi người dùng vào trang chủ "/", gửi file index.html ra
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/index.html", "text/html");
    });
    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/script.js", "application/javascript");
    });
    server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/styles.css", "text/css"); 
    });

    // 3. Khi Web gửi lệnh bấm phím (VD: /press?key=5)
    server.on("/press", HTTP_GET, [](AsyncWebServerRequest *request){
        if (request->hasParam("key")) {
            String keyStr = request->getParam("key")->value();
            char key = keyStr.charAt(0);
            
            // Nhét phím vào Queue để gửi sang calc_core xử lý
            if(keyQueue != NULL) {
                xQueueSend(keyQueue, &key, (TickType_t)10);
            }
            request->send(200, "text/plain", "OK");
        } else {
            request->send(400, "text/plain", "Missing key");
        }
    });

    // 4. Khi Web hỏi màn hình đang có gì (Cập nhật mỗi 500ms)
    server.on("/display", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", currentDisplay);
    });

    // 5. Khi Web gửi Form lưu cấu hình WiFi (Tab 2)
    server.on("/save-wifi", HTTP_POST, [](AsyncWebServerRequest *request){
        String ssid = "";
        String pass = "";
        
        // Lấy dữ liệu từ Form (POST body)
        if (request->hasParam("ssid", true)) {
            ssid = request->getParam("ssid", true)->value();
        }
        if (request->hasParam("pass", true)) {
            pass = request->getParam("pass", true)->value();
        }

        if (ssid != "") {
            // Mở không gian nhớ tên "wifi" ở chế độ Ghi (false = Read/Write)
            preferences.begin("wifi", false);
            preferences.putString("ssid", ssid);
            preferences.putString("pass", pass);
            preferences.end();
            
            request->send(200, "text/plain", "Saved. Restarting...");
            
            Serial.println("Đã lưu WiFi mới. Đang khởi động lại...");
            delay(1000);
            ESP.restart(); // Khởi động lại chip ngay lập tức để nhận WiFi mới
        } else {
            request->send(400, "text/plain", "Error: No SSID");
        }
    });

    if (MDNS.begin("calculator")) { 
        Serial.println("✅ mDNS responder started");
        MDNS.addService("http", "tcp", 80);
    } else {
        Serial.println("❌ Error setting up MDNS responder!");
    }

    // Khởi chạy Server
    server.begin();
    Serial.println("[Web Server] Đã khởi chạy ở Port 80!");

    // Vì ESPAsyncWebServer chạy ngầm bằng các ngắt (Interrupts/Events)
    // Task này không cần vòng lặp while(1) để giữ nó sống. Ta có thể xóa Task đi để tiết kiệm RAM.
    vTaskDelete(NULL);
}