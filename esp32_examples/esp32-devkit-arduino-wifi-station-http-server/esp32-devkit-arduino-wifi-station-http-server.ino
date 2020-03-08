// Author: Erwin Ouyang, aiotedge.tech
// Date  : 1 Mar 2020

#include <WiFi.h>

const char ssid[] = "Huawei-E5573";
const char pass[] = "huaweie5573";

// TCP server port for HTTP
const uint16_t port = 80;

// TCP server object declaration
WiFiServer server(port);

String httpResponse =
  "HTTP/1.1 200 OK\r\n" \
  "Content-Type: text/html\r\n" \
  "Connection: close\r\n" \
  "\r\n";
String webPage =
  "<!DOCTYPE HTML>\r\n" \
  "<html>\r\n" \
  "<head>\r\n" \
  "<title>ESP32 HTTP Server</title>\r\n" \
  "</head>\r\n" \ 
  "<body>\r\n" \
  "<p>A web page from ESP32</p>\r\n" \
  "</body>\r\n" \
  "</html>\r\n";

void setup()
{
  // Setup serial communication
  Serial.begin(115200);

  // *** Connect to a WiFi access point ***
  Serial.printf("Connecting to %s ...\n", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.printf("WiFi connect failed! Rebooting ...\n");
    delay(1000);
    ESP.restart();
  }
  Serial.printf("Connected\n");
  Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());

  // *** Start TCP server ***
  server.begin();
  Serial.printf("TCP server started at port %d\n", port);
}

void loop()
{
  // Get TCP client
  WiFiClient client = server.available();

  // *** If a client connected ***
  if (client)
  {
    Serial.printf("[Client connected]\n");

    // An http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected())
    {
      if (client.available())
      {
        // *** Read a character from client ***
        char c = client.read();
        Serial.write(c);
                
        if (c == '\n' && currentLineIsBlank)
        {
          // The end of the line (received a newline character),
          // and the line is blank, the http request has ended,
          // so you can send a reply

          // Send HTTP response
          client.print(httpResponse);
          // Send web page
          client.print(webPage);
                    
          break;
        }
                
        if (c == '\n')
        {
          // The last character on line of the received text is received,
          // then starts a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
          // Receive character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    delay(1);
        
    // *** Close client ***
    client.stop();
    Serial.printf("[Client disconnected]\n");
  }
}

