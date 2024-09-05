/*-----( Import needed libraries )-----*/
#include <SPI.h> // Use the Serial Peripheral Interface
#include <Wire.h> //Βιβλιοθηκι που επιτρέπει να επικοινωνείτε με συσκευές I2C Mega2560 20 (SDA), 21 (SCL)
#include <LiquidCrystal_I2C.h>//Library for LCD
#include <Ethernet.h>//Ethernet Shield Library
#include <DHT.h> //Βιβλιοθήκη για αισθητήρα Dht11 
#include <HCSR04.h> //librari Ultrasonic Sensor HC-SR04
#include <DS3231.h> //library for real time clock Rtc ds3231
//_____________________________________________________________________________________
/*-----(Set the Digital pin connected to the sensor )-----*/
const int MOS_AirRecyclingFan = 2; //Gate mosfet 1 attach to d5 pin arduino for Air Recycling area greenhouse
const int MOS_CoolingFan = 3; //Pc fan for cooling area Gate mosfet Irf540N 2 attach to d5 pin arduino 
int MOS_RgbLeds = 5;    // Gate Mosfet attach to Rgb Led strip

int RELAY_Pump1 = 30;//Relay of real Pump 1 for watering plant
int RELAY_HeatingLight = 31;//Relay for heating the area
int RELAY_ValveWater = 32; //Relay Electric valve for watering

int LED_Pump2 = 45; //led blue pump for filling a tank

#define SEN_Dht11 38    // Digital pin connected to the DHT sensor

#define SEN_UltraSonicTrigPin 48 //attach pin D49 Arduino to pin Trig  of HC-SR04
#define SEN_UltraSonicEchoPin 49 // attach pin D48 Arduino to pin Echo of HC-SR04

int SEN_LdrOut = A9; // Analog pin A9 connected to the LDR Sensor
//_____________________________________________________________________________________
/*-----( Declare Variables )-----*/
// LCD address and geometry and library initialization
const byte lcdAddr = 0x27;  // Address of I2C backpack
const byte lcdCols = 16;    // Number of character in a row
const byte lcdRows = 2;     // Number of lines
LiquidCrystal_I2C lcd(lcdAddr, lcdCols, lcdRows);// set the LCD address to 0x27 for a 16 chars and 2 line display 
//_____________________________________________________________________________________
/*-----( Declare Variables )-----*/
// define the Xbee sensor variables for frame
unsigned int analogMSB1 = 0; // πιο σημαντικό ψηφίο bit
unsigned int analogLSB1 = 0; // λιγότερο σημαντικό ψηφίο Bit
unsigned int Val_SoilHygro =0;//variable for the soil hygrometer data

unsigned int analogMSB2 = 0;// πιο σημαντικό ψηφίο bit
unsigned int analogLSB2 = 0;// λιγότερο σημαντικό ψηφίο Bit
unsigned int Val_InLdr = 0;// variable for the LDR in data

unsigned int analogMSB3 = 0;// πιο σημαντικό ψηφίο bit
unsigned int analogLSB3 = 0;// λιγότερο σημαντικό ψηφίο Bit
unsigned int Val_Mq07Gas = 0;// variable for the Mq-07 data

float Val_temp = 0;// Temperature variables
float Val_humi = 0; // Humidity variables
int Val_OutLdr = 0;// variable for the out LDR data

int Val_distance=0; // variable for the distance measurement
int Val_distancePerCent=0;// variable for the distance per cent measurement 
//_____________________________________________________________________________________
//Value for swithc buton in web site
int Mode =0;
boolean Val_Set_Mode = false;
boolean Val_Fans = false;
boolean Val_Light = false;
boolean Val_Watering= false;
boolean Val_Xbee= false;
//----------------------Set the preference Constants-------------------------------    
int My_Val_Max_temp=30; // Μεγίστη τιμή θερμοκρασίας σε βαθμούς Celsius
int My_Val_Min_temp=26; // Ελάχιστη τιμή θερμοκρασίας σε βαθμούς Celsius

int My_Val_Max_humi=90; // μέγιστη τιμή υγρασιας %
int My_Val_Min_humi=65; // ελάχιστη τιμή υγρασιας %

int My_Val_Max_distancePerCent=95; // μέγιστη τιμή νερού στο δοχείο
int My_Val_refill_distancePerCent=70;
int My_Val_Min_distancePerCent=60; // ελάχιστη τιμή νερού στο δοχείο

int My_Val_Max_OutLdr=80; // μέγιστη τιμή εξωτερικής φωτεινότητας 
int My_Val_Min_OutLdr=50; // ελάχιστη τιμή εξωτερικής φωτεινότητας

