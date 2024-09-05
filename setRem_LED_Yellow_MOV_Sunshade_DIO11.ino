//πλαίσιο για των ελέγχου του κίτρινου LED που εξομοιώνει το σύστημα 
//σκίασης
void setRem_LED_Yellow_MOV_Sunshade_DIO11(char value) {
  Serial.write(0x7E); //start byte
  Serial.write(byte(0x0)); // high part of length (always zero)
//low part of length (the number of bytes that follow, not including 
//check
  Serial.write(0x10);
  Serial.write(0x17); //0x17 is a remote AT command
  Serial.write(byte(0x0));//frame id set to zero for no reply
  //Id of recipient, or use 0xFFF for broadcast 
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(0xFF); // 0xFF for broadcast
  Serial.write(0xFF);// 0xFF for broadcast

  //16 bit of recipient or 0xFFFE
  Serial.write(0xFF);
  Serial.write(0xFE);

  Serial.write(0x02); // 0x02 to apply changes immediately on remote
  
  //ΑΤ command name in ASCII character
  Serial.write('P'); 
  Serial.write('1'); 

  // command data in as many bytes as needed
  Serial.write(value);

  //checksum is all bytes after length bytes
long sum = 0x17 + 0xFF + 0xFF + 0xFF + 0xFE + 0x02 + 'P' + '1' + value;
  Serial.write(0xFF - (sum & 0xFF)); // calculate the proper checksum
}
