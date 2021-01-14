#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h> //essa biblioteca já vem com a IDE. Portanto, não é preciso baixar nenhuma biblioteca adicional
#include <DHT.h>
#include <FS.h>

 
/*
* Defines do projeto
*/
//GPIO do NodeMCU que o pino de comunicação do sensor está ligado.
#define DHTPIN 4
#define FILE_NAME "/100.txt"
#define GET_REQ true
#define POST_REQ true
 
/* defines - wi-fi */
#define SSID_REDE "" /* coloque aqui o nome da rede que se deseja conectar */
#define SENHA_REDE "" /* coloque aqui a senha da rede que se deseja conectar */
#define INTERVALO_ENVIO_THINGSPEAK 30000 /* intervalo entre envios de dados ao ThingSpeak (em ms) */

 
/* A biblioteca serve para os sensores DHT11, DHT22 e DHT21.
* No nosso caso, usaremos o DHT22, porém se você desejar utilizar
* algum dos outros disponíveis, basta descomentar a linha correspondente.
*/
 //#define DHTTYPE DHT11 // DHT 11
#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301

 
/* constantes e variáveis globais */
char endereco_api_thingspeak[] = "api.thingspeak.com";
String chave_escrita_thingspeak = "";  /* Coloque aqui sua chave de escrita do seu canal */
unsigned long last_connection_time;
int pos=0;  // for readLine function
WiFiClient client;
DHT dht(DHTPIN, DHTTYPE);
 
/* prototypes */
void postRequestWiFiClass(bool underTest, String linha);
void getRequestWiFiClass(bool underTest, String linha);
void postRequestHTTPClass(bool underTest, String linha);
void getRequestHTTPClass(bool underTest, String linha);
void init_wifi(void);
void conecta_wifi(void);
void checkClientAvailability(void);
String readLine();

/* Função: envia informações ao ThingSpeak via requisicoes HTTP pelo metodo POST utilizando classe **WiFiClient**
* Parâmetros:
*   bool para escolher servidor proprio (false) ou servidor do tutorial (true) 
*   String com a informação a ser enviada
* Retorno: nenhum
*/
void postRequestWiFiClass(bool underTest, String linha){
    String msg, url, route;
    String contentType;
    uint16_t port;
    if(underTest){
      url = "api.thingspeak.com";
      port = 80;
      route = "/update";
      msg = linha;
      contentType = "application/x-www-form-urlencoded";
    }else{
      url = "http://ecgremoto.herokuapp.com";
      port = 80;
      route = "/demo";
      msg = "{\"data\":\"";   msg += linha;     msg += "\"}";
      contentType = "application/json";
    }
    
    if (client.connect(url, port)){
        if (client.connected()) {
          Serial.print("vai fazer o POST em ");
          Serial.println(url);
          /* faz a requisição HTTP ao ThingSpeak */
          client.print("POST ");      client.print(route);        client.print(" HTTP/1.1\n");
          client.print("Host: ");     client.print(url);     client.print("\n");
          client.print("Connection: close\r\n");
          client.print("X-THINGSPEAKAPIKEY: "+chave_escrita_thingspeak+"\n");
          client.print("Content-Type: ");   client.print(contentType);     client.print("\n");
          client.print("Content-Length: ");
          client.print(msg.length());
          client.print("\n\n");
          client.print(msg);
        }else{
          Serial.println("Problems");
        }
        
       checkClientAvailability();

        Serial.println("Respond:");
        while (client.available()) {
          char ch = static_cast<char>(client.read());
          Serial.print(ch);
        }
        Serial.println();
    }else{
      Serial.print("Cannot connect to ");
      Serial.print(url);
      Serial.print(":");
      Serial.print(port);
    }
}

