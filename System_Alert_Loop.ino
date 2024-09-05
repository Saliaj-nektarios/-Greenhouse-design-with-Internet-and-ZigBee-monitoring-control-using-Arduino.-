//controll the Alert Sytem ->Buzzer Red led
void System_Alert_Loop() {
//εαν η τιμη του αισθητιρα αεριου ειναι πανω απο 70 ή
//η το επιπεδο του νερο ξεπερασει το 90% τοτε
  if ((Val_Mq07Gas >= My_Val_Max_Mq07Gas) || (Val_distancePerCent > My_Val_Max_distancePerCent)){
//κανε το value=0x5 ώστε το Red Led και Buzzer να είναι ON
    setRem_LED_RED_Org_ALERT_DIO4(0x5); 
//Εμφάνιση της κατάστασης στην σειριακή οθόνη
    Serial.println(F("Alert=On"));
  }
  else{
//το value=0x4 ώστε το Red Led και Buzzer να είναι Off
    setRem_LED_RED_Org_ALERT_DIO4(0x4); 
  //Εμφάνιση της κατάστασης στην σειριακή οθόνη
    Serial.println(F("Alert=Off"));
  }
}
