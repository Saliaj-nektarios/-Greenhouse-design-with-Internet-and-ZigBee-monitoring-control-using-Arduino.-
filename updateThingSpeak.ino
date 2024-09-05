void updateThingSpeak(String tsData){
  if (client.connect(thingSpeakAddress, 80)){ 
    //Χρήση Http post για την ενημέρωση των δεδομένων
    //Το Start line αποτελείται από 
    //(method post/the protocol/έκδοση) αντίστοιχα
    client.print("POST /update HTTP/1.1\n");
    
    //Τα header για αναγνωρίσει μηνύματος post Request από το ThingSpeak
    //thingspeak Host
    client.print("Host: api.thingspeak.com\n");
    //Header Connection: το οποίο θα κλίσει την σύνδεση όταν στείλουμε κα λάβουμε το αίτημα μας
    client.print("Connection: close\n");
    //Header X-THINGSPEAKAPIKEY που είναι το ApiKey
    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    //Connection type: το οποίο υποδεικνύει το είδος αποστολής 
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    //conection length
    client.print("Content-Length: ");
    
    
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);
    lastConnectionTime = millis();
    if (client.connected()){
      Serial.println("Connecting to ThingSpeak...");
      Serial.println();
      failedCounter = 0;
    }else{
      failedCounter++;
      Serial.println("Connection to ThingSpeak failed ("+String(failedCounter, DEC)+")");   
      Serial.println();
    }   
  }else{
    failedCounter++;
    Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");   
    Serial.println();
    lastConnectionTime = millis(); 
  }
}
