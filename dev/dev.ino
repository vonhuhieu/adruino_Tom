#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

// ================= CẤU HÌNH CÁC CHÂN =================
#define PIN_BUZZER  5    // Còi Buzzer
#define PIN_RAIN    18   // Cảm biến Mưa (chân DO)
#define PIN_LIGHT   19   // Cảm biến Ánh sáng (chân DO)
#define PIN_DHT     4    // Cảm biến DHT11 (chân DATA)
#define DHTTYPE     DHT11

// Cấu hình màn hình OLED 0.96 inch (SDA = D21, SCL = D22)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Khởi tạo cảm biến DHT11
DHT dht(PIN_DHT, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n==========================================");
  Serial.println("   THANH CO: KHOI DONG TOAN BO HE THONG   ");
  Serial.println("==========================================");

  // Cấu hình chân còi và cảm biến
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW); // Tắt còi ban đầu

  pinMode(PIN_RAIN, INPUT);
  pinMode(PIN_LIGHT, INPUT);

  // Khởi động DHT11
  dht.begin();

  // Khởi động OLED I2C (thử 0x3C rồi đến 0x3D)
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3D);
  }

  // --- BƯỚC TEST CÒI CHÀO MỪNG: KÊU BÍP BÍP 2 TIẾNG ---
  digitalWrite(PIN_BUZZER, HIGH);
  delay(150);
  digitalWrite(PIN_BUZZER, LOW);
  delay(100);
  digitalWrite(PIN_BUZZER, HIGH);
  delay(150);
  digitalWrite(PIN_BUZZER, LOW);

  // Màn hình khởi động chào mừng
  display.clearDisplay();
  display.drawRect(0, 0, 128, 64, WHITE);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(15, 15);
  display.println("THANH CO BAN PHUOC");
  display.setCursor(20, 32);
  display.println("KHOI TAO HE THONG");
  display.setCursor(28, 48);
  display.println("SAN SANG TEST!");
  display.display();
  delay(2000);
}

void loop() {
  // 1. ĐỌC CẢM BIẾN MƯA (Module LM393: Khi có nước chân DO kéo xuống 0)
  int rainState = digitalRead(PIN_RAIN);
  bool isRaining = (rainState == LOW);

  // 2. ĐỌC CẢM BIẾN ÁNH SÁNG (Khi có ánh sáng chân DO kéo xuống 0)
  int lightState = digitalRead(PIN_LIGHT);
  bool isBright = (lightState == LOW);

  // 3. ĐỌC NHIỆT ĐỘ VÀ ĐỘ ẨM TỪ DHT11
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // 4. KÍCH HOẠT CÒI BÁO ĐỘNG KHI CÓ MƯA
  if (isRaining) {
    // Kêu tít tít cảnh báo mưa
    digitalWrite(PIN_BUZZER, HIGH);
  } else {
    digitalWrite(PIN_BUZZER, LOW);
  }

  // 5. HIỂN THỊ ĐẦY ĐỦ LÊN MÀN HÌNH OLED
  display.clearDisplay();

  // Khung viền
  display.drawRect(0, 0, 128, 64, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Dòng 1: Tiêu đề
  display.setCursor(8, 5);
  display.println("NHA THONG MINH STEM");
  display.drawLine(0, 15, 128, 15, WHITE);

  // Dòng 2: Nhiệt độ & Độ ẩm
  display.setCursor(6, 20);
  if (!isnan(temp) && !isnan(hum)) {
    display.print("N.Do:");
    display.print((int)temp);
    display.print("C  Am:");
    display.print((int)hum);
    display.println("%");
  } else {
    display.println("DHT11: Dang do...");
  }

  // Dòng 3: Trạng thái mưa
  display.setCursor(6, 34);
  display.print("Mua: ");
  if (isRaining) {
    display.println("CO MUA [CANH BAO]");
  } else {
    display.println("KHO RAO (Tot)");
  }

  // Dòng 4: Ánh sáng
  display.setCursor(6, 48);
  display.print("Troi: ");
  if (isBright) {
    display.println("SANG (Ngay)");
  } else {
    display.println("TOI (Dem)");
  }

  display.display();

  // 6. IN CHI TIẾT RA SERIAL MONITOR ĐỂ THEO DÕI
  Serial.println("-------------- THONG SO HE THONG --------------");
  Serial.print("1. Cam bien Mua (D18): ");
  Serial.println(isRaining ? "DANG CO MUA! (Coi reo)" : "Khong mua");

  Serial.print("2. Quang tro (D19): ");
  Serial.println(isBright ? "Troi Sang" : "Troi Toi");

  Serial.print("3. DHT11 (D4): ");
  if (!isnan(temp) && !isnan(hum)) {
    Serial.print("Nhiet do = ");
    Serial.print(temp);
    Serial.print(" *C | Do am = ");
    Serial.print(hum);
    Serial.println(" %");
  } else {
    Serial.println("Chua doc duoc (Kiem tra lai chan D4)");
  }
  Serial.println("-----------------------------------------------\n");

  delay(1000); // Lặp lại kiểm tra mỗi 1 giây
}
