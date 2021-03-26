#include <iostream>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <string>
#include <limits>
#include "Kugelspiel.hpp"

Spielfeld::Spielfeld()
{
    verloreneKugelnW = 0;
    verloreneKugelnS = 0;
    std::iota(RandOben.begin(),RandOben.end(),1);
    std::iota(RandLinks.begin(),RandLinks.end(),'A');
    std::for_each(Felder.begin(),Felder.end(), [](std::array<char,8> &Reihe){Reihe = {'W','W','.','.','.','.','S','S'};});
    Zugspieler = Spieler::Weiss;
}

Spieler Spielfeld::get_Zugspieler()const
{
    return Spielfeld::Zugspieler;
}

int Spielfeld::get_verloreneKugelnW()const
{
    return Spielfeld::verloreneKugelnW;
}

int Spielfeld::get_verloreneKugelnS()const
{
    return Spielfeld::verloreneKugelnS;
}

std::array<int,8> Spielfeld::get_RandOben()const
{
    return Spielfeld::RandOben;
}

std::array<char,7> Spielfeld::get_RandLinks()const
{
    return Spielfeld::RandLinks;
}

std::array<std::array<char,8>,7> Spielfeld::get_Felder()const
{
    return Spielfeld::Felder;
}

void Spielfeld::change_Felder(const int &Zeile, const int &Spalte, const char &aendernZu)
{
    Spielfeld::Felder.at(static_cast<unsigned int>(Zeile)).at(static_cast<unsigned int>(Spalte))= aendernZu;
}

void Spielfeld::change_verloreneKugelnW(const int &neuerWert)
{
    Spielfeld::verloreneKugelnW = neuerWert;
}

void Spielfeld::change_verloreneKugelnS(const int &neuerWert)
{
    Spielfeld::verloreneKugelnS = neuerWert;
}

void Spielfeld::change_Zugspieler(const Spieler &neuerZugspieler)
{
    Spielfeld::Zugspieler = neuerZugspieler;
}


char KugelVon(const Spieler &spieler)
{
    if(spieler==Spieler::Schwarz)
    {
        return 'S';
    }
    else
    {
        return 'W';
    }
}

Spieler BesitzerKugel(const char &Kugel)
{
    if(Kugel == 'W')
    {
        return Spieler::Weiss;
    }
    else
    {
        return Spieler::Schwarz;
    }
}

