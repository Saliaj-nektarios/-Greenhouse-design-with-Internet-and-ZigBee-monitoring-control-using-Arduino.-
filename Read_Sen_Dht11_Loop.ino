//---Read data Dht11 Data sensor
void Read_Sen_Dht11_Loop() {
  // read the humidity
  Val_humi = dht.readHumidity(); 
  // Read temperature as Celsius (the default)
  Val_temp = dht.readTemperature();
}
