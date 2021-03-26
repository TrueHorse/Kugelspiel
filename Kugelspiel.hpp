#pragma once
#include<array>
enum class Spieler {Weiss, Schwarz};


///Instanzen dieser Klasse haben die Informationen über den Spielstand als Attribute und Methoden um diese abzufragen und zu verändern.
class Spielfeld
{
public:
    /**
    *@brief Der Konstructor setzt alle Attribute auf den Wert, den sie zu Spielbeginn haben sollen.
    *@details Die verlorenen Kugeln beider Spieler werden auf 0 gesetzt, die Ränder werden mit den Werten von 1 bis 8 bzw. A bis G
    *aufgefüllt, das Spielfeld mit der Anfangsbelegung der Kugeln belegt und Weiss als Zugspieler festgelegt.
    */
    Spielfeld();
    ///get_Zugspieler: @return Gibt den Spieler zurück, der am Zug ist.
    Spieler get_Zugspieler()const;
    ///get_verloreneKugelnW: @return Gibt die Anzahl der verlorenen Kugeln von Weiss zurück.
    int get_verloreneKugelnW()const;
    ///get_verloreneKugelnS: @return Gibt die Anzahl der verlorenen Kugeln von Schwarz zurück.
    int get_verloreneKugelnS()const;
    ///get_RandOben: @return Gibt den oberen Rand des Spielfelds zurück.
    std::array <int,8> get_RandOben()const;
    ///get_RandLinks: @return Gibt den linken Rand des Spielfelds zurück.
    std::array <char,7> get_RandLinks()const;
    ///get_Felder: @return Gibt die Kugelbelegung des Spielfelds zurück.
    std::array <std::array <char,8>,7> get_Felder()const;
    /**
    *change_Felder: @brief Ändert den Wert eines Feldes des Spielfeldes zu einem anderen Wert.
    *@param Zeile : Zeile des zu ändernden Feldes.
    *@param Spalte : Spalte des zu ändernden Feldes.
    *@param aendernZu : Wert, zu dem das Feld an der Position geändert werden soll.
    */
    void change_Felder(const int &Zeile, const int &Spalte, const char &aendernZu);
    /**
    *change_verloreneKugelnW: @brief Ändert die die Anzahl an Kugeln, die Weiss bisher verloren hat.
    *@param neuerWert : Zahl, zu der die Anzahl der verlorenen Kugeln von Weiss geändert werden soll.
    */
    void change_verloreneKugelnW(const int &neuerWert);
    /**
    *change_verloreneKugelnS: @brief Ändert die die Anzahl an Kugeln, die Schwarz bisher verloren hat.
    *@param neuerWert : Zahl, zu der die Anzahl der verlorenen Kugeln von Schwarz geändert werden soll.
    */
    void change_verloreneKugelnS(const int &neuerWert);
    /**
    *change_Zugspieler: @brief Macht den übergebenen Spieler zum Zugspieler.
    *@param neuerZugspieler : Der Spieler, der Zugspieler werden soll.
    */
    void change_Zugspieler(const Spieler &neuerZugspieler);

private:
    Spieler Zugspieler;
    int verloreneKugelnW;
    int verloreneKugelnS;
    std::array <int,8> RandOben;
    std::array <char,7> RandLinks;
    std::array <std::array<char,8>,7> Felder;
};

/**
*Spielfeldausgabe: @brief Gibt die Ränder und Felder des Spielfeldes aus.
*@param aktuellesSpielfeld : Spielfeld, dessen Ränder und Felder ausgegeben werden sollen.
*/
void Spielfeldausgabe(Spielfeld &aktuellesSpielfeld);

