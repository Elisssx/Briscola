#include <fstream>
#include <iostream>
using namespace std;


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
        getline(file, line);
        if (line == username) {
            return true;
        }
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
void inserisciUtente(string nomi[], int dati[][5], string username, int punteggio, int n) {
    int pos;
    if (esisteUtente(username, n)==true) { // L'utente esiste
        for (int i=0; i<n; i++) {
            if (nomi[i] == username)
                pos = i;
        }
        dati[pos][0] += punteggio;
        dati[pos][1]++;
        if (punteggio < 60)
            dati[pos][2]++;
        else if (punteggio == 60)
            dati[pos][3]++;
        else
            dati[pos][4]++;
    } else {
        pos = n;
        nomi[pos] = username;
        dati[pos][0] = punteggio;
        dati[pos][1]++;
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
    // Viva le tette
    ifstream file;
    file.open("statistiche.txt", ios::in);
    string s;
    while (getline(file, s))
        cout << s << endl;
    system("pause");
}


void registraUtente(string user, int punteggio) {
    int righe = contaRighe();
    if (!esisteUtente(user, righe))
        righe++;
    string nomi[righe];
    int dati[righe][5];
}