/* Função: Solicita json via requisicoes HTTP pelo metodo GET utilizando classe **WiFiClient** 
* Parâmetros: 
*   bool para escolher servidor proprio (false) ou jsonplaceholder(true) 
*   String com a informação a ser enviada
* Retorno: nenhum
*/
void getRequestWiFiClass(bool underTest, String linha) {
    String msg, url, route;
    uint16_t port;
    if(underTest){
      url = "djxmmx.net";
      port = 17;
      route = "/";
//      msg = "{\"data\":\"";   msg += linha;     msg += "\"}";
    }else{
      url = "ecgremoto.herokuapp.com";
      port = 80;
      route = "/";
//      msg = "{\"data\":\"";   msg += linha;     msg += "\"}";
    }
    Serial.print("Vai conectar com o site ");
    Serial.println(url);
    if (client.connect(url, port))
    {
        if (client.connected()) {
          Serial.println("vai fazer o GET");
          /* faz a requisição HTTP ao ThingSpeak */
          client.print("GET ");      client.print(route);        client.print(" HTTP/1.1\n");
          client.print("Host: ");     client.print(url);     client.print("\n");
//          client.print("User-Agent: Andre del Mestre\n");
//          client.print("Accept: */*");
        }else{
          Serial.println("Problems");
        }
        
        checkClientAvailability();
      
        Serial.println("Respond:");
        while (client.available()) {
          char ch = static_cast<char>(client.read());
          Serial.print(ch);
        }
        Serial.println();
    }else{
      Serial.println("Nao conseguiu conectar...");      
    }
}

/* Função: envia informações ao ThingSpeak via requisicoes HTTP pelo metodo POST utilizando classe **HTTPClient**
* Parâmetros:
*   bool para escolher servidor proprio (false) ou servidor do tutorial (true) 
*   String com a informação a ser enviada
* Retorno: nenhum
*/
void postRequestHTTPClass(bool underTest, String linha) {
  String msg;
  int httpCode;
  String payload;

  WiFiClient localClient; //Declarei um objeto local de HTTPClient para nao dar pau com o objeto global 'client'
  HTTPClient http;    //Declare object of class HTTPClient
  if(underTest){
    msg = "{\"api_key\":\"tPmAT5Ab3j7F9\"}";
    http.begin(localClient, "http://jsonplaceholder.typicode.com/posts");  //Specify request destination
//      http.begin(localClient, "http://jsonplaceholder.typicode.com/", 80, "/posts/1");  //Specify request destination
  }else{
    msg = "{\"data\":\""+linha+"\"}";
    http.begin(localClient, "http://ecgremoto.herokuapp.com/demo");  //Specify request destination
//      http.begin(localClient, "http://ecgremoto.herokuapp.com", 3333, "/demo");  //Specify request destination
  }
  
  Serial.print("Try a POST. msg: ");   //Print msg
  Serial.println(msg);   //Print msg

  http.addHeader("Content-Type", "application/json");
  httpCode = http.POST(msg);
  payload = http.getString();                  //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection

  delay(3000);  
}


/* Função: Solicita json via requisicoes HTTP pelo metodo GET utilizando classe **HTTPClient**
* Parâmetros: 
*   bool para escolher servidor proprio (false) ou jsonplaceholder(true) 
*   String com a informação a ser enviada
* Retorno: nenhum
*/
void getRequestHTTPClass(bool underTest, String linha) {
  int httpCode;
  String payload;

  WiFiClient localClient;
  HTTPClient http;    //Declare object of class HTTPClient
  // If you need an HTTP request with a content type: application/json, use the following:
  if(underTest){
    http.begin(localClient, "http://jsonplaceholder.typicode.com/posts/1");  //Specify request destination
//      http.begin(localClient, "http://jsonplaceholder.typicode.com/", 80, "/users");  //Specify request destination
  }else{
    http.begin(localClient, "http://ecgremoto.herokuapp.com");  //Specify request destination
//      http.begin(localClient, "http://ecgremoto.herokuapp.com", 80, "/");  //Specify request destination
  }

  Serial.println("Try a GET.");
  
  http.addHeader("Content-Type", "application/json");
  httpCode = http.GET();
  payload = http.getString();                  //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  
  http.end();  //Close connection

  delay(3000);  
}

/* Função: inicializa wi-fi
* Parametros: nenhum
* Retorno: nenhum
*/
void init_wifi(void)
{
    Serial.println("------WI-FI -----");
    Serial.println("Conectando-se a rede: ");
    Serial.println(SSID_REDE);
    Serial.println("\nAguarde...");

   /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID_REDE, SENHA_REDE);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network ");
  Serial.println(SSID_REDE);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

    conecta_wifi();
}
 
