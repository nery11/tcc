// https://randomnerdtutorials.com/esp8266-web-server/

#include <ESP8266WiFi.h>

const char* ssid     = "CLICKNET_05";
const char* password = "ap506toshiba";

WiFiServer server(80);

String header;

const int output5 = 1;
const int output4 = 2;
const int output3 = 3;
const int output2 = 4;

String output5State = "off";
String output4State = "off";
String output3State = "off";
String output2State = "off";

void setup() {
  Serial.begin(115200); 

  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  
  pinMode(output3, OUTPUT);
  pinMode(output2, OUTPUT);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");    
            client.println();

             client.println("<!DOCTYPE html>");
             client.println("<html>");
            client.println("<read>");
                           
             client.println("<title>P&aacutegina nery</title");
             
             client.println("</read>");
             client.println("<body background=https://heypeppers.com.br/blog/wp-content/uploads/2017/04/74950-robotica-educacional-entenda-o-que-e-e-quais-sao-os-ganhos-no-seu-aprendizado-1.jpg > ");     
             client.println("</br>");
             client.println("<body>");
             client.println("<H1><CENTER> P&aacutegina Iury Nery </CENTER></H1>");
             client.println("<H1><CENTER> Controle da sua casa <CENTER></H1>");
             client.println("<br>");
             client.println("</body>");
            client.println("</htmal>"); 



               
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("Sala on");
              output5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("Sala off");
              output5State = "off";
              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("Quarto on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("Quarto off");
              output4State = "off";
              digitalWrite(output4, LOW);
            }
             else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("Luz da garagem on");
              output3State = "on";
              digitalWrite(output3, HIGH);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("Luz de garagem off");
              output3State = "off";
              digitalWrite(output3, LOW);
            }
               else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("tomada ligado");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("tomado desligado");
              output2State = "off";
              digitalWrite(output2, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<B><p>Sala - State " + output5State + "</p></B>");
            // If the output5State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<B><p>Quarto - State " + output4State + "</p></B>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
             client.println("<B><p>Luz da garagem - State " + output3State + "</p></B>");
            // If the output5State is off, it displays the ON button       
            if (output3State=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<B><p>Tomado - State " + output2State + "</p></B>");
            // If the output4State is off, it displays the ON button       
            if (output2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</b>");
            client.println("<H3><CENTER> Acredita no seu potencial!! <CENTER></H3>");
            
            client.println("</body></html>");
           
             
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

}
