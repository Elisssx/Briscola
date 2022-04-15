#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;
 
struct Carta {
    string carta; // es. asso…valori numerici per capire quale carta è piu alta?
    string seme;
    int valore;
    bool briscola;
    bool uscita; // La carta è già uscita?
    bool distribuita; // La carta è già stata distribuita?
};
struct Partita {
    string briscola; // Seme di briscola della partita corrente
    int giocatore; // punteggio Giocatore
    int computer; // punteggio Computer
    Carta carteGiocatore[20]; // Carte utente
    Carta carteComputer[20]; // Carte computer
    Carta mazzo[40]; // 40 carte totali
    Carta cartaATerra; // Carta che è appena stata gettata dal computer
    int _contatoreComputer; // Contatore carte computer
};


void inizializzaMazzo(Partita &m)
{
    for (int i = 0; i < 40; i++) // Ciclo for per assegnare valore alle carte del mazzo
	{
        m.mazzo[i].uscita = false; // All'inizio nessuna carta è ancora uscita
        m.mazzo[i].distribuita = false; // All'inizio nessuna carta è ancora stata distribuita
        if (i%10 == 0) 
        {
            m.mazzo[i].carta = "Asso";
            m.mazzo[i].valore = 11;
        }
        else if (i%10 == 1) 
        {
            m.mazzo[i].carta = "Due";
            m.mazzo[i].valore = 0;
        } 
        else if (i%10 == 2) {
            m.mazzo[i].carta = "Tre";
            m.mazzo[i].valore = 10;
        } 
        else if (i%10 == 3) 
        {
            m.mazzo[i].carta = "Quattro";
            m.mazzo[i].valore=0;
        } 
        else if (i%10 == 4)
        {
            m.mazzo[i].carta = "Cinque";
            m.mazzo[i].valore=0;
        } 
        else if (i%10 == 5) 
        {
            m.mazzo[i].carta = "Sei";
            m.mazzo[i].valore=0;
        } 
        else if (i%10 == 6) 
        {
            m.mazzo[i].carta = "Sette";
            m.mazzo[i].valore=0;
        } 
        else if (i%10 == 7) 
        {
            m.mazzo[i].carta = "Fante";
            m.mazzo[i].valore=2;
        } 
        else if (i%10 == 8) 
        {
            m.mazzo[i].carta = "Cavallo";
            m.mazzo[i].valore=3;
        } 
        else if (i%10 == 9) 
        {
            m.mazzo[i].carta = "Re";
            m.mazzo[i].valore=4;
        }
        if (i%4 == 0)
            m.mazzo[i].seme = "Spade";
        if (i%4 == 1)
            m.mazzo[i].seme = "Bastoni";
        if (i%4 == 2)
            m.mazzo[i].seme = "Denari";
        if (i%4 == 3)
            m.mazzo[i].seme = "Coppe";
    }
    // Dice se è una briscola
    for (int i=0; i<40; i++)
        m.mazzo[i].briscola = (m.mazzo[i].seme == m.briscola);
}


void _debugMazzo(Partita &m)
{
    string s = "          ";
    for (int i=0; i<40; i++)
        cout << m.mazzo[i].carta << s << m.mazzo[i].seme << s << m.mazzo[i].valore << s << m.mazzo[i].briscola << s << m.mazzo[i].uscita << s << m.mazzo[i].distribuita << endl;
    system("pause");
}


// Divide il mazzo originale da 40 in 2 mani
void dividiMazzo(Partita &p)
{
    // A questo punto il mazzo è tutto dentro p.mazzo, lungo 40 e ordinato
    srand(time(0)); // Inizializza il generatore di numeri casuali
    int x; // Variabile per il ciclo for
    for (int i=0; i<20; i++) {
        x = rand()%40; // Numero da 0 a 39
        while (p.mazzo[x].distribuita) // Finché è già stata distribuita
            x = rand()%40;
        p.carteComputer[i] = p.mazzo[x];
        p.mazzo[x].distribuita = true;

        x = rand()%40;
        while (p.mazzo[x].distribuita) // Finché è già stata distribuita
            x = rand()%40;
        p.carteGiocatore[i] = p.mazzo[x];
        p.mazzo[x].distribuita = true;
    }

    _debugMazzo(p);
}


// Funzione che ti dice se il mazzo è esaurito
bool controllo(Partita &p) {
    bool esaurito = true;
    for (int i = 0; i < 20; i++) {
        if (!p.carteComputer[i].uscita) // ! significa NOT
            esaurito = false;
        if (!p.carteGiocatore[i].uscita)
            esaurito = false;
    }
    return esaurito;
}


