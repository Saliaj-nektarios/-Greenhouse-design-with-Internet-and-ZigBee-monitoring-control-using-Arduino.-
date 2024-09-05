// πλαίσιο για των έλεγχο του μπλε LED που εξομοιώνει το σύστημα 
//ψεκασμού ομίχλης νερού
void setRem_LED_Blue_Blue_ForggerSpraySytem_DIO12(char value) { 
  Serial.write(0x7E);
  Serial.write(byte(0x0));
  Serial.write(0x10);
  Serial.write(0x17);
  Serial.write(byte(0x0));

  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(byte(0x0));
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFE);

  Serial.write(0x02);
  Serial.write('P');
  Serial.write('2');
  Serial.write(value);
  long sum = 0x17 + 0xFF + 0xFF + 0xFF + 0xFE + 0x02 + 'P' + '2' + value;
  Serial.write(0xFF - (sum & 0xFF));
}
//=====================================================