int My_Val_InLdr=50;    //Give the desired light value

int My_Val_Max_Mq07Gas=70;// μέγιστη τιμή αισυητιρα αεριου %

//he have WATER  Give the desired soil moisture value
int My_Val_Max_SoilHygro=60;
// don’t have WATER Give the desired soil moisture value 
int My_Val_Min_SoilHygro=30; 

// Rtc ds3231
const int My_Val_OnHour = 6; //SET Hour TO ON the rgb led
const int My_Val_OnMin = 01;//SET min TO ON the rgb led
const int My_Val_OffHour = 21; //SET TIME TO OFF  the rgb led
const int My_Val_OffMin = 10;//SET min TO OFF the rgb led
//_____________________________________________________________________________________
byte thermometer[8] = {//icon for termometer
  B00100,
  B01010,
  B01010,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110
};
byte drop[8] = {//icon for water droplet
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110,
};
//_____________________________________________________________________________________
/*-----( Declare objects )-----*/
// selected sensor type the DHT 11
#define DHTTYPE DHT11  
DHT dht(SEN_Dht11, DHT11);
//initialization class HCSR04 (trig pin , echo pin)
HCSR04 hc(SEN_UltraSonicTrigPin, SEN_UltraSonicEchoPin);

//RTC
DS3231  rtc(SDA, SCL);
Time t;

byte mac[] = { 0xD4, 0x28, 0xB2, 0xFF, 0xA0, 0xA1 }; //Ορισμός μοναδικής διεύθυνσης MAC του Arduino Ethernet shield
byte ip[] = {192, 168, 1,7 };//Enter the IP of ethernet shield  Must be unique on local network
byte serv[] = {192, 168, 1, 50} ;//Εισαγωγη της διευθηνσης IPv4 address του Η/Υ που ειναι ο Server 
byte gateway[] = { 192, 168, 1, 1}; 
byte subnet[]  = { 255, 255, 255, 0};
//_____________________________________________________________________________________
// Initialize Arduino Ethernet Client
EthernetClient client;             //subnet mask
EthernetServer server(80);//server port επιτρεπει στην ασπιδα να επικοινωνει με το δρομολογητη χρησημοπιοντας την θυρα 80 
String HTTP_req, webPage;

/*-----( Declare Variables )-----*/
// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";//διακομιστής ThingSpeak
String writeAPIKey = "NFNEYSXD0MUBW6MG";//Write the Write api key
const int updateThingSpeakInterval = 16 * 1000;// Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)
// Variable Setup
long lastConnectionTime = 0; 
boolean lastConnected = false;
int failedCounter = 0;
//_____________________________________________________________________________________
void setup(){
  //Serial Communication is starting with 9600 of baud rate speed
  Serial.begin(9600); //start serial to 9600 baud
  dht.begin();// Start the DHT sensor
  rtc.begin();// Start Rtc dc331 on Arduino
  Wire.begin(); //Start the I2C protocol

  //for lcd
  lcd.begin(16, 2);//Να ξεκινήσει η οθόνη για 16 στήλες και 2 γραμμές
  lcd.init(); // initialize the lcd
  lcd.backlight();  //Turns the backlight on
  lcd.createChar(1, thermometer); // Δημιουργία χαρακτήρα θερμομέτρου
  lcd.createChar(2, drop);// Δημιουργία χαρακτήρα σταγόνας
  lcd.clear(); //Καθαρισμός οθόνης
  
  // print some text in Serial Monitor
  Serial.println(F("DHT11 test!"));
  Serial.println(F("Ultrasonic Sensor HC-SR04 Test")); // print some text in Serial Monitor
  Serial.println(F("with Arduino UNO R3"));

  //start the Ethernet connection and the server:
  Serial.print("ETHERNET Server SHIELD Started...\nLocal IP: ");  
  Ethernet.begin(mac, ip);// initialize Ethernet device
  
  // Start Ethernet connection on Arduino for ThingSpeak
  startEthernet();

  //Set the INPUT pin mode
  pinMode(SEN_LdrOut, INPUT);
  pinMode(SEN_Dht11, INPUT); 
  // Sets the echoPin as an INPUT
  pinMode(SEN_UltraSonicEchoPin, INPUT); 
  
  //Set the Outout pin mode
  // Sets the trigPin as an OUTPUT
  pinMode(SEN_UltraSonicTrigPin, OUTPUT); 
  pinMode(MOS_AirRecyclingFan, OUTPUT);
  pinMode(MOS_CoolingFan, OUTPUT);
  pinMode(MOS_RgbLeds, OUTPUT);
  pinMode(RELAY_ValveWater, OUTPUT);
  pinMode(RELAY_Pump1, OUTPUT);
  pinMode(LED_Pump2, OUTPUT);
  pinMode(RELAY_HeatingLight, OUTPUT);
  
  digitalWrite(MOS_AirRecyclingFan, LOW); // set the pin to LOW
  digitalWrite(MOS_CoolingFan, LOW); // set the pin to LOW
  digitalWrite(MOS_RgbLeds, LOW); // set the pin to LOW
  
  setRem_LED_RED_Org_ALERT_DIO4(0x4);//set the Xbee pin D4 to LOW
  setRem_LED_Yellow_MOV_Sunshade_DIO11(0x4);//set the Xbee pin to LOW
  setRem_LED_Blue_Blue_ForggerSpraySytem_DIO12(0x4);//Set the to LOW
  
  // For switch buton in web site
  digitalWrite(Mode, Val_Set_Mode);
  
  digitalWrite(MOS_AirRecyclingFan, Val_Fans);
  digitalWrite(MOS_CoolingFan, Val_Fans);
  
  digitalWrite(RELAY_ValveWater, Val_Watering);
  digitalWrite(RELAY_Pump1, Val_Watering);
  digitalWrite(LED_Pump2, Val_Watering);
  
  digitalWrite(RELAY_HeatingLight, Val_Light);
  digitalWrite(MOS_RgbLeds, Val_Light);

  digitalWrite(setRem_LED_RED_Org_ALERT_DIO4, Val_Xbee);
  digitalWrite(setRem_LED_Yellow_MOV_Sunshade_DIO11, Val_Xbee);
  digitalWrite(setRem_LED_Blue_Blue_ForggerSpraySytem_DIO12, Val_Xbee);

}

