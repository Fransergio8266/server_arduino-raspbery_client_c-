/*
 * Server will accept data and send it back to the client.
 */

#include <UIPEthernet.h>

EthernetServer server = EthernetServer(8077);

void setup()
{
  Serial.begin(115200);
  while (!Serial) {}

  Serial.println("Start!");
  //the MAC for the shield:
  uint8_t mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0xED};
  //the IP address for the shield:
  byte ip[] = { 169, 254, 102, 173 };
  //the gateway for the shield:
  byte gateway[] = { 169, 254, 1, 1 };
  //the subnet for the shield:
  byte subnet[] = {255,255,0,0};
  byte myDns[] = { 169, 254, 1, 1 };

  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  delay(1000);
  
  Serial.print("localIP: ");
  Serial.println(Ethernet.localIP());
  Serial.print("subnetMask: ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("gatewayIP: ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("dnsServerIP: ");
  Serial.println(Ethernet.dnsServerIP());
  server.begin();
  delay(1000);
}
.
void loop()
{
  size_t size;

  if (EthernetClient client = server.available())
    {
      while((size = client.available()) > 0)
        {
          uint8_t* msg = (uint8_t*)malloc(size);
          size = client.read(msg,size);
          Serial.write(msg,size);
          client.write(msg,size);
          client.println("");
          free(msg);
          delay(500);
        }
      
    }

    
}
