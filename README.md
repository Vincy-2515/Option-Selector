<p align="center">
    <img alt = "option-selector-banner" src = "src/resources/media/images/option_selector_readme_banner.png">
</p>

---

<p align="center">
    <img alt="c language" src="https://img.shields.io/badge/-C-black?style=for-the-badge&logo=c">
    <span>&nbsp;&nbsp;</span>
    <img alt="versione - v1.0.0.0" src="https://img.shields.io/badge/Versione-v1.0.0.0-black?style=for-the-badge">
    <span>&nbsp;&nbsp;</span>
    <img alt="wiki" src="https://img.shields.io/badge/-Wiki-black?style=for-the-badge&logo=wikibooks&link= wiki link ### ">
</p>


## Cos'è?
<p>
    E' una semplice libreria scritta in C che permette la creazione e la navigazione di una lista di opzioni in una console, 
    navigazione che avviene tramite l'uso di tasti che permettono al cursore di spostarsi tra le opzioni. 
    Permette varie opzioni di personalizzazione dalla scelta del layout della lista di opzioni, 
    al modo in cui appaiono le opzioni selezionate e non.
</p>

<p align="center">
    <img alt="gif-risultato" src="src\resources\media\gifs\full_grid.gif"> 
</p>

> [!IMPORTANT]
> In questo README sono presenti inforamzioni molto generali.
> Per la documentazione del consultare la <a href=" wiki link ### ">wiki della repository</a>.

## Come utilizzare la libreria?
> [!NOTE]
> E' possibile trovare un progetto esempio, scaricabile nella versione corrente della libreria
<p>
    Normalmente la funzione "initializeSelection()" ritorna il numero dell'opzione selzionata, in caso d'errore invece ne ritornerà 
    il codice. Di seguito si trovano le informazioni neccessarie per il corretto utilizzo della libreria.
</p>

<ul>
    <li>
        <h3>Impostazioni</h3>
        <p>
            Di seguito è riportato l'elenco dei parametri richiesti, e una rappresentazione sotto forma di codice
            che rispetta l'ordine dei parametri della funzione "initializeSelection()":
        </p>
        <p align="center">
            <img alt="parametri-impostazioni" src="src\resources\media\images\settings_parameters.png">
        </p>
        <table>
            <tr> <th>Parametro</th> <th>Valori accettati</th> <th>Descrizione</th> </tr>
            <tr> <td><b>use_columns</b></td> <td>x = 0 o 1</td> <td>permette di scegliere l'uso di colonne nella griglia delle opzioni</td> </tr>
            <tr> <td><b>use_rows</b></td> <td>x = 0 o 1</td> <td>permette di scegliere l'uso di righe nella griglia delle opzioni</td> </tr>
            <tr> <td><b>max_options</b></td> <td>x >= 2</td> <td>indica il numero di opzioni che comporrà la griglia</td> </tr>
            <tr> <td><b>max_columns</b></td> <td>x > 0</td> <td>permette la scelta del numero di colonne che comporranno la griglia</td> </tr>
            <tr> <td><b>max_rows</b></td> <td>x > 0</td> <td>permette la scelta del numero di righe che comporranno la griglia</td> </tr>
            <tr> <td><b>max_option_string_length</b></td> <td>x > 3</td> <td>lunghezza effetiva della stringa più lunga + 2 (<b>NECESSARIO PER IL CORRETTO FUNZIONAMENTO</b>)</td> </tr>
            <tr> <td><b>path</b></td> <td> stringa </td> <td>indica il percorso di destinazione del file che conterrà le stringhe delle opzioni</td> </tr>
            <tr> <td><b>start_x</b></td> <td>x > 0</td> <td>indica da quale colonna del terminale cominciare a stampare le opzioni</td> </tr>
            <tr> <td><b>start_y</b></td> <td>x > 0</td> <td>indica da quale riga del terminale cominciare a stampare le opzioni</td> </tr>
        </table>
    </li>
    <li>
        <h3>Personalizzazione</h3>
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
            opzione per riga, nell'eventualità in cui le stringhe delle opzioni siano di lunghezza
            variabile è <b>NECESSARIO</b> l'uso di spazi per riempire lo spazio mancante rispetto
            alla stringa più lunga, in caso contrario le opzioni risulteranno sfalsate. 
            Nell'esempio che segue vengono aggiunti due spazi a fine stringa, per corrispondere 
            in lunghezza con la stringa di dimensione più grande.
        </p>
<pre>
Prima opzione  <-- DUE SPAZII AGGIUNTIVI A FINE STRINGA
Seconda opzione
Terza opzione  <-- DUE SPAZII AGGIUNTIVI A FINE STRINGA
etc...
</pre>
    </li>
</ul>
