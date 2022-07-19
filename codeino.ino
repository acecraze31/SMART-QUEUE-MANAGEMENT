
//includes
#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <TM1637Display.h>
#include "source.h" // All Web Pages are written here

// Seven segment led
#define CLK 3
#define DIO 2

#define TEST_DELAY   300
TM1637Display display(CLK, DIO);
uint8_t blank[] = { 0x0, 0x0, 0x0, 0x0 };// data to clear the screen

const char* ssid_sta = "ACECRAzE";     // your network SSID (name)
const char* pass_sta = "rupesh31";     // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;              // your network key Index number (needed only for WEP)

const char* ssid_ap = "QMN";     // Acces point name
const char* pass_ap = "12345678";     // your network password (use for WPA, or use as key for WEP)

char ser[] = "api.thingspeak.com";         //Thingspeak server
const String apiKey = "2SBSH3FUKSM1VVZY";  //API key for the Thingspeak ThingHTTP already configured
String code = "+91";                       //Country Code,In order to work put your country code

int Pin = 7;   // choose the input pin (for a pushbutton)
int val = 0;  //value to store the current value of button

// Define Wifi Client parameters
        
IPAddress gwip(172,128, 128, 1);         // GW fixed IP adress
IPAddress apip(172,128, 128, 10);         // AP fixed IP adress
uint8_t apChannel = 2;                  // AP wifi channel             

int status = WL_IDLE_STATUS; // wifi status
WiFiServer server(80); // Server declaring on port 80

// Define UDP settings for DNS 
#define UDP_PACKET_SIZE 128           // MAX UDP packaet size = 512
#define DNSHEADER_SIZE 12             // DNS Header
#define DNSANSWER_SIZE 16             // DNS Answer = standard set with Packet Compression
#define DNSMAXREQUESTS 16             // trigger first DNS requests, to redirect to own web-page
byte packetBuffer[ UDP_PACKET_SIZE];  // buffer to hold incoming and outgoing packets
byte dnsReplyHeader[DNSHEADER_SIZE] = { 
  0x00,0x00,   // ID, to be filled in #offset 0
  0x81,0x80,   // answer header Codes
  0x00,0x01,   //QDCOUNT = 1 question
  0x00,0x01,   //ANCOUNT = 1 answer
  0x00,0x00,   //NSCOUNT / ignore
  0x00,0x00    //ARCOUNT / ignore
  };
byte dnsReplyAnswer[DNSANSWER_SIZE] = {   
  0xc0,0x0c,  // pointer to pos 12 : NAME Labels
  0x00,0x01,  // TYPE
  0x00,0x01,  // CLASS
  0x00,0x00,  // TTL
  0x00,0x3c,  // TLL 1 hour
  0x00,0x04,   // RDLENGTH = 4
  0x00,0x00,  // IP adress octets to be filled #offset 12
  0x00,0x00   // IP adress octeds to be filled
  } ;
byte dnsReply[UDP_PACKET_SIZE];       // buffer to hold the send DNS repluy
IPAddress dnsclientIp;
unsigned int dnsclientPort;
unsigned int udpPort = 53;            // local port to listen for UDP packets
WiFiUDP Udp;                          // A UDP instance to let us send and receive packets over UDP
int dnsreqCount=0;

int i = 0; // array variable
int j = 0; // array variable

int x = 0; // Array check variable
String number; 
String otpnumber;
String queue[15];
int Flag = 0; // Flag variable

String otp_sub;
String otp_gen;

int Flag_Token;

void setup() 
{ 
  
  pinMode(Pin,INPUT); // Button declaring..

  display.setBrightness(0x0f);// set brightness of display  
  uint8_t data8888[] = { 0xff, 0xff, 0xff, 0xff };  // all segments show
  display.setSegments(data8888); // display 8888 on display for test 
  delay(3000);// give time to user to read the display at the beginning
  display.setSegments(blank); // clear the screen from previous values 
  display.showNumberDec(0);// display zero at the belonging
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Serial.println("Access Point Web Server with CaptivePortal");

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  // by default the local IP address of will be 192.168.4.1
  // Create open network. Change this line if you want to create an WEP network:
  Serial.print("Creating access point named: ");
  Serial.println(ssid_ap);
  WiFi.disconnect();
  WiFi.config(apip,apip,gwip,IPAddress(255,255,255,0));
  //WiFi.setHostname(myHost);
  status = WiFi.beginAP(ssid_ap,pass_ap,apChannel); // setup AP 
  if (status != WL_AP_LISTENING) 
  {
    Serial.println("Creating access point failed");
    // don't continue
    while (true) ;  
  }
    // wait 1 seconds for connection:
  delay(1000);

  // start the web server on port 80
  Udp.begin(udpPort);
  server.begin();
}


