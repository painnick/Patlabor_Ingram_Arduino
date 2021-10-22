/*
  제목   : 패트레이버 잉그램
  내용   : 경광등 효과
*/
#include "Siren.h"

#define BUZZER_PIN_NO 5

#define LED_HEAD_PIN_NO 7  // GREEN & BLUE. 200 ohm
#define LED_WAIST_PIN_NO 8 // YELLOW. 330 ohm

#define LED_SHOULDER1_PIN_NO 9  // RED? PNK? 1K ohm
#define LED_SHOULDER2_PIN_NO 10 // RED? PNK? 1K ohm
#define LED_SHOULDER3_PIN_NO 11 // YELLOW. 330 ohm

#define SHOULDER_INTERVAL 100  // soulder 1 & 2
#define SHOULDER3_INTERVAL 300 // soulder 3

#define INIT_MILLS 10000

bool soulder_led_on = true;
bool soulder3_led_on = true;

Siren siren(BUZZER_PIN_NO, false);

void setup()
{
  pinMode(BUZZER_PIN_NO, OUTPUT);

  pinMode(LED_HEAD_PIN_NO, OUTPUT);
  pinMode(LED_WAIST_PIN_NO, OUTPUT);

  pinMode(LED_SHOULDER1_PIN_NO, OUTPUT);
  pinMode(LED_SHOULDER2_PIN_NO, OUTPUT);
  pinMode(LED_SHOULDER3_PIN_NO, OUTPUT);

  digitalWrite(LED_HEAD_PIN_NO, HIGH);
  digitalWrite(LED_WAIST_PIN_NO, soulder3_led_on ? HIGH : LOW);

  digitalWrite(LED_SHOULDER1_PIN_NO, soulder_led_on ? HIGH : LOW);
  digitalWrite(LED_SHOULDER2_PIN_NO, soulder_led_on ? LOW : HIGH);
  digitalWrite(LED_SHOULDER3_PIN_NO, soulder3_led_on ? HIGH : LOW);
}

unsigned long soulder_lastMills = INIT_MILLS;
unsigned long soulder3_lastMills = INIT_MILLS;
void loop()
{
  unsigned long currentMills = millis();
  if (soulder_lastMills == INIT_MILLS || soulder_lastMills + SHOULDER_INTERVAL < currentMills)
  {
    soulder_led_on = !soulder_led_on;
    digitalWrite(LED_SHOULDER1_PIN_NO, soulder_led_on ? HIGH : LOW);
    digitalWrite(LED_SHOULDER2_PIN_NO, soulder_led_on ? LOW : HIGH);

    soulder_lastMills = currentMills;
  }
  if (soulder3_lastMills == INIT_MILLS || soulder3_lastMills + SHOULDER3_INTERVAL < currentMills)
  {
    soulder3_led_on = !soulder3_led_on;
    digitalWrite(LED_WAIST_PIN_NO, soulder3_led_on ? HIGH : LOW);
    digitalWrite(LED_SHOULDER3_PIN_NO, soulder3_led_on ? HIGH : LOW);

    soulder3_lastMills = currentMills;
  }

  siren.call(currentMills);
}
