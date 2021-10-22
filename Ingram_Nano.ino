/*
  제목   : 패트레이버 잉그램
  내용   : 경광등 효과
*/

#define BUZZER 5

#define LED_HEAD 7  // GREEN & BLUE. 200 ohm
#define LED_WAIST 8 // YELLOW. 330 ohm

#define LED_SHOULDER1 9  // RED? PNK? 1K ohm
#define LED_SHOULDER2 10 // RED? PNK? 1K ohm
#define LED_SHOULDER3 11 // YELLOW. 330 ohm

#define BUZZER_INTERVAL 50

#define SHOULDER_INTERVAL 100  // soulder 1 & 2
#define SHOULDER3_INTERVAL 300 // soulder 3

bool buzzer_on = true;
bool soulder_on = true;
bool soulder3_on = true;

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

unsigned long buzzer_lastMills = 0;
unsigned long soulder_lastMills = 0;
unsigned long soulder3_lastMills = 0;
void loop()
{
  unsigned long currentMills = millis();
  if (buzzer_lastMills == 0 || buzzer_lastMills + BUZZER_INTERVAL < currentMills)
  {
    soulder_on = !soulder_on;
    digitalWrite(BUZZER, soulder_on ? HIGH : LOW);

    buzzer_lastMills = currentMills;
  }
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
  // delay(2);

  police_siren();
}

#define FREQ_MIN 634
#define FREQ_MAX 912
#define SIREN_SPEED_MODE true

int freq, tone_delay = 0;
void police_siren()
{
  for (freq = FREQ_MIN + 1; freq <= FREQ_MAX; freq++)
  {
    tone(BUZZER, freq);
    delay(tone_delay);

    if (SIREN_SPEED_MODE)
      tone_delay = 1;
    else
      tone_delay = 7;
  }

  for (freq = FREQ_MAX - 1; freq >= FREQ_MIN; freq--)
  {
    tone(BUZZER, freq);
    delay(tone_delay);

    if (SIREN_SPEED_MODE)
      tone_delay = 1;
    else
      tone_delay = 10;
  }
}