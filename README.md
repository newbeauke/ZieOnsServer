Welkom bij de repo voor ZieOns, het slimme IoT project dat het mogelijk maakt om bezoekers van het ZieDit evenement te monitoren.
Om het systeem klaar te maken voor een event kunnen de volgende installatie instructies worden gebruikt.


**Backend webserver:**

De server en database draaien op een laptop die lokaal aanwezig is gedurende het evenement. Deze dient verbonden te zijn met hetzelfde WiFi-netwerk als de ESP32's.
- Ga naar de Build folder in deze repository en download ZieOnsServer.exe, voer deze uit op de laptop.
- Ga naar http://localhost:5000 in een webbrowser om de front-end te openen.


**Database:**

Voor de server om data op te kunnen slaan dient eenmaalig MongoDB lokaal geïnstalleerd te worden. Dit gebeurt als een 'service' onder Windows, wat wil zeggen dat je deze niet handmatig hoeft op te starten. Een eenmalige installatie is voldoende.
- Volg de installatie instructies op https://www.mongodb.com/docs/manual/tutorial/install-mongodb-on-windows/ onder 'Install MongoDB Community Edition'.


**ESP32's:**

De software op de ESP32's dient geüpdatet te worden om verbinding te maken met het juiste WiFi-netwerk.
- Download en installeer eerst de Arduino IDE van https://www.arduino.cc/en/software.
- Ga in de IDE naar je Board Manager, en download de add-on voor ESP32's van Espressif Systems. Selecteer dan de 'AI Thinker ESP32 Cam'.
- Verbind de ESP32 met je laptop doormiddel van een micro-usb kabel en selecteer de juiste COM-poort.
- Open 'ESP32_CAM_SNAP.ino' in de ESP32 folder van deze repo in de IDE en update het IP in de 'serverName' met het lokale IP-adres van je laptop (te vinden met Win+R> cmd > ipconfig > en zoek naar 'IPv4 Address' onder het kopje Wi-Fi adapter)'.
- Stel de SSID en het wachtwoord in op je WiFi-netwerk.
- Elke ESP32 heeft een eigen ID, dit staat voor de index van de poster waarmee deze wordt geassocieerd. Zet deze in de 'espId'.
- Upload de code vervolgens naar de ESP32. Raadpleeg eventueel https://support.arduino.cc/hc/en-us/articles/4733418441116-Upload-a-sketch-in-Arduino-IDE.


**D3 Frontend:**

- Download het project: Download het project en sla het op in een map op je computer.
- Open de Verkenner: Ga naar de map "/D3" waarin de D3 frontend applicatie zich bevindt.
- Shift + Rechtermuisknop: Houd de Shift-toets ingedrukt en klik met de rechtermuisknop in de map. Kies de optie "Open PowerShell-venster hier" of "Open Opdrachtvenster hier", afhankelijk van je Windows-versie.
- Installeer Live Server (indien nodig): Als Live Server nog niet is geïnstalleerd, voer dan het commando 'npm install -g live-server uit' in het geopende PowerShell- of Opdrachtvenster en druk op Enter.
- Start Live Server: Voer het commando 'live-server' uit en druk op Enter.
- Bekijk de applicatie: Open je webbrowser en ga naar het adres dat wordt weergegeven in het PowerShell- of Opdrachtvenster, meestal iets als http://127.0.0.1:8080/index.html.


**Het starten van een evenement:**

- Zorg dat alle ESP32's up-to-date zijn met het juiste WiFi-netwerk
- Plaats de ESP32's boven elke poster op ca. 2 meter afstand van de grond, op een hoek van 15-30 graden naar beneden gericht voor het beste resultaat, en zorg dat de ruimte voldoende verlicht is.
- Voorzie de ESP32's van stroom en ze zullen automatisch verbinden met de server.
- Start de webserver op de laptop en ga naar http://localhost:5000 in een webbrowser om de front-end te openen.
- Ga naar de pagina 'Posters' om deze te beheren en nieuwe aan te maken. Upload een preview afbeelding van de poster en maak deze aan. De 4 recentste foto's van elke ESP32 boven een poster zullen automatisch getoond worden in de tabel. Hervers regelmatig de webpagina.


**Open de server code voor wijzigingen:**

Wanneer je de server code wil wijzigen, download dan deze volledige repo en open hem in Visual Studio 2022 met het ASP.NET pakket geïnstalleerd. Dubbelklik op de .sln solution file om hem in VS voor te bereiden.


**Data Field Test importeren:**
- Zorg dat (lokaal) een MongoDB database draaiende is. Indien dit niet het geval is, volg dan de eerdere stap om een MongoDB database te installeren.
- Start MongoDB op en verbind met de applicatie (MongoDB).
- Klik op 'Create Database' en maak vervolgens een nieuwe database aan genaamd: **ZieOns**.
- In dezelfde stap typ je bij 'Collection Name': **Posters**.
- Navigeer naar de net aangemaakte database (ZieOns) en klik op 'Create Collection'. Typ 
  hier vervolgens: **Snapshots**.

- De volgende stap is het importeren van de CSV bestanden. Gebruik hiervoor de zip-file (aangeleverd door docent), unzip het bestand en gebruik het wachtwoord: *Brightl@nds!2024* om het bestand vervolgens te unlocken.
- Klik binnen de database (ZieOns) op *Posters* en vervolgens op 'ADD DATA'. Importeer hier het **ZieOns.Posters.csv** bestand.
- Klik nu binnen de database (ZieOns) Op *Snapshots* en vervolgens op 'ADD DATA'. Importeer hier het **ZieOns.Snapshots.csv** bestand.
- De data van de gehouden Field Test is nu geïmporteerd.


**Documentatie Project:**

Documentatie met betrekking tot dit project is terug te vinden in deze repository binnen de map **Documentatie**.