void loop(){
  Read_RemoteXbee_Loop();
  Read_Rtc_Loop();
  Read_Sen_Dht11_Loop();
  Read_Sen_UltraSonic_Loop();
  Read_Sen_OutLDR_Loop();
  
  Print_Serial_loop(); // print the data sensor to serial monitor
  Print_Lcd_loop();
  Print_DataBase_loop();
  Print_ThingSpeak_loop();

  control_NETarea_loop();
}

//---Read the sensor value of Router Xbee--------------------------------
void Read_RemoteXbee_Loop() {
     // έλεγχος εάν το frame έχει τουλάχιστον 29 bits
    if (Serial.available() >= 29) { 
        // έλεγχος εάν έχει start byte 7E
        if (Serial.read() == 0x7E) { 
            // Απόρριψη των πρώτων 21 byte
            for (int i = 1; i < 21; i++) {
                byte discardbyte = Serial.read();
            }
            //τα Πρώτα  byte είναι η τιμή  του Soil hygrometer 
            // Read the most significant bit of the analog data 
            analogMSB1 = Serial.read(); // Read the first analog byte data
            analogLSB1 = Serial.read(); // Read the second byte
//μαθηματική πράξη για την δημιουργία από 2 bit LSB και MSB σε ένα 
            //byte
            Val_SoilHygro = analogLSB1 + (analogMSB1 * 256);
            //Αντιστοιχήσει των Byte σε επι τοις εκατό
            Val_SoilHygro =   map(Val_SoilHygro, 700, 1000, 100, 0);
            
            //τα Επόμενα byte είναι η τιμή  του LDR
            analogMSB2 = Serial.read();// Read the first analog byte data
            analogLSB2 = Serial.read();// Read the second byte
//μαθηματική πράξη για την δημιουργία από 2 bit LSB και MSB σε ένα 
            //byte
            Val_InLdr = analogLSB2 + (analogMSB2 * 256);
            //Αντιστοιχήσει των Byte σε επι τοις εκατό
            Val_InLdr =   map(Val_InLdr, 9, 1023, 0, 100);
            //τα τελευταία byte είναι η τιμή το Gas Sensor Mq07 
            
            analogMSB3 = Serial.read();// Read the first analog byte data
            analogLSB3 = Serial.read();// Read the second byte
//μαθηματική πράξη για την δημιουργία από 2 bit LSB και MSB σε ένα 
            //byte
            Val_Mq07Gas = analogLSB3 + (analogMSB3 * 256);
            //Αντιστοιχήσει των Byte σε επι τοις εκατό
            Val_Mq07Gas =   map(Val_Mq07Gas, 0, 1023, 0, 100);
        }
    }
}

