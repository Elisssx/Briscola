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
};
struct Mano
{
    string semeIniziale; // Il seme che è stato giocato per prima nella mano
    Carta carteGiocatore[20]; // Carte utente
    Carta carteComputer[20]; // Carte computer
    bool giocatore; // Quale giocatore ha giocato per primo in questa mano? True se è il computer, False se è l'umano.
};
struct Giocatore
{
   int punteggio;
};
struct Partita
{
    string briscola; // Seme di briscola della partita corrente
    Giocatore giocatore; // Giocatore che ha giocato per primo
    Giocatore computer; // Computer
    Carta mazzo[40]; // 40 carte totali
    Mano manoCorrente; // Mano corrente
};
 
void spiegazionebriscola()
{
    int x=1;
    cout<<"Briscola è un gioco molto semplice, si dispongono di 40 carte, divise in 4 corrispettivi semi:"<<endl;
    cout<<"bastoni"<<endl;
    cout<<"coppa"<<endl;
    cout<<"denari"<<endl;
    cout<<"spade"<<endl;
    cout<<"premi un tasto per continuare"<<endl;
    
    

    cout<<"tutte le carte assumono un valore costante, ciò non succede però per le cosiddette ‘scartelle’, ovvero le carte numerate. Le carte numerate possono comportarsi in 3 modi diversi:."<<endl;
	cout<<"se la scartella non appartiene al seme della partita e viene battuta contro una carta appartenente al seme della partita assume valore nullo"<<endl;
	cout<<"se la scartella appartiene al seme della partita e viene battuta contro una carta non appartenente al seme di briscola, assume automaticamente il valore maggiore fra le due"<<endl;
	cout<<"se la scartella viene battuta contro un’altra scartella vince quella dal valore maggiore"<<endl;
	cout<<"queste regole non si applicano al 3, che ha sempre valore costante"<<endl;
    cout<<"i valori delle carte sono i seguenti"<<endl;
    cout<<"l'asso vale 11 punti "<<endl;
    cout<<"il 3 vale 10 punti"<<endl;
    cout<<"il re vale 4 punti"<<endl;
    cout<<"il cavallo vale 3 punti"<<endl;
    cout<<"il fante vale 2 punti"<<endl;
    cout<<"schiaccia un pulsante per continuare"<<endl;
    system("PAUSE");
    
    //qui dobbiamo capire come dichiarare  un invio, in quanto se dichiarata in int il compilatore procede solamente se x è un numero
    cout<<"vengono consegnate 3 carte per ogni giocatore, in seguito viene pescata una carta che designerà il seme per la partita "<<endl;
    cout<<"ovviamente le carte con il seme pescato vinceranno sempre contro qualsiasi carta di altro seme compreso l'asso."<<endl;
    cout<<"Se vuoi una piccola curiosità digita 'si'"<<endl;
    string si;
    cin>>si;
    if(si=="si")
    {
        cout<<"Nel gioco della briscola in coppia, non è possibile parlare tra compagni, e bisogna comunicare con la gestualità cercando di "<<endl;
        cout<<"evitare lo sguardo degli avversari. Ecco i segni più frequenti con il corrispettivo significato"<<endl;
        cout<<"distorcere la bocca indica il possesso del Tre"<<endl;
        cout<<"alzare gli occhi al cielo indica il possesso del Re"<<endl;
        cout<<"alzare leggermente una spalla per indicare il possesso del Fante"<<endl;
        cout<<"mostrare la punta della lingua per indicare il possesso del Cavallo"<<endl;
        cout<<"serrare le labbra per indicare il possesso dell’Asso"<<endl;
        cout<<"Inoltre, è consentito ai giocatori appartenenti alla stessa squadra di scambiarsi le carte a vicenda, prima dell’ultima mano, per capire la strategia da mettere in campo"<<endl;
		cout<<"premi 2 per tornare al gioco"<<endl;
		cin>>x;
		if(x==2)
		{
			//mi porta al gioco
		}
		
    }
}
 


