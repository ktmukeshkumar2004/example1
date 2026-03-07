#include <bluefruit.h>

#define RELAY_Forward 2
#define RELAY_Backword 3

BLEUart bleuart;

String command = "";

void setup() {

  pinMode(RELAY_Forward, OUTPUT);
  pinMode(RELAY_Backword, OUTPUT);

  digitalWrite(RELAY_Forward, LOW);
  digitalWrite(RELAY_Backword, LOW);

  Bluefruit.begin();
  Bluefruit.setName("m_k");

  bleuart.begin();

  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.Advertising.start(0);
}

void loop() {

  if (bleuart.available()) {

    delay(10);  // wait for full message

    command = "";

    while (bleuart.available()) {
      char c = bleuart.read();
      command += c;
    }

    command.trim();   // remove spaces / newline

    processCommand(command);
  }
}

void processCommand(String cmd) {

  if (cmd == "FORWARD") {

    digitalWrite(RELAY_Forward, HIGH);
    digitalWrite(RELAY_Backword, LOW);
    bleuart.println("Motor POSITIVE");

  }

  else if (cmd == "BACKWARD") {

    digitalWrite(RELAY_Forward, LOW);
    digitalWrite(RELAY_Backword, HIGH);
    bleuart.println("Motor NEGATIVE");

  }

  else if (cmd == "STOP") {

    digitalWrite(RELAY_Forward, LOW);
    digitalWrite(RELAY_Backword, LOW);
    bleuart.println("Motor Idle");

  }

  else {

    bleuart.println("Unknown Command");

  }
}