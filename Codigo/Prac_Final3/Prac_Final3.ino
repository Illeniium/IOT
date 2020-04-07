#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Ticker.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <DHT.h>
#include <SoftwareSerial.h>
#include <Servo.h>

//SERVO MOTOR
#define SERVOPIN 15
#define SERVOPIN2 1
#define PULSOMIN 450
#define PULSOMAX 2550
Servo servoMotor;
Servo servoMotor2;

int RX = 0;
int TX = 2;
char dato;

SoftwareSerial myBT(RX,TX);

//VARIABLES DEL LED WIFI
#define pinLedWifi 2
#define pinLed 13

float ledDistancia = 15;

//VARIABLES DEL SONAR 
#define pinEnvia 14
#define pinRecibe 12
float distancia;
int serieDistancia = 1;  

//VARIABLES DEL DHT11
#define pinDht 3
#define typeDht DHT11
DHT dht(pinDht, typeDht); //CLASE
float h = 0;
float t = 0;
int serieTemperatura = 1;  
int serieHumedad = 1;  

//VARIABLES DE LA FOTORRESISTENCIA 
#define LDRPIN A0
int valorLDR = 0;
int serieFotoresistencia = 1;  

//DEFINICION AREGLOS PARA LOS SENSORES  
#define TamArr 5
float distanciaArr[TamArr];
float temperaturaArr[TamArr];
float humedadArr[TamArr];
float fotoResistenciaArr[TamArr];

//VARIABLES DE CONTADORES
int con1 = -1;
int con2 = -1;
int con3 = -1;
int con4 = -1;

//VARIABLES MILLIS
unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;
unsigned long tiempo3 = 0;
unsigned long tiempo4 = 0;


//VARIABLES DE PROMEDIO
float promedioDistancia;
float promedioResistencia;
float promedioTemperatura;
float promedioHumedad;

//VARIABLES DE LA RED
HTTPClient http;
WiFiManager wifiManager;
#define httpPort 80
String host = "192.168.1.88";
String url = "/ServidorIOT/clsArduino.php";  
String payload;

//CLASE DE LA PANTALLA LCD 
LiquidCrystal_I2C lcd(0x27, 20, 4);

//DEFINICION DE TICKERS 
Ticker ticWifiLed;
Ticker ticSonar;
Ticker ticTemperatura;
Ticker ticHumedad;

//FUNCIONES 

//FUNCION PARA CONECTAR WIFI
void parpadearLedWifi() {
  byte estado = digitalRead(pinLedWifi);
  digitalWrite(pinLedWifi, !estado);
}

//FUNCION DEL SONAR
double funDistancia(int pinSalida, int pinEntrada){
  double distancia,t;
  digitalWrite(pinSalida,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinSalida,LOW);
  t=pulseIn(pinEntrada,HIGH);
  distancia=t/58.3;
  if(distancia <=400 && distancia>=2)
  {
    return distancia;
  }else 
    return -1;
}

