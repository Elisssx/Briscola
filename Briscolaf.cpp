#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>
// g++ briscolaf.cpp -o briscolaf.exe

using namespace std;
 
struct Carta 
{
    string carta; // es. asso?valori numerici per capire quale carta ? piu alta?
    int valore;
    string seme;
    bool briscola;
    bool uscita; // La carta ? gi? uscita?
    bool distribuita; // La carta ? gi? stata distribuita?
};
struct Mano
{
    string semeIniziale; // Il seme che ? stato giocato per prima nella mano
    Carta carteGiocatore[20]; // Carte utente
    Carta carteComputer[20]; // Carte computer
    Carta cartaATerra; // Carta che ? appena stata gettata dal computer
    bool giocatore; // Quale giocatore ha giocato per primo in questa mano? True se ? il computer, False se ? l'umano.
};
struct Partita
{
    string briscola; // Seme di briscola della partita corrente
    int giocatore; // punteggio Giocatore che ha giocato per primo
    int computer; // punteggio Computerr
    Carta mazzo[40]; // 40 carte totali
    Mano manoCorrente; // Mano corrente
};

void inizializzaMazzo(Partita &m)
{
    for (int i = 0; i < 40; i++) // Ciclo for per assegnare valore alle carte del mazzo
	{
        m.mazzo[i].uscita = false; // All'inizio nessuna carta ? ancora uscita
        m.mazzo[i].distribuita = false; // All'inizio nessuna carta ? ancora stata distribuita
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
        if (i<10)
            m.mazzo[i].seme = "Spada";
        if (i<20&&i>=10) //cosi nn ci sono doppioni
            m.mazzo[i].seme = "Bastoni";
        if (i<30&&i>=20)
            m.mazzo[i].seme = "Denari";
        if (i<40&&i>=30)
            m.mazzo[i].seme = "Coppe";
    }

    // Dice se ? una briscola
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
    // A questo punto il mazzo ? tutto dentro p.mazzo, lungo 40 e ordinato
    for (int i=0; i<20; i++) 
	{
        int x = rand()%40; //Numero da 0 a 39
        while (p.mazzo[x].distribuita) { // Finch? ? gi? stata distribuita
            x = rand()%40;
        }
        p.manoCorrente.carteComputer[i] = p.mazzo[x];
        p.mazzo[x].distribuita = true;
        while (p.mazzo[x].distribuita) { // Finch? ? gi? stata distribuita
            x = rand()%40;
        }
        p.manoCorrente.carteGiocatore[i] = p.mazzo[x];
        p.mazzo[x].distribuita = true;
    }
}

// Funzione che ti dice se il mazzo è esaurito
bool controllo(int x) {
    return x<=1;
    /*
    bool esaurito = true;
    for (int i = 0; i < 20; i++) {
        if (!p.manoCorrente.carteComputer[i].uscita) // ! significa NOT
            esaurito = false;
        if (!p.manoCorrente.carteGiocatore[i].uscita)
            esaurito = false;
    }
    return esaurito;
    */
}


// Funzione che fa gettare una carta al computer e che guarda se non ? gia uscita
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
		if (!p.manoCorrente.carteGiocatore[i].uscita)//se non ? uscita fa stampare
            cout << i+1 << ")" << p.manoCorrente.carteGiocatore[i].carta << " di " << p.manoCorrente.carteGiocatore[i].seme << " (valore: " << p.manoCorrente.carteGiocatore[i].valore << ')' << endl;
        else
            cout << i+1 << ")" << "<Carta uscita>" << endl;
    }
    cout<<""<<endl;
    if(p.giocatore>p.computer)
        cout<<"Bravo! stai vincendo :)"<<endl;
    if(p.giocatore<p.computer)
        cout<<"Stai perdendo...devi riformulare la tua strategia :("<<endl;
    if(p.giocatore==p.computer)
        cout<<"Continua cosi' stai pareggiando!! "<<endl;
    cout<<""<<endl;
    cout<<"Carta: ";
    int scelta; // Carta scelta dal giocatore
    cin >> scelta;
    while (scelta<1 || scelta>3 || p.manoCorrente.carteGiocatore[scelta-1].uscita) {//finch?  non ? gia uscita continua a richiederla oppure hai scelto un numero diverso dal 1 2 3 
        cout<<"Carta: ";
        cin >> scelta;
    }
    p.manoCorrente.carteGiocatore[scelta-1].uscita = true;
    return scelta-1; // Carta corretta da mettere nell'array   
}


// Funzione che scala tutte le carte al di sotto di sceltax in alto di una posizione
int scaloCarte(Partita &p, int lunghezza,int sceltax) {
    for(int i=sceltax; i<lunghezza-1; i++)// Tira tutte le carte indietro di uno 
    {
        p.manoCorrente.carteGiocatore[i] = p.manoCorrente.carteGiocatore[i+1];
	}
}


