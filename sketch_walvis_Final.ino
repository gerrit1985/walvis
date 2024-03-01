#include <elapsedMillis.h>

#define PIR_PIN 2 // aansluit punt pir op digipin 2
#define LUCHT_PIN 3 // aansturing lucht op digipin 3
#define WATER_PIN 4 // aansturing water op digipin 4
#define INTERVAL_AUTOMATISCH 120000 // Interval spuit automatisch
#define MAXIMALE_PIR_INTERVAL 60000 // minimum tussentijd pir sensor
#define TIJD_SPUIT_AAN 3000 // was 2 seconden
#define VERTRAGING_NA_UITSCHAKELEN_WATER 1000  // vertraging uitschakelen lucht
#define VERTRAGING_NA_INSCHAKELEN_LUCHT 2000 //1 seconden was te kort tijd eerder inschakelen lucht

elapsedMillis timeElapsed; 
unsigned long lastPIRTrigger = 0; // telt hoe lang het geweest is na laatste pir trigger

void setup() { // instellingen pin`s 
  pinMode(PIR_PIN, INPUT);
  pinMode(LUCHT_PIN, OUTPUT);
  pinMode(WATER_PIN, OUTPUT);

  digitalWrite(LUCHT_PIN, HIGH); //lucht uit
  digitalWrite(WATER_PIN, HIGH); //water uit
}

void loop() {  // pir sensor
  if(digitalRead(PIR_PIN) == HIGH && millis() - lastPIRTrigger > MAXIMALE_PIR_INTERVAL) {
    ACTIVEER_PROGRAMMA();
    lastPIRTrigger = millis();
  }
  else if(timeElapsed > INTERVAL_AUTOMATISCH) { // tijds interval activatie
    ACTIVEER_PROGRAMMA();
    timeElapsed = 0;
  }
}

void ACTIVEER_PROGRAMMA() { //programma water
  digitalWrite(LUCHT_PIN, LOW); // zet lucht klep open
  delay(VERTRAGING_NA_INSCHAKELEN_LUCHT); // vertraging voor openen water klep
   digitalWrite(WATER_PIN, LOW); // openen waterklep
    delay(TIJD_SPUIT_AAN); // tijd dat de spuit aan staat
    digitalWrite(WATER_PIN, HIGH); // zet water uit
    delay(VERTRAGING_NA_UITSCHAKELEN_WATER); // extra tijd lucht aan
     digitalWrite(LUCHT_PIN, HIGH);  // zet lucht uit
 
}