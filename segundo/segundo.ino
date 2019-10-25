// https://randomnerdtutorials.com/esp8266-web-server/

#include <ESP8266WiFi.h>

const char* ssid     = "NOME_REDE";
const char* password = "SENHA_REDE";

WiFiServer server(80);  //porta do roteador

String header;

const int output1 = D0;
const int output2 = D1;
const int output3 = D2;
const int output4 = D3;

String output1State = "off";
String output2State = "off";
String output3State = "off";
String output4State = "off";

void setup() {
  Serial.begin(115200); 

  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  
  pinMode(output3, OUTPUT);
  pinMode(output4, OUTPUT);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Imprima o endereço IP local e inicie o servidor web
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

}

void loop() {
  WiFiClient client = server.available();   // Ouça os clientes recebidos

  if (client) {                             // Se um novo cliente se conectar,
    Serial.println("New Client.");          // imprimir uma mensagem na porta serial
    String currentLine = "";                // faça uma String para armazenar dados recebidos do cliente
    while (client.connected()) {            // enquanto o cliente está conectado
      if (client.available()) {             // bytes para ler do cliente,
        char c = client.read();             //leia um byte e depois
        Serial.write(c);                    // imprima-o no monitor serial
        header += c;
        if (c == '\n') {                    // se o byte for um caractere de nova linha
          // se a linha atual estiver em branco, você terá dois caracteres de nova linha seguidos.
          // como é o fim da solicitação HTTP do cliente, envie uma resposta:
          if (currentLine.length() == 0) {
            // Os cabeçalhos HTTP sempre começam com um código de resposta (por exemplo, HTTP / 1.1 200 OK)
            // e um tipo de conteúdo para que o cliente saiba o que está por vir e, em seguida, uma linha em branco:
//            client.println("Pagina OK");
            client.println("HTTP / 1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");    
            client.println();

             client.println("<!DOCTYPE html>");
             client.println("<html>");
            client.println("<read>");
                           
             client.println("<title>P&aacutegina do TCC</title");
             
             client.println("</read>");
             client.println("<body background=https://heypeppers.com.br/blog/wp-content/uploads/2017/04/74950-robotica-educacional-entenda-o-que-e-e-quais-sao-os-ganhos-no-seu-aprendizado-1.jpg > ");     
             client.println("</br>");
             client.println("<body>");
             client.println("<H1><CENTER> P&aacutegina do TCC </CENTER></H1>");
             client.println("<H1><CENTER> Controle da sua casa <CENTER></H1>");
             client.println("<br>");
             client.println("</body>");
            client.println("</htmal>"); 



               
            // liga e desliga os GPIOs
            if (header.indexOf("GET /Sala/on") >= 0) {  //No local de sala pode ser mudado para o desejado 
              Serial.println("Sala on");
              output1State = "on";
              digitalWrite(output1, HIGH);
            } else if (header.indexOf("GET /Sala/off") >= 0) {
              Serial.println("Sala off");
              output1State = "off";
              digitalWrite(output1, LOW);
            } else if (header.indexOf("GET /Quarto/on") >= 0) {  //No local de Quarto pode ser mudado para o desejado
              Serial.println("Quarto on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /Quarto/off") >= 0) {
              Serial.println("Quarto off");
              output2State = "off";
              digitalWrite(output2, LOW);
            }
             else if (header.indexOf("GET /Luz da garagem/on") >= 0) {  //No local de Luz da garagem pode ser mudado para o desejado
              Serial.println("Luz da garagem on");
              output3State = "on";
              digitalWrite(output3, HIGH);
            } else if (header.indexOf("GET /Luz da garagem/off") >= 0) {
              Serial.println("Luz de garagem off");
              output3State = "off";
              digitalWrite(output3, LOW);
            }
               else if (header.indexOf("GET /Tomada ligada/on") >= 0) { //No local de tomada ligada pode ser mudado para o desejado
              Serial.println("tomada ligada");
              output4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /Tomada desligada/off") >= 0) {
              Serial.println("tomada desligada");
              output4State = "off";
              digitalWrite(output4, LOW);
            }
            
            // Exibir a página da web em HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS para estilizar os botões liga / desliga
            // Sinta-se à vontade para alterar os atributos de cor de fundo e tamanho da fonte para atender às suas preferências
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            
            // Exibir estado atual e botões ON / OFF para GPIO D0 
            client.println("<B><p>Sala - State " + output1State + "</p></B>");
            // Se o output5State estiver desativado, ele exibirá o botão ON      
            if (output1State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Exibir estado atual e botões ON / OFF para GPIO  D1  
            client.println("<B><p>Quarto - State " + output2State + "</p></B>");
            // Se o output4State estiver desativado, ele exibirá o botão ON       
            if (output2State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            //  Exibir estado atual e botões ON / OFF para GPIO D2
             client.println("<B><p>Luz da garagem - State " + output3State + "</p></B>");
            // Se o output3State estiver desativado, ele exibirá o botão ON / OFF PARA GPIO        
            if (output3State=="off") {
              client.println("<p><a href=\"/3/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/3/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            //  Exibir estado atual e botões ON / OFF para GPIO D3  
            client.println("<B><p>Tomado - State " + output4State + "</p></B>");
            //  Se o output2State estiver desativado, ele exibirá o botão ON       
            if (output4State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</b>");
            client.println("<H3><CENTER> Acredita no seu potencial!! <CENTER></H3>");
            
            client.println("</body></html>");
           
             
            // A resposta HTTP termina com outra linha em branco
            client.println();
            // Quebre o loop while
            break;
          } else { // se você recebeu uma nova linha, limpe currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // se você tiver mais alguma coisa além de um caractere de retorno de caracter,
          currentLine += c;      // adicione-o ao final do currentLine
        }
      }
    }
    // Limpe a variável de cabeçalho
    header = "";
    // Feche a conexão
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

}
