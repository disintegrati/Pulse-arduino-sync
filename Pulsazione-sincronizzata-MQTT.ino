#include <SPI.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>

// Update these with values suitable for your hardware/network.
IPAddress server(167,71,79,43);

//il pin che viene usato
int ledPin = 0;

//serve per la luminosità massima (diminuisci con 2/3/1 oppure usa float per i numeri decimali)
int m = 4; 

long lastReconnectAttempt = 0;
long lastPulse = 0;
long now = 0;
char nomeClient[20] = "XXX"; //qui inserisci il nome dell'insegna 

// Questa callback è esattamente la funzione che viene chiamata nel momento in cui riceve un messaggio
void callback(char* topic, byte* payload, unsigned int length) {
  
  now = millis();
  Serial.println("Ricevo messaggio\n");
  pulsa();
  
}

WiFiClient wifiClient;
PubSubClient client(wifiClient);

boolean reconnect() {

  if (client.connect(nomeClient)) {
    //resubscribe
    client.subscribe("main");
  }
  return client.connected();

}

void setup(){

  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP

  Serial.begin(115200);

    WiFiManager wm;
    wm.setCustomHeadElement("<style>body{background:#D00C2E;color:white;}button{background:white;color:#D00C2E;}h1{color:white;}a{color:white;}:before{filter:invert(1);}:after{filter:invert(1);}</style>");
    //reset settings - wipe credentials for testing
    //wm.resetSettings();

    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    wm.setConfigPortalTimeout(5200); //imposto i secondi di limite per impostare il wifi
    res = wm.autoConnect("#CUOREDINAPOLI",""); // password protected ap

    if(!res) {

        Serial.println("Failed to connect");
        // ESP.restart();

    } 
    else {

        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");

    }
  
  client.setServer(server, 1883);
  client.setCallback(callback);
  client.connect(nomeClient);
  client.subscribe("main");

  lastReconnectAttempt = 0;
  lastPulse=0;

}


void loop(){

  now = millis();
  
  if (now - lastPulse >= 4000){
      pulsa();
      Serial.println("Fake Pulse\n");
      delay(3000);
    }

  if (!client.connected()) {

    if (now - lastReconnectAttempt > 350000) {
      Serial.println("Not connected\n");
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } 

  else {
    // Client connected

    client.loop();
  }

}

void pulsa() {

  delay(100);
  for (int i = 0; i < 255; i=i+2) {
    analogWrite(ledPin, i*m);
    delay(1);
  }
  for (int i = 255; i > 0; i=i-2) {
    analogWrite(ledPin, i*m);
    delay(1);
  }
  for (int i = 0; i < 255; i=i+2) {
    analogWrite(ledPin, i*m);
    delay(1);
  }
  delay(20*m);

  for (int i = 255; i >= 0; i--) {
    analogWrite(ledPin, i*m);
    delay(3);
  }

  lastPulse = now;

}