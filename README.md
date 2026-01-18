# ESP32-S3 Simple Calculator (FreeRTOS & PlatformIO)

Đây là dự án máy tính bỏ túi đơn giản được xây dựng trên vi điều khiển **ESP32-S3 N16R8**. Dự án sử dụng **FreeRTOS** để quản lý đa luồng (multitasking) và tách biệt hoàn toàn giữa logic tính toán và xử lý phần cứng.

## 🚀 Tính năng
* Thực hiện các phép tính cơ bản: Cộng, Trừ, Nhân, Chia.
* Hỗ trợ số nguyên và số thực (dấu chấm động).
* Kiến trúc **Modular**: Tách biệt Logic (Core) và Hardware (Tasks).
* **FreeRTOS**: Sử dụng `xTaskCreate` để quản lý Keypad, Button và các tác vụ khác.
* Nút **Clear**: Sử dụng nút BOOT trên mạch để xóa/reset phép tính.
* Output: Kết quả hiển thị qua Serial Monitor (có thể mở rộng lên LCD/OLED).

## 🛠 Phần cứng yêu cầu
* 1x ESP32-S3 (N16R8 hoặc tương đương).
* 1x Keypad Matrix 4x4.
* Dây nối (Jumper wires).

## 🔌 Sơ đồ kết nối (Pinout)

**Lưu ý:** Các chân GPIO dưới đây là cấu hình mặc định trong code, vui lòng kiểm tra lại file `src/task_keypad.cpp` để chỉnh sửa cho phù hợp với mạch thực tế của bạn.

| Keypad Pin | ESP32-S3 GPIO |
| :--- | :--- |
| Row 0 | GPIO 4 |
| Row 1 | GPIO 5 |
| Row 2 | GPIO 6 |
| Row 3 | GPIO 7 |
| Col 0 | GPIO 15 |
| Col 1 | GPIO 16 |
| Col 2 | GPIO 17 |
| Col 3 | GPIO 17 |

* **Nút Clear:** Sử dụng nút BOOT tích hợp sẵn (GPIO 0).

## ⌨️ Bản đồ phím (Keymap)

Do Keypad 4x4 có các ký tự A, B, C, D, chúng được quy ước lại chức năng như sau:

| Phím trên Keypad | Chức năng |
| :---: | :--- |
| `0` - `9` | Nhập số |
| `A` | Cộng (`+`) |
| `B` | Trừ (`-`) |
| `C` | Nhân (`*`) |
| `D` | Chia (`/`) |
| `#` | Bằng (`=`) |
| `*` | Dấu chấm thập phân (`.`) |
| `BOOT Button` | Xóa tất cả (Clear All) |

## 📂 Cấu trúc dự án

Dự án được tổ chức theo cấu trúc module để dễ dàng bảo trì và mở rộng:

```text
├── include/
│   ├── calc_core.h      # Header cho logic tính toán (State Machine)
│   ├── global.h         # Các biến toàn cục (Flags)
│   ├── task_keypad.h    # Header cho tác vụ bàn phím
│   └── button.h         # Header cho tác vụ nút bấm
├── src/
│   ├── calc_core.cpp    # CHỨA LOGIC CHÍNH: Xử lý cộng trừ nhân chia
│   ├── task_keypad.cpp  # Tác vụ FreeRTOS: Quét phím và gửi tín hiệu vào Core
│   ├── button.cpp       # Tác vụ FreeRTOS: Đọc nút BOOT để reset
│   ├── main.cpp         # Khởi tạo và tạo các Task
│   └── ...
└── platformio.ini       # Cấu hình PlatformIO & Thư viện
