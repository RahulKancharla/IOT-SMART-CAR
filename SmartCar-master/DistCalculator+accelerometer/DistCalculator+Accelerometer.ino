#include <Wire.h>
#include <ESP8266WiFi.h>
#include <math.h>
#include <Servo.h>

const int x_out = 14; /* connect x_out of module to A1 of UNO board */
const int y_out = 12; /* connect y_out of module to A2 of UNO board */
const int z_out = 15;
Servo servo;
int angle = 10;
/* connect z_out of module to A3 of UNO board */


#define anInput     4
#define digTrigger  2 
#define co2Zero     55                        
#define ledr         3
#define ledg         1

const int trigPin =  16;
const int echoPin =5 ;
const int Buzzer=0;
long dur;
int dis;
void setup() {
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(Buzzer, OUTPUT);
pinMode(anInput,INPUT);                   
pinMode(digTrigger,INPUT);                  
pinMode(ledr,OUTPUT);
pinMode(ledg,OUTPUT);
  servo.attach(8);
  servo.write(angle);
Serial.begin(9600);
}

void loop() {
  
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

dur= pulseIn(echoPin, HIGH);
dis=dur*0.034/2;

Serial.print("DISTANCE");
Serial.print(dis);
Serial.print("\n");
int co2now[10];
int co2raw = 0;
int co2comp = 0; 
int co2ppm = 0;               
int zzz = 0;                                  
int grafX = 0;

if(dis<50)
{
  digitalWrite(Buzzer,HIGH);  
}
else
{
  digitalWrite(Buzzer,LOW);
}
 for (int x = 0;x<10;x++){                   
    co2now[x]=analogRead(anInput);
    delay(300);
  }

for (int x = 0;x<10;x++){                    
    zzz=zzz + co2now[x];
    
  }
  co2raw = zzz/10;                           
  co2comp = co2raw - co2Zero;                
  co2ppm = map(co2comp,0,1023,400,5000);      
  grafX = map(co2ppm,0,1000,0,127);          
  Serial.println("co2ppm");
  Serial.println(co2ppm);
  Serial.println("\n");
 if(co2ppm<999){                            
    digitalWrite(ledg,HIGH);
    digitalWrite(ledr,LOW);
    }
  else{                                      
    digitalWrite(ledr,HIGH);
    digitalWrite(ledg,LOW);//turn off led
    
  }
    for(angle = 10; angle < 180; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);                   
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 10; angle--)    
  {                                
    servo.write(angle);           
    delay(15);       
  } 
  int x_adc_value, y_adc_value, z_adc_value; 
  double x_g_value, y_g_value, z_g_value;
  double roll, pitch, yaw;
  x_adc_value = analogRead(x_out); 
  y_adc_value = analogRead(y_out);
  z_adc_value = analogRead(z_out);
  Serial.print("x = ");
  Serial.print(x_adc_value);
  Serial.print("\t\t");
  Serial.print("y = ");
  Serial.print(y_adc_value);
  Serial.print("\t\t");
  Serial.print("z = ");
  Serial.print(z_adc_value);
  Serial.print("\t\t");
  //delay(10);
  
  
  x_g_value = ( ( ( (double)(x_adc_value * 5)/1024) - 1.65 ) / 0.330 );
  y_g_value = ( ( ( (double)(y_adc_value * 5)/1024) - 1.65 ) / 0.330 ); 
  z_g_value = ( ( ( (double)(z_adc_value * 5)/1024) - 1.80 ) / 0.330 );
  roll = ( ( (atan2(y_g_value,z_g_value) * 180) / 3.14 ) + 180 ); 
  pitch = ( ( (atan2(z_g_value,x_g_value) * 180) / 3.14 ) + 180 );
  //yaw = ( ( (atan2(x_g_value,y_g_value) * 180) / 3.14 ) + 180 );

  Serial.print("Roll = ");
  Serial.print(roll);
  Serial.print("\t");
  Serial.print("Pitch = ");
  Serial.print(pitch);
  Serial.print("\n\n");
  delay(10);
}
