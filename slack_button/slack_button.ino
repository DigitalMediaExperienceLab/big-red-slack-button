#include <SPI.h>
#include <Ethernet.h>

//button variables
const char buttonPin = 2; //NEED TO EDIT THIS
boolean buttonState;

//networking settings, incuding Ethernet Sheild MAC 
byte mac[] = { 0x68, 0x8F, 0xC7, 0x18, 0x35, 0xF4 }; //Edited: Double-check whe you get the chance
EthernetClient client;

//slack-specific settings
#define server "hooks.slack.com"
#define urlPath "/services/AAAAAA/BBBBBB/CCCCCCCCCC" //NEED TO EDIT THIS
String message = "Someone pushed the big red button."; //NEED TO EDIT THIS
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; //NEED TO EDIT THIS
EthernetClient client;

//slack-specific settings
#define server "http://hooks.slack.com"
#define urlPath "/services/AAAAAA/BBBBBB/CCCCCCCCCC" //NEED TO EDIT THIS

void setup() {
  //init button pin
  pinMode(buttonPin, INPUT_PULLUP);

  //begin debug serial
  Serial.begin(9600);

  //connect to network
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Failed to configure Ethernet using DHCP"));
    while(true){} //failed, so do nothing forever
  }
  delay(1000);

  //get initial state of button
  if(digitalRead(buttonPin) == HIGH)
  {
    buttonState = true;
  }
  else
  {
    buttonState = false;
  }
}

void loop()
{
  //check if button was just pushed
  if(buttonState == false && digitalRead(buttonPin) == HIGH)
  {
    Serial.println(F("Button was pressed."));
    post();
  }

  //update button state
  if(digitalRead(buttonPin) == HIGH)
  {
    buttonState = true;
  }
  else
  {
    buttonState = false;
  }
}

//function for posting message
void post() {
  //connect to server
  Serial.println(F("Connecting to server..."));
  if(!client.connect(server, 443))
  {
    Serial.println(F("Connection failed"));
    client.stop();
    return;
  }
  Serial.println(F("Connected to server"));

  // Send a POST request to your Slack webhook:
  // {"text": "Someone pushed the big red button."}

  //compose message
  String request = "";
  request += F("POST ");
  request += urlPath;
  request += F(" HTTP/1.1\r\n");

  request += F("server: ");
  request += server;
  request += F("\r\n");

  int len = message.length() + 12;  // JSON wrapper length
  request += F("Content-Length: ");
  request += len;
  request += F("\r\n");

  request += F("Accept: application/json\r\n");
  request += F("Connection: close\r\n");
  request += F("Content-Type: application/json\r\n");

  request += F("\r\n");
  Serial.print(F("POST "));
  //Serial.print(server);
  Serial.print(F(urlPath));
  Serial.print(F(" HTTP/1.1\r\n"));
  client.print(F("POST "));
  //client.print(server);
  client.print(F(urlPath));
  client.print(F(" HTTP/1.1\r\n"));

  Serial.print(F("Host: "));
  Serial.print(F(server));
  Serial.print(F("\r\n"));
  client.print(F("Host: "));
  client.print(F(server));
  client.print(F("\r\n"));

  //int len = message.length() + 12;  // JSON wrapper length
  //Serial.print(F("Content-Length: "));
  //Serial.print(len);
  //Serial.print(F("\r\n"));
  //client.print(F("Content-Length: "));
  //client.print(len);
  //client.print(F("\r\n"));

  //Serial.print(F("Accept: application/json\r\n"));
  //Serial.print(F("Connection: close\r\n"));
  //Serial.print(F("Content-Type: application/json\r\n"));
  //client.print(F("Accept: application/json\r\n"));
  //client.print(F("Connection: close\r\n"));
  //client.print(F("Content-Type: application/json\r\n"));

  Serial.print(F("Cache-Control: no-cache\r\n"));
  client.print(F("Cache-Control: no-cache\r\n"));
  Serial.print(F("Postman-Token: bed00753-d001-5a50-5440-743f7b43fbcb\r\n"));
  client.print(F("Postman-Token: bed00753-d001-5a50-5440-743f7b43fbcb\r\n"));

  Serial.print(F("\r\n"));
  client.print(F("\r\n"));
  
  Serial.print(F("{\"text\": \""));
  Serial.print(message);
  Serial.print(F("\"}"));
  client.print(F("{\"text\": \""));
  client.print(message);
  client.print(F("\"}"));
  
  request += F("{\"text\": \"");
  request += message;
  request += F("\"}");

  //send message to debug and server
  Serial.print(request);
  Serial.println();
  client.print(request);

  //wait for disconnect or timout (end connection either way)
  long timeout = millis() + 5000;
  while (!client.available())
  {
    if (millis() > timeout)
    {
      Serial.println(F("Request timed out"));
      client.stop();
      return;
    }
  }

  //print any response from server to debug
  Serial.println(F("Response:"));
  while (client.available())
  {
    Serial.write(client.read());
  }
  Serial.println();

  //end of request
  Serial.println(F("Request complete"));
}
