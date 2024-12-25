#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define I2C address for OLED (umumnya 0x3C)
#define OLED_ADDRESS 0x3C

// Initialize the OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Analog input pin
int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; // resistance of R1 (100K)
float R2 = 10000.0;  // resistance of R2 (10K)
int value = 0;

void setup() {
  // Initialize serial monitor for debugging (optional)
  Serial.begin(9600);

  // Initialize OLED display
  if (!display.begin(SSD1306_I2C_ADDRESS, OLED_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Clear display buffer
  display.clearDisplay();
  display.display();

  // Set analog pin as input
  pinMode(analogInput, INPUT);
}

void loop() {
  // Read analog value
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0; // Convert to voltage
  vin = vout / (R2 / (R1 + R2)); // Calculate input voltage
  
  // Filter out noise
  if (vin < 0.09) {
    vin = 0.0;
  }

  // Clear display buffer
  display.clearDisplay();

  // Display "M21 Volt Meter" title
  display.setTextSize(1);             // Text size small
  display.setTextColor(SSD1306_WHITE); // Text color
  display.setCursor(25, 0);           // Position
  display.println("M21 Volt Meter");

  // Display "VOLTAGE" label
  display.setTextSize(1);
  display.setCursor(40, 20);
  display.println("VOLTAGE");

  // Display voltage value in larger font
  display.setTextSize(2);             // Larger text size
  display.setCursor(30, 40);
  display.print(vin, 2);              // Print voltage with 2 decimal places
  display.print(" V");

  // Render the buffer to the screen
  display.display();

  // Delay before updating
  delay(500);
}
