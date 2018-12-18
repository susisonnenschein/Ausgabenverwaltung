#include <iostream>

using namespace std;

//Klasse der Rechnungen
class Rechnung
{
//damit auch die Klasse Rechnungsliste auf private zugreifen kann
    friend class Rechnungsliste;

private:
    //Deklaration der Variablen
    string name;
    int monat;
    float betrag;
    int kategorie;
    Rechnung *nachfolger;

public:
    //Konstruktor
    Rechnung (string n, int m, float b, int k):name (n), monat(m), betrag(b), kategorie(k)
    {
        nachfolger = 0;
        cout << "Neue Rechnung wurde verbucht." << endl << endl;
    }
    //Funktionen, um auf Daten zugreifen zu können
    string get_name()
    {
        return name;
    }
    int get_monat()
    {
        return monat;
    }
    float get_betrag()
    {
        return betrag;
    }
    int get_kategorie()
    {
        return kategorie;
    }
    //Funktion, um die nachfolgende Rechnung ausgeben zu können
    Rechnung* next()
    {
        return nachfolger;
    }
};

//Liste der Rechnungen
class Rechnungsliste
{
private:
    //Zeiger auf Listenanfang
    Rechnung *anfang;

public:
    //Funktion, um Listenanfang ausgeben zu können
    Rechnung* begin()
    {
        return anfang;
    }
    //Funktion, um Rechnung Liste hinzufügen zu können
    void insert (Rechnung *k)
    {
        k->nachfolger=anfang;
        anfang=k;
    }
    //Funktion, die Rechnung anhand ihres Namens finden kann
    Rechnung* find(string s)
    {
        Rechnung *zeiger;
        for(zeiger = begin(); zeiger != 0; zeiger = zeiger->next())
        {
            if(zeiger->get_name() == s)
            {
                break;
            }
        }
        return zeiger;
    }
    //Funktion, die Rechnung aus Liste löscht
    void remove(Rechnung *r)
    {
        if(anfang != 0)
        {
            if(r == anfang)
            {
                anfang = r->next();
            }
            else
            {
                Rechnung *zeiger;
                for(zeiger = begin(); zeiger != 0; zeiger = zeiger->next())
                {
                    if(zeiger->next() == 0)
                    {
                        break;
                    }
                    else if(zeiger->next() == r)
                    {
                        zeiger->nachfolger = zeiger->next()->next();
                        break;
                    }
                }
            }
        }
    }
};

//Eine Liste wird erstellt
Rechnungsliste liste;

//Funktionen deklarieren
int Menue();
void Datenerfassung();
void Anzeige();
void Anzeige_Kat();
void Loeschen();
void Programmende();


int main()
{
    //lokale Variablen definieren
    int m = 0;

    cout << "Herzlich Willkommen in Ihrer persoenlichen Ausgabenverwaltung" << endl << endl;

    //Menü
    do
    {
    cout << "Bitte waehlen Sie einen Menuepunkt:" << endl << "1. Erfassung einer Rechnung" << endl << "2. Alle Ausgaben anzeigen" << endl
    << "3. Ausgabensummen pro Kategorie anzeigen" << endl << "4. Rechnung loeschen" << endl << "5. Programmende" << endl << endl;
    cin >> m;
    if (m == 1)
        {Datenerfassung();}
    else if (m == 2)
        {Anzeige();}
    else if (m == 3)
        {Anzeige_Kat();}
    else if (m == 4)
        {Loeschen();}
    else if (m == 5)
        {Programmende();}
    else
        {cout << "Ungueltige Eingabe." << endl;}
    }while(m!=5);

    return 0;
}

//Funktionen definieren

//Erfasst eine neue Rechnung
void Datenerfassung()
{
    string name;
    int monat;
    float betrag;
    int kategorie;

    cout << "Eindeutiger Name der Rechnung:" << endl;
    cin >> name;
    cout << "Monat der Rechnung (1-12): " << endl;
    cin >> monat;
    cout << "Betrag der Rechnung:" << endl;
    cin >> betrag;
    cout << "Kategorie der Rechnung (1-8): " << endl << "1. Tanken" << endl << "2. Kleidung" << endl
    << "3. Essen" << endl << "4. Urlaub" <<endl << "5. Nebenkosten" << endl << "6. Geschenke" << endl
    << "7. Bueromaterialien" << endl << "8. Haustiere" << endl;
    cin >> kategorie;
    Rechnung *objekt = new Rechnung (name, monat, betrag, kategorie);
    liste.insert (objekt);

}

//Zeigt alle Ausgaben sortiert nach Monat an
void Anzeige()
{
   Rechnung *zeiger;
   int i = 0;
   int j = 0;
   float k[8][12] = {0};

   for(zeiger = liste.begin(); zeiger != 0; zeiger = zeiger->next())
   {
       i = zeiger->get_kategorie();
       j = zeiger->get_monat();
       k[i-1][j-1] += zeiger->get_betrag();
   }
   for (j=0; j<12; j++)
   {
       cout << "-----------------------" << endl;
       cout << "Monat " << j+1 << endl;
       cout << "-----------------------" << endl;
       cout << "Tanken: " << k[0][j] << " Euro" << endl;
       cout << "Kleidung: " << k[1][j] << " Euro" << endl;
       cout << "Essen: " << k[2][j] << " Euro" << endl;
       cout << "Urlaub: " << k[3][j] << " Euro" << endl;
       cout << "Nebenkosten: " << k[4][j] << " Euro" << endl;
       cout << "Geschenke: " << k[5][j] << " Euro" << endl;
       cout << "Bueromaterialien: " << k[6][j] << " Euro" << endl;
       cout << "Haustiere: " << k[7][j] << " Euro" << endl;

        float ges = 0;
        for(i=0; i<8; i++)
        {
            ges += k[i][j];
        }
        cout << "Gesamt: " << ges << " Euro" << endl;
        if (ges > 500)
        {
            cout << "Mehr ausgegeben als geplant!" << endl;
        }
        cout << endl;
   }
}

//Zeigt Ausgabensummen pro Kategorie an
void Anzeige_Kat()
{
   Rechnung *zeiger;
   int i = 0;
   float k[8] = {0};

   for(zeiger = liste.begin(); zeiger != 0; zeiger = zeiger->next())
   {
       i = zeiger->get_kategorie();
       k[i-1] += zeiger->get_betrag();
   }
   cout << "Tanken: " << k[0] << " Euro" << endl;
   cout << "Kleidung: " << k[1] << " Euro" << endl;
   cout << "Essen: " << k[2] << " Euro" << endl;
   cout << "Urlaub: " << k[3] << " Euro" << endl;
   cout << "Nebenkosten: " << k[4] << " Euro" << endl;
   cout << "Geschenke: " << k[5] << " Euro" << endl;
   cout << "Bueromaterialien: " << k[6] << " Euro" << endl;
   cout << "Haustiere: " << k[7] << " Euro" << endl << endl;
}


//Ermöglicht das Löschen einer Rechnung
void Loeschen()
{
    Rechnung *zeiger;
    string s;

    cout << "Welche Rechnung moechten Sie loeschen? (Geben Sie den Namen der Rechnung an)" << endl;
    cin >> s;
    zeiger = liste.find(s);
    if(zeiger == 0)
        {
            cout << "Rechnung existiert nicht." << endl << endl;
        }
    else
        {
            cout << "Rechnung " << zeiger->get_name() << " wurde geloescht" << endl << endl;
            liste.remove(zeiger);
        }
}

//Beendet das Programm
void Programmende()
{
    cout << "Alle Daten werden geloescht." << endl;
}