bool ungueltigeFelder(const std::string &Eingabe)
{
    if(Eingabe.at(0)<'A' or Eingabe.at(0)>'G' or Eingabe.at(3)<'A' or Eingabe.at(3)>'G' or Eingabe.at(1)<'1' or Eingabe.at(1)>'8' or Eingabe.at(4)<'1' or Eingabe.at(4)>'8' or Eingabe.at(2)!=' ')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool ZielKeinFeld(const int &ZeileHinterKugeln,const int &SpalteHinterKugeln)
{
    if(ZeileHinterKugeln== 7 or ZeileHinterKugeln==-1 or SpalteHinterKugeln==8 or SpalteHinterKugeln==-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool JaNeinFrage()
{
    std::string Antwort;
    do
    {
        std::cin>>Antwort;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        if((Antwort.at(0)!= 'J' and Antwort.at(0) != 'N') or Antwort.length()!=1)
        {
            std::cout<<'\n'<<"Bitte antworte mit J oder N. (J fuer Ja, N fuer Nein)"<<std::endl;
        }
    }while(((Antwort.at(0) != 'J') and (Antwort.at(0) != 'N')) or (Antwort.length()!=1));
    if(Antwort == "J")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void SpielSpeichern(Spielfeld &aktuellesSpielfeld)
{
    std::cout<<'\n'<<"Ist schon ein Spiel gespeichert wird es ueberschrieben. Trotzdem fortfahren?(J/N)"<<std::endl;
    if(JaNeinFrage())
    {
        remove("gespeichertesSpiel.txt");
        std::ofstream Spielstand ("gespeichertesSpiel.txt");
        for(size_t i=0;i<7;i++)
        {
            for(size_t j = 0;j<8;j++)
            {
                Spielstand<<aktuellesSpielfeld.get_Felder().at(i).at(j);
            }
        }
        Spielstand<<KugelVon(aktuellesSpielfeld.get_Zugspieler())<<aktuellesSpielfeld.get_verloreneKugelnW()<<aktuellesSpielfeld.get_verloreneKugelnS();
        Spielstand.close();
    }
}

void SpielLaden(Spielfeld &aktuellesSpielfeld)
{
    std::cout<<'\n'<<"Soll dieses Spiel abgebrochen und das gespeicherte Spiel geladen werden?(J/N)"<<std::endl;
    if(JaNeinFrage())
    {
        std::string Spielstand;
        std::ifstream gespeicherterStand ("gespeichertesSpiel.txt");
        if(gespeicherterStand.good())
        {
            std::getline(gespeicherterStand,Spielstand);
            gespeicherterStand.close();
            if(Spielstand.length()==59)//59 ist die Anzahl der Felder + die 3 Zeichen für den Zugspieler und die Anzahl der verlorenen Kugeln beider Spieler.
            {
                for(int i=0;i<7;i++)
                {
                    for(int j=0;j<8;j++)
                    {
                        aktuellesSpielfeld.change_Felder(i,j,Spielstand.at(static_cast<unsigned int>(i*8+j)));
                    }
                }
                aktuellesSpielfeld.change_Zugspieler(BesitzerKugel(Spielstand.at(56)));
                aktuellesSpielfeld.change_verloreneKugelnW(Spielstand.at(57)-'0');
                aktuellesSpielfeld.change_verloreneKugelnS(Spielstand.at(58)-'0');
                Spielfeldausgabe(aktuellesSpielfeld);
            }
            else
            {
                std::cout<<"gespeichertesSpiel.txt enthaelt einen Spielstand ungueltiger Laenge"<<'\n'<<std::endl;
            }
        }
        else
        {
            std::cout<<'\n'<<"Es existiert kein gespeichertes Spiel."<<std::endl;
        }
    }
}

bool gueltigeEingabe(const std::string &Eingabe, const Spielfeld &aktuellesSpielfeld)
{
    if(Eingabe.length()!= 5)
            {
                std::cout<<'\n'<<"Die Eingabe hat nicht die richtige Laenge. Eingabe in der Form:A1 A2"<<std::endl;
                return 0;
            }
            else
            {
                if(ungueltigeFelder(Eingabe))
                {
                    std::cout<<'\n'<<"Ungueltiges Feld. Eingabe in der Form:A1 A2"<<std::endl;
                    return 0;
                }
                else
                {
                    int Zeile = Eingabe.at(0)-'@';//Abziehen des ASCII Wertes von @, um die theoretische Zeilennummer zu erhalten.
                    int Spalte = Eingabe.at(1)-'0';
                    if(aktuellesSpielfeld.get_Felder().at(static_cast<unsigned int>(Zeile-1)).at(static_cast<unsigned int>(Spalte-1))=='.')
                    {
                        std::cout<<'\n'<<"Auf dem angegebenen Feld liegt keine Kugel."<<std::endl;
                        return 0;
                    }
                    else
                    {
                        if(BesitzerKugel(aktuellesSpielfeld.get_Felder().at(static_cast<unsigned int>(Zeile-1)).at(static_cast<unsigned int>(Spalte-1))) != aktuellesSpielfeld.get_Zugspieler())
                        {
                            std::cout<<'\n'<<"Die angegebene Kugel gehoert dir nicht."<<std::endl;
                            return 0;
                        }
                        else
                        {
                            return 1;
                        }
                    }
                }
            }
}

void Zug (const std::string &Eingabe, Spielfeld &aktuellesSpielfeld)
{
    int Zeilenabstand = Eingabe.at(3)- Eingabe.at(0);
    int Spaltenabstand = Eingabe.at(4)- Eingabe.at(1);
    int KugelnImWeg = 0;
    if(Zeilenabstand+Spaltenabstand == 1 or Zeilenabstand+Spaltenabstand == -1)
    {
        int Zielzeile = Eingabe.at(3)-'@';//Abziehen des ASCII Wertes von @, um die theoretische Zeilennummer zu erhalten.
        int Zielspalte = Eingabe.at(4)-'0';
        bool durchgefuehrterZug = 0;
        do
        {
            int ZeileHinterKugeln = (Zielzeile-1)+(Zeilenabstand*KugelnImWeg);
            int SpalteHinterKugeln = (Zielspalte-1)+(Spaltenabstand*KugelnImWeg);
           if(ZielKeinFeld(ZeileHinterKugeln,SpalteHinterKugeln) or aktuellesSpielfeld.get_Felder().at(static_cast<unsigned int>(ZeileHinterKugeln)).at(static_cast<unsigned int>(SpalteHinterKugeln))=='.')
            {
                if(ZielKeinFeld(ZeileHinterKugeln,SpalteHinterKugeln))
                {
                    if(aktuellesSpielfeld.get_Felder().at(static_cast<unsigned int>(ZeileHinterKugeln-Zeilenabstand)).at(static_cast<unsigned int>(SpalteHinterKugeln-Spaltenabstand))=='W')
                    {
                        aktuellesSpielfeld.change_verloreneKugelnW(aktuellesSpielfeld.get_verloreneKugelnW()+1);
                        std::cout<<'\n'<<"Die "<<aktuellesSpielfeld.get_verloreneKugelnW()<<". Kugel von Weiss wurde rausgeworfen."<<std::endl;
                    }
                    else
                    {
                        aktuellesSpielfeld.change_verloreneKugelnS(aktuellesSpielfeld.get_verloreneKugelnS()+1);
                        std::cout<<'\n'<<"Die "<<aktuellesSpielfeld.get_verloreneKugelnS()<<". Kugel von Schwarz wurde rausgeworfen."<<std::endl;
                    }
                    for(int i = 0;i<KugelnImWeg;i++)//Wenn eine Kugel aus dem Feld geschoben wird, muss diese Kugel nicht verschoben werden, weshalb nur KugelnImWeg-1 Kugeln + die Startkugel bewegt werden müssen
                    {
                        aktuellesSpielfeld.change_Felder(ZeileHinterKugeln-(Zeilenabstand*(i+1)),SpalteHinterKugeln-(Spaltenabstand*(i+1)),aktuellesSpielfeld.get_Felder().at(static_cast<unsigned int>(ZeileHinterKugeln-(Zeilenabstand*(i+2)))).at(static_cast<unsigned int>(SpalteHinterKugeln-(Spaltenabstand*(i+2)))));
                    }
                }
                else
                {
                    for(int i = 0;i<=KugelnImWeg;i++)//Es müssen immer die Kugeln die vor der Kugel liegen + die Startkugel verschoben werden.
                    {
                        aktuellesSpielfeld.change_Felder(ZeileHinterKugeln-(Zeilenabstand*i),SpalteHinterKugeln-(Spaltenabstand*i),aktuellesSpielfeld.get_Felder().at(static_cast<unsigned int>(ZeileHinterKugeln-(Zeilenabstand*(i+1)))).at(static_cast<unsigned int>(SpalteHinterKugeln-(Spaltenabstand*(i+1)))));
                    }
                }
                aktuellesSpielfeld.change_Felder(Zielzeile-1+(Zeilenabstand*-1),Zielspalte-1+(Spaltenabstand*-1),'.');
                Spielfeldausgabe(aktuellesSpielfeld);
                if(aktuellesSpielfeld.get_Zugspieler()== Spieler::Weiss)
                {
                    aktuellesSpielfeld.change_Zugspieler(Spieler::Schwarz);
                }
                else
                {
                    aktuellesSpielfeld.change_Zugspieler(Spieler::Weiss);
                }
                durchgefuehrterZug=1;
            }
            else
            {
            KugelnImWeg++;
            }
        }while (durchgefuehrterZug==0 and KugelnImWeg<3);
    }
    else
    {
        std::cout<<'\n'<<"Du kannst nur ein Feld weit ziehen"<<std::endl;
    }
    if(KugelnImWeg==3)
    {
        std::cout<<'\n'<<"Ungueltiger Zug. Du kannst hoechstens 2 Kugeln vor dir herschieben."<<std::endl;
    }
}


void Spielfeldausgabe(Spielfeld& aktuellesSpielfeld)
{
    std::cout<<'\n'<<' '<<' ';
    for(size_t i=0;i<8;i++)
    {
        std::cout<<aktuellesSpielfeld.get_RandOben().at(i);
    }
    std::cout<<'\n';
    for(size_t i =0; i<7;i++)
    {
        std::cout<<aktuellesSpielfeld.get_RandLinks().at(i)<<' ';
        for(size_t j = 0;j<8;j++)
        {
            std::cout<<aktuellesSpielfeld.get_Felder().at(i).at(j);
        }
    std::cout<<'\n';
    }
    std::cout<<std::endl;
}

void Spielende(Spielfeld &aktuellesSpielfeld)
{
    if(aktuellesSpielfeld.get_verloreneKugelnW() == 5)
    {
        std::cout<<"///////////////////////////////////////////////////////////////"<<'\n';
        std::cout<<'\n'<<"Schwarz hat 5 Kugeln von Weiss rausgeworfen und damit gewonnen!"<<'\n';
        std::cout<<'\n'<<"///////////////////////////////////////////////////////////////"<<'\n'<<std::endl;
    }
    else
    {
        std::cout<<"///////////////////////////////////////////////////////////////"<<'\n';
        std::cout<<'\n'<<"Weiss hat 5 Kugeln von Schwarz rausgeworfen und damit gewonnen!"<<'\n';
        std::cout<<'\n'<<"///////////////////////////////////////////////////////////////"<<'\n'<<std::endl;
    }
    std::string Neu;
    std::cout<<"Neues Spiel? (J/N)"<<std::endl;
    if(JaNeinFrage())
    {
        Spielfeld neuesSpielfeld;
        aktuellesSpielfeld = neuesSpielfeld;
        Spielfeldausgabe(aktuellesSpielfeld);
    }
}

