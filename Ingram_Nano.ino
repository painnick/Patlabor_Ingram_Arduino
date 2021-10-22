/*
  제목   : 패트레이버 잉그램
  내용   : 경광등 효과
*/
#include "Siren.h"

#define BUZZER 5

#define LED_HEAD 7  // GREEN & BLUE. 200 ohm
#define LED_WAIST 8 // YELLOW. 330 ohm

#define LED_SHOULDER1 9  // RED? PNK? 1K ohm
#define LED_SHOULDER2 10 // RED? PNK? 1K ohm
#define LED_SHOULDER3 11 // YELLOW. 330 ohm

#define SHOULDER_INTERVAL 100  // soulder 1 & 2
#define SHOULDER3_INTERVAL 300 // soulder 3

bool soulder_on = true;
bool soulder3_on = true;

Siren siren(BUZZER);

void setup()
{
  pinMode(BUZZER, OUTPUT);

  pinMode(LED_HEAD, OUTPUT);
  pinMode(LED_WAIST, OUTPUT);

  pinMode(LED_SHOULDER1, OUTPUT);
  pinMode(LED_SHOULDER2, OUTPUT);
  pinMode(LED_SHOULDER3, OUTPUT);

  digitalWrite(LED_HEAD, HIGH);
  digitalWrite(LED_WAIST, soulder3_on ? HIGH : LOW);

  digitalWrite(LED_SHOULDER1, soulder_on ? HIGH : LOW);
  digitalWrite(LED_SHOULDER2, soulder_on ? LOW : HIGH);
  digitalWrite(LED_SHOULDER3, soulder3_on ? HIGH : LOW);
}

unsigned long soulder_lastMills = 0;
unsigned long soulder3_lastMills = 0;
void loop()
{
  unsigned long currentMills = millis();
  if (soulder_lastMills == 0 || soulder_lastMills + SHOULDER_INTERVAL < currentMills)
  {
    soulder_on = !soulder_on;
    digitalWrite(LED_SHOULDER1, soulder_on ? HIGH : LOW);
    digitalWrite(LED_SHOULDER2, soulder_on ? LOW : HIGH);

    soulder_lastMills = currentMills;
  }
  if (soulder3_lastMills == 0 || soulder3_lastMills + SHOULDER3_INTERVAL < currentMills)
  {
    soulder3_on = !soulder3_on;
    digitalWrite(LED_WAIST, soulder3_on ? HIGH : LOW);
    digitalWrite(LED_SHOULDER3, soulder3_on ? HIGH : LOW);

    soulder3_lastMills = currentMills;
  }

  siren.call(currentMills);
  // delay(1);
}