void inizializzaMazzo(Partita &m)
{
    for (int i = 0; i < 40; i++) //for per assegnare valore alle carte del mazzo
	{
        m.mazzo[i].uscita = false; // All'inizio nessuna carta è ancora uscita
        if (i%10 == 0) 
        {
            m.mazzo[i].carta = "Asso";
            m.mazzo[i].valore = 11;
        }
        else if (i%10 == 1) 
        {
            m.mazzo[i].carta = "Due";
            m.mazzo[i].valore = 0;
        } else if (i%10 == 2) {
            m.mazzo[i].carta = "Tre";
               } else if (i%10 == 3) {
            m.mazzo[i].carta = "Quattro";
            m.mazzo[i].valore=0;
            } else if (i%10 == 4) {
            m.mazzo[i].carta = "Cinque";
            m.mazzo[i].valore=0;
            } else if (i%10 == 5) {
            m.mazzo[i].carta = "Sei";
            m.mazzo[i].valore=0;
            } else if (i%10 == 6) {
            m.mazzo[i].carta = "Sette";
            m.mazzo[i].valore=0;
            } else if (i%10 == 7) {
            m.mazzo[i].carta = "Fante";
            m.mazzo[i].valore=2;
            } else if (i%10 == 8) {
            m.mazzo[i].carta = "Cavallo";
            m.mazzo[i].valore=3;
            } else if (i%10 == 9) {
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
    /*
    for(int g=0;g<40;g++)
    {
        cout<<m.mazzo[g].seme<<' ';
        cout<<m.mazzo[g].carta<<endl;
  	}
    */
}


void distribuisciCarte(Partita &p) //DISTRIBUISCE LE CARTE CON MAZZI DA 20 GIA PREDEFINITI!!!
{
    int contatore=0;
    while (contatore < 40) 
    {
        int numero = rand() % 40;//genera un numero tra 0 e 40

        if(!p.mazzo[numero].uscita) // uscita � bool quindi se non � uscita la carta fa la procedura DOMANDA 
        {
            if (contatore%2 != 0) //se contatore � dispari va al giocatore
            { 
                p.manoCorrente.carteGiocatore[contatore]=p.mazzo[numero];
                p.mazzo[numero].uscita=true;
            } 
            else // se contatore � pari va al pc
            { 
                p.manoCorrente.carteComputer[contatore] = p.mazzo[numero];
                p.mazzo[numero].uscita = true;
            }
        }
        contatore++;
    }
}


bool controllo(Partita &p) { // Funzione che ti dice se il mazzo è esaurito
    bool esaurito = true;
    for (int i = 0; i < 40; i++)
        if (!p.mazzo[i].uscita) // ! significa NOT
            esaurito = false;
    return esaurito;
}
int tishowolecarte(Partita &p,int numc){//!!!!!!ho provato a fare quello che avevamo detto ieri sera nelle due funzioni 
	cout<<"ecco le tue carte a disposizione"<<endl;
	for(int i=0;i<3;i++)
	{
		cout<<"1) "<<p.carteGiocatore[i]<<endl;;
	}
	cout<<"scegli una delle seguenti carte"<<endl;
	cin>>numc;
	return numc;
	
}
int scalocarta(Partita &p,int numc){
	for(int i=numc;i<20-1;i++)
	{
		p.carteGiocatore[i]=p.carteGiocatore[i+1];//!!!!!non so che struct mettere qua c'� le carte che ha in mano il giocatore 
	}
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
    {
        spiegazionebriscola();
    }
    else
    {
    	if(istruzioni!=2)
    		return 0;
    }

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

    inizializzaMazzo(m); // Ciao

    // Funzione che distribuisce le tre carte in mano al giocatore
    distribuisciCarte(m);
    int cartascelta;
    
    while(!controllo(m))
    {
    	tishowolecarte(m,cartascelta);
    	scalocarta(m.cartascelta);
	}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    while (!controllo(m)) 
    {

        mossaComputer(m);
        mossaUtente(m);

        //if per verificare se le carte hanno seme dominantem, if per verificare la carta con valore maggiore fra le due

        //ripetizione assegnazione carta (una carta) ☑️
        //quando il mazzo finisce finisce la partita ☑️
        
        
        //file di testo che memorizza il punteggio degli utenti
    }

    // Funzione che fa il conteggio dei punti
  	return 0;
}
