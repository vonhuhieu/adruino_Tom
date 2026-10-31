# 📖 BÍ KÍP SETUP DỰ ÁN ARDUINO / ESP32 TRÊN LAPTOP TỪ A ĐẾN Z
> **Thánh Cô ban phước lành và khai sáng cho đệ tử**  
> *Dành cho buổi thuyết trình và báo cáo đồ án Nhà thông minh STEM (ESP32)*

---

## 🎯 MỤC TIÊU
Giúp đệ tử sao chép toàn bộ dự án từ máy tính để bàn (PC) sang Laptop, cài đặt đầy đủ môi trường, thư viện, driver nạp code mượt mà, sẵn sàng biểu diễn demo trực tiếp trước mặt thầy cô và bạn bè mà không gặp bất kỳ lỗi nào.

---

## BƯỚC 1: COPY TOÀN BỘ THƯ MỤC DỰ ÁN SANG LAPTOP
1. Trên PC, hãy nén cả thư mục `arduino_Tom` thành file `.zip` (hoặc chép qua USB / Google Drive / Zalo).
2. Tải về và giải nén trên Laptop (Ví dụ đặt tại: `D:\arduino_Tom` hoặc `C:\arduino_Tom` hoặc ngoài màn hình Desktop).

> 💡 **Lưu ý quan trọng từ Thánh cô về file code:**  
> File code của con hiện tại tên là `dev.cpp`. Phần mềm Arduino IDE quy định file code chính phải có đuôi `.ino` và nằm trong thư mục trùng tên.  
> 👉 Con hãy tạo một thư mục con tên là `dev`, sau đó copy file `dev.cpp` vào và đổi tên thành `dev.ino` (hoặc mở trực tiếp `dev.cpp` bằng Arduino IDE, phần mềm sẽ tự hỏi có muốn tạo thư mục `dev` không -> chọn **OK**).

---

## BƯỚC 2: CÀI ĐẶT DRIVER GIAO TIẾP MÁY TÍNH VỚI ESP32 (CP210x)
Khi cắm cáp kết nối ESP32 với laptop, laptop cần Driver để nhận diện cổng COM (USB to UART).

Trong thư mục dự án `arduino_Tom` của con đã có sẵn bộ driver **Silicon Labs CP210x**:
1. Cắm bo mạch ESP32 vào cổng USB trên Laptop bằng cáp truyền dữ liệu (cáp sạc có dây data).
2. Vào thư mục `arduino_Tom`:
   - Tìm file **`silabser.inf`** (loại file *Setup Information*).
   - Nhấp chuột phải vào file **`silabser.inf`** -> Chọn **Install** (Cài đặt).
   - Chờ vài giây có thông báo *"The operation completed successfully"*.
3. **Kiểm tra cổng COM:**
   - Nhấn phím `Windows + X` -> Chọn **Device Manager** (Quản lý thiết bị).
   - Mở rộng mục **Ports (COM & LPT)**.
   - Nếu thấy hiện dòng: `Silicon Labs CP210x USB to UART Bridge (COMx)` (với `x` là số, ví dụ `COM3`, `COM4`...) là đã cài thành công!

*(Nếu bo ESP32 của con dùng chip nạp CH340 giá rẻ mà cắm vào chưa thấy cổng COM, chỉ cần tải thêm driver `CH341SER.EXE` cài là xong).*

---

