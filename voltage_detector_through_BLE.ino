#include <bluefruit.h>

BLEUart bleuart;

const int analogPin = A0;
float voltage = 0.0;

void setup()
{
  Serial.begin(115200);

  // Wait for Serial Monitor (important for nRF52840)
  while ( !Serial ) delay(10);

  analogReadResolution(12);

  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("mk");

  bleuart.begin();

  // Advertising setup
  Bluefruit.Advertising.stop();
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.Advertising.addName();
  Bluefruit.ScanResponse.addName();

  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.start(0);

  Serial.println("BLE Voltage Monitor Started");
}

void loop()
{
  int raw = analogRead(analogPin);
  voltage = (raw / 4095.0) * 3.3;

  // Print to USB
  Serial.print("Voltage: ");
  Serial.println(voltage, 3);

  // Print to BLE only if connected
  if (Bluefruit.connected())
  {
    bleuart.print("mk: ");
    bleuart.println(voltage, 3);
  }

  delay(1000);
}