// Funzione che fa gettare una carta al computer e che guarda se non è gia uscita
void computer(Partita &p) {
    p.carteComputer[p._contatoreComputer].uscita = true;
    p.cartaATerra = p.carteComputer[p._contatoreComputer];
    p._contatoreComputer++;
}


// Funzione che mostra al giocatore le tre carte in cima al mazzetto e gliene fa scegliere una
int stampaCarteGiocatore(Partita &p) {
    system("cls"); // Cancella lo schermo
    cout << p.computer << " - " << p.giocatore << "   (Briscola: " << p.briscola << ")" << endl << endl;
    cout << "COMPUTER: " << p.cartaATerra.carta << " di " << p.cartaATerra.seme << " (valore: " << p.cartaATerra.valore << ')' << endl << endl;//mette la carta buttata dal giocatore precendente(computre)
	for (int i=0;i<3;i++) {  
		if (!p.carteGiocatore[i].uscita)//se non è uscita fa stampare
            cout << i+1 << ") " << p.carteGiocatore[i].carta << " di " << p.carteGiocatore[i].seme << " (valore: " << p.carteGiocatore[i].valore << ')' << endl;
        else
            cout << i+1 << ") " << "<Carta uscita>" << endl;
    }
    cout<<"Carta: ";
    int scelta; // Carta scelta dal giocatore
    cin >> scelta;
    while (scelta<1 || scelta>3 || p.carteGiocatore[scelta-1].uscita) {//finchè  non è gia uscita continua a richiederla oppure hai scelto un numero diverso dal 1 2 3 
        cout<<"Carta: ";
        cin >> scelta;
    }
    p.carteGiocatore[scelta-1].uscita = true;
    return scelta-1; // Carta corretta da mettere nell'array   
}


// Funzione che scala tutte le carte al di sotto di sceltax in alto di una posizione
void scaloCarte(Partita &p, int lunghezza, int sceltax) {
    for(int i=sceltax; i<lunghezza-1; i++)// Tira tutte le carte indietro di uno 
        p.carteGiocatore[i] = p.carteGiocatore[i+1];
}


// Funzione che ritorna true se la carta sfidante vince quella a terra, altrimenti false ☑️
bool _vinceS(Carta terra, Carta sfidante) {
    if (terra.seme == sfidante.seme) {
        // Se i semi sono uguali, vince quella con il valore più alto
        return (terra.valore < sfidante.valore);
    } else {
        if (terra.briscola) {
            // Se la carta a terra è di briscola vince
            return false;
        } else if (sfidante.briscola) {
            // Se la carta sfidante è briscola e la carta a terra non lo è allora vince la sfidante
            return true;
        } else {
            // Se i semi sono diversi e nessuno è di briscola... allora vince la carta che era già a terra
            return false;
        }
    }
}


// Funzione che assegna i punti
void assegnaPunti(Partita &p, int s) {
    // Se la carta sfidante vince la carta a terra, allora il giocatore guadagna un punto
    if (_vinceS(p.cartaATerra, p.carteGiocatore[s]))// Se la carta del giocatore batte quella del computer
        p.giocatore += p.cartaATerra.valore + p.carteGiocatore[s].valore;//se _vinceS ritorna true i punti vanno al giocatore
    else
        p.computer += p.cartaATerra.valore + p.carteGiocatore[s].valore;//se _vinceS ritorna false i punti vanno al PC
}


int main() 
{
	int istruzioni;
    cout << "Benvenuto su Briscola"<<endl;
    cout << "Username: ";
    string utente;
    cin >> utente;

    // mazzo semi valori
    Partita m;
    m.giocatore = 0; // Azzera i punteggi
    m.computer = 0;
    m._contatoreComputer = 0;

  	//random seme primario
    srand(time(0)); // Rende casuale la generazione di numeri casuali con rand() sulla base dell'orario corrente
    int s = rand()%4; // Genera un numero casuale tra 0 e 3
    if (s == 0)
        m.briscola = "Spade";
    else if (s == 1)
        m.briscola = "Bastoni";
    else if (s == 2)
        m.briscola = "Denari";
    else if (s == 3)
        m.briscola = "Coppe";

    inizializzaMazzo(m);
    dividiMazzo(m);
    int x=20; // Lunghezza residua del mazzo del giocatore
    
    while(!controllo(m))
    {
        computer(m);
    	int s = stampaCarteGiocatore(m);
        assegnaPunti(m, s);
    	scaloCarte(m, x, s);
	}
  	return 0;
}
