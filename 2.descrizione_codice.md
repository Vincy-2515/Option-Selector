* ### initializeSelection()
	- **_Descrizione_**:  E' la funzione principale della libreria e si occupa oltre
		che alle chiamate delle altre funzioni, anche dell'allocazione e 
		la deallocazione delle variabili e alla gestione del tasto premuto in 
		input.

	- **_Parametri_**: 
		| Parametro | Valori accettati | Descrizione |
		| --- | --- | --- |
		| use_columns | valore = 0 o 1 | permette di scegliere l'uso di colonne nella griglia delle opzioni |
		| use_rows | valore = 0 o 1 | permette di scegliere l'uso di righe nella griglia delle opzioni |
		| max_options | valore >= 2 | indica il numero di opzioni che comporrà la griglia |
		| max_columns | valore > 0 | permette la scelta del numero di colonne che comporranno la griglia |
		| max_rows | valore > 0 | permette la scelta del numero di righe che comporranno la griglia |
		| max_option_string_length | valore > 3 | lunghezza effetiva della stringa più lunga + 2 (**NECESSARIO PER IL CORRETTO FUNZIONAMENTO**) |
		| path | stringa | indica il percorso di destinazione del file che conterrà le stringhe delle opzioni |
		| start_x | valore > 0 | indica da quale colonna del terminale cominciare a stampare le opzioni |
		| start_y | valore > 0 | indica da quale riga del terminale cominciare a stampare le opzioni |

	- **Ritorna**: il valore dell'opzione selezionata (a partire da 0), mentre in caso di 
		errore ne ritorna il codice.

* ### setSettings()

	- **_Descrizione_**: Prende in input tutti i parametri della funzione 
		"initializeSelection()", più una struct "settings" per poi caricargli tutti i valori
		corrispondenti all'interno.
		
	- **_Parametri_**:
		| Parametro | Valori accettati | Descrizione |
		| --- | --- | --- |
		| indentici a "initializeSelection()" | ... | ... |
		| *p_settings | --- | puntatore alla struct contenente tutte le impostazioni di visualizzazione |

	- **_Ritorna_**: nulla.

* ### checkSettings()
	- **_Descrizione_**: Si occupa del controllo di tutte le impostazioni contenute nella struct 
		"settings".

	- **_Parametri_**:
		| Parametro | Valori accettati | Descrizione |
		| --- | --- | --- |
		| settings | --- | struct contenente tutte le impostazioni di visualizzazione |

	- **_Ritorna_**: 0 in caso di nessun errore, altrimenti il codice rispettivo.

* ### printOptionsStrings()
	
	- **_Descrizione_**: Si occupa prima di tutto di cancellare la porzione di schermo riguardante 
		le opzioni stampate, di recuperare le stringhe delle opzioni tramite la funzione "getStrings()", 
		e successivamente in base alle impostazioni fornite sceglie la funzione per la stampa delle 
		opzioni corrispondente al layout richiesto.
	
	- **_Parametri_**:
		| Parametro | Valori accettati | Descrizione |
		| --- | --- | --- |
		| settings | --- | struct contenente tutte le impostazioni di visualizzazione |
		| **options_strings | stringhe | matrice contenente le stringhe delle opzioni |
		| selected_option | valore > 0 | contiene il numero dell'opzione selezionata |

	- **_Ritorna_**: 0 in caso di nessun errore, altrimenti il codice rispettivo.

* ### getStrings()
	- **_Descrizione_**: Si occupa di recuperare le stringhe delle opzioni dal file 
  		che le contiene, implementando vari controlli sul file e sulle stringhe da
		copiare.

	- **_Parametri_**: 
		| Parametro | Valori accettati | Descrizione |
		| --- | --- | --- |
		| settings | --- | struct contenente tutte le impostazioni di visualizzazione |
		| **options_strings | stringhe | matrice contenente le stringhe delle opzioni |

	- **_Ritorna_**: 0 in caso di nessun errore, altrimenti il codice rispettivo.

