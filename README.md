# P2-project: qDB
Sistema minimale per la gestione di un database tramite GUI (Università degli Studi di Padova, Progetto didattico relativo al corso di Programmazione ad Oggetti 2013/2014, Stefano Munari)

# Descrizione:
Lo scopo del progetto qDB è lo sviluppo in C++/Qt di un sistema minimale per la gestione di un (piccolo) database tramite una interfaccia grafica utente.

Tutte le parti sono state implementate utilizzando il linguaggio C++ in quanto richiesto dal corso e il framework Qt per implementare le views. Maggiori dettagli sono indicati nei documenti "specificaProgetto.pdf" e "qDB.pdf" che rappresenta la relazione finale consegnata.

# Struttura cartelle:
	
    |
    |_src/:
	|     |
	|	  |__ model/: contiene il modello definito per il progetto, ovvero una gerarchia di personaggi RPG;
	|	  |		 |
	|	  |		 |__ business_logic: contiene la struttura dati per la gestione del database, contiene functor.h in cui vengono definiti i funtori utilizzati per implementare la funzionalità di ricerca nel DB;
	|	  |
	|	  |
	|	  |__ view/: contiene le varie view definite utilizzando il farmework Qt;
	|	  |
	|	  |__ controller/: contiene il controller, quest'ultimo si occupa di notificare il model ed aggiornare le view in base ai dati ottenuti dal model. Implementato attraverso il pattern singleton;
    |
	|_docs/: cartella che contiene la specifica di progetto e la relazione consegnata;
	|
	|_examples/: contiene un file .xml per popolare il DB;
	|
	|_images/: cartella contenente le immagini utilizzate nelle view;
	|
	|_test/: cartella contenente file .txt utili per testare il programma.