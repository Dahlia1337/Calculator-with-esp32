// 1. Logic chuyển Tab
function openTab(tabId) {
  document
    .querySelectorAll(".tab-content")
    .forEach((tab) => tab.classList.remove("active"));
  document
    .querySelectorAll(".tab-btn")
    .forEach((btn) => btn.classList.remove("active"));
  document.getElementById(tabId).classList.add("active");
  event.currentTarget.classList.add("active");
}

// 2. Logic gửi phím bấm từ Web xuống ESP32
function sendKey(key) {
  // Gửi HTTP GET request (vd: /press?key=5)
  fetch(`/press?key=${encodeURIComponent(key)}`)
    .then((response) => console.log("Đã gửi phím:", key))
    .catch((error) => console.error("Lỗi:", error));
}

// 3. Logic gửi thông tin WiFi
function saveWiFi(event) {
  event.preventDefault(); // Ngăn trang web tải lại
  const ssid = document.getElementById("ssid").value;
  const pass = document.getElementById("password").value;

  // Gửi HTTP POST request tới ESP32
  fetch("/save-wifi", {
    method: "POST",
    headers: { "Content-Type": "application/x-www-form-urlencoded" },
    body: `ssid=${encodeURIComponent(ssid)}&pass=${encodeURIComponent(pass)}`,
  })
    .then((response) => {
      alert("Đã gửi cấu hình WiFi! ESP32 đang khởi động lại...");
    })
    .catch((error) => alert("Có lỗi xảy ra khi gửi."));
}

// 4. Logic liên tục cập nhật màn hình máy tính từ ESP32
// Cứ mỗi 500ms sẽ hỏi ESP32 xem màn hình đang hiển thị gì
setInterval(() => {
    fetch('/display')
        .then(response => {
            if (response.ok) return response.text(); // Chỉ xử lý nếu tìm thấy trang (status 200)
            throw new Error('Chưa có dữ liệu');
        })
        .then(text => {
            document.getElementById('display').innerText = text;
        })
        .catch(err => {
            // Không làm gì cả hoặc hiện số 0 để giữ thẩm mỹ
            console.log("0");
        });
}, 500);