void control_NETarea_loop(){
  // Create a client connection
  EthernetClient client = server.available();
  //----------------------------------------------------------------------------
  if(client){
    Serial.println(F("new client"));
    boolean currentLineIsBlank = true;
    String postText=""; //for switch
    // an http request ends with a blank line
    while (client.connected()){
      if(client.available()){ 
        char c = client.read();
    //--------------------------------------------------------------------
        //read char by char HTTP request
        if (postText.length() < 10) {
          //store characters to string
          postText += c;
          Serial.print(c);
        }
  //--------------------------------------------------------------------
        HTTP_req += c;
        if(c == '\n' && currentLineIsBlank){
          if(HTTP_req.indexOf("read") > -1){ //AJAX request for DHT11 values
            AJAX_request(client);
          }else{
            HTML_webpage();
            client.println(webPage);
          }
          //--------------------------------------------------------------------
          Serial.print(HTTP_req);
          HTTP_req = ""; //reset HTTP request string
          break;
        }
        //----------------------------------------------------------------------
        if(c == '\n') currentLineIsBlank = true;
        else if(c != '\r') currentLineIsBlank = false;
      }
    }
         //controls the Arduino if you press the buttons
//------------------sw1--auto/manual----------------------------
  if (postText.indexOf("?on1") >0){ //auto
    digitalWrite(Mode, LOW);
    Val_Set_Mode= true;
  }
  if (postText.indexOf("?off1") >0){ //manual
    digitalWrite(Mode, HIGH);
    Val_Set_Mode= false;
  }
//------------------sw2---Fans---------------------------
  if (postText.indexOf("?on2") >0){
    digitalWrite(MOS_CoolingFan, LOW);
    digitalWrite(MOS_AirRecyclingFan, LOW);
    Val_Fans= true;
  }
  if (postText.indexOf("?off2") >0){
    digitalWrite(MOS_CoolingFan, HIGH);
    digitalWrite(MOS_AirRecyclingFan, HIGH);
    Val_Fans= false;
  }
//------------------sw3-Watering plants valve and pump 1-----------------------------
  if (postText.indexOf("?on3") >0){
    digitalWrite(RELAY_Pump1, HIGH);
    digitalWrite(RELAY_ValveWater, HIGH);
    digitalWrite(LED_Pump2, LOW);
    Val_Watering= true;
  }
  if (postText.indexOf("?off3") >0){
    digitalWrite(RELAY_Pump1, LOW);
    digitalWrite(RELAY_ValveWater, LOW);
    digitalWrite(LED_Pump2, HIGH);
    Val_Watering= false;
  }
//------------------sw4--Light----------------------------
  if (postText.indexOf("?on4") >0){
    digitalWrite(MOS_RgbLeds, LOW);
    digitalWrite(RELAY_HeatingLight, HIGH);
    Val_Light= true;
  }
  if (postText.indexOf("?off4") >0){
    digitalWrite(MOS_RgbLeds, HIGH);
    digitalWrite(RELAY_HeatingLight, LOW);
    Val_Light= false;
  }
//------------------sw5--Alarm----------------------------
  if (postText.indexOf("?on5") >0){
    setRem_LED_RED_Org_ALERT_DIO4(0x4);
    setRem_LED_Yellow_MOV_Sunshade_DIO11(0x4);
    setRem_LED_Blue_Blue_ForggerSpraySytem_DIO12(0x4);
    Val_Xbee= true;
  }
  if (postText.indexOf("?off5") >0){
    setRem_LED_RED_Org_ALERT_DIO4(0x5);
    setRem_LED_Yellow_MOV_Sunshade_DIO11(0x5);
    setRem_LED_Blue_Blue_ForggerSpraySytem_DIO12(0x5);
    Val_Xbee= false;
  }
//****************************************
  if (Val_Set_Mode== false){ //manual
    System_Temprature_Loop();
    System_Water_Loop();
    System_SunsHade_Loop();
    System_AirRecycling_Loop();
    System_Alert_Loop();
    System_ForggerSpray_Loop();
    System_Light_Loop();
  }else{ //auto
    style_controll_loop(client);
  }

  style_controllMode(client);
    delay(10);
    client.stop(); //sever client connection with server
  }
}
//==================================================================================
//**********************Start***Switch************************************************************
void style_controllMode(EthernetClient cl){
  Serial.print("Auto");
  if (Val_Set_Mode){
    cl.println("<a class=""status1"" href=\"./?off1\"><img src=""http://192.168.1.50/db_allSensor/stylepage/Photos/off1.jpg"" alt=""off"" width=""90em"" height=""70em""</a>");
  }else{
    cl.println("<a class=""status1"" href=\"./?on1\"><img src=""http://192.168.1.50/db_allSensor/stylepage/Photos/on1.jpg"" alt=""off"" width=""90em"" height=""70em""</a>");
  }
}
void style_controll_loop(EthernetClient cl){
  Serial.print("Manual");
  if (Val_Fans){
      cl.println("<a class=""status2"" href=\"./?off2\"><img src=""http://192.168.1.50/db_allSensor/stylepage/Photos/off1.jpg"" alt=""off"" width=""90em"" height=""70em""</a>");
  }else{
      cl.println("<a class=""status2"" href=\"./?on2\"><img src=""http://192.168.1.50/db_allSensor/stylepage/Photos/on1.jpg"" alt=""off"" width=""90em"" height=""70em""</a>");
  }
  if (Val_Watering){
      cl.println("<a class=""status3"" href=\"./?off3\"><img src=""http://192.168.1.50/db_allSensor/stylepage/Photos/off1.jpg"" alt=""off"" width=""90em"" height=""70em""</a>");
  }else{
      cl.println("<a class=""status3"" href=\"./?on3\"><img src=""http://192.168.1.50/db_allSensor/stylepage/Photos/on1.jpg"" alt=""off"" width=""90em"" height=""70em""</a>");
  }
  if (Val_Light){
      cl.println("<a class=""status4"" href=\"./?off4\"><img src=""http://192.168.1.50/db_allSensor/stylepage/Photos/off1.jpg"" alt=""off"" width=""90em"" height=""70em""</a>");
  }else{
      cl.println("<a class=""status4"" href=\"./?on4\"><img src=""http://192.168.1.50/db_allSensor/stylepage/Photos/on1.jpg"" alt=""off"" width=""90em"" height=""70em""</a>");
  }
  if (Val_Xbee){
      cl.println("<a class=""status5"" href=\"./?off5\"><img src=""http://192.168.1.50/db_allSensor/stylepage/Photos/off1.jpg"" alt=""off"" width=""90em"" height=""70em""</a>");
  }else{
      cl.println("<a class=""status5"" href=\"./?on5\"><img src=""http://192.168.1.50/db_allSensor/stylepage/Photos/on1.jpg"" alt=""off"" width=""90em"" height=""70em""</a>");
  }
}
//==================================================================================
void AJAX_request(EthernetClient client){
  client.print("Online");
}
//==================================================================================
void HTML_webpage(){
  //HTTP response header
  webPage = "HTTP/1.1 200 OK\n\rContent-Type: text/html\n\r\n\r";//versions protocol->HTTP/1.1 or HTTP/2
  //-------------------------------------------------------------
  //webpage - HTML + JavaScript with AJAX calls
  webPage += R"***(
  <!DOCTYPE html>
  <html lang="el">
    <head>
     <TITLE>Control area</TITLE>
      <link rel='stylesheet' tye='text/css' href='http://192.168.1.50/db_allSensor/stylepage/StyleArduino.css'/>
    </head>
  <html>
  <body>
    <H1>Control area</H1>
    <div class=""menu-bar"">
      <ul>
        <li class="active"><a href='https://192.168.1.50/db_allsensor/index.html'><i class="fa-solid fa-house-blank"></i>HOME</a></li>
      </UL>
    </DIV>
    <div class="table-box">
        <div class="table-head">
            <div class="table-cell first-cell">
                <p>Devices</p>
            </div>
            <div class="table-cell last-cell">
                <p>Switch</p>
            </div>
        </div>
        <div class="table-row">
            <span style="color:rgb(196, 3, 3)" id="IdVals">N/A</span>
        </div>
        <div class="table-row">
            <p>Auto </p>
        </div> 
        
        <div class="table-row">
            <p>Fans</p>
        </div>
        
        <div class="table-row">
            <p>Watering plants</p>
        </div>
        
        <div class="table-row">
            <p>Light</p>
        </div>

        <div class="table-row">
            <p>Xbee Divice</p>
        </div>

    </div>
  <!-------------------------JavaScript---------------------------->
  <script>
    setInterval(
      function(){
        getIdVals();
      }, 2000
    );
    
    function getIdVals(){
      var Request = new XMLHttpRequest();
      Request.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200){
          document.getElementById("IdVals").innerHTML = this.responseText;
        }
      };
      Request.open("GET", "read", true);
      Request.send();
    }
  </script>
    
  </body>
  </html>
  )***";
}
////**********************End***Switch************************************************************