* ### printOnOnlyColumnsGrid()

	- **_Descrizione_**: Si occupa di stampare le opzioni in una griglia di sole colonne.

	- **_Parametri_**:
		| Parametro | Valori accettati | Descrizione |
		| --- | --- | --- |
		| settings | --- | struct contenente tutte le impostazioni di visualizzazione |
		| **options_strings | stringhe | matrice contenente le stringhe delle opzioni |
		| selected_option | valore > 0 | contiene il numero dell'opzione selezionata |
	
	- **_Ritorna_**: nulla.

* ### printOnOnlyRowsGrid()

	- **_Descrizione_**: Si occupa di stampare le opzioni in una griglia di sole righe.
  
	- **_Parametri_**:
		| Parametro | Valori accettati | Descrizione |
		| --- | --- | --- |
		| settings | --- | struct contenente tutte le impostazioni di visualizzazione |
		| **options_strings | stringhe | matrice contenente le stringhe delle opzioni |
		| selected_option | valore > 0 | contiene il numero dell'opzione selezionata |

	- **_Ritorna_**: nulla.

* ### printOnGrid()

	- **_Descrizione_**: Si occupa di stampare le opzioni in una griglia contenente sia righe che colonne.
  
	- **_Parametri_**:
		| Parametro | Valori accettati | Descrizione |
		| --- | --- | --- |
		| settings | --- | struct contenente tutte le impostazioni di visualizzazione |
		| **options_strings | stringhe | matrice contenente le stringhe delle opzioni |
		| selected_option | valore > 0 | contiene il numero dell'opzione selezionata |
	
	- **_Ritorna_**: nulla.
  
* ### printOption()

	- **_Descrizione_**: Si occupa di stampare le opzioni usando le impostazioni di personalizzazione
		predefinite tramite costanti ("SELECTED_OPTION_INDICATOR", "UNSELECTED_OPTION_INDICATOR").

	- **_Parametri_**: 
		| Parametro | Valori accettati | Descrizione |
		| --- | --- | --- |
		| **options_strings | stringhe | matrice contenente le stringhe delle opzioni |
		| option_number | valore > 0 | numero dell'opzione da stampare |
		| option_type | 0 o 1 | indica se deve essere stampata l'opzione selezionata o meno |

	- **_Ritorna_**: nulla.

* ### checkGridLimitOverflow()

	- **_Descrizione_**: Si occupa di controllare che i valori di x e y del cursore non aquisiscano
		valori impossibili per la griglia di opzioni fornita.

	- **_Parametri_**:
		| Parametro | Valori accettati | Descrizione |
		| --- | --- | --- |
		| settings | --- | struct contenente tutte le impostazioni di visualizzazione |
		| *p_x | interi | puntatore alla variabile x |
		| *p_y | interi | puntatore alla variabile y |
		| last_input | carattere | indica l'ultimo tasto premuto dall'utente |

	- **_Ritorna_**: nulla.

* ### verifySelectedOptionCoords()

	- **_Descrizione_**: Si occupa della determinazione dell'opzione su cui è attualmente il cursore,
		ciò possibile grazie alla comparazione delle coordinate del cursore e quelle delle opzioni
		rapperesentate nel formato seguente: `yyyxxx`.
	
	- **_Parametri_**:
		| Parametro | Valori accettati | Descrizione |
		| --- | --- | --- |
		| settings | --- | struct contenente tutte le impostazioni di visualizzazione |
		| *options_coords | valore >= 0 | vettore contenente le coordinate di tutte le opzioni |
		| x | valore >= 0 | indica la coordinata x del cursore |
		| y | valore >= 0 | indica la coordinata y del cursore |
	
	- **_Ritorna_**: 0 in caso di nessun errore, altrimenti il codice ripsettivo.

* ### generateOptionsCoordinates()

	- **_Descrizione_**: Si occupa della generazione delle coordinate delle opzioni rispettando
		il formato seguente: `yyyxxx` e salvandole nel vettore "*options_coords".
	
	- **_Parametri_**:
		| Parametro | Valori accettati | Descrizione |
		| --- | --- | --- |
		| settings | --- | struct contenente tutte le impostazioni di visualizzazione |
		| *options_coords | valore >= 0 | vettore contenente le coordinate di tutte le opzioni |

	- **_Ritorna_**: nulla.

*fin* :)