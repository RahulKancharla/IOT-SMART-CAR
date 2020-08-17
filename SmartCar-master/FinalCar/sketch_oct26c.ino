#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiConnector.h>
WiFiConnector *wifi;
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <math.h>
//#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x3F, 16, 2);
const int trigPin = 16;
const int echoPin = 5;
const int Buzzer=0;
long dur;
int dis;
int co2ppm = 0;
#define anInput     A0                        //analog feed from MQ135
#define digTrigger   2                        //digital feed from MQ135
#define co2Zero     55
#define led   10    //calibrated CO2 0 level

//const char* ssid     = "Isis";
//const char* password = "kill1234";
//const char* host = "api.thingspeak.com";
//const String talkBackAPIKey = "UWLC1QOYQ7QCI87V";
//const String talkBackID = "34725";
//const String channelsAPIKey = "1GTUOMF42THJ9XJH"; //WRITE KEY
//unsigned long myChannelNumber = 855900;
//String talkBackCommand,tbRequest,b;
//int status = WL_IDLE_STATUS;
//WiFiClient client;
//void updateChannels();
//int readValue;
//String tsData;
void setup() {
  // put your setup code here, to run once:
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(Buzzer, OUTPUT);
pinMode(anInput,INPUT);                     //MQ135 analog feed set for input
pinMode(digTrigger,INPUT);
Serial.begin(9600);
//ThingSpeak.begin(client);
//startWiFi();
//Wire.begin(2,0);
//lcd.begin();   // initializing the LCD
//lcd.backlight(); // Enable or Turn On the backlight 
//lcd.print(dis);
}

void loop() {
  // put your main code here, to run repeatedly:
int co2now[10];                               //int array for co2 readings
int co2raw = 0;                               //int for raw value of co2
int co2comp = 0;                              //int for compensated co2 
                               //int for calculated ppm
int zzz = 0;
digitalWrite(trigPin, LOW);
delayMicroseconds(10);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

dur= pulseIn(echoPin, HIGH);
dis=dur*0.034/2;

Serial.print("DISTANCE");
Serial.print(dis);
Serial.print("\n");
if(dis<50)
{
  digitalWrite(Buzzer,HIGH);  
}
else
{
  digitalWrite(Buzzer,LOW);
}

  for (int x = 0;x<10;x++){                   //samplpe co2 10x over 2 seconds
    co2now[x]=analogRead(A0);
    delay(200);
  }
  for (int x = 0;x<10;x++){                     //add samples together
    zzz=zzz + co2now[x];
    
  }
  co2raw = zzz/10;                            //divide samples by 10
  co2comp = co2raw - co2Zero;                 //get compensated value
  co2ppm = map(co2comp,0,1023,400,5000);
  if(co2ppm>850)
  {
    digitalWrite(led,HIGH); 
  }
  else
  {
    digitalWrite(led,LOW); 
  }
  Serial.println(co2ppm);
  Serial.println("ppm");
//sendAndriodValues();
delayMicroseconds(10);
//getTalkBack();

}
/*void getTalkBack()
{
tbRequest="GET /talkbacks/"+ talkBackID + "/commands/execute?api_key=" + talkBackAPIKey;
//Serial.println(tbRequest);

if(!client.connected())
{
  if (client.connect("api.thingspeak.com", 80))
  {
    client.println(tbRequest);
    if (client.connected())
      {
        b="";
        while(client.connected() && !client.available()) delay(30000); //waits for data
        while (client.connected() || client.available())
            {
              b = client.readString();
            }
        //Serial.print("Command -> ");
      // Serial.println(b);
       // Serial.println();
      }
  client.stop();
  Serial.flush();
 }
}
}
void sendAndriodValues()
{
  tsData="@&field1="+String(co2ppm);//+"&field2="+String(co2ppm);
  //Serial.println(tsData);
  delay(10);
  //Serial.print("connecting to ");
//Serial.println(host);
delay(10); 
 //Serial.println("tsData");
 updateChannels();
 //Serial.println(tsData);
}

void updateChannels()
{

//Serial.println(tsData);

if (client.connect("api.thingspeak.com", 80))
{
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+channelsAPIKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(tsData.length());
client.print("\n\n");
client.print(tsData);

if (client.connected())
{
//Serial.println("****************************************");
//Serial.println();
//Serial.println("Connecting to ThingSpeak...");
while(client.connected() && !client.available()) delay(30000); //waits for data
while (client.connected() || client.available())
{
char charIn = client.read();
//Serial.print(charIn);
}
//Serial.println();
//Serial.println();
//Serial.println("...disconnected");
//Serial.println();
}
}
client.stop();
Serial.flush();
}

void startWiFi()
{
client.stop();
//Serial.println();
//Serial.println("Connecting to");
//Serial.println(ssid);

WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(10);
    //Serial.print(".");
  }

 // Serial.println("");
 // Serial.println("WiFi connected");  
 // Serial.println("IP address: ");
 // Serial.println(WiFi.localIP());
delay(10);
}*/
