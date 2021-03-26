# Kugelspiel
Meine Abschlussaufgabe des Moduls "Grundlagen der Programmierung" an der HTWK Leipzig.

Aufgabenstellung:
Stellen Sie sich ein Spiel vor, das auf einem Raster mit 8x7 Feldern gespielt wird. Es gibt zwei
Spieler, die jeweis 14 Kugeln, der erste Spieler weisse, der zweite schwarze, erhaelt die wie folgt
angeordnet auf dem Spielfeld liegen:

  12345678
A WW....SS
B WW....SS
C WW....SS
D WW....SS
E WW....SS
F WW....SS
G WW....SS

Der weisse Spieler faengt an und es wird abwechselnd eine Kugel gezogen. Die Kugel darf vertikal
oder horizontal um ein Feld verschoben werden. Liegt in dieser Richtung bereits eine Kugel, so
darf die eigene Kugel dann auf das Feld verschoben werden, wenn dadurch nicht mehr als 2
Kugeln verschoben werden muessen. Am Beispiel:

..WS... weiss darf nach rechts verschoben werden. ...WS..
..WSS.. weiss darf nach rechts verschoben werden. ...WSS.
..WSSS. weiss darf nicht verschoben werden, da vier weitere Kugeln verschoben werden muessten.
..WSW.. weiss darf nach rechts verschoben werden: ...WSW.

Ziel des Spieles ist es, fuenf Kugeln des Gegners aus dem Spielfeld zu schieben. Wer dies zuerst
erreicht hat, hat gewonnen.
Implementieren Sie das Spiel so, dass zwei Spieler gegeneinander spielen koennen. Die Zuege sollen
also "A1 A2" eingegeben werden. Der Rechner soll die Gueltigkeit der Zuege ueberpruefen und im
Fehlerfall eine Neueingabe verlangen. Nach jedem Spielzug soll das Spielfeld neu ausgegeben
werden. Durch Eingabe von "S" soll das aktuelle Spielfeld und der aktuelle Spieler, der am Zug
ist, in eine Datei abgespeichertw werden. Durch Eingabe von "L" soll diese Datei wieder geladen
werden koennen, um das Spiel spaeter fortzusetzen.
