//CONTROL THE SUNLIGHT 
void System_SunsHade_Loop() {
//εάν η τιμή του LDR είναι μεγαλύτερη από 90% τότε
  if (Val_OutLdr > My_Val_Max_OutLdr) { 
//Κάνε το value=0x5 ώστε το yellow led να είναι ON
    setRem_LED_Yellow_MOV_Sunshade_DIO11(0x5); 
//Εμφάνιση της κατάστασης στην σειριακή οθόνη
    Serial.println(F("Yellow Led=ON"));
  }else { // αλλιώς θα είναι κάτω από 90% και τότε
//Κάνε το value=0x4 ώστε το yellow led να είναι Off
    setRem_LED_Yellow_MOV_Sunshade_DIO11(0x4);
//Εμφάνιση της κατάστασης στην σειριακή οθόνη
    Serial.println(F("Yellow Led=OFF"));
  }
}
