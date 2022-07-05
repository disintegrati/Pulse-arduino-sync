#GUIDA PER INSERIRE IL CODICE SU ARDUINO

Ciao,
per prima cosa scaricati arduino ide 2.0, lo trovi in questo [link](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing).
Una volta installato procedi in questo modo:
1. Scarica la cartella intitolata Pulse-arduino-sync che trovi dentro questa repository;
2. Aprila e accedici sopra;
3. Vai su File/Preferenze e inserisci questo codice su *Additional boards manager URLS*:
> http://arduino.esp8266.com/stable/package_esp8266com_index.json
4. Adesso installa le librerie che mancano andando sulla sinistra e clicca sulla terza icona _Library manager_
5. Se hai un ESP8266-01s controlla di avere un programmatore con pulsante e prima di inserire il programmatore equipaggiata dall'ESP tieni premuto il pulsante e conta 2 secondi dopo averlo inserito;
6. Adesso vai a riga 17 e sostiuisci le *XXX* con il nome dell'insegna del luogo dove l'andrai a mettere;
7. Clicca sul pulsante _UPLOAD_ ed attendi il caricamento e il gioco è fatto

