void startEthernet(){
  client.stop();
  Serial.println("Connecting Arduino to network...");
  Serial.println();  
  // Connect to network amd obtain an IP address using DHCP
  if (Ethernet.begin(mac) == 0){
    Serial.println("DHCP Failed, reset Arduino to try again");
    Serial.println();
  }else{
    Serial.println("Arduino connected to network using DHCP");
    Serial.println();
  }
}
