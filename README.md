# Network-Test

It is a simple low cost Arduino based network testing device which will let us know if a network can resolve DNS queries and can access the Internet.

# How it works

The main brain of the device is an Arduino UNO and Arduino compatable ethernet shield (I'm using a shield with w500 ethernet chip but you can even use ENC28J60. Keep in mind that if you use this chip you have to use different libraries) and a generic OLED display.
The device first sends a DHCP request to the DHCP server in the network. Once it gets the IP address it is printed on the OLED display and then it trys to send a request to google.com. Once the connection is made, both DNS and Internet Access status on the OLED display turns to [+] indicating that the network can resolve DNS requests and the network traffic can reach the internet.

If the DHCP request fails, then the OLED displays IP address as "0.0.0.0" as no address is assigned to it. If the DHCP request is success and IP address is obtained but the DNS request fails, then the OLED Status of DNS and Internet Access turns to [-] indicating the failure. 

### Connections 

| UNO | OLED  |
|:---:|:-----:|
|A4   |SCL    |
|A5   |SDA    |
|GND  |GND    |
|+5v  | Vcc   |

![aeb3c598-9ba7-408e-a190-73327cf391cd](https://cloud.githubusercontent.com/assets/14306244/24331276/6545d7ac-124e-11e7-8d7b-dbe0fe63963e.jpg)


# [Video Demo](https://youtu.be/LQ3Fr18DHvQ)
