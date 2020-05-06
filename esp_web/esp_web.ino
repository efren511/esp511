//importamos la libreria para usar el modulo
#include <ESP8266WiFi.h>

//nuestra pagina html
String pagina = "<!DOCTYPE html>"
"<html lang='en' dir='ltr'>"
"  <head>"
"    <meta charset='utf-8'>"
"    <title>ESP511</title>"
"  </head>"
"  <body>"
"    <center>"
"      <h1><FONT SIZE=7>UwU Efren UwU</font></h1>"
"       <p><a href='/encender'><button type='button' name='encender'>ON</button></a></p>"
"       <br>"
"       <p><a href='/apagar'><button type='button' name='apagar'>OFF</button></a></p>"
"    </center>"
"  </body>"

"</html>";

//creamos variable para almacenar la solicitud
String solicitud;

//creamos nuestro servidor
WiFiServer servidor(80);

void setup(){
  //iniciamos monitor serial
  Serial.begin(115200);
  //nos conectamos a la red wifi nombre / clave
  WiFi.begin("INFINITUM3102", "PYutdsRddo");
  //mientras no estemos conectados
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //imprimimos un puntito
    Serial.print(".");
  }
  //iniciamos el servidor
  servidor.begin();
  //al terminar significa que estamos conectados
  Serial.println("\nConexion Exitosa 7w7!");
  //mostramos algunos ajustes
  Serial.print("Nuestra IP: ");
  //mostramos nuestra IP
  Serial.println(WiFi.localIP());
  //declaramos 2 como la salida
  pinMode(2, OUTPUT);
}

void loop(){
  //ajustamos los clientes con el servidor al tener datos
  WiFiClient cliente = servidor.available();
  //si un navegador se conecta
  if(cliente){
    Serial.println("Cliente conectado!");
    //mientras el cliente este conectado
    while(cliente.connected()){
      //si el cliente esta enviando datos
      if(cliente.available()){
        //leemos la informacion recibida
        solicitud = cliente.readStringUntil('\r');
        //imprimimos la solicitud
        Serial.println(solicitud);
        cliente.flush();
        //enviamos cabeceras
        cliente.println("HTTP/1.1 200 OK");
        cliente.println("Content-type:text/html");
        cliente.println("Connection: close");
        cliente.println("");
        //buscamos datos en el html uwu
        //si encontramos la palabra encender en la solicitud
        if(solicitud.indexOf("encender") != -1){
          digitalWrite(2, HIGH);
        }
        //si encontramos la palabra apagar en la solicitud
        if(solicitud.indexOf("apagar") != -1){
          digitalWrite(2, LOW);
        }
        //enviamos la pagina
        cliente.println(pagina);
        cliente.println("");
        break;
      }
    }
  }
}
