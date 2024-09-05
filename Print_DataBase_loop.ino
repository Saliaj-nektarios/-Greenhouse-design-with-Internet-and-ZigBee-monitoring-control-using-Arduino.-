void Print_DataBase_loop(){
  if (client.connect(serv, 80)) { //Connecting at the IP address and port we saved before
    Serial.println("connected");
    client.print("GET /db_allSensor/data.php?"); //Connecting and Sending values to database
    
    //send the value to data.php
    client.print("temperature="); client.print(Val_temp);
    client.print("&humidity="); client.print(Val_humi);
    client.print("&outLdr="); client.print(Val_OutLdr);
    client.print("&tank="); client.print(Val_distancePerCent);
    client.print("&soilhygro="); client.print(Val_SoilHygro);
    client.print("&inLdr="); client.print(Val_InLdr);
    client.print("&Mq07Gas="); client.print(Val_Mq07Gas);

    client.print("&AirRecyclingFan="); client.print(digitalRead(MOS_AirRecyclingFan));
    client.print("&CoolingFan="); client.print(digitalRead(MOS_CoolingFan));
    client.print("&RgbLeds="); client.print(digitalRead(MOS_RgbLeds));
    
    client.print("&Pump1="); client.print(digitalRead(RELAY_Pump1));
    client.print("&HeatingLight="); client.print(digitalRead(RELAY_HeatingLight));
    client.print("&ValveWater="); client.print(digitalRead(RELAY_ValveWater));
    client.print("&LED_Pump2="); client.print(digitalRead(setRem_LED_Blue_Blue_ForggerSpraySytem_DIO12));
    
    client.println(" HTTP/1.1"); // Part of the GET request
    client.println("Host: 192.168.1.50"); // IMPORTANT: If you are using XAMPP you will have to find out the IP address of your computer and put it here (it is explained in previous article). If you have a web page, enter its address (ie.Host: "www.yourwebpage.com")
    client.println("Connection: close"); // Part of the GET request telling the server that we are over transmitting the message
    client.println(); // Empty line
    client.println(); // Empty line
    client.stop();    // Closing connection to server
//    delay(900);
  }else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}