void loop()
{
  int t;
  char c;
  // compare the previous AP status to the current status
  IPAddress ip = WiFi.localIP();
  if (status != WiFi.status()) {
  // it has changed update the variable
    status = WiFi.status();

    if (status == WL_AP_CONNECTED) {
      // a device has connected to the AP
      Serial.println("Device connected to AP");
      dnsreqCount=0; 
      udpScan(); // scan DNS request for redirect
    }
    else {
      // a device has disconnected from the AP, and we are back in listening mode
      Serial.println("Device disconnected from AP");
    }
  }
  // Wifi Server check
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        c = client.read();             // read a byte, then
        Serial.write(c);
        if (c == '\n') 
        {                    
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
               client.println("HTTP/1.1 200 OK");
               client.println("Content-type:text/html");
               client.println();
               client.print(first); // Index page will be loadede
               break;
          }
          else 
          {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was a post
        if (currentLine.endsWith("POST /checkpass.php")) 
        {
                Serial.println("** found POST");  
                currentLine = ""; 
                while (client.connected()) 
                {                
                if (client.available()) 
                {                    
                   c = client.read(); // read a byte, then
                   Serial.write(c);
                    if (c == '\n') 
                    {                          // if the byte is a newline character
                       //if (currentLine.length() == 0) break; // no lenght :  end of data request
                       currentLine = "";                      // if you got a newline, then clear currentLine:
                    }
                    else if (c != '\r') currentLine += c;     // if you got anything else but a carriage return character, add to string
  
               if (currentLine.startsWith("data=")) 
                  {        
                     number += c;
                     if (currentLine.endsWith("&action"))
                     {
                         Serial.println("Number Found");
                         number.remove(11);
                         number.remove(0, 1); // submitted number variable will be stored in "number"
                         Serial.print(number);
                         Flag = 1;
                         break;
                     }    
                  }
    
                 } 
            }
            delay(1000);
            Serial.println("OTP PAGE");
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print(otpp);  // OTP page
            break;
        } // check also for the submitted otp
         if (currentLine.endsWith("POST /checkotp.php")) 
        {
                Serial.println("OTP submitted");  
                currentLine = ""; 
                while (client.connected()) 
                {                
                if (client.available()) 
                {                    
                   c = client.read();                        // read a byte, then
                    if (c == '\n') 
                    {                          // if the byte is a newline character
                       //if (currentLine.length() == 0) break; // no lenght :  end of data request
                       currentLine = "";                      // if you got a newline, then clear currentLine:
                    }
                    else if (c != '\r') currentLine += c;     // if you got anything else but a carriage return character, add to string
                   if (currentLine.startsWith("otp=")) 
                   {        
                       otp_sub += c;
                      if (currentLine.endsWith("&action"))
                      {
                         otp_sub.remove(5);
                         otp_sub.remove(0, 1); // submitted otp will be stored on this variable
                         Serial.print(otp_sub);
                         otp_verify(); // Function called for verifying OTP
                         break;
                      }  
                   }
               }
             }
            if(Flag_Token == 1)
            {
               client.println("HTTP/1.1 200 OK");
               client.println("Content-type:text/html");
               client.println();
               client.print(tok1); // Prints the first page of token
               client.print(i);    // Token number
               client.print(tok2); // Then prints the second page of token
               client.stop();  
               break;
            }
            else if( Flag_Token == 0)
            {
               client.println("HTTP/1.1 200 OK");
               client.println("Content-type:text/html");
               client.println();
               client.print(invalid); // Invalid page
               break;
               
            }
            else
            {
               client.println("HTTP/1.1 200 OK");
               client.println("Content-type:text/html");
               client.println();
               client.print(already); // Already registered page
               client.stop();
               break;
            }
                  
        } 
      } // end loop client avaialbe    
    } // end loop client connected
    
    // close the connection:
    client.stop();
    Serial.println(" client disconnected");
  }
  if(Flag == 1)
  {
     Serial.println("Generating OTP");
     Flag = 0;
     otp(); // Function for generating OTP
     AP_MODE(); // Function for switching to AP mode
  }
  val = digitalRead(Pin);  // read input value
  if (val == LOW) // For calling the Token
   { 
        delay(800);
        Serial.println("Token Calling...");
        display.setSegments(blank); // clear the screen from previous values   
        display.showNumberDec(j);// display the count 
        STA_MODE();             // For switching into STA mode
        String sendNumber = code + queue[j]; // Number stored in the queue array will append with country code
        String msg = "Your Turn";    // MSG content
        sendSMS(sendNumber,msg); // Function call to send SMS
        j=j+1;
        display.setSegments(blank); // clear the screen from previous values   
        display.showNumberDec(j);// display the count 
        AP_MODE();
   } 
  else udpScan();
}

