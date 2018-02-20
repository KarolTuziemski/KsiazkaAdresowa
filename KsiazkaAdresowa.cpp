#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

struct Kontakt
{
    int id;
    string imie, nazwisko, nr_telefonu, e_mail, adres;
};

void szukajKontakt (Kontakt kontakty[], int iloscKontaktow)
{
    string imie, nazwisko;
    bool czyJestKontakt = false;
    char wybor;

    system("cls");
    cout << "Wyszukaj kontakt: " << endl;
    cout << "1. Wyszukaj po imieniu." << endl;
    cout << "2. Wyszukaj po nazwisku." << endl;
    cin >> wybor;

    if (wybor == '1')
    {
        cout << "Wpisz imie: " << endl;
        cin >> imie;
        int i=0;

        for(int i=0; i<iloscKontaktow; i++)
        {
            if (kontakty[i].imie==imie)
            {
            cout << "Imie: " << kontakty[i].imie << endl;
            cout << "Nazwisko: " << kontakty[i].nazwisko << endl;
            cout << "Numer telefonu: " << kontakty[i].nr_telefonu << endl;
            cout << "E-mail: " << kontakty[i].e_mail << endl;
            cout << "Adres: " << kontakty[i].adres << endl;
            czyJestKontakt = true;
            }
        }
            if (czyJestKontakt == false)
            {
            cout << "Brak kontaktow o tym imieniu" << endl;
            }
            system("pause");
    }
    else if (wybor == '2')
    {
        cout << "Wpisz nazwisko: " << endl;
        cin >> nazwisko;
        int i=0;

        for(int i=0; i<iloscKontaktow; i++)
        {
            if (kontakty[i].nazwisko==nazwisko)
            {
            cout << "Imie: " << kontakty[i].imie << endl;
            cout << "Nazwisko: " << kontakty[i].nazwisko << endl;
            cout << "Numer telefonu: " << kontakty[i].nr_telefonu << endl;
            cout << "E-mail: " << kontakty[i].e_mail << endl;
            cout << "Adres: " << kontakty[i].adres << endl;
            czyJestKontakt = true;
            }
        }
            if (czyJestKontakt == false)
            {
            cout << "Brak kontaktow o tym nazwisku" << endl;
            }
            system("pause");
    }
}

int dodajKontakt (Kontakt kontakty[], int iloscKontaktow)
{
    string imie, nazwisko, nr_telefonu, e_mail, adres;

    system("cls");
    cout << "Dodaj nowa osobe: " << endl;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, nr_telefonu);
    cout << "Podaj e-mail: ";
    cin >> e_mail;
    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, adres);

    int kontaktId = iloscKontaktow + 1;

    kontakty[iloscKontaktow].id = kontaktId;
    kontakty[iloscKontaktow].imie = imie;
    kontakty[iloscKontaktow].nazwisko = nazwisko;
    kontakty[iloscKontaktow].nr_telefonu = nr_telefonu;
    kontakty[iloscKontaktow].e_mail = e_mail;
    kontakty[iloscKontaktow].adres = adres;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if (plik.good())
    {
        plik << kontaktId << endl;
        plik << imie << endl;
        plik << nazwisko << endl;
        plik << nr_telefonu << endl;
        plik << e_mail << endl;
        plik << adres << endl;

        plik.close();

        cout << imie << " " <<nazwisko << " jest w ksiazce adresowej." << endl;
        Sleep(2000);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }

    iloscKontaktow++;
    return iloscKontaktow;
}

void wszystkieKontakty (Kontakt kontakty[], int iloscKontaktow)
{
    for (int i=0; i<iloscKontaktow; i++)
    {
        cout << "Imie: "            << kontakty[i].imie << endl;
        cout << "Nazwisko: "        << kontakty[i].nazwisko << endl;
        cout << "Numer telefonu: "  << kontakty[i].nr_telefonu << endl;
        cout << "E-mail: "          << kontakty[i].e_mail << endl;
        cout << "Adres: "           << kontakty[i].adres << endl;
        cout << endl << "   " << endl;
    }
    system("pause");
}

int wczytajKontakty(Kontakt kontakty[])
{
    int indeks = 0;
    string linia;
    int nr_linii = 1;
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good() == false)
    {
        cout << "Nie udalo sie utworzyc pliku!";
        return 0;
    }

    while (getline(plik,linia))
    {
        switch (nr_linii)
        {
            case 1: kontakty[indeks].id = atoi(linia.c_str());      break;
            case 2: kontakty[indeks].imie = linia;                  break;
            case 3: kontakty[indeks].nazwisko = linia;              break;
            case 4: kontakty[indeks].nr_telefonu = linia;           break;
            case 5: kontakty[indeks].e_mail = linia;                break;
            case 6: kontakty[indeks].adres = linia;                 break;
        }
        if (nr_linii == 6)
        {
            nr_linii = 0;
            indeks++;
        }
        nr_linii++;
    }
    plik.close();

    return indeks;
}

int main()
{
    Kontakt kontakty[100];
    int iloscKontaktow = 0;
    char wybor;

    iloscKontaktow = wczytajKontakty(kontakty);

    while (1)
    {
        system("cls");
        cout << "1. Szukaj kontaktow" << endl;
        cout << "2. Dodaj konktakt" << endl;
        cout << "3. Pokaz wszystkie kontakty" << endl;
        cout << "9. Zakoncz program" << endl;
        cin >> wybor;

        switch (wybor)
        {
            case '1':
            szukajKontakt(kontakty, iloscKontaktow);
            break;

            case '2':
            iloscKontaktow = dodajKontakt(kontakty, iloscKontaktow);
            break;

            case '3':
            wszystkieKontakty(kontakty, iloscKontaktow);
            break;

            case '9':
            exit (0);
            break;
        }
    }

    return 0;
}
