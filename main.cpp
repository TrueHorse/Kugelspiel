#include <iostream>
#include <array>
#include <string>
#include "Kugelspiel.hpp"



int main()
{
    std::string Eingabe;
    Spielfeld aktuellesSpielfeld;
    std::cout<<'\n'<<"----------------------------------------------------------------"<<'\n';
    std::cout<<"Ein Zug muss in der folgenden Form eingegeben werden:A1 A2."<<'\n';
    std::cout<<"Wenn du den aktuellen Spielstand speichern moechtest, gib S ein."<<'\n';
    std::cout<<"Moechtest du einen gespeicherten Spielstand laden, gib L ein,"<<std::endl;
    std::cout<<"----------------------------------------------------------------"<<std::endl;
    Spielfeldausgabe(aktuellesSpielfeld);
    while(aktuellesSpielfeld.get_verloreneKugelnW()<5 and aktuellesSpielfeld.get_verloreneKugelnS()<5)
    {
        if(aktuellesSpielfeld.get_Zugspieler() == Spieler::Weiss)
        {
            std::cout<<"Weiss ist am Zug:"<<std::endl;
        }
        else
        {
            std::cout<<"Schwarz ist am Zug:"<<std::endl;
        }
        std::getline(std::cin, Eingabe);
        if (Eingabe=="S")
        {
            SpielSpeichern(aktuellesSpielfeld);
        }
        else
        {
            if(Eingabe =="L")
            {
                SpielLaden(aktuellesSpielfeld);
            }
            else
            {
                if(gueltigeEingabe(Eingabe, aktuellesSpielfeld))
                {
                    Zug(Eingabe, aktuellesSpielfeld);
                    if(aktuellesSpielfeld.get_verloreneKugelnW()==5 or aktuellesSpielfeld.get_verloreneKugelnS()==5)
                    {
                        Spielende(aktuellesSpielfeld);
                    }
                }
            }
        }
    }
}

