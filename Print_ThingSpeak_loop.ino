void Print_ThingSpeak_loop(){
  // μετατροπή της μεταβλητής Float σε String
  String temp = String (Val_temp);
  String hum = String (Val_humi);      
  String SoilHygro = String (Val_SoilHygro);      
  String InLdr = String (Val_InLdr);  
  String OutLdr = String (Val_OutLdr);      
  String Mq07Gas = String (Val_Mq07Gas);  
  String distance = String (Val_distancePerCent);     
  
  // Print Update Response to Serial Monitor
  if (client.available()){
    char c = client.read();
    Serial.print(c);
  }
  
  // Disconnect from ThingSpeak
  if (!client.connected() && lastConnected){
    Serial.println("...disconnected");
    Serial.println();
    client.stop();
  }
  
  //Ενημέρωση τιμών
  //chart sensor
  if(!client.connected() && (millis() - lastConnectionTime>updateThingSpeakInterval)){ 
    updateThingSpeak("field1="+temp + "&field2="+hum + "&field3="+SoilHygro + "&field4="+InLdr + "&field5="+OutLdr+"&field6="+distance + "&field7="+ Mq07Gas); 
  }
  
  // Check if Arduino Ethernet needs to be restarted
  if (failedCounter > 3 ) {
    startEthernet();
  }
  
  lastConnected = client.connected();
}
