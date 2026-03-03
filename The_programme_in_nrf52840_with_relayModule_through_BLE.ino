#include <bluefruit.h>

#define RELAY_PIN 2

BLEUart bleuart;

void setup() {

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);   // Assume OFF

  delay(100);  // Small delay stabilize

  Bluefruit.begin();
  Bluefruit.setName("Motor_Control");

  bleuart.begin();

  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.Advertising.start(0);
}

void loop() {

  if (bleuart.available()) {

    char c = bleuart.read();

    if (c == '1') {
      digitalWrite(RELAY_PIN, HIGH);
      bleuart.println("Motor ON");

      
    }

    else if (c == '0') {
      digitalWrite(RELAY_PIN, LOW);
      bleuart.println("Motor OFF");

    }
  }
}