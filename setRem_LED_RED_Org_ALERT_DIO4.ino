//===================================================================
// create the frame to send to router
// πλαίσιο για των ελέγχου του κόκκινου LED και του buzzer που 
//εξομοιώνει το σύστημα ειδοποίησης
void setRem_LED_RED_Org_ALERT_DIO4(char value) {
  Serial.write(0x7E); //0
  Serial.write(byte(0x0)); //1
  Serial.write(0x10); //2
  Serial.write(0x17); // 3
  Serial.write(byte(0x0)); //4 
 
  Serial.write(byte(0x0)); //5
  Serial.write(byte(0x0)); //6
  Serial.write(byte(0x0)); //7 
  Serial.write(byte(0x0)); //8
  Serial.write(byte(0x0)); //9
  Serial.write(byte(0x0)); //10
  Serial.write(0xFF); //12
  Serial.write(0xFF); // 13
  
  Serial.write(0xFF); //14
  Serial.write(0xFE); //15

  Serial.write(0x02); //16
  Serial.write('D'); //17
  Serial.write('4'); //18
  Serial.write(value); // 19
  long sum = 0x17 + 0xFF + 0xFF + 0xFF + 0xFE + 0x02 + 'D' + '4' + value;
  Serial.write(0xFF - (sum & 0xFF));
}
