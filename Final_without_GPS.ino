#include <dht.h>  //library if DHT Sensor
#include <SoftwareSerial.h> // library of GSM
#define FORCE_SENSOR_PIN A1// the FSR and 10K pulldown are connected to 2
#define dht_apin 2 // Analog Pin sensor is connected to 
#define SENSE A0 // iris sensor pin
dht DHT;

int switch_pin=12; 
SoftwareSerial mySerial(9, 10);//(TX,RX)
void SendMessage();
void SendMessageFS();
void SendMessageDHT();

void setup(){
 
  Serial.begin(9600);//9600 is baud rate
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  

  pinMode(SENSE, INPUT);
  pinMode(A0, OUTPUT);
  pinMode(switch_pin,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
 
}//end "setup()"
 
void loop(){
  //Start of Program 

  //  Iris Start 
 if(digitalRead(SENSE))
 {
 digitalWrite(LED_BUILTIN, LOW);
 pinMode(A0, LOW);
 }
 else
 {
  delay (1000);
  if(digitalRead(SENSE))
  {
   digitalWrite(LED_BUILTIN, LOW);
   pinMode(A0, LOW);
  }
  else
  digitalWrite(LED_BUILTIN, HIGH);  
  pinMode(A0, HIGH);
  }
//Iris End
  
// DHT Sensor 
    DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
    delay(1000);//Wait 5 seconds before accessing sensor again.

  if (DHT.temperature>33)
   {
   delay(3000);
  SendMessageDHT();
  }
  else
  {
    Serial.println("hello");
   }
//DHT END
// if (mySerial.available()>0)
// Serial.write(mySerial.read());


  //Fastest should be once every two seconds.

//Button start
 Serial.println("Please Press the button");
 delay(2000);
  if(digitalRead(switch_pin)==HIGH)
  {
  Serial.println("Button pressed");
  SendMessage();
  }
//  Button END

//Force Sensor Start
int analogReading = analogRead(FORCE_SENSOR_PIN);

  Serial.print("Force sensor reading = ");
  Serial.print(analogReading); // print the raw analog reading

  if (analogReading <10)       // from 0 to 9
    Serial.println(" -> no pressure");
  else if (analogReading < 200) // from 10 to 199
    Serial.println(" -> light touch");
  else if (analogReading < 500) // from 200 to 499
    Serial.println(" -> light squeeze");
  else if (analogReading < 800) // from 500 to 799
    Serial.println(" -> medium squeeze");
  else if (analogReading < 900)
    Serial.println(" -> big squeeze");

  delay(500);
  if(analogReading>800)
  {
    SendMessageFS();
  }
//Force Sensor End
}// end loop(



void SendMessageFS()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+919313463668\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println("Emergency!!! Vishal Got Accident please follow this link to Find him::https://maps.app.goo.gl/BMjybvtsi3PPFwB19");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
 
}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+919313463668\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println("YEAH BOis.. There is an SERIOUS Accident happen at the following link Plaese immediately reach on that location::https://maps.app.goo.gl/BMjybvtsi3PPFwB19");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);
  
  
}


void SendMessageDHT()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+919313463668\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println("High Temprature!!! Pen and paper stationery and printing https://maps.app.goo.gl/BMjybvtsi3PPFwB19");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(100);

}
