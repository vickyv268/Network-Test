/*
  DHCP-based IP printer

  This sketch uses the DHCP extensions to the Ethernet library
  to get an IP address via DHCP and print the address obtained.
  using an Arduino Wiznet Ethernet shield.

  Circuit:
   Ethernet shield attached to pins 10, 11, 12, 13

  created 12 April 2011
  modified 9 Apr 2012
  by Tom Igoe
  modified 02 Sept 2015
  by Arturo Guadalupi

*/

#include <SPI.h>
#include <Ethernet.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};
char serverName[] = "www.google.com";


String dhcp="[-]";
String dn="[-]";
String ia="[-]";
String dhcpIp="";

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

 display.begin();
 display.clearDisplay();
 // text display tests

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("link state:");
  display.println(dhcp); 
  

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Dev IP:");
  display.println("waiting...");
  display.setTextColor(WHITE); // 'inverted' text
   
  display.print("DNS:");
  display.println(dn);
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Internet Access:");
  
  display.print(ia);
  display.display();
  delay(1000);
  display.clearDisplay();

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
// start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    dhcp="[-]";
    dn="[-]";
    ia="[-]";
  }
  else {

   dhcp="[+]";
  
   if (client.connect(serverName, 80)) {
    dn="[-]";
     client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
    ia="[-]";
   }
   else {   
    dn="[+]";
    ia="[+]";
    }

  }
}

void loop(){
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    dhcp="[-]";
    dn="[-]";
    ia="[-]";
  }
  else {

   dhcp="[+]";
  }
//   if (client.connect(serverName, 80)) {
//    dn="[-]";
//    ia="[-]";
//   }
//   else {   
//    dn="[+]";
//    ia="[+]";
//    }
//  
//  }
display.clearDisplay();
 // text display tests

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("link state:");
  display.println(dhcp); 
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Dev IP:");
  printIPAddress();
  display.setTextColor(WHITE); // 'inverted' text
   
  display.print("DNS:");
  display.println(dn);
  //
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Internet Access:");

  display.print(ia);
  display.display();
  delay(1000);
  display.clearDisplay();
  } 

void printIPAddress()
{
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    display.print(Ethernet.localIP()[thisByte], DEC);
    display.print(".");
  }
  display.println();
}
