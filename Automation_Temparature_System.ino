#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define I2C_ADDR 0x3F //I2C adress, you should use the code to scan the adress first (0x27) here
//#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3 // Declaring LCD Pins
#define En_pin 2
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
const int wait_time_for_IR_sensor = 100;
const int max_temparature = 37;

bool std_state = false;

LiquidCrystal_I2C lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


int Stage = 0;

void setup() {
  Serial.begin(9600);

  mlx.begin();
  lcd.begin (16, 2);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH); //Lighting backlight
  lcd.home ();

  pinMode(ir_pin, INPUT);
  Stage = 1;
}


void loop() {
  //  const int temparature = temp();
  //  const int len = len_to_hand();
  //  Serial.print("Temparature : ");
  //  Serial.println(temparature);
  //  Serial.print("Length      : ");
  //  Serial.println(len);
  //  Serial.println();
  //  delay(200);

  //    lcd.setCursor(0, 1);
  //    lcd.print("Target  ");
  //    lcd.print(mlx.readObjectTempC());
  //    lcd.print(" C");

  switch (Stage) {
    case 1:
      Serial.println("Stage 1");
      stage_1();
      break;
    case 2:
      Serial.println("Stage 2");
      stage_2();
      break;
    case 3:
      Serial.println("Stage 3");
      stage_3();
      break;
    default:
      break;
  }
}