// UIDP port 53 - DNS - Scan
void udpScan()
{
int t=0;  // generic loop counter
int r,p;  // reply and packet counters
unsigned int packetSize=0;
unsigned int replySize=0;
  packetSize = Udp.parsePacket();
  if ( (packetSize!=0) && (packetSize<UDP_PACKET_SIZE) )  //only packets with small size
    {
    // We've received a packet, read the data from it
    Udp.read(packetBuffer, packetSize); // read the packet into the buffer
    dnsclientIp = Udp.remoteIP();
    dnsclientPort = Udp.remotePort();
    if ( (dnsclientIp != apip) && (dnsreqCount<=DNSMAXREQUESTS) ) // only non-local IP and only the first few DNSMAXREQUESTS x times
    {  
    //Copy Packet ID and IP into DNS header and DNS answer
    dnsReplyHeader[0] = packetBuffer[0];dnsReplyHeader[1] = packetBuffer[1]; // Copy ID of Packet offset 0 in Header
    dnsReplyAnswer[12] = apip[0];dnsReplyAnswer[13] = apip[1];dnsReplyAnswer[14] = apip[2];dnsReplyAnswer[15] = apip[3]; // copy AP Ip adress offset 12 in Answer
    r=0; // set reply buffer counter
    p=12; // set packetbuffer counter @ QUESTION QNAME section
    // copy Header into reply
    for (t=0;t<DNSHEADER_SIZE;++t) dnsReply[r++]=dnsReplyHeader[t];
    // copy Qusetion into reply:  Name labels till octet=0x00
    while (packetBuffer[p]!=0) dnsReply[r++]=packetBuffer[p++];
    // copy end of question plus Qtype and Qclass 5 octets
    for(t=0;t<5;++t)  dnsReply[r++]=packetBuffer[p++];
    //copy Answer into reply
    for (t=0;t<DNSANSWER_SIZE;++t) dnsReply[r++]=dnsReplyAnswer[t];
    replySize=r;
  // Send DSN UDP packet
  Udp.beginPacket(dnsclientIp, dnsclientPort); //reply DNSquestion
  Udp.write(dnsReply, replySize);
  Udp.endPacket();
  dnsreqCount++;
    } // end loop correct IP
 } // end loop received packet
  
}

 void sendSMS(String number, String message)
  {
    WiFiClient client1;
    // Make a TCP connection to remote host
    if (client1.connect(ser, 80))
    {
        Serial.println(number);
        Serial.println(message);
        client1.print("GET /apps/thinghttp/send_request?api_key=");
        client1.print(apiKey);
        client1.print("&number=");
        client1.print(number);
        client1.print("&message=");
        client1.print(message);
        client1.println(" HTTP/1.1");
        client1.print("Host: ");
        client1.println(ser);
        client1.println("Connection: close");
        client1.println();
    }
    else
    {
      Serial.println(F("Connection failed"));
    }

    // Check for a response from the server, and route it
    // out the serial port.
    while (client1.connected())
    {
      if ( client1.available() )
      {
        char c = client1.read();
        Serial.print(c);
      }
    }
    Serial.println();
    client1.stop();
  }
  
void otp() //Function to sent OTP
  {
    STA_MODE();
    Serial.print("OTP service activating");
    int random_num = random(1000, 9999); // OTP generated
    otp_gen = String(random_num); //  converted to string
    Serial.println(otp_gen);
    String otp_msg = "Your OTP is  " + otp_gen; // Message content for the OTP 
    String otp_sent_number = code + number; // Number taken
    sendSMS(otp_sent_number,otp_msg); // Function call
  }
  int otp_verify() // Function to verify OTP
  {
    Serial.println("\n Comparing Otp's");
    if( otp_gen == otp_sub) // comparing submitted OTP and generated OTP
    {
        //Serial.println("Numbers");
        for (x=0; x<2; x=x+1)
        { 
          Serial.println(queue[x]);
          if (queue[x] == number)
          {
             Serial.println("Number Duplicate"); // Flag when a duplicate number is entered
             Flag_Token = 2;
             return 0;
          }
        }
       
      Flag_Token = 1;
      queue[i] = number; // Add the number to thr queue
      number = ""; // clearing variables
      otp_gen = "";
      otp_sub = "";    
      Serial.print(queue[i]);
      Serial.println("OTP verified"); //otp verified zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz    
      i = i + 1;
    }
    else
    {
      Flag_Token = 0;
    }
  }

void STA_MODE() // Function for STA mode
{
  
  WiFi.end();
  WiFi.begin(ssid_sta,pass_sta);
  
}
void AP_MODE() // Function for AP mode
{
  
  WiFi.end();
  WiFi.config(apip, apip, gwip, IPAddress(255, 255, 255, 0)); //WiFi.setHostname(myHost);
  WiFi.beginAP(ssid_ap,pass_ap, apChannel); // setup AP
  server.begin(); 
  Serial.println("OTP verified"); //otp verified zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
  
}
