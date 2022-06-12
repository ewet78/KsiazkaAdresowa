#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct DanePrzyjaciela {
    int id = 0;
    string imie = "",nazwisko = "", nrTelefonu = "", email = "", adres = "";
};

string konwerjsaIntNaString(int liczba) {
    ostringstream ss;
    ss << liczba;
    string str = ss.str();

    return str;
}

void dopiszPrzyjacielaDoPliku(DanePrzyjaciela adresat) {
    fstream plik;
    plik.open("wizytowki.txt", ios::out | ios::app);

    if (plik.good() == true) {
        plik << adresat.id << '|';
        plik << adresat.imie << '|';
        plik << adresat.nazwisko << '|';
        plik << adresat.nrTelefonu << '|';
        plik << adresat.email << '|';
        plik << adresat.adres << '|' << endl;
        plik.close();

    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

void zapiszWszystkichAdresatowDoPlikuTekstowego(vector<DanePrzyjaciela> &Przyjaciele) {
    fstream plik;
    string liniaZDanymiAdresata = "";

    plik.open("wizytowki.txt", ios::out);
    if (plik.good()) {
        for (vector<DanePrzyjaciela>::iterator itr = Przyjaciele.begin(); itr != Przyjaciele.end(); itr++) {
            liniaZDanymiAdresata += konwerjsaIntNaString(itr->id) + '|';
            liniaZDanymiAdresata += itr->imie + '|';
            liniaZDanymiAdresata += itr->nazwisko + '|';
            liniaZDanymiAdresata += itr->nrTelefonu + '|';
            liniaZDanymiAdresata += itr->email + '|';
            liniaZDanymiAdresata += itr->adres + '|';

            plik << liniaZDanymiAdresata << endl;
            liniaZDanymiAdresata = "";
        }
        plik.close();
    } else {
        cout << "Nie mozna otworzyc pliku wizytowki.txt" << endl;
    }
}


void wczytywanieDanychPrzyjaciela(vector <DanePrzyjaciela> &Przyjaciele) {

    int idOstatniegoPrzyjaciela = 0;
    DanePrzyjaciela Adresat;

    system("cls");

    cout << "Podaj imie: ";
    cin >> Adresat.imie;
    cout << "Podaj nazwisko: ";
    cin >> Adresat.nazwisko;
    cout << "Podaj nr telefonu: ";
    cin >> Adresat.nrTelefonu;
    cout << "Podaj adres email: ";
    cin >> Adresat.email;
    cout << "Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin, Adresat.adres);
    cout << endl;

    if (Przyjaciele.size() != 0) {
        idOstatniegoPrzyjaciela = Przyjaciele[Przyjaciele.size()-1].id;
    }

    Adresat.id = idOstatniegoPrzyjaciela+1;

    Przyjaciele.push_back(Adresat);

    dopiszPrzyjacielaDoPliku(Adresat);


    cout << "Dane przyjaciela zostaly zapisane" << endl;
    Sleep(1000);

}

void wyszukiwaniePoImieniu (string imie, vector <DanePrzyjaciela> & Przyjaciele) {
    int i=0;
    int id=0;
    while (i<Przyjaciele.size()) {
        if (Przyjaciele[i].imie == imie) {
            cout << Przyjaciele[i].id <<endl;
            cout << Przyjaciele[i].imie <<endl;
            cout << Przyjaciele[i].nazwisko <<endl;
            cout << Przyjaciele[i].nrTelefonu <<endl;
            cout << Przyjaciele[i].email <<endl;
            cout << Przyjaciele[i].adres <<endl;
            cout << endl;
            id = Przyjaciele[i].id;
        }
        i++;

    }
    if (id == 0) {
        cout << "W bazie danych nie ma osoby o podanym imieniu" << endl;
        Sleep(3000);
    }


}

void wyszukiwaniePoNazwisku (string nazwisko, vector <DanePrzyjaciela> &Przyjaciele) {
    int i=0;
    int id=0;
    while (i<Przyjaciele.size()) {
        if (Przyjaciele[i].nazwisko == nazwisko) {
            cout << Przyjaciele[i].id <<endl;
            cout << Przyjaciele[i].imie <<endl;
            cout << Przyjaciele[i].nazwisko <<endl;
            cout << Przyjaciele[i].nrTelefonu <<endl;
            cout << Przyjaciele[i].email <<endl;
            cout << Przyjaciele[i].adres <<endl;
            cout << endl;
            id = Przyjaciele[i].id;
        }
        i++;

    }
    if (id == 0) {
        cout << "W bazie danych nie ma osoby o podanym nazwisku" << endl;
        Sleep(3000);
    }


}

void wyswietlenieWszystkichZapisanychOsob(vector <DanePrzyjaciela> & Przyjaciele) {
    for (int i=0; i<Przyjaciele.size(); i++) {
        cout << Przyjaciele[i].id <<endl;
        cout << Przyjaciele[i].imie <<endl;
        cout << Przyjaciele[i].nazwisko <<endl;
        cout << Przyjaciele[i].nrTelefonu <<endl;
        cout << Przyjaciele[i].email <<endl;
        cout << Przyjaciele[i].adres <<endl;
        cout << endl;

    }
}

void odczytDanychZPliku( vector <DanePrzyjaciela> & Przyjaciele) {
    string linia = "";
    string daneDoZapisu = "";
    int nr_danych=1;
    DanePrzyjaciela Adresat;

    fstream plik;
    plik.open("wizytowki.txt", ios::in);
    if (plik.good()==false) {
        plik.open("wizytowki.txt", ios::out | ios::app);
        cout<< "Utworzono plik z wizytowkami";
        Sleep(3000);
        plik.close();
    }

    while (getline(plik, linia)) {


        for (int i=0; i<linia.length(); i++) {
            while (linia[i] != '|') {
                daneDoZapisu += linia[i];
                i++;
            }
            switch(nr_danych) {
            case 1:
                Adresat.id=atoi(daneDoZapisu.c_str());
                break;
            case 2:
                Adresat.imie=daneDoZapisu;
                break;
            case 3:
                Adresat.nazwisko=daneDoZapisu;
                break;
            case 4:
                Adresat.nrTelefonu=daneDoZapisu;
                break;
            case 5:
                Adresat.email=daneDoZapisu;
                break;
            case 6:
                Adresat.adres=daneDoZapisu;
                break;

            }

            nr_danych++;
            daneDoZapisu = "";


        }
        Przyjaciele.push_back(Adresat);
        nr_danych = 1;

    }
    plik.close();
}

void usuwanieAdresata (int idDoUsuniecia, vector <DanePrzyjaciela> & Przyjaciele) {
    int id=0;
    char wybor;
    cout << "Czy na pewno chcesz usunac wybranego adresata? (t/n)" << endl;
    cin >> wybor;
    if (wybor == 't') {
        for (int i=0; i < Przyjaciele.size(); i++) {
            if (Przyjaciele[i].id == idDoUsuniecia) {
                id = Przyjaciele[i].id;
                Przyjaciele.erase(Przyjaciele.begin()+i);

                cout << "Adresat zostal usuniety" << endl;
            }
        }

        zapiszWszystkichAdresatowDoPlikuTekstowego(Przyjaciele);
    }


    if (id == 0) {
        cout << "W bazie danych nie ma osoby o podanym id" << endl;
        Sleep(3000);
    }


}

int edycjaAdresata (int idDoEdycji, vector <DanePrzyjaciela> & Przyjaciele) {
    char wybor;
    int numerKontrolny = 0;
    string edytowaneImie, edytowaneNazwisko, edytowanyNrTelefonu, edytowanyEmail, edytowanyAdres;
    for (int i=0; i < Przyjaciele.size(); i++) {
        if (Przyjaciele[i].id == idDoEdycji) {
            system("cls");
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu" << endl<<endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            switch(wybor) {
            case '1': {
                system("cls");
                cout << "Podaj nowe imie: ";
                cin >> edytowaneImie;
                Przyjaciele[i].imie = edytowaneImie;
                zapiszWszystkichAdresatowDoPlikuTekstowego(Przyjaciele);
                cout << "Dane zostaly zmienione" << endl;
                numerKontrolny = 1;
                return numerKontrolny;
                break;

            }
            case '2': {
                system("cls");
                cout << "Podaj nowe nazwisko: ";
                cin >> edytowaneNazwisko;
                Przyjaciele[i].nazwisko = edytowaneNazwisko;
                zapiszWszystkichAdresatowDoPlikuTekstowego(Przyjaciele);
                cout << "Dane zostaly zmienione" << endl;
                numerKontrolny = 1;
                return numerKontrolny;
                break;
            }
            case '3': {
                system("cls");
                cout << "Podaj nowy numer telefonu: ";
                cin >> edytowanyNrTelefonu;
                Przyjaciele[i].nrTelefonu = edytowanyNrTelefonu;
                zapiszWszystkichAdresatowDoPlikuTekstowego(Przyjaciele);
                cout << "Dane zostaly zmienione" << endl;
                numerKontrolny = 1;
                return numerKontrolny;
                break;
            }
            case '4': {
                system("cls");
                cout << "Podaj nowy email: ";
                cin >> edytowanyEmail;
                Przyjaciele[i].email = edytowanyEmail;
                zapiszWszystkichAdresatowDoPlikuTekstowego(Przyjaciele);
                cout << "Dane zostaly zmienione" << endl;
                numerKontrolny = 1;
                return numerKontrolny;
                break;
            }
            case '5': {
                system("cls");
                cout << "Podaj nowy adres: ";
                cin.sync();
                getline(cin, edytowanyAdres);
                Przyjaciele[i].adres = edytowanyAdres;
                zapiszWszystkichAdresatowDoPlikuTekstowego(Przyjaciele);
                cout << "Dane zostaly zmienione" << endl;
                numerKontrolny = 1;
                return numerKontrolny;
                break;
            }
            case '6': {
                return numerKontrolny;
                break;
            }
            }


        } else cout << "W bazie danych nie ma osoby o podanym id" <<endl;
    }

}

int main() {
    vector <DanePrzyjaciela> Przyjaciele;
    int numerKontrolny = 0;
    int iloscPrzyjaciol = 0;
    string szukaneImie, szukaneNazwisko;
    int idDoUsuniecia, idDoEdycji;
    char wybor;

    odczytDanychZPliku(Przyjaciele);
    iloscPrzyjaciol = Przyjaciele.size();


    while (1) {
        if (numerKontrolny == 0) {
            system("cls");
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj dane po imieniu" << endl;
            cout << "3. Wyszukaj dane po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "9. Zakoncz program" << endl << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            switch (wybor) {
            case '1': {
                wczytywanieDanychPrzyjaciela(Przyjaciele);
                numerKontrolny = 1;
                break;

            }
            case '2': {
                system("cls");
                cout << "Podaj imie szukanego przyjaciela: ";
                cin >> szukaneImie;
                wyszukiwaniePoImieniu(szukaneImie, Przyjaciele );
                numerKontrolny = 1;
                break;


            }
            case '3': {
                system("cls");
                cout << "Podaj nazwisko szukanego przyjaciela: ";
                cin >> szukaneNazwisko;
                wyszukiwaniePoNazwisku(szukaneNazwisko, Przyjaciele );
                numerKontrolny = 1;
                break;
            }
            case '4': {
                system("cls");
                wyswietlenieWszystkichZapisanychOsob(Przyjaciele);
                numerKontrolny = 1;
                break;

            }
            case '5': {
                system("cls");
                cout << "Podaj id adresata, ktorego chcesz usunac: ";
                cin >> idDoUsuniecia;
                usuwanieAdresata(idDoUsuniecia,  Przyjaciele);
                numerKontrolny = 1;
                break;

            }
            case '6': {
                system("cls");
                cout << "Podaj id adresata, ktorego dane chcesz edytowac: ";
                cin >> idDoEdycji;
                numerKontrolny = edycjaAdresata(idDoEdycji, Przyjaciele);
                break;

            }
            case '9': {
                exit(0);
            }
            }



        } else {
            cout << endl;
            cout << "1. Powrot do menu glownego" << endl;
            cout << "2. Zakoncz program" << endl;
            cin >> wybor;
            switch (wybor) {
            case '1': {
                numerKontrolny = 0;
                break;
            }
            case '2': {
                exit(0);
            }
            }
        }
    }
    return 0;
}