/**
*SpielSpeichern: @brief Fragt den Benutzer, ob das Spiel gespeichert werden soll und falls das der Fall ist, speichert sie den
*Spielstand in der Datei "gespeichertesSpiel.txt".
*@details Die Funktion fragt den Benutzer, ob das Spiel gespeichert werden soll. Dann wird die Funktion "JaNeinFrage" aufgerufen. Gibt sie 1
*zurück, löscht die Funktion die Datei "gespeichertesSpiel.txt", falls sie schon existiert, erstellt eine neue Datei
*"gespeichertesSpiel.txt" und schreibt dann alle Felder, die Anzahl der verlorenen Kugeln beider Spieler und den Zugspieler des
*Spielfelds in die Datei.
*@param aktuellesSpielfeld : Das Spielfeld, dessen Spielstand gespeichert werden soll.
*/
void SpielSpeichern(Spielfeld &aktuellesSpielfeld);

/**
*SpielLaden: @brief Fragt den Benutzer, ob das gespeicherte Spiel geladen werden soll und falls das der Fall ist, lädt sie den
*Spielstand, der in der Datei "gespeichertesSpiel.txt" gespeichert ist.
*@details Die Funktion fragt den Benutzer, ob das gespeicherte Spiel geladen werden soll. Bei der Eingabe von "J" überprüft es, ob eine
*Datei "gespeichertesSpiel.txt" existiert, auf die Zugegriffen werden kann. Falls dies nicht zutrifft wird wird dem Benutzer
*mitgeteilt, das kein gespeichertes Spiel existiert, ansonsten wird die Datei ausgelesen, es wird überprüft, ob das Eingelesene
*die richtige Länge hat und falls ja wird der aktuelle Spielstand durch den gelesenen ersetzt. Danach wird die Funktion
*Spielfeldausgabe aufgerufen, um das Spielfeld auszugeben.
*@param aktuellesSpielfeld : Spielfeld, dessen Spielstand zum gespeicherten geändert werden soll.
*/
void SpielLaden(Spielfeld &aktuellesSpielfeld);

/**
*KugelVon: @brief Gibt die den Anfangsbuchstaben der Kugelfarbe des übergebenen Spielers zurück.
*@param spieler : Spieler, dessen Kugelfarbe bestimmt werden soll.
*/
char KugelVon(const Spieler &spieler);

/**
*BesitzerKugel: @brief Gibt den Spieler zurück, dem die übergebene Kugel gehört.
*@param Kugel : Die Kugel,deren Besitzer zurückgegeben wird.
*/
Spieler BesitzerKugel(const char &Kugel);

/**
*JaNeinFrage: @brief Lässt den Benutzer eine Frage mit "J" oder "N" beantworten.
*@details Liest die Eingabe des Benutzers und gibt bei "J" 1 und bei "N" 0 zurück. Bei einer anderen Eingabe fragt sie den
*Benutzer nach einer weiteren Eingabe und wiederholt den Vorgang.
*@pre Der Nutzer sollte vorher eine Frage gestellt bekommen haben, die mit Ja oder Nein beantwortbar ist.
*@return Gibt bei der Eingabe "J" 1 und bei der Eingabe "N" 0 zurück.
*/
bool JaNeinFrage();

/**
*ungueltigeFelder: @brief Überprüft, ob die übergebenen Zeichenkette mit zwei gültigen Feldern beginnt.
*@details Die Funktion überprüft, ob die erste Stelle der Felder im Berich von A bis G liegt, die zweite Stelle im Bereich 1 bis 8
*liegt und zwischen den Feldern ein Leerzeichen ist. Falls dies zutrifft gibt sie 1 zurück.
*@param Eingabe : Die Zeichenkette, die überprüft wird.
*@return Gibt 1 zurück, wenn die übergebene Eingabe mit 2 formal gültigen Feldern beginnt, ansonsten gibt sie 0 zurück.
*/
bool ungueltigeFelder(const std::string &Eingabe);