void funLedDistancia(){
  //LECTURA PARA ANGULO DE LOS SERVOMOTORES MEDIANTE PETICIONES AL HOST
  if(http.begin("http://192.168.1.88/ServidorIOT/clsArduino.php?OPCION=10")) //Iniciar conexión
  {
    int httpCode = http.GET();  // Realizar petición
 
    if (httpCode > 0) {
        
      Serial.printf("[HTTP] Numero de respueta: %d\n", httpCode);
 
      if(httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        
        payload = http.getString();   // Obtener respuesta
        Serial.println(payload);   // Mostrar respuesta por serial
        int dis = payload.toInt();

        //LECTURA DE SERVOMOTOR
        ledDistancia = dis;
        
      }
    }
    else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
  else {
    Serial.printf("[HTTP} Unable to connect\n");
  }
}


void funSonarArr (){
  
  distancia = funDistancia(pinEnvia, pinRecibe);
  if(distancia != -1){
    con1++;
    if(con1 < (TamArr -1)){
      distanciaArr[con1] = distancia;
    }
    else
    {
      con1 = -1;
      for(int i = 0; i < (TamArr -1) ; i++){
          promedioDistancia = promedioDistancia + distanciaArr[i];
      }

      promedioDistancia = promedioDistancia / (TamArr -1);
   
      lcd.setCursor(11,1);
      lcd.print("       ");
      lcd.setCursor(11,1);
      lcd.print(String(promedioDistancia));

      WiFiClient client;
      const int puerto = 80;
      String url = "/ServidorIOT/clsArduino.php"; 

      if(!client.connect(host, httpPort))
      {
        Serial.println("Conexion fallida");
        return;
      }

      //PETICION DE PROMESA PARA LA INSERCIONDE DATOS
      String data = "txtSerie="+ String(serieDistancia) + "&txtDistancia=" + String(promedioDistancia);
  
      String peticion = String("POST ") + url + "?OPCION=4" + " HTTP/1.0\r\n" + 
                "Host: " + host + "\r\n" + 
                "Accept: *" + "/" + "*\r\n" +
                "Content-Length: " + data.length() + "\r\n" +
                "Content-Type: application/x-www-form-urlencoded; \r\n" +
                "\r\n" + data;
      Serial.println(peticion);
      client.print(peticion);
      
      serieDistancia++; 
    }

    if(distancia < ledDistancia){
      digitalWrite(pinLed, 1);
    }else{
      digitalWrite(pinLed, 0);
    }
  }
  Serial.print("DISTANCIA:");
  Serial.println(distancia);
  Serial.println(promedioDistancia);
}

void funTemperaturaArr (){

  //LECTURA DE LA TEMPERATURA
  t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  }
  else
  {
    con2++;
  
    if(con2 < (TamArr -1)){
      temperaturaArr[con2] = t;
    }
    else
    {
      con2 = -1;
      for(int i = 0; i < (TamArr -1) ; i++){
        promedioTemperatura = promedioTemperatura + temperaturaArr[i];
      }
  
      promedioTemperatura = promedioTemperatura / TamArr;

      lcd.setCursor(6,2);
      lcd.print("       ");
      lcd.setCursor(6,2);
      lcd.print(String(promedioTemperatura));

      WiFiClient client;
      const int puerto = 80;
      String url = "/ServidorIOT/clsArduino.php"; 

      if(!client.connect(host, httpPort))
      {
        Serial.println("Conexion fallida");
        return;
      }

      //PETICION DE PROMESA PARA LA INSERCIONDE DATOS
      String data = "txtSerie="+ String(serieTemperatura) + "&txtTemperatura=" + String(promedioTemperatura);
  
      String peticion = String("POST ") + url + "?OPCION=2" + " HTTP/1.0\r\n" + 
                "Host: " + host + "\r\n" + 
                "Accept: *" + "/" + "*\r\n" +
                "Content-Length: " + data.length() + "\r\n" +
                "Content-Type: application/x-www-form-urlencoded; \r\n" +
                "\r\n" + data;
      Serial.println(peticion);
      client.print(peticion);
      
      serieTemperatura++; 
    }
  }
  Serial.print("TEMPERATURA:");
  Serial.println(t);
  Serial.println(promedioTemperatura);
}

void funHumedadArr (){
  //LECTURA DE LA HUMENEDAD
  h = dht.readHumidity();

  if (isnan(h)) {
    Serial.println(F("Failed to read from DHT sensor!"));
  }
  else
  {
    con3++;
  
    if(con3 < (TamArr -1)){
      humedadArr[con3] = h;
    }
    else
    {
      con3 = -1;
      for(int i = 0; i < (TamArr -1) ; i++){
        promedioHumedad = promedioHumedad + humedadArr[i];
      }
  
      promedioHumedad = promedioHumedad / TamArr;
     
      lcd.setCursor(5,3);
      lcd.print("       ");
      lcd.setCursor(5,3);
      lcd.print(String(promedioHumedad));

      WiFiClient client;
      const int puerto = 80;
      String url = "/ServidorIOT/clsArduino.php"; 

      if(!client.connect(host, httpPort))
      {
        Serial.println("Conexion fallida");
        return;
      }

      //PETICION DE PROMESA PARA LA INSERCIONDE DATOS
      String data = "txtSerie="+ String(serieHumedad) + "&txtHumedad=" + String(promedioHumedad);
  
      String peticion = String("POST ") + url + "?OPCION=3" + " HTTP/1.0\r\n" + 
                "Host: " + host + "\r\n" + 
                "Accept: *" + "/" + "*\r\n" +
                "Content-Length: " + data.length() + "\r\n" +
                "Content-Type: application/x-www-form-urlencoded; \r\n" +
                "\r\n" + data;
      Serial.println(peticion);
      client.print(peticion);
      
      serieHumedad++; 
    }
  }
  Serial.print("HUMADA:");
  Serial.println(h);
  Serial.print(promedioHumedad);
}

