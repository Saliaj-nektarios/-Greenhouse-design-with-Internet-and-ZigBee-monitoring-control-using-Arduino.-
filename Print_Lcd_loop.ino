// Displays the value on the Serial Monitor
void Print_Lcd_loop() {
  // start to print at the first row
  lcd.setCursor(0, 0); lcd.write(1); lcd.print(Val_temp); lcd.print((char)223); lcd.print("C ");
  lcd.setCursor(9, 0); lcd.write(2); lcd.print(Val_humi); lcd.print("%");
  lcd.setCursor(1, 1); lcd.print("Hour:"); lcd.print(t.hour); lcd.print(":"); lcd.print(t.min); lcd.print(":"); lcd.println(t.sec);
}