// Funzione che ritorna true se la carta sfidante vince quella a terra, altrimenti false ??
bool _vinceS(Carta terra, Carta sfidante) {
    if (terra.seme == sfidante.seme) {
        // Se i semi sono uguali, vince quella con il valore pi? alto
        return (terra.valore < sfidante.valore);
    } else {
        if (terra.briscola) {
            // Se la carta a terra ? di briscola vince
            return false;
        } else if (sfidante.briscola) {
            // Se la carta sfidante ? briscola e la carta a terra non lo ? allora vince la sfidante
            return true;
        } else {
            // Se i semi sono diversi e nessuno ? di briscola... allora vince la carta che era gi? a terra
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
    
    
    
    
    
    
void stampaFile(string nomi[], int dati[][5], int n);
    
// Funzione che ritorna il numero di righe presenti in statistiche.txt
int contaRighe() {
    ifstream file("statistiche.txt", ios::in);
    int count = 0;
    string line;
    while (getline(file, line)) {
        count++;
    }
    return count;
}


// Funzione che dice se l'utente esiste già nel file statistiche.txt
bool esisteUtente(string username, int n) {
    ifstream file("statistiche.txt", ios::in);
    string line;
    for (int i = 0; i < n; i++) {
        file >> line;
        if (line == username) // Line in questo momento è solo il primo elemento della linea
            return true;
        for (int j = 0; j < 5; j++) // Scorro i numeri, che non mi interessano
            file >> line;
    }
    return false;
}


// Funzione che legge il file statistiche.txt e ritorna i dati in un array
void leggiFile(string nomi[], int dati[][5], int n) {
    ifstream file("statistiche.txt", ios::in);
    for (int i = 0; i < n; i++) { // "Per ogni riga..."
        file >> nomi[i]; // La prima cosa che leggi va nell'array nomi perché è l'username
        for (int j = 0; j < 5; j++) { // "I successivi cinque valori..."
            file >> dati[i][j]; // Vengono messi dentro la matrice dati
        }
    }
}


// Funzione che inserisce i dati dell'utente nelle statistiche
void inserisciUtente(string nomi[], int dati[][5], string username, int punteggio, int n)
 {
    int pos;
    if (esisteUtente(username, n)==true) { // L'utente esiste
        for (int i=0; i<n; i++) {
            if (nomi[i] == username)
                pos = i;
        }
        /* primacolonna=username, secondacolonna=punteggio, partite totali, sconfitte, pareggi, vittorie*/
        dati[pos][0] += punteggio;
        dati[pos][1]++;
        if (punteggio < 60)
            dati[pos][2]++;
        else if (punteggio == 60)
            dati[pos][3]++;
        else
            dati[pos][4]++;
    } 
    else {
        pos = n-1;
        nomi[pos] = username;
        dati[pos][0] = punteggio;
        dati[pos][1] = 1;
        dati[pos][2] = 0;
        dati[pos][3] = 0;
        dati[pos][4] = 0;
        if (punteggio < 60)
            dati[pos][2]++;
        else if (punteggio == 60)
            dati[pos][3]++;
        else
            dati[pos][4]++;
    }
}


// Funzione che rimette i dati dell'utente nelle statistiche.txt
void stampaFile(string nomi[], int dati[][5], int n) {
    for (int i = 0; i < n; i++) {
        cout << nomi[i] << " ";
        for (int j = 0; j < 5; j++) {
            cout << dati[i][j] << " ";
        }
        cout << endl;
    }
}


// Stampa le statistiche
void stampaStatistiche() {
    
    ifstream file;
    file.open("statistiche.txt", ios::in);
    string s;
    while (getline(file, s))
        cout << s << endl;
    system("pause");
}


void scriviFile(string nomi[], int dati[][5], int n) {
    ofstream file;
    file.open("statistiche.txt", ios::out);
    for (int i = 0; i < n; i++) {
        file << nomi[i] << " ";
        for (int j = 0; j < 5; j++) {
            file << dati[i][j] << " ";
        }
        file << endl;
    }
}


void registraUtente(string user, int punteggio)
{
    int righe = contaRighe();
    
    if (!esisteUtente(user, righe))
        righe++;
         
    string nomi[righe];
    int dati[righe][5];
    leggiFile(nomi, dati, righe);
    inserisciUtente(nomi, dati, user, punteggio, righe);
    scriviFile(nomi, dati, righe);
}


int main() 
{
    stampaStatistiche();
    cout<<"Benvenuto a Briscola"<<endl;
    cout<<"Questo gioco si svolgera' come una normale partita di briscola, con la sola differenza che il tuo avversario sara' il computer, a te bastera' scegliere la carta vincente"<<endl;
    cout<<"inserisci nome utente"<<endl;
    string utente;
    cin>>utente;
	cout<<"Digita 'continua' per andare avanti"<<endl;
	string continua;
	cin>>continua;
	while(continua!="continua")
	{
		cout<<"Digita 'continua' per andare avanti"<<endl;
		cin>>continua;
	}
	// mazzo semi valori
    Partita m;
    m.giocatore = 0;//azzera punteggi
    m.computer = 0;

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

    while(!controllo(x))
    {
        computer(m);
    	int s = stampaCarteGiocatore(m);
        assegnaPunti(m, s);
    	scaloCarte(m, x, s);
        x--;
	}
    registraUtente(utente, m.giocatore);

  	return 0;
}

