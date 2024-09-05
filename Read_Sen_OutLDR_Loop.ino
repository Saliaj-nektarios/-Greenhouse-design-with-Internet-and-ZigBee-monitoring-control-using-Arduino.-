//---Read the value of ldr out of greenhouse--------------------------------
void Read_Sen_OutLDR_Loop() { 
  Val_OutLdr = analogRead(SEN_LdrOut);// read the analog data 0-1023 byte
  //Αντιστοιχήσει των Bytes σε επί τοις εκατό
  Val_OutLdr =   map(Val_OutLdr, 0, 1023, 0, 100);
}
