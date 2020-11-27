float temp() {
  //  Serial.print("Ambient ");
  //  Serial.println(mlx.readAmbientTempC());
  //  Serial.print("Target  ");
  //  Serial.println(mlx.readObjectTempC());
  //  Serial.println();
  const int x = 27, y = 35
                        , z = 0;
  const float val = mlx.readObjectTempC() / x * y + z;
  return val;
}

int len_to_hand() {
  const int val = analogRead(ir_pin);
  //  Serial.println(val);
  return val;
}

void check_for_hand_distance() {
  const int pre_time = millis();
  while (len_to_hand() > proximity_max_distance) {
    if (millis() - pre_time > wait_time_for_IR_sensor) {
      Stage++;
      return;
    }
  }
}

void low_temp_door_signal_on() {
  digitalWrite(low_temp_led_pin, HIGH);
  digitalWrite(high_temp_led_pin, LOW);
}

void high_temp_door_signal_on() {
  digitalWrite(low_temp_led_pin, LOW);
  digitalWrite(high_temp_led_pin, HIGH);
}

void wrong_door_alarm() {
}

void low_temp_door_interupt() {
  Serial.println("Low temparature intrupted fired");
  Serial.println(Stage);
  Serial.println(std_state);

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Low Door");

  if (Stage == 4) {
    if (std_state == true) {
      Stage = 1;
      lcd.clear();
    } else {
      wrong_door_alarm();
    }
  }
}

void high_temp_door_interupt() {
  Serial.println("High temparature intrupted fired");
  Serial.println(Stage);
  Serial.println(std_state);

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("High Door");

  if (Stage == 4) {
    if (std_state == true) {
      wrong_door_alarm();
    } else {
      Stage = 1;
      lcd.clear();
    }
  }
}


void stage_1() {
  digitalWrite(low_temp_led_pin, LOW);
  digitalWrite(high_temp_led_pin, LOW);

  lcd.setCursor(6, 0);
  lcd.print("Wellcome");
  //  lcd.setCursor(1, 1);
  //  lcd.print("Pull your hand near to the temparature sensor");

  check_for_hand_distance();
}


void stage_2() {
  float temparature = 0;
  const int count = 50;
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

  std_state = temparature < max_temparature;

  if (std_state) {
    low_temp_door_signal_on();
  } else  {
    high_temp_door_signal_on();
  }
  Stage++;
  delay(3000);
  lcd.clear();
}


void stage_3() {
  attachInterrupt(digitalPinToInterrupt(low_temp_door_pin), low_temp_door_interupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(high_temp_door_pin), high_temp_door_interupt, FALLING);
  lcd.setCursor(4, 0);
  lcd.print("Thank You");
  lcd.setCursor(5, 1);
  lcd.print("Stay safe");
  Stage++;
}