/* Função: conecta-se a rede wi-fi
* Parametros: nenhum
* Retorno: nenhum
*/
void conecta_wifi(void)
{
    /* Se ja estiver conectado, nada é feito. */
    if (WiFi.status() == WL_CONNECTED)
    {
        return;
    }
     
    /* refaz a conexão */
    WiFi.begin(SSID_REDE, SENHA_REDE);
     
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
    }
 
    Serial.println("Conectado com sucesso a rede wi-fi \n");
    Serial.println(SSID_REDE);
}

/* Função: Verifica se servidor ainda esta online
* Funcao importante, pois a mensagem enviada ao cliente pode causar problemas na coneccao.
*   Exemplo: NAO use '\r' para quebra de linha
* Retorno: nenhum
*/
void checkClientAvailability(){
    // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(30000);
      return;
    }
  }
}

/* Função: Le uma linha do arquivo a partir da posicao 'pos'
* Parametros: nenhum
* Retorno: String com uma linha do arquivo
*/
String readLine(){
  File file = SPIFFS.open(FILE_NAME, "r");
  String line;
  char ch;
  if(!file){
    Serial.println("Failed to open file for reading");
    return "-1";
  }

  file.seek(pos, SeekCur);

  while(file.available()){
    ch = file.read();
    if(ch == '\n'){     // found end of line
      pos = file.position();  // save 'pos' for next readings
      file.close();
      return line;
    }
    line += ch;
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(2000);
  delay(2000);
  // Wait for serial to initialize.
  while (! Serial);

  Serial.println("Device Started");
  Serial.println("-------------------------------------");
  
  last_connection_time = 0;

  /* Inicializa e conecta-se ao wi-fi */
  init_wifi();

  /* Inicializa a memoria flash*/
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
}
 
//loop principal
void loop()
{
//    float temperatura_lida = 0.0;
//    float umidade_lida = 0.0;
    boolean underTest = false;
 
    /* Força desconexão ao ThingSpeak (se ainda estiver conectado) */
    if (client.connected())
    {
        client.stop();
        Serial.println("- Desconectado do cliente");
        Serial.println();
    }
 
    /* Garante que a conexão wi-fi esteja ativa */
    conecta_wifi();
     
    /* Verifica se é o momento de enviar dados para o ThingSpeak */
    if( millis() - last_connection_time > INTERVALO_ENVIO_THINGSPEAK )
    {
        String line = readLine();       //LEU A LINHA COM O CONTEUUDO
        String fields_a_serem_enviados = "field1=0.0&field2=0.0&field3=";
      
        // VERIFICA SE EH DADO NUMERICO OU CABECALHO 
        if(line[0]>='0' && line[0]<='9'){

          Serial.println("#############################################");
          Serial.println("# PART 1 - http requests by using HTTPClass #");
          Serial.println("#############################################");

          if(GET_REQ){
            getRequestHTTPClass(underTest, line);
          }

          if(POST_REQ){
            postRequestHTTPClass(underTest, line);
          }
          
          Serial.println("#############################################");
          Serial.println("# PART 2 - http requests by using WiFiClass #");
          Serial.println("#############################################");

          if(GET_REQ){
            getRequestWiFiClass(underTest, line);
          }

          if(POST_REQ){
            if(underTest){
              fields_a_serem_enviados += line;
              postRequestWiFiClass(true, fields_a_serem_enviados);
            }else{
              postRequestWiFiClass(false, line);
            }
          }

          last_connection_time = millis(); 
        }
//  QUANDO EU CONSEGUIR UM SENSOR QUE FUNCIONE, DESCOMENTO E USO ESSE TRECHO        
//        sprintf(fields_a_serem_enviados,"field1=%.2f&field2=%.2f", temperatura_lida, umidade_lida);
//        Serial.print("temp = ");
//        Serial.println(temperatura_lida);
//        Serial.print("umid = ");
//        Serial.println(umidade_lida);
  
    }
 
    delay(1000);
}
