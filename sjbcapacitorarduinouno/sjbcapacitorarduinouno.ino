#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int OUT_PIN = A2;
const int IN_PIN = A0;
const float IN_STRAY_CAP_TO_GND = 24.48;
const float IN_CAP_TO_GND = IN_STRAY_CAP_TO_GND;
const float R_PULLUP = 34.8;  
const int MAX_ADC_VALUE = 1023;

void setup(){
  pinMode(OUT_PIN, OUTPUT);
  pinMode(IN_PIN, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop(){
    pinMode(IN_PIN, INPUT);
    digitalWrite(OUT_PIN, HIGH);
    int val = analogRead(IN_PIN);
    digitalWrite(OUT_PIN, LOW);

    if (val < 1000){
      pinMode(IN_PIN, OUTPUT);

      float capacitance = (float)val * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val);

      lcd.setCursor(0,0);
      lcd.print(F("Capacitance = "));
      lcd.setCursor(0,1);
      lcd.print(capacitance, 3);
      lcd.print(F("pF "));
      lcd.print(val);
      lcd.print("mS");
      Serial.println(capacitance);  
        Serial.print("pF");        
    }
    
    else{
      pinMode(IN_PIN, OUTPUT);
      delay(1);
      pinMode(OUT_PIN, INPUT_PULLUP);
      unsigned long u1 = micros();
      unsigned long t;
      int digVal;

      do{
        digVal = digitalRead(OUT_PIN);
        unsigned long u2 = micros();
        t = u2 > u1 ? u2 - u1 : u1 - u2;
      } 
      
      while ((digVal < 1) && (t < 400000L));

      pinMode(OUT_PIN, INPUT);  
      val = analogRead(OUT_PIN);
      digitalWrite(IN_PIN, HIGH);
      int dischargeTime = (int)(t / 1000L) * 5;
      delay(dischargeTime);   
      pinMode(OUT_PIN, OUTPUT);  
      digitalWrite(OUT_PIN, LOW);
      digitalWrite(IN_PIN, LOW);

      float capacitance = -(float)t / R_PULLUP / log(1.0 - (float)val / (float)MAX_ADC_VALUE);

      lcd.setCursor(0,0);
      lcd.print(F("Capacitance = "));
      if (capacitance > 1000.0){
        lcd.setCursor(0,1);
        lcd.print(capacitance / 1000.0, 2);
        lcd.print(F("uF "));
        lcd.print(val);
        lcd.print("mS");
        Serial.println(capacitance/1000.0);  
        Serial.print("uF");                
      }
        
      else{
        lcd.setCursor(0,1);
        lcd.print(capacitance, 2);
        lcd.print(F("nF "));
        lcd.print(val);
        lcd.print("mS");
        Serial.println(capacitance);  
        Serial.print("nF");  
      }
  }
    while (millis() % 1000 != 0);
}