void funFotoResistenciaArr (){
  promedioResistencia = 0;

  valorLDR = analogRead(LDRPIN); 
  
  if(valorLDR != -1){
    con4++;
    if(con4 < (TamArr -1)){
      fotoResistenciaArr[con4] = valorLDR;
    }
    else
    {
      con4 = -1;
      for(int i = 0; i < (TamArr -1) ; i++){
          promedioResistencia = promedioResistencia + fotoResistenciaArr[i];
      }

      promedioResistencia = promedioResistencia / TamArr;

      WiFiClient client;
      const int puerto = 80;
      String url = "/ServidorIOT/clsArduino.php"; 

      if(!client.connect(host, httpPort))
      {
        Serial.println("Conexion fallida");
        return;
      }

      //PETICION DE PROMESA PARA LA INSERCIONDE DATOS
      String data = "txtSerie="+ String(serieFotoresistencia) + "&txtLuminosidad=" + String(promedioResistencia);
  
      String peticion = String("POST ") + url + "?OPCION=1" + " HTTP/1.0\r\n" + 
                "Host: " + host + "\r\n" + 
                "Accept: *" + "/" + "*\r\n" +
                "Content-Length: " + data.length() + "\r\n" +
                "Content-Type: application/x-www-form-urlencoded; \r\n" +
                "\r\n" + data;
      Serial.println(peticion);
      client.print(peticion);
      
      serieFotoresistencia++; 
      
    }
  }
  Serial.print("Luminosidad: ");
  Serial.println(valorLDR); 
  Serial.println(promedioResistencia);
}



void setup() {
  
  Serial.begin(115200);
  Serial.println("");
  myBT.begin(38400);
  
  //INICIALIZACION DE LA PANTALLA LCD
  lcd.init();
  lcd.backlight();

  //AVILITACION DEL LED WIFI
  pinMode(pinLedWifi, OUTPUT);
  pinMode(pinLed, OUTPUT);
  
  //AVILITADOR DEL SONAR
  pinMode(pinEnvia, OUTPUT);
  pinMode(pinRecibe, INPUT);
  digitalWrite(pinEnvia, LOW);

  //INICIALIZACION DE LA CONEXION A LA RED
  lcd.setCursor(0,0);
  lcd.print("Buscando WIFI..");
  ticWifiLed.attach(0.2, parpadearLedWifi);

  //AVILITACION DEL WIFIMANAGER
  wifiManager.autoConnect("Tavo", "12345678");
  Serial.print("Ya estas conectado");

  //DESABILITACION DEL TICLED
  ticWifiLed.detach();
  digitalWrite(pinLedWifi, 1);

  //MENSAJE NUEVO 
  Serial.print("Conectado a la red ");
  Serial.println(WiFi.SSID());
  lcd.setCursor(0,0);
  lcd.print("                 ");
  lcd.setCursor(0,0);
  lcd.print(String("Red: " +  WiFi.SSID()));

  //AVILITACION DEL SONAR EL LA PANTALLA LCD
  lcd.setCursor(0,1);
  lcd.print("Distancia:");
  digitalWrite(pinEnvia,LOW);
  //ticSonar.attach(0.1,funSonarArr);

  //AVILITACION DE LA TEMPERATURA
  lcd.setCursor(0,2);
  lcd.print("Temp:");
  //ticTemperatura.attach(0.1,funTemperaturaArr);

  //AVILITACION DE LA HUMEDAD
  lcd.setCursor(0,3);
  lcd.print("Hum:");
  //ticHumedad.attach(0.1,funHumedadArr);

  //SERVOMOTOR
  servoMotor.attach(SERVOPIN,PULSOMIN,PULSOMAX);
  servoMotor2.attach(SERVOPIN2,PULSOMIN,PULSOMAX);

  //INICIALIZACION DE TIEMPO
  tiempo1 = millis();
  tiempo2 = millis();
  tiempo3 = millis();
  tiempo4 = millis();

}

void loop() {

  if(myBT.available())
  {
    dato = myBT.parseInt();
    Serial.print(dato);
    servoMotor.write(dato);
  }

  if(millis() > tiempo1 + 200){
    tiempo1 = millis();
    funFotoResistenciaArr();
  }
  
  if(millis() > tiempo2 + 200){
    tiempo2 = millis();
    funTemperaturaArr();
  }

  if(millis() > tiempo3 + 200){
    tiempo3 = millis();
    funHumedadArr();
  }

  if(millis() > tiempo4 + 200){
    tiempo4 = millis();
    funSonarArr();
  }

  funLedDistancia();
  
}
