#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;
 
struct Carta 
{
    string carta; // es. asso…valori numerici per capire quale carta è piu alta?
    int valore;
    string seme;
    bool briscola;
    bool uscita; // La carta è già uscita?
    bool distribuita; // La carta è già stata distribuita?
};
struct Mano
{
    string semeIniziale; // Il seme che è stato giocato per prima nella mano
    Carta carteGiocatore[20]; // Carte utente
    Carta carteComputer[20]; // Carte computer
    Carta cartaATerra; // Carta che è appena stata gettata dal computer
    bool giocatore; // Quale giocatore ha giocato per primo in questa mano? True se è il computer, False se è l'umano.
};
struct Partita
{
    string briscola; // Seme di briscola della partita corrente
    int giocatore; // punteggio Giocatore che ha giocato per primo
    int computer; // punteggio Computer
    Carta mazzo[40]; // 40 carte totali
    Mano manoCorrente; // Mano corrente
};
 
void spiegazionebriscola()
{
    cout << "Cicucia";
}


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
        // cosi per tutte le carte
        if (i%4 == 0)
            m.mazzo[i].seme = "Spada";
        if (i%4 == 1)
            m.mazzo[i].seme = "Bastoni";
        if (i%4 == 2)
            m.mazzo[i].seme = "Denari";
        if (i%4 == 3)
            m.mazzo[i].seme = "Coppe";
    }
    // Dice se è una briscola
    for (int i=0; i<40; i++) 
    {
        m.mazzo[i].briscola = false;
        if (m.mazzo[i].seme==m.briscola)
            m.mazzo[i].briscola=true;
    }
}


// Divide il mazzo originale da 40 in 2 mani
void dividiMazzo(Partita &p)
{
    // A questo punto il mazzo è tutto dentro p.mazzo, lungo 40 e ordinato
    for (int i=0; i<20; i++) {
        int x = rand()%40; //Numero da 0 a 39
        while (p.mazzo[x].distribuita) { // Finché è già stata distribuita
            x = rand()%40;
        }
        p.manoCorrente.carteComputer[i] = p.mazzo[x];
        p.mazzo[x].distribuita = true;
        while (p.mazzo[x].distribuita) { // Finché è già stata distribuita
            x = rand()%40;
        }
        p.manoCorrente.carteGiocatore[i] = p.mazzo[x];
        p.mazzo[x].distribuita = true;
    }
}


// Funzione che ti dice se il mazzo è esaurito
bool controllo(Partita &p) {
    bool esaurito = true;
    for (int i = 0; i < 20; i++) {
        if (!p.manoCorrente.carteComputer[i].uscita) // ! significa NOT
            esaurito = false;
        if (!p.manoCorrente.carteGiocatore[i].uscita)
            esaurito = false;
    }
    return esaurito;
}


// Funzione che fa gettare una carta al computer e che guarda se non è gia uscita
void computer(Partita &p) {
    int i = 0;
    while (p.manoCorrente.carteComputer[i].uscita)
        i++;
    p.manoCorrente.carteComputer[i].uscita = true;
    p.manoCorrente.cartaATerra = p.manoCorrente.carteComputer[i];
}


// Funzione che mostra al giocatore le tre carte in cima al mazzetto e gliene fa scegliere una
int stampaCarteGiocatore(Partita &p) {
    system("cls"); // Cancella lo schermo
    cout << p.computer << " - " << p.giocatore << "   (Briscola: " << p.briscola << ")" << endl;
    cout << "COMPUTER: " << p.manoCorrente.cartaATerra.carta << " di " << p.manoCorrente.cartaATerra.seme << " (valore: " << p.manoCorrente.cartaATerra.valore << ')' << endl;//mette la carta buttata dal giocatore precendente(computre)
	cout<<"Ecco le carte a disposizione"<<endl;
	for (int i=0;i<3;i++) {  
		if (!p.manoCorrente.carteGiocatore[i].uscita)//se non è uscita fa stampare
            cout << i+1 << ")" << p.manoCorrente.carteGiocatore[i].carta << " di " << p.manoCorrente.carteGiocatore[i].seme << " (valore: " << p.manoCorrente.carteGiocatore[i].valore << ')' << endl;
        else
            cout << i+1 << ")" << "<Carta uscita>" << endl;
    }
    cout<<"Carta: ";
    int scelta; // Carta scelta dal giocatore
    cin >> scelta;
    while (scelta<1 || scelta>3 || p.manoCorrente.carteGiocatore[scelta-1].uscita) {//finchè  non è gia uscita continua a richiederla oppure hai scelto un numero diverso dal 1 2 3 
        cout<<"Carta: ";
        cin >> scelta;
    }
    p.manoCorrente.carteGiocatore[scelta-1].uscita = true;
    return scelta-1; // Carta corretta da mettere nell'array   
}


// Funzione che scala tutte le carte al di sotto di sceltax in alto di una posizione
int scaloCarte(Partita &p, int lunghezza,int sceltax) {
    for(int i=sceltax; i<lunghezza-1; i++)// Tira tutte le carte indietro di uno 
        p.manoCorrente.carteGiocatore[i] = p.manoCorrente.carteGiocatore[i+1];
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
    if (_vinceS(p.manoCorrente.cartaATerra, p.manoCorrente.carteGiocatore[s]))// Se la carta del giocatore batte quella del computer
        p.giocatore += p.manoCorrente.cartaATerra.valore + p.manoCorrente.carteGiocatore[s].valore;//se _vinceS ritorna true i punti vanno al giocatore
    else
        p.computer += p.manoCorrente.cartaATerra.valore + p.manoCorrente.carteGiocatore[s].valore;//se _vinceS ritorna false i punti vanno al PC
}


int main() 
{
	int istruzioni;
    cout<<"Benvenuto su briscola"<<endl;
    cout<<"inserisci nome utente"<<endl;
    string utente;
    cin>>utente;
	cout<<" puoi scoprire le regole del gioco digitando '1'.  In alternativa puoi iniziare una nuova partita, digitando '2'"<<endl;
    cin>>istruzioni;
    if(istruzioni==1)
        spiegazionebriscola();
    else if(istruzioni!=2)
    	return 0;

    // mazzo semi valori
    Partita m;

  	//random seme primario
    srand(time(0)); // Rende casuale la generazione di numeri casuali con rand() sulla base dell'orario corrente
    int s = rand()%4; // Genera un numero casuale tra 0 e 3
    if (s == 0)
        m.briscola = "Spada";
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
