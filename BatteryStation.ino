unsigned int total;
const int battNumber = 8;
float voltage [battNumber];
const int relaySwitchBase = 2;
const int fullyChargedBase = 12;
const int chargingBase = 22;
const int readCharge = 32;
int c;

void setup() {
  analogReference (INTERNAL1V1);
  Serial.begin(9600);

  for (c = 0; c < battNumber; c++) {
    pinMode(relaySwitchBase + c, OUTPUT);
    pinMode(fullyChargedBase + c, OUTPUT);
    pinMode(chargingBase + c, OUTPUT);
  }
}

void loop() {
  for (c = 0; c < battNumber; c++) {
    digitalWrite(relaySwitchBase + c, HIGH); //turns relay off
    digitalWrite(fullyChargedBase + c, LOW);
    digitalWrite(chargingBase + c, LOW);
  }
  digitalWrite(readCharge, HIGH);
  for (c = 0; c < battNumber; c++) {
    total = 0;
    analogRead(A0 + c);
    for (int x = 0; x < 64; x++) {
        total = total + analogRead(A0 + c);
    }
    voltage [c] = total * 0.0002667;

    if (voltage [c] < 17 && voltage [c] > 1) {
      Serial.print(c);
      Serial.print(" ");
      Serial.print("battery is ");
      Serial.print(voltage [c]);
      Serial.println(" volts");
      Serial.println("");
    }
    else {
      Serial.print(c);
      Serial.print(" ");
      Serial.println("battery is not connected");
      Serial.println("");
    }
  }
  delay(1000);
  digitalWrite(readCharge, LOW);

  for (c = 0; c < battNumber; c++) {
    if (voltage[c] >= 17 || voltage [c] <= 1) {
      digitalWrite(relaySwitchBase + c, HIGH); //relay off
      digitalWrite(fullyChargedBase + c, LOW);
      digitalWrite(chargingBase + c, LOW);     
    }
    else if (voltage [c] >= 13) { 
      digitalWrite(relaySwitchBase + c, HIGH); //relay off
      digitalWrite(fullyChargedBase + c, HIGH);
    }
    else {
      digitalWrite(relaySwitchBase + c, LOW); //relay on
      digitalWrite(chargingBase + c, HIGH);     
    }
  }
  delay(100000);
}
