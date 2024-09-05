//control ForggerSpraySytem at the fire extinguishing system and humidity
void System_ForggerSpray_Loop() {
//Εαν η τιμή του αισθητηρα αεριου ή υγρασια ειναι μικροτερο απο 65% τοτε
  if (Val_Mq07Gas > My_Val_Max_Mq07Gas || Val_humi < My_Val_Min_humi) {//High Humidity ->ForggerSpray system OFF
//το value=0x5 ώστε το Blue led να είναι ON
  setRem_LED_Blue_Blue_ForggerSpraySytem_DIO12(0x5); // 0x5 -> on
    //Εμφάνιση της κατάστασης στην σειριακή οθόνη
  Serial.println(F("blueLed=on"));
  }else {
//το value=0x5 ώστε το Blue led να είναι OFF
    setRem_LED_Blue_Blue_ForggerSpraySytem_DIO12(0x4); //0x4 -> off
  //Εμφάνιση της κατάστασης στην σειριακή οθόνη
    Serial.println(F("blueLed=off"));
  }
}
