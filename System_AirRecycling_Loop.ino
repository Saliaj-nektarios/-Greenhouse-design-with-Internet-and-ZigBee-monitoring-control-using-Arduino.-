//controll the Humidity Sytem  
void System_AirRecycling_Loop() {
//εαν η τιμη της υγρασιας ειναι πανω απο 90% ή   //η ποιοτιτα του αερα είναι πανω απο 70% τοτε

  if (Val_humi >= My_Val_Max_humi ||   Val_Mq07Gas > My_Val_Max_Mq07Gas ) {
//Ο δευτερος ανεμηστιρας που ειναι για των εξαερισμο δουλευει στης μεγηστες στροφες
  digitalWrite(MOS_AirRecyclingFan, HIGH);
//Εμφάνιση της κατάστασης στην σειριακή οθόνη
    Serial.println(F("Air Recycle Fan=Full"));
//εαν η υγρασια είναι πανω απο 65% τοτε
  }else if (Val_humi >= My_Val_Min_humi) {
// ο ανεμηστηρας θα δουλευει στης μισες στροφες
    analogWrite(MOS_AirRecyclingFan, 127); //PWM
//Εμφάνιση της κατάστασης στην σειριακή οθόνη
    Serial.println(F("Air Recycle=Medium"));
//αλλιως εαν ειναι χαμιλοτερα απο 65% τοτε
  }else {
// Ο ανεμηστηρας του εξαερισμου ειναι σβηστος
    digitalWrite(MOS_AirRecyclingFan, LOW);
//Εμφάνιση της κατάστασης στην σειριακή οθόνη
    Serial.println(F("Air Recycle=Stop"));
  }    
}
