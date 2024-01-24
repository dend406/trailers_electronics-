#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Підключення DHT11 до піна 7
#define DHT_PIN 7

// Адреса I2C для LCD екрана
#define I2C_ADDR 0x27

// Розмір екрана (16 стовпців і 2 рядки)
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Пін для підключення реле
#define RELAY_PIN 6

DHT dht(DHT_PIN, DHT11);
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

void setup() {
  lcd.begin(LCD_COLUMNS, LCD_ROWS);  // Ініціалізація LCD
  lcd.backlight();  // Включення підсвічування
  dht.begin();  // Ініціалізація DHT датчика

  pinMode(RELAY_PIN, OUTPUT);  // Налаштування піна для реле як вихідний
}

void loop() {
  // Отримання значень вологості та температури
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  

  // Виведення результатів на LCD екран
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humid:");
  lcd.print(humidity);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temperature);
  lcd.print("C");

  // Керування реле в залежності від вологості
  if (humidity > 50.0) {
    digitalWrite(RELAY_PIN, HIGH);  // Вмикання реле
    lcd.setCursor(13, 1);
    lcd.print("ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Вимикання реле
    lcd.setCursor(13, 1);
    lcd.print("OFF");
  }

  delay(2000);  // Затримка для читання результатів (може бути адаптована)
}
