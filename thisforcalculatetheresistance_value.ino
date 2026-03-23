int sensorPin = A0;
float Vin = 5.0;       // Measure your actual 5V pin and adjust!
float Rref = 100.0;    // Measure your actual reference resistor too

void setup() {
  Serial.begin(9600);
  analogReference(DEFAULT);
}

void loop() {
  long sum = 0;
  for(int i = 0; i < 20; i++) {
    sum += analogRead(sensorPin);
    delay(5);
  }

  float adcValue = sum / 20.0;
  float voltage = adcValue * (Vin / 1023.0);

 
  float resistance = Rref * voltage / (Vin - voltage);

  float temperature = (resistance - 100.0) / 0.385;

  Serial.print("Resistance: ");
  Serial.print(resistance);
  Serial.println(" Ω ");
 

  delay(1000);
}