float temp() {
  //  Serial.print("Ambient ");
  //  Serial.println(mlx.readAmbientTempC());
  //  Serial.print("Target  ");
  //  Serial.println(mlx.readObjectTempC());
  //  Serial.println();
  const int x = 1, y = 0;
  const float val = mlx.readObjectTempC() * x + y;
  return val;
}

int len_to_hand() {
  const int val = analogRead(ir_pin);
  //  Serial.println(val);
  return val;
}

void low_temp_door_signal_on() {
  digitalWrite(low_temp_led_pin, HIGH);
  digitalWrite(high_temp_led_pin, LOW);
}

void high_temp_door_signal_on() {
  digitalWrite(low_temp_led_pin, LOW);
  digitalWrite(high_temp_led_pin, HIGH);
}

void door_signal_initialization() {
  digitalWrite(low_temp_led_pin, LOW);
  digitalWrite(high_temp_led_pin, LOW);
}

void wrong_door_alarm() {
}

void low_temp_door_interupt() {
  Serial.println("Low temparature intrupted fired");
  Serial.println(std_state);
  switch (std_state) {
    case 'N':
      door_signal_initialization();
      break;
    case 'G':
      std_state = 'N';
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Wellcome");
      break;
    case 'B':
      wrong_door_alarm();
      break;
  }
}

void high_temp_door_interupt() {
  Serial.println("High temparature intrupted fired");
  Serial.println(std_state);
  switch (std_state) {
    case 'N':
      door_signal_initialization();
      break;
    case 'G':
      wrong_door_alarm();
      break;
    case 'B':
      std_state = 'N';
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Wellcome");
      break;
  }
}
