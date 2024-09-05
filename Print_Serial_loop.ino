//εμφάνιση τιμών στην σειριακής οθόνης
void Print_Serial_loop() { 
  Serial.println(F("***************************************"));
  //Εμφάνιση Θερμοκρασίας στην σειριακή οθόνη
  Serial.print(F("Temperature: ")); 
  Serial.print(Val_temp); Serial.println(F("°C"));
  // Εμφάνιση υγρασίας στην σειριακή οθόνη
  Serial.print(F("Humidity: ")); 
  Serial.print(Val_humi); Serial.println(F("%"));
  
  Serial.print(F("LDR OUT Value: ")); 
  Serial.print(Val_OutLdr); Serial.println(F("%"));
  
  Serial.print(F("Distance(%): ")); 
  Serial.print(Val_distancePerCent);  Serial.println(F("%"));
  
  Serial.print(F("Distance(cm): ")); 
  Serial.print(Val_distance);  Serial.println(F("cm"));
  
  Serial.print(F("Soil moisture: ")); 
  Serial.print(Val_SoilHygro); Serial.println(F("%"));
  
  Serial.print(F("Ldr IN Value: ")); 
  Serial.print(Val_InLdr); Serial.println(F("%"));
  
  Serial.print(F("Gas Value: ")); 
  Serial.print(Val_Mq07Gas); Serial.println(F("%"));

  Serial.println("++++++++++++++++++++++++++++++++++++++");
  Serial.print(F("AirRecyclingFane: ")); Serial.println(digitalRead(MOS_AirRecyclingFan));
  Serial.print(F("CoolingFan: ")); Serial.println(digitalRead(MOS_CoolingFan));
  Serial.print(F("RgbLeds: ")); Serial.println(digitalRead(MOS_RgbLeds));
  
  Serial.print(F("Pump1: ")); Serial.println(digitalRead((RELAY_Pump1)));
  Serial.print(F("HeatingLight: ")); Serial.println(digitalRead((RELAY_HeatingLight)));
  Serial.print(F("ValveWater: ")); Serial.println(digitalRead((RELAY_ValveWater)));
  
  Serial.print(F("Pump2: ")); Serial.println(digitalRead(LED_Pump2));
  Serial.println("++++++++++++++++++++++++++++++++++++++");

  Serial.print("Date : ");
  Serial.print(t.date); Serial.print("/"); Serial.print(t.mon); 
  Serial.print("/"); Serial.print(t.year); Serial.print("   ");
  Serial.print("Hour : ");
  Serial.print(t.hour); Serial.print(":"); Serial.print(t.min); 
  Serial.print(":"); Serial.println(t.sec);
}     
