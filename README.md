Welkom bij de repo voor ZieOns, het slimme IoT project dat het mogelijk maakt om bezoekers van het ZieDit evenement te monitorenn
Om het systeem klaar te maken voor een event kunnen de volgende installatieinstructies worden gebruikt.


**Backend webserver**

De server en database draaien op een laptop die lokaal aanwezig is gedurende het evenement. Deze dient verbonden te zijn met hetzelfde WiFi-netwerk als de ESP32's.
- Ga naar de Build folder in deze repository en download ZieOnsServer.exe, voer deze uit op de laptop.
- Ga naar https://localhost:5000 in een webbrowser om de front-end te openen.


**Database:**

Voor de server om data op te kunnen slaan dient eenmaalig MongoDB lokaal geïnstalleerd te worden. Dit gebeurt als een 'service' onder Windows, wat wil zeggen dat je deze niet handmatig hoeft op te starten. Een eenmalige installatie is voldoende.
- Volg de installatie instructies op https://www.mongodb.com/docs/manual/tutorial/install-mongodb-on-windows/ onder 'Install MongoDB Community Edition'.


**ESP32's:**

De software op de ESP32's dient geüpdatet te worden om verbinding te maken met het juiste WiFi-netwerk.
- Download en installeer eerst de Arduino IDE van https://www.arduino.cc/en/software.
- Ga in de IDE naar je Board Manager, en download de add-on voor ESP32's van Espressif Systems. Selecteer dan de 'AI Thinker ESP32 Cam'.
- Verbind de ESP32 met je laptop doormiddel van een micro-usb kabel en selecteer de juiste COM-poort.
- Open 'ESP32_CAM_SNAP.ino' in de ESP32 folder van deze repo in de IDE en update het IP in de 'serverName' met het lokale IP-adres van je laptop.
- Stel de SSID en het wachtwoord in op je WiFi-netwerk.
- Elke ESP32 heeft een eigen ID, dit staat voor de index van de poster waarmee deze wordt geassocieerd. Zet deze in de 'espId'.
- Upload de code vervolgens naar de ESP32. Raadpleeg eventueel https://support.arduino.cc/hc/en-us/articles/4733418441116-Upload-a-sketch-in-Arduino-IDE.


**Het starten van een evenement:**

- Zorg dat alle ESP32's up-to-date zijn met het juiste WiFi-netwerk
- Plaats de ESP32's boven elke poster op ca. 2 meter afstand van de grond, op een hoek van 15-30 graden naar beneden gericht voor het beste resultaat, en zorg dat de ruimte voldoende verlicht is.
- Voorzie de ESP32's van stroom en ze zullen automatisch verbinden met de server.
- Start de webserver.


**Open de server code voor wijzigingen:**

Wanneer je de server code wil wijzigen, download dan deze volledige repo en open hem in Visual Studio 2022 met het ASP.NET pakket geïnstalleerd. Dubbelklik op de .sln solution file om hem in VS voor te bereiden.
