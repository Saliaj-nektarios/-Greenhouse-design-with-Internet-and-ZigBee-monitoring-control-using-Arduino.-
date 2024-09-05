//-----------------------------------------------
// Control the water system
void System_Water_Loop(){ 
  // εάν το επίπεδο νερού είναι χαμηλότερη από 80 τότε  
  if (Val_distancePerCent < 80 ) {
// να ανάψει η αντλία 2 δηλαδή το LED για να γεμίσει το δοχείο με νερό 
    digitalWrite(LED_Pump2,HIGH );
    //Εμφάνιση της κατάστασης στην σειριακή οθόνη
    Serial.println("PUMP2(LED Blue)=ON - The water level is under 90%(Low Level)");
  }else{ // εάν το επίπεδο είναι υψηλότερο από 80 τότε 
    // η αντλία που εξομοιώνετε με το μπλε led θα ειναι σβηστη
    digitalWrite(LED_Pump2, LOW);
    //Εμφάνιση της κατάστασης στην σειριακή οθόνη
    Serial.println(F("PUMP2(LED Blue)=OFF - The tank is Full is over 90%"));
  }
// εάν το επίπεδο του νερού είναι υψηλότερο από 60 και η τιμή της 
//εξωτερική φωτεινότητας είναι υψηλότερη από 50 δηλαδή είναι μέρα τότε 
//έλεγξε εάν χεριάζετε νερό το φυτό 
if(Val_distancePerCent > My_Val_Min_distancePerCent && Val_OutLdr > My_Val_Min_OutLdr){
  Serial.println("The tank have water at tank, | The out light is over 50(Mera)");
  //εάν η τιμή του αισθητήρα soil hygrometer είναι μεγαλύτερη από min=30 τότε το 
  //φυτό χρειάζεται νερό και
    if (Val_SoilHygro < My_Val_Min_SoilHygro){ 
      digitalWrite(RELAY_Pump1, LOW); // η αντλία είναι on και 
      digitalWrite(RELAY_ValveWater, LOW); // η βάνα είναι on
      //Εμφάνιση της κατάστασης στην σειριακή οθόνη
      Serial.println("PUMP-1=ON | The plant wants water");
    }
    else{ // εάν είναι μικρότερη του 9 τότε το φυτό έχει νερό και 
      digitalWrite(RELAY_Pump1, HIGH);// η αντλία είναι off και 
      digitalWrite(RELAY_ValveWater, HIGH); // η βάνα είναι OFF
      //Εμφάνιση της κατάστασης στην σειριακή οθόνη
      Serial.println("PUMP-1=OFF | The plant has water");
    }
  // εάν το επίπεδο του νερού είναι χαμηλότερη από 60 και η τιμή της 
  //εξωτερική φωτεινότητας είναι χαμηλότερη από 50 δηλαδή είναι βραδύ τότε
  }else{ 
      digitalWrite(RELAY_Pump1, HIGH);// η αντλία είναι κλιστεί OFF και 
      digitalWrite(RELAY_ValveWater, HIGH); // η βάνα κλιστεί
    //Εμφάνιση της κατάστασης στην σειριακή οθόνη
      Serial.println("PUMP-1=OFF / Είναι νύχτα ή δεν υπάρχει νερό στο δοχείο. ");
  }
}
// My_Val_Max_SoilHygro=75 33
// My_Val_Min_SoilHygro=20 16
