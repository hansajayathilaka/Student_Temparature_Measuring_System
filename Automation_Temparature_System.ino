#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define I2C_ADDR 0x3F //I2C adress, you should use the code to scan the adress first (0x27) here
//#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3 // Declaring LCD Pins
#define En_pin 8
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

#define low_temp_led_pin 10
#define high_temp_led_pin 10

#define low_temp_door_pin 2
#define high_temp_door_pin 3

#define ir_pin A7

const int proximity_max_distance = 170;
const int wait_time_for_IR_sensor = 500;
const int max_temparature = 37;

char std_state = 'N'; // G, B, N

LiquidCrystal_I2C lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void high_temp_door_interupt();
void low_temp_door_interupt();

int Stage = 0;


void setup() {
  Serial.begin(9600);

  mlx.begin();
  lcd.begin (20, 4);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH); //Lighting backlight
  lcd.home ();

  pinMode(ir_pin, INPUT);

  attachInterrupt(digitalPinToInterrupt(low_temp_door_pin), low_temp_door_interupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(high_temp_door_pin), high_temp_door_interupt, FALLING);

}

void loop() {

  const int pre_time = millis();
  while (len_to_hand() > proximity_max_distance) {
    if (millis() - pre_time > wait_time_for_IR_sensor) {





      float temparature = 0;
      const int count = 10;
      for (int i = 0; i < count; i++) {
        temparature += temp();
      }
      temparature /= count;

      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Your Temparature");
      lcd.setCursor(6, 1);
      lcd.print(temparature);
      lcd.print(" C");
      lcd.setCursor(3, 2);
      lcd.print("Thank You");
      lcd.setCursor(6, 3);
      lcd.print("Stay Safe");
      Serial.println(temparature);

      if (temparature < max_temparature) {
        std_state = 'G';
        low_temp_door_signal_on();
      } else  {
        std_state = 'B';
        high_temp_door_signal_on();
      }





    }
  }

}
