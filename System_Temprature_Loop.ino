// My_Val_Max_temp=30
// My_Val_Min_temp=26
// Control Temperature
void System_Temprature_Loop() { 
  //εάν η θερμοκρασία είναι πάνω από My_Val_Max_temp=30 τότε
  if (Val_temp > My_Val_Max_temp) {
    //ο ανεμιστήρας να δουλέψει στης μέγιστες στροφές και
    digitalWrite(MOS_CoolingFan, HIGH);
    //η λάμπα θερμοκρασίας να είναι σβηστή
    digitalWrite(RELAY_HeatingLight, HIGH);
    //εμφάνισε στην σειριακή οθόνη την κατάσταση
    Serial.println(F("Full rpm Cool Fan temp is over 30 and Heating=OFF"));
    }    
  //εάν η θερμοκρασία είναι πάνω από My_Val_Min_temp=26 τότε
  else if (Val_temp >= My_Val_Min_temp) {
    //ο ανεμιστήρας να δουλέψει στης μισές στροφές μέσω της PWM και 
    analogWrite(MOS_CoolingFan, 127); 
    digitalWrite(RELAY_HeatingLight, HIGH);// η λάμπα να είναι σβηστή
    // εμφάνισε στην σειριακή οθόνη την κατάσταση
    Serial.println(F("Medium rpm Cool Fan temp is under 30 and Heating=OFF"));
  
    // εάν η θερμοκρασία δεν είναι πάνω από 30 αλλά ούτε πάνω από 26 τότε  
    }else { 
      digitalWrite(MOS_CoolingFan, LOW);// ο ανεμιστήρας να είναι σβηστός και
      digitalWrite(RELAY_HeatingLight, LOW);//η λάμπα αναμμένη
      
      // εμφάνισε στην σειριακή οθόνη την κατάσταση
      Serial.println(F("Zero rpm Cool Fan temp is under 26 and Heating=ON"));
  }
}
