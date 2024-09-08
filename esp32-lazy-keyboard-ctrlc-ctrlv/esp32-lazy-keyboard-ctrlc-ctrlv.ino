#include <BleKeyboard.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

const int buttonPin = 23;
const int buttonPin1 = 19;

int buttonState = HIGH;
int lastButtonState = HIGH;

int buttonState1 = HIGH;
int lastButtonState1 = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long lastDebounceTime1 = 0;
const unsigned long debounceDelay = 10;

unsigned long buttonPressStartTime = 0;
unsigned long buttonPressStartTime1 = 0;
const unsigned long longPressDuration = 300;
const unsigned long doubleClickDelay = 300;

unsigned long lastButtonPressTime = 0;
unsigned long lastButtonPressTime1 = 0;
bool doubleClickDetected = false;
bool doubleClickDetected1 = false;

BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  // Initialize BLE
  BLEDevice::init("BLEKeyboard");
  
  // Create BLE Server and clear previous bondings
  BLEServer *pServer = BLEDevice::createServer();
  pServer->getAdvertising()->start(); // Start advertising

  // Wait for a moment before starting BLE Keyboard
  delay(1000);

  bleKeyboard.begin();

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Handle buttonPin
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = currentMillis;
    if (reading == LOW) {
      buttonPressStartTime = currentMillis;
    }
  }

  if ((currentMillis - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) { // Button released
        unsigned long pressDuration = currentMillis - buttonPressStartTime;
        if ((currentMillis - lastButtonPressTime) <= doubleClickDelay) {
          doubleClickDetected = true;
        } else {
          doubleClickDetected = false;
          if (pressDuration >= longPressDuration) {
            Serial.println("Sending Ctrl+A...");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.write('a');
            delay(10);
            bleKeyboard.releaseAll();
          } else {
            Serial.println("Sending Ctrl+C...");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.write('c');
            delay(10);
            bleKeyboard.releaseAll();
          }
        }
        lastButtonPressTime = currentMillis;
      }
    }
  }
  lastButtonState = reading;

  // Handle buttonPin1
  int reading1 = digitalRead(buttonPin1);
  if (reading1 != lastButtonState1) {
    lastDebounceTime1 = currentMillis;
    if (reading1 == LOW) {
      buttonPressStartTime1 = currentMillis;
    }
  }

  if ((currentMillis - lastDebounceTime1) > debounceDelay) {
    if (reading1 != buttonState1) {
      buttonState1 = reading1;
      if (buttonState1 == HIGH) { // Button released
        unsigned long pressDuration1 = currentMillis - buttonPressStartTime1;
        if ((currentMillis - lastButtonPressTime1) <= doubleClickDelay) {
          doubleClickDetected1 = true;
        } else {
          doubleClickDetected1 = false;
          if (pressDuration1 >= longPressDuration) {
            Serial.println("Sending Ctrl+Shift+Left Arrow...");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.press(KEY_LEFT_SHIFT);
            bleKeyboard.press(KEY_LEFT_ARROW);
            delay(10);
            bleKeyboard.releaseAll();
          } else {
            Serial.println("Sending Ctrl+V...");
            bleKeyboard.press(KEY_LEFT_CTRL);
            bleKeyboard.write('v');
            delay(10);
            bleKeyboard.releaseAll();
          }
        }
        lastButtonPressTime1 = currentMillis;
      }
    }
  }
  lastButtonState1 = reading1;

  // Check for simultaneous button presses for selection reset
  if (buttonState == LOW && buttonState1 == LOW) {
    Serial.println("Both buttons pressed - Resetting selection...");
    // Move cursor right and then back left to reset selection
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.write('x');
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_RIGHT_ARROW);
    bleKeyboard.releaseAll();
    delay(10); // Add delay to avoid multiple detections
    // Ensure that the buttons are not being counted again in this loop
    buttonState = HIGH;
    buttonState1 = HIGH;
  }
}