/**
*ZielKeinFeld: @brief Überprüft, ob das Feld hinter den zu verschiebenden Kugeln außerhalb des Spielfelds liegt.
*@details Überprüft, ob der Index der Zeile, auf die zugegriffen werden würde, 7 oder -1 und der Index der Spalte, auf die zugegriffen
*werden würde 8 oder -1 wäre.
*@pre Es muss überprüft worden sein, das zwischen dem zu überprüfenden Feld und der Kugel, die bewegt werden soll, nur valide Felder
*liegen.
*@param ZeileHinterKugeln : Theoretischer Index der Zeile hinter den zu verschiebenden Kugeln.
*@param SpalteHinterKugeln : Theoretischer Index der Spalte hinter den zu verschiebenden Kugeln.
*@return Gibt 1 zurück, wenn das Feld hinter den zu verschiebenden Kugeln außerhalb des Spielfelds liegt, ansonsten gibt sie 0 zurück.
*/
bool ZielKeinFeld(const int &ZeileHinterKugeln,const int &SpalteHinterKugeln);

/**
*gueltigeEingabe: @brief Überprüft die Eingabe des Nutzers auf formale Korrektheit und ob das Startfeld valide ist.
*@details Die Funktion überprüft, ob die Länge der Eingabe 5 ist, ob die eingegebenen Felder gültig sind, wofür die Funktion ungültigeFelder
*auferufen wird und ob auf dem Startfeld eine Kugel des Zugspielers liegt. Falls all das der Fall ist gibt sie 1 zurück.
*@param Eingabe : Die Eingabe, die auf Gültigkeit überprüft wird.
*@param aktuellesSpielfeld : Das Spielfeld für das überprüft wird, ob die Eingabe gültig ist.
*@return Gibt 1 zurück, wenn die Eingabe des Nutzers formale korrekt ist und das Startfeld valide ist, ansonsten gibt sie 0 zurück.
*/
bool gueltigeEingabe (const std::string &Eingabe, const Spielfeld &aktuellesSpielfeld);

/**
*Zug: @brief Überprüft, ob die übergebene Eingabe ein gültiger Zug ist und führt ihn aus.
*@details Die Funktion überprüft, ob Start- und Zielfeld 1 Feld auseinander liegen und ob weniger als 3 Kugeln dabei verschoben
*werden. Falls beides der Fall ist werden die Kugeln entsprechend der Eingabe verschoben und zur Audgabe des Spielfeldes die
*Funktion Spielfeldausgabe aufgerufen. Falls durch den Spielzug eine Kugel aus dem Feld geschoben wird, was unter Verwendung der
*Funktion ZielKeinFeld festgestellt wird, wird dies dem Benutzer mitgeteilt und dieverlorene_Kugeln Variable die der Kugelfarbe
*entspricht um 1 erhöht.
*@pre Es muss vorher überprüft worden sein, dass die Eingabe formal korrekt ist und das Startfeld valide ist.
*@param Eingabe : Zeichenkette, die als Spielzug verwendet wird.
*@param aktuellesSpielfeld : Spielfeld, in dem der Spielzug versucht wird auszuführen.
*/
void Zug (const std::string &Eingabe, Spielfeld &aktuellesSpielfeld);

/**
*Spielende: @brief Gibt eine Siegesnachicht für den Sieger aus und fragt, ob ein neues Spiel gestartet werden soll und setzt in
*diesem Fall den Spielstand auf den Spielstart zurück.
*@details Die Funktion gibt eine Siegesnachicht fürden Spieler aus, der nicht 5 Kugeln verloren hat und fragt den Benutzer dann, ob ein neues
*Spiel gestartet werden soll. Dann wird die Funktion JaNeinFrage aufgerufen. Falls sie 1 zurückgibt wird der Spielstand auf den
*Startzustand zurückgesetzt.
*@pre Für eine korrekte Ausgabe muss einer der beiden Spieler 5 Kugeln verloren haben.
*@param aktuellesSpielfeld : Der Spielstand, für dessen Sieger eine Siegesnachicht ausgegeben werden soll.
*/
void Spielende(Spielfeld &aktuellesSpielfeld);
