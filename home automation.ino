#include <ESP8266WiFi.h>

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "tHereisnospoon"
#endif

/* Set tHese to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

int l1 = 14; // GPIO13 or for NodeMCU you can directly write D5
int l2 = 12;//D6
int l3 = 13;//D7
int l4 = 15;//D8
WiFiServer server(80); // Creates a server tHat listens for incoming connections on tHe specified port, Here in tHis case port is 80. 


/* Just a little test message.  Go to Http://192.168.4.1 in a web browser
   connected to tHis access point to see it.
*/

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.print("Configuring access point...");
  /* You can remove tHe password parameter if you want tHe AP to be open. */
  pinMode(l1 ,OUTPUT);
  digitalWrite(l1 ,HIGH);
    pinMode(l2 ,OUTPUT);  
  digitalWrite(l2 ,HIGH);
    pinMode(l3 ,OUTPUT);
  digitalWrite(l3 ,HIGH);
    pinMode(l4 ,OUTPUT);
  digitalWrite(l4 ,HIGH);
 
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
  
  server.begin();
  Serial.println("HTTP server started");

  
}

void loop() {
 IPAddress myIP = WiFi.softAPIP();
  //Serial.print("AP IP address: ");
  //Serial.println(myIP);
   // CHeck if a client Has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until tHe client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read tHe first line of tHe request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
  static int value[5]={1,1,1,1,1};
  
   if(request.indexOf("/LED1=ON1") != -1)  {
              digitalWrite(l1, LOW);
              value[1]=0;             
              }
   if(request.indexOf("/LED1=OFF1") != -1)  {
              digitalWrite(l1, HIGH);
              value[1] = 1;
                         
              }


          
   if(request.indexOf("/LED2=ON2") != -1)  {
              digitalWrite(l2, LOW);
              value[2] =0;
              
              }                              
   if(request.indexOf("/LED2=OFF2") != -1)  {
              digitalWrite(l2, HIGH);
              value[2] =1;
              }

                          
   if(request.indexOf("/LED3=ON3") != -1)  {
              digitalWrite(l3, LOW);
              value[3] =0;
              } 
   if(request.indexOf("/LED3=OFF3") != -1)  {
              digitalWrite(l3, HIGH);
              value[3] =1;
              
              }
                                                    
   if(request.indexOf("/LED4=ON4") != -1)  {
              digitalWrite(l4, LOW);
              value[4] =0;            
              }
   if(request.indexOf("/LED4=OFF4") != -1)  {
              digitalWrite(l4, HIGH);
              value[4] =1;
              
              } 

// Set ledPin according to tHe request
//digitalWrite(ledPin, value);
 
  // Return tHe response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/Html");
  client.println(""); //  do not forget tHis one
  client.println("<!DOCTYPE HTML>");
  client.println("<Html>");
 
  client.println("<body bgcolor=#d8adf5><br><br><br><br><br><br><br><center>");
  
   if(value[1] == 0 ) {
    client.println("<a Href=\"/LED1=OFF1\"\"><button style=height:53%;width:53%;border-radius:10px;background-color:#ee1c25><H1>Turn OFF 1</H1></button></a><br /><hr>");
  } else if(value[1] == 1){
    client.println("<a href=\"/LED1=ON1\"\"><button style=height:53%;width:53%;border-radius:10px;background-color:#31ae1f><h1>Turn ON 1</h1></button></a><br /><br /><hr>"); 
  }

     if(value[2] == 0) {
    client.println("<a href=\"/LED2=OFF2\"\"><button style=height:53%;width:53%;border-radius:10px;background-color:#ee1c25><h1>Turn OFF 2</h1></button></a><br /><hr>");
  } else if(value[2] == 1){
    client.println("<a href=\"/LED2=ON2\"\"><button style=height:53%;width:53%;border-radius:10px;background-color:#31ae1f><h1>Turn ON 2</h1></button></a><br /><br /><hr>"); 
  }

     if(value[3] == 0) {
    client.println("<a href=\"/LED3=OFF3\"\"><button style=height:53%;width:53%;border-radius:10px;background-color:#ee1c25><h1>Turn OFF 3</h1></button></a><br /><hr>");
  } else if(value[3] == 1){
    client.println("<a href=\"/LED3=ON3\"\"><button style=height:53%;width:53%;border-radius:10px;background-color:#31ae1f><h1>Turn ON 3</h1></button></a><br /><br /><hr>"); 
  }

     if(value[4] == 0 ) {
    client.println("<a href=\"/LED4=OFF4\"\"><button style=height:53%;width:53%;border-radius:10px;background-color:#ee1c25><h1>Turn OFF 4</h1></button></a><br /><hr>");
  } else if(value[4] == 1){
    client.println("<a href=\"/LED4=ON4\"\"><button style=height:53%;width:53%;border-radius:10px;background-color:#31ae1f><h1>Turn ON 4</h1></button></a><br /><br /><hr>"); 
  }
  
   
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 

}

