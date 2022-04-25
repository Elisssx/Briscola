#include <fstream>
#include <iostream>
using namespace std;


void _main(string user, int punteggio) {
    int righe = contaRighe();
    if (!esisteUtente(user))
        righe++;
    string nomi[righe];
    int dati[righe][5];
}


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
    
}


// Funzione che rimette i dati dell'utente nelle statistiche.txt
void stampaFile(string nomi[], int dati[][5], int n) {
    
}