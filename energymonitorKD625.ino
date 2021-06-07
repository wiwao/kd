#include<LiquidCrystal.h>
#include<stdio.h>
LiquidCrystal lcd(3,4,5,6,7,8);
const int chan1_pin = 2;
//My meter flashes 50000 times per kWh
const float w_per_pulse = 12;
const unsigned long ms_per_hour = 3600000UL;
unsigned int chan1_count = 0;
unsigned long report_time = 0;
unsigned long chan1_first_pulse = 0;
unsigned long chan1_last_pulse = 0;
volatile byte chan1_pulse = 0;

void chan1_isr() {
chan1_pulse = 1;
}

void setup() {
pinMode(chan1_pin, INPUT);
attachInterrupt(0, chan1_isr, RISING);
Serial.begin(9600);
lcd.begin(16,2);
delay(1000);
}
void loop() {
static unsigned int chan1_watts=0;
unsigned long chan1_delta; // Time since last pulse
Serial.print("Chan1 ");
Serial.println(chan1_watts);
lcd.clear();
lcd.print("Chan1 ");
lcd.print(chan1_watts);
lcd.print("Wh");
lcd.setCursor(0,1);
lcd.print("chan1_count ");
lcd.print(chan1_count);
if (chan1_pulse == 1) {
  chan1_count++;
chan1_pulse = 0;
}
chan1_watts = chan1_count * w_per_pulse;
delay(50);
}
