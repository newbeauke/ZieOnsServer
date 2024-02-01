Welkom bij de repo voor ZieOns, het slimme IoT project dat het mogelijk maakt om bezoekers van het ZieDit evenement te monitorenn
Om het systeem klaar te maken voor een event kunnen de volgende installatieinstructies worden gebruikt.

Server en database:

De server en database draaien op een laptop die lokaal aanwezig is gedurende het evenement. Deze dient verbonden te zijn met hetzelfde WiFi-netwerk als de ESP32's.
- Ga naar de Build folder in deze repository en download ZieOnsServer.exe, voer deze uit op de laptop.
- Ga naar https://localhost:5000 in een webbrowser.

ESP32's:

De software op de ESP32's dient geüpdatet te worden om verbinding te maken met het juiste WiFi-netwerk. Download en installeer eerst de Arduino IDE van https://www.arduino.cc/en/software.
Ga in de IDE naar je Board Manager, en selecteer de 'AI Thinker ESP32 Cam'.
