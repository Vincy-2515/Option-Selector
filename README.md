<p align="center">
    <img alt = "" src = "src/resources/media/images/option_selector_readme_banner.png">
</p>

---

<p align="center">
    <img alt="c language" src="https://img.shields.io/badge/-C-black?style=for-the-badge&logo=c">
    <span>&nbsp;&nbsp;</span>
    <img alt="versione - v1.0.0.0" src="https://img.shields.io/badge/Versione-v1.0.0.0-black?style=for-the-badge">
    <span>&nbsp;&nbsp;</span>
    <img alt="wiki" src="https://img.shields.io/badge/-Wiki-black?style=for-the-badge&logo=wikibooks&link=linkmoltolungodasostituire##########################################################################################################">
</p>


## Cos'è?
E' una semplice libreria scritta in C che permette la creazione e la navigazione di una lista di opzioni in una console, 
navigazione che avviene tramite l'uso di tasti che permettono al cursore di spostarsi tra le opzioni. 
Permette varie opzioni di personalizzazione dalla scelta del layout della lista di opzioni, 
al modo in cui appaiono le opzioni selezionate e non.
<p align="center">
    <img alt="gif-risultato" src="src\resources\media\gifs\full_grid.gif"> 
</p>


## Come funziona?
Le opzioni vengono stampate da sinistra verso destra e dall'alto verso il basso (comportamento non modificabile), 
ad ogni opzione viene poi assegnata una stringa, ovvero il label dell'opzione che sarà successivamente visualizzato, 
e delle coordinate per determinare la sua posizone in questa pseudo-griglia di opzioni, tramite la pressione dei 
tasti predefiniti poi vengono incrementate o decrementate le variabili x e y che determinaeranno la posizione del cursore, 
una volta premuto il tasto di conferma, verrà poi restituito il numero dell'opzione selezionata. Dietro tutto questo è 
anche presente un robusto sistema di controllo che gestisce vari casi ed eccezzioni.

## Come utilizzare la libreria?
<ul>
    <li>
        <h3>Impostazioni</h3>
        <p>
            Di seguito è riportato l'elenco dei parametri richiesti, e una rappresentazione sotto forma di codice
            che rispetta l'ordine dei parametri della funzione "initializeSelection()":
        </p>
        <table>
            <tr> <th>Parametro</th> <th>Valori accettati</th> <th>Descrizione</th> </tr>
            <tr> <td><b>use_columns</b></td> <td>x = 0 o 1</td> <td>permette di scegliere l'uso di colonne nella griglia delle opzioni</td> </tr>
            <tr> <td><b>use_rows</b></td> <td>x = 0 o 1</td> <td>permette di scegliere l'uso di righe nella griglia delle opzioni</td> </tr>
            <tr> <td><b>max_options</b></td> <td>x >= 2</td> <td>indica il numero di opzioni che comporrà la griglia</td> </tr>
            <tr> <td><b>max_columns</b></td> <td>x > 0</td> <td>permette la scelta del numero di colonne che comporranno la griglia</td> </tr>
            <tr> <td><b>max_rows</b></td> <td>x > 0</td> <td>permette la scelta del numero di righe che comporranno la griglia</td> </tr>
            <tr> <td><b>max_option_string_length</b></td> <td>x > 3</td> <td>indica lo spazio massimo occupato dalle stringhe delle opzioni</td> </tr>
            <tr> <td><b>path</b></td> <td> stringa </td> <td>indica il percorso di destinazione del file che conterrà le stringhe delle opzioni</td> </tr>
            <tr> <td><b>start_x</b></td> <td>x > 0</td> <td>indica da quale colonna del terminale cominciare a stampare le opzioni</td> </tr>
            <tr> <td><b>start_y</b></td> <td>x > 0</td> <td>indica da quale riga del terminale cominciare a stampare le opzioni</td> </tr>
        </table>
        <p align="center">
            <img alt="parametri-impostazioni" src="src\resources\media\images\settings_parameters.png">
        </p>
    </li>
    <li>
        <h3>Altra personalizzazione</h3>
        <p>
            All'interno del file <a href="src\option_selector.c">option_selector.c</a> è possibile cambiare il contenuto 
            di alcune stringhe, il che può permettere di cambiare come esse appaiono a schermo, non è ancora disponibile
            una grande varietà di opzioni, ma potrebbe cambiare in futuro. Di seguito sono rappresentate le costanti con
            i loro valori di predefiniti:
        </p>
        <p align="center">
            <img alt="costanti-personalizzazione" src="src\resources\media\images\constants_personalization.png"> 
        </p>
    </li>
    <li>
        <h3>Struttura del progetto</h3>
        <p>
            Sotto questo punto di vista non c'è nulla di specifico, le cartelle possono essere organizzate
            in qualsiasi modo, fino a quando venga fornito il giusto percorso per il file contenente le 
            stringhe delle opzioni. A seguire viene rappresentato un possibile metodo di sistemazione delle cartelle:
        </p>
<pre>
ilTuoProgetto
    │   main.c
    └───src
        │   option_selector.c
        │   option_selector.h
        └───resources
                options_strings.txt
</pre> 
    </li>
    <li>
        <h3>File delle stringhe delle opzioni</h3>
        <p>
            Il file deve essere un normalissimo documento di testo e deve conternere una stringa di 
            opzione per riga, come nell'esempio che segue:
        </p>
<pre>
Opzione 01
Opzione 02
Opzione 03
etc...
</pre>
    </li>
</ul>

> [!NOTE]
> E' possibile trovare un progetto esempio, scaricabile nella versione corrente della libreria