## BƯỚC 3: CÀI ĐẶT PHẦN MỀM ARDUINO IDE TRÊN LAPTOP
1. Vào trang chủ tải Arduino IDE: [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Chọn phiên bản mới nhất: **Windows Win 10 and newer, 64 bits**.
3. Tải về file `.exe` và cài đặt bình thường (Next -> I Agree -> Install).

---

## BƯỚC 4: CẤU HÌNH GÓI BO MẠCH ESP32 TRONG ARDUINO IDE
Arduino IDE ban đầu chỉ hỗ trợ Arduino Uno/Nano, con phải thêm gói bo mạch ESP32 theo các bước sau:

1. Mở **Arduino IDE**.
2. Trên thanh menu, vào **File** -> **Preferences** (hoặc nhấn tổ hợp phím `Ctrl + ,`).
3. Tại ô **Additional boards manager URLs**, dán đường link sau vào:
   ```text
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
   *(Nếu đã có sẵn link khác, nhấn icon cửa sổ bên cạnh rồi dán link này xuống dòng mới)* -> Nhấn **OK**.
4. Nhìn sang thanh công cụ bên trái, bấm vào biểu tượng **Boards Manager** (hình bo mạch IC) hoặc nhấn `Ctrl + Shift + B`.
5. Gõ tìm kiếm: `esp32`.
6. Tìm gói **esp32 by Espressif Systems** -> Nhấn nút **INSTALL** (chờ tải khoảng 1-2 phút tùy mạng).

---

## BƯỚC 5: CÀI ĐẶT CÁC THƯ VIỆN CẦN THIẾT
Dự án của con dùng Màn hình OLED và Cảm biến nhiệt ẩm DHT11, do đó cần cài đủ 3 thư viện:

1. Trên thanh công cụ bên trái Arduino IDE, bấm vào biểu tượng **Library Manager** (hình 3 cuốn sách) hoặc nhấn `Ctrl + Shift + I`.
2. **Cài thư viện 1 - Màn hình OLED:**
   - Gõ tìm: `Adafruit SSD1306`.
   - Chọn bản của **Adafruit** -> Bấm **INSTALL**.
   - Nếu hiện bảng hỏi *"Install library with all dependencies?"* -> Bấm chọn **INSTALL ALL** (nó sẽ tự cài luôn thư viện `Adafruit GFX Library`).
3. **Cài thư viện 2 - Đồ họa Adafruit GFX (nếu chưa cài):**
   - Gõ tìm: `Adafruit GFX Library` của **Adafruit** -> Bấm **INSTALL**.
4. **Cài thư viện 3 - Cảm biến DHT11:**
   - Gõ tìm: `DHT sensor library`.
   - Chọn bản của **Adafruit** -> Bấm **INSTALL** -> Chọn **INSTALL ALL** (nó sẽ tự cài thêm `Adafruit Unified Sensor`).

---

## BƯỚC 6: CHỌN BO MẠCH, CỔNG COM VÀ NẠP CODE
1. Mở file code dự án (`dev.ino` hoặc `dev.cpp`).
2. Vào menu **Tools** -> **Board** -> **esp32** -> Chọn **DOIT ESP32 DEVKIT V1** (hoặc chọn dòng *ESP32 Dev Module*).
3. Vào menu **Tools** -> **Port** -> Chọn đúng cổng COM của ESP32 (ví dụ: `COM3`, `COM4`...).
4. Bấm nút dấu tích tròn **Verify (Biên dịch)** ở góc trên bên trái để kiểm tra code có biên dịch thành công không.
5. Bấm nút mũi tên sang phải **Upload (Nạp code)**:
   - Lúc màn hình đen bên dưới hiện chữ `Connecting........_____.....`:
   - 👉 **Mẹo của Thánh cô:** Nếu thấy máy đứng ở chữ `Connecting...`, hãy **nhấn và giữ nút BOOT** trên bo ESP32 khoảng 1 - 2 giây rồi thả ra, code sẽ bắt đầu nạp ngay!
6. Khi nạp xong 100%, bo mạch sẽ khởi động lại và còi Buzzer kêu bíp bíp 2 tiếng chào mừng, màn hình OLED sáng lên!

---

## BƯỚC 7: CÁCH MỞ SERIAL MONITOR ĐỂ THUYẾT TRÌNH TRÊN LỚP
1. Trong Arduino IDE, bấm vào biểu tượng kính lúp ở góc trên bên phải để mở **Serial Monitor** (hoặc phím tắt `Ctrl + Shift + M`).
2. Ở góc của cửa sổ Serial Monitor, nhớ chỉnh tốc độ truyền baudrate là: **`115200 baud`** (trùng với `Serial.begin(115200)` trong code).
3. Con sẽ thấy dữ liệu cảm biến nhảy liên tục mỗi 1 giây rất chuyên nghiệp để trình chiếu lên máy chiếu cho thầy cô xem!

---

## 📌 SƠ ĐỒ ĐẤU DÂY DỰ PHÒNG (CHO ĐỆ TỬ NẾU BỊ TUỘT DÂY TRÊN LỚP)
- **Màn hình OLED 0.96 (I2C):**
  - `VCC` -> Chân `3V3` (hoặc `5V`)
  - `GND` -> Chân `GND`
  - `SDA` -> Chân `D21`
  - `SCL` -> Chân `D22`
- **Còi Buzzer:**
  - Chân `+` -> Chân `D5`
  - Chân `-` -> Chân `GND`
- **Cảm biến Mưa (Rain Sensor):**
  - Chân `DO` -> Chân `D18`
  - `VCC` -> `3V3`
  - `GND` -> `GND`
- **Cảm biến Ánh sáng (Quang trở):**
  - Chân `DO` -> Chân `D19`
  - `VCC` -> `3V3`
  - `GND` -> `GND`
- **Cảm biến DHT11 (Nhiệt độ - Độ ẩm):**
  - Chân `DATA / OUT` -> Chân `D4`
  - `VCC` -> `3V3` (hoặc `5V`)
  - `GND` -> `GND`

---

## ⚠️ BẢO BỐI CỨU NGUY KHI LÊN LỚP THUYẾT TRÌNH
1. **Dây cáp USB:** Tuyệt đối phải dùng sợi cáp **có truyền dữ liệu** (cáp sạc xịn), không dùng sợi cáp sạc trôi nổi chỉ có 2 dây nguồn vì cắm vào máy tính sẽ không bao giờ nhận cổng COM!
2. **Nước thử cảm biến mưa:** Mang theo một miếng khăn giấy ướt hoặc lọ nước nhỏ để nhỏ 1 giọt lên mặt cảm biến mưa lúc thuyết trình kịch bản cảnh báo.
3. **Mẹo che cảm biến ánh sáng:** Dùng ngón tay bịt đầu quang trở để mô phỏng trời tối (đêm) và bỏ tay ra để thành trời sáng (ngày).
4. **Mẹo thở hơi ấm vào DHT11:** Thổi một hơi thở nhẹ vào DHT11 để nhiệt độ và độ ẩm trên màn hình OLED tăng lên tức thì trước mắt thầy cô.

*Thánh cô chúc đệ tử bảo vệ đồ án đại thành công, đạt điểm 10 rực rỡ!*

