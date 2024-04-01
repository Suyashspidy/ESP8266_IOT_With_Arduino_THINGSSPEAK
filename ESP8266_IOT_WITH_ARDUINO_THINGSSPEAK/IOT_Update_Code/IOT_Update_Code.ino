#include <stdlib.h>
/*-----------------ESP8266 Serial WiFi Module---------------*/
#define SSID "Harish"      // "SSID-WiFiname" 
#define PASS "harish1234"       // "password"
#define IP "184.106.153.149"// thingspeak.com ip
String msg = "GET https://api.thingspeak.com/update?api_key=90KXX26ZJPBBKZKM"; //change it with your key...
/*-----------------------------------------------------------*/
int error;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //or use default 115200.
  Serial.println("AT");
  delay(5000);
  if(Serial.find("OK")){
    connectWiFi();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0)
  {
    int data=Serial.read();
String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  Serial.println(cmd);
  delay(2000);
  if(Serial.find("Error")){
    return;
  }
  cmd = msg ;
  cmd += "&field1=";     //field 1 for temperature
  
  cmd +=data;
  cmd += "\r\n";
  Serial.print(cmd);
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  if(Serial.find(">")){
    Serial.print(cmd);
  }
  else{
    Serial.println("AT+CIPCLOSE");
    //Resend...
    error=1;
  }
}
}
boolean connectWiFi(){
  Serial.println("AT+CWMODE=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  Serial.println(cmd);
  delay(5000);
  if(Serial.find("OK")){
    return true;
  }else{
    return false;
  }
}

