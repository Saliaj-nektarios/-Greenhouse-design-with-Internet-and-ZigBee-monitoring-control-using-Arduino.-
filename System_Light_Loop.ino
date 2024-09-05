//control the inside Light System
void System_Light_Loop(){ 
//εάν η τιμή του εσωτερικου LDR ειναι μικροτερη απο 40 και
//η τιμη εξωτερικου ειναι μικροτερη απο 90 και
// η ωρα ειναι πανω απο 6 και
// τα λεπτα ειναι πανω απο 0 και
// η ωρα ειναι κατω απο 22 και
// τα λεπτα ειναι κατω απο 0 τοτε
  if ((Val_InLdr<=My_Val_InLdr || Val_OutLdr < My_Val_Max_OutLdr) && t.hour >= My_Val_OnHour  && t.min >= My_Val_OnMin &&  t.hour <= My_Val_OffHour && t.min <= My_Val_OffMin) {
  // οι λεντ ταινιες ειναι ON
    digitalWrite(MOS_RgbLeds, HIGH); 
  //εμανιση καταστασης στην σειριακη οθονη
    Serial.println(("RGB=ON"));
  }else { //εαν δεν υσχει κατι απο αυτα τοτε
    // οι λεντ ταινιες ειναι OFF
    digitalWrite(MOS_RgbLeds, LOW);
  //εμανιση καταστασης στην σειριακη οθονη  
    Serial.println(F("RGB=OFF"));
  }
}
