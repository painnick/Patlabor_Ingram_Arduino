/*
  제목   : 패트레이버 잉그램
  내용   : 경광등 효과
*/
#include "Siren.h"

#define BUZZER_PIN_NO 5

#define LED_PATROL_CAR_SIREN_PIN_NO 6
#define LED_PATROL_CAR_LIGHT_PIN_NO 12

#define LED_HEAD_PIN_NO 7  // GREEN & BLUE. 330 ohm - RED line
#define LED_WAIST_PIN_NO 8 // YELLOW. 330 ohm - YELLOW line

#define LED_SHOULDER1_PIN_NO 9  // RED? PNK? 1K ohm - BLUE line
#define LED_SHOULDER2_PIN_NO 10 // RED? PNK? 1K ohm - GREEN line
#define LED_SHOULDER3_PIN_NO 11 // YELLOW. 1K ohm - BLACK line

#define PATROL_CAR_SIREN_INTERVAL 100  // patrol car siren
#define SHOULDER_INTERVAL 100  // soulder 1 & 2
#define SHOULDER3_INTERVAL 300 // soulder 3

#define INIT_MILLS 10000

bool patrol_car_siren_led_on = true;
bool soulder_led_on = true;
bool soulder3_and_waist_led_on = true;

Siren siren(BUZZER_PIN_NO, true);

void setup()
{
  pinMode(BUZZER_PIN_NO, OUTPUT);

  // Patrol Car
  pinMode(LED_PATROL_CAR_SIREN_PIN_NO, OUTPUT);
  digitalWrite(LED_PATROL_CAR_SIREN_PIN_NO, patrol_car_siren_led_on ? HIGH : LOW);

  pinMode(LED_PATROL_CAR_LIGHT_PIN_NO, OUTPUT);
  digitalWrite(LED_PATROL_CAR_LIGHT_PIN_NO, HIGH);

  // Ingram
  pinMode(LED_HEAD_PIN_NO, OUTPUT);
  digitalWrite(LED_HEAD_PIN_NO, HIGH);

  pinMode(LED_SHOULDER1_PIN_NO, OUTPUT);
  pinMode(LED_SHOULDER2_PIN_NO, OUTPUT);
  digitalWrite(LED_SHOULDER1_PIN_NO, soulder_led_on ? HIGH : LOW);
  digitalWrite(LED_SHOULDER2_PIN_NO, soulder_led_on ? LOW : HIGH);

  pinMode(LED_SHOULDER3_PIN_NO, OUTPUT);
  digitalWrite(LED_SHOULDER3_PIN_NO, soulder3_and_waist_led_on ? HIGH : LOW);
  pinMode(LED_WAIST_PIN_NO, OUTPUT);
  digitalWrite(LED_WAIST_PIN_NO, soulder3_and_waist_led_on ? HIGH : LOW);
}

unsigned long patrol_car_siren_lastMills = INIT_MILLS;
unsigned long soulder_lastMills = INIT_MILLS;
unsigned long soulder3_and_waist_lastMills = INIT_MILLS;
void loop()
{
  unsigned long currentMills = millis();

  // Patrol Car
  if (patrol_car_siren_lastMills == INIT_MILLS || patrol_car_siren_lastMills + PATROL_CAR_SIREN_INTERVAL < currentMills)
  {
    patrol_car_siren_led_on = !patrol_car_siren_led_on;
    digitalWrite(LED_PATROL_CAR_SIREN_PIN_NO, patrol_car_siren_led_on ? HIGH : LOW);

    patrol_car_siren_lastMills = currentMills;
  }

  // Ingram
  if (soulder_lastMills == INIT_MILLS || soulder_lastMills + SHOULDER_INTERVAL < currentMills)
  {
    soulder_led_on = !soulder_led_on;
    digitalWrite(LED_SHOULDER1_PIN_NO, soulder_led_on ? HIGH : LOW);
    digitalWrite(LED_SHOULDER2_PIN_NO, soulder_led_on ? LOW : HIGH);

    soulder_lastMills = currentMills;
  }

  if (soulder3_and_waist_lastMills == INIT_MILLS || soulder3_and_waist_lastMills + SHOULDER3_INTERVAL < currentMills)
  {
    soulder3_and_waist_led_on = !soulder3_and_waist_led_on;
    digitalWrite(LED_WAIST_PIN_NO, soulder3_and_waist_led_on ? HIGH : LOW);
    digitalWrite(LED_SHOULDER3_PIN_NO, soulder3_and_waist_led_on ? HIGH : LOW);

    soulder3_and_waist_lastMills = currentMills;
  }

  siren.call(currentMills);
}
