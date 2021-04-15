#include <ESP8266WiFi.h>
#include <Adafruit_MLX90614.h>
#include<Servo.h>
#include "dht.h"
#define TrigPin 6 //ultrasonic transmit ultrasound
#define echoPin 7 //observing echo of ultrasound
#define Relay_1 0 // relay define for eletrical units
#define Relay_2 1
#define Relay_3 3
#define Relay_4 4
#define dht_pin A0
Servo servo;      //create servo object
dht DHT;
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); //create mlx function >>NOT sure sam<<
int angle = 10;    //define servo angle 
int Ir =0 ;
long duration;
int distance;

void setup() 
{
Serial.begin(115200);
Serial.println("Hello welcome to my Minor project");
pinMode(Ir,INPUT);
pinMode(TrigPin,INPUT);
pinMode(echoPin,OUTPUT);
pinMode(Relay_1,OUTPUT);
pinMode(Relay_2,OUTPUT);
pinMode(Relay_3,OUTPUT);
pinMode(Relay_4,OUTPUT);
mlx.begin();
servo.attach(8);
servo.write(angle);  
}

void loop() 
{
  // ultrasonic
  digitalWrite(TrigPin,LOW);
  delay(1000);
  digitalWrite(TrigPin,HIGH);
  delay(1000);
  digitalWrite(TrigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  distance = duration*0.034/2;
  Serial.println(distance);

//DHT
DHT.read11(dht_pin);
float dht_hum=DHT.humidity;
float dht_temp=DHT.temperature;

 //IR
 int sensorstatus = digitalRead(Ir);

//mlx
 Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  float Read_object_temp = mlx.readObjectTempC();
  delay(500);

  if(36 >= Read_object_temp <= 38)
  {
    Serial.print(mlx.readObjectTempC());
    if(distance<=100) //distance should be 1 meter
    {
         for(angle=10;angle<110;angle++)
         {
          servo.write(angle); 
         }
         if(sensorstatus == 1)
         {
            digitalWrite(Relay_1, HIGH);
            digitalWrite(Relay_2, HIGH);
               if( 65>= dht_hum <=30 or dht_temp >= 30 )
               {
                 digitalWrite(Relay_3, HIGH);
                 digitalWrite(Relay_4, HIGH);
               }
               else
               {
                digitalWrite(Relay_3, LOW);
                digitalWrite(Relay_4, LOW); 
               }
          }
          else
          {
             digitalWrite(Relay_1, LOW);
             digitalWrite(Relay_2, LOW);
          }
          
    }
    else
    {
         angle = 10;
         servo.write(angle);
    }
  }
  else
  {
  Serial.println("Body temperture is Low/High no entry allowed");
  }
}
