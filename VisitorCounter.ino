#include<LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);

#define in 7
#define out 4
#define relay 2

int count = 0;
bool lastInState = LOW;
bool lastOutState = LOW;

void updateDisplay() {
  lcd.clear();
  lcd.print("People In Room:");
  lcd.setCursor(0,1);
  lcd.print(count);
}

void IN() {
  count++;
  updateDisplay();
  delay(1000); // Debouncing delay
}

void OUT() {
  if (count > 0) {
    count--;
    updateDisplay();
    delay(1000); // Debouncing delay
  }
}

void setup() {
  lcd.begin(16,2);
  lcd.print("Visitor Counter");
  delay(2000);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  pinMode(relay, OUTPUT);
  lcd.clear();
  Serial.begin(9600);
  Serial.println("System Initialized"); 
}

void loop() {
  int inValue = digitalRead(in);
  int outValue = digitalRead(out);

  Serial.print("In Sensor: ");
  Serial.print(inValue);
  Serial.print(" | Out Sensor: ");
  Serial.println(outValue);

  if (inValue == HIGH && lastInState == LOW) {
    Serial.println("Person Entered");
    IN();
  }
  if (outValue == HIGH && lastOutState == LOW) {
    Serial.println("Person Exited");
    OUT();
  }

  lastInState = inValue;
  lastOutState = outValue;

  if (count <= 0) {
    digitalWrite(relay, LOW);
    lcd.clear();
    lcd.print("Nobody In Room");
    lcd.setCursor(0,1);
    lcd.print("Light Is Off");
  } else {
    digitalWrite(relay, HIGH);
  }
  
  delay(200); // General delay to avoid rapid state changes
}