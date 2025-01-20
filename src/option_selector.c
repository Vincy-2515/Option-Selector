/*!
 * @author  Vincy-2515
 * @version v1.0
 *
 * @brief   Questa libreria contiene tutte le funzioni che permettono la creazione
 *          e la selezione di opzioni all'interno di una lista mostrata in una console.
 *
 * @details Per permettere il funzionamento della lista delle opzioni bisogna invocare
 *          la funzione "initializeSelection()", fornendo correttamente i parametri
 *          richiesti, all'interno di un file contenente la funzione main del vostro
 *          programma. Il resto delle funzioni sono fini a questo stesso file, non ne è
 *          previsto il loro uso al di fuori.
 *
 * @note    La descrizione dei codici di errore e altre informazioni possono essere trovate 
 * 			su Github a questo link: https://github.com/Vincy-2515/option-selector/wiki
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define TRUE 1
#define FALSE 0

// TASTI:
#define KEY_W 'w'
#define KEY_A 'a'
#define KEY_S 's'
#define KEY_D 'd'
#define ENTER '\r'

// PERSONALIZZAZIONE:
#define SPACE_BEFORE_OPTIONS "    "
#define SELECTED_OPTION_INDICATOR ">>"
#define UNSELECTED_OPTION_INDICATOR "--"

// PUILIZIA DEL TERMINALE:
#define ERASE_FROM_CURSOR_TO_ENDSCREEN "\033[0J"

// CURSORE:
#define CURSOR_VISIBILITY_TRUE "\033[?25h"
#define CURSOR_VISIBILITY_FALSE "\033[?25l"
#define MOVE_CUROSOR_TO_HOME "\033[H"

// COLORE DEL TESTO:
#define INVERT_COLORS_TRUE "\033[7m"
#define INVERT_COLORS_FALSE "\033[27m"

// CODICI ERRORE:
#define ERR_COORDS_COMPARING_UNRESOLVED -100
#define ERR_ROWS_AND_COLUMNS_DISABLED -200
#define ERR_TOO_FEW_OPTIONS -201
#define ERR_TOO_FEW_ROWS_OR_COLUMNS -202
#define ERR_GRID_TOO_SMALL -203
#define ERR_INVALID_VALUE_OF_USECOLUMNS_OR_USEROWS -204
#define ERR_UNEXPECTED_VALUE_OF_MAXCOLUMNS_OR_MAXROWS_USECOLUMNS_OR_USEROWS_DISABLED -205
#define ERR_MAXOPTIONSTRINGLENGTH_TOO_SMALL -206
#define ERR_ROWS_OR_COLUMNS_ENABLED_AND_NUMBER_EQUALS_TO_ONE -207
#define ERR_GRID_TOO_BIG -208
#define ERR_INVALID_VALUES_OF_STARTX_OR_STARTY -209
#define ERR_INVALID_KEY_PRESSED -300
#define ERR_FILE_NOT_FINISHED -400
#define ERR_INVALID_STRING_DECLARATION -401
#define ERR_FILE_OPENING -404

// IMPOSTAZIONI (modificabili solo da "setSettings()"):
typedef struct Settings{
	int use_columns;
	int use_rows;
	int max_options;
	int max_columns;
	int max_rows;
	int max_option_string_length;
	char *path;
	int start_x;
	int start_y;
} Settings;

int initializeSelection (int use_columns, int use_rows, int max_options, int max_columns, int max_rows, int max_option_string_length, char *path, int start_x, int start_y);
static void setSettings (Settings *p_settings, int use_columns, int use_rows, int max_options, int max_columns, int max_rows, int max_option_string_length, char *path, int start_x, int start_y);
static int checkSettings (Settings settings);
static int printOptionsStrings (Settings settings, char **options_strings, int selected_option);
static int getStrings (Settings settings, char **options_strings);
static void printOnOnlyColumnsGrid (Settings settings, char **options_strings, int selected_option);
static void printOnOnlyRowsGrid (Settings settings, char **options_strings, int selected_option);
static void printOnGrid (Settings settings, char **options_strings, int selected_option);
static void printOption (char **options_strings, int option_number, int option_type);
static void checkGridLimitOverflow (Settings settings, int *p_x, int *p_y, char last_input);
static int verifySelectedOptionCoords (Settings settings, int *options_coords, int x, int y);
static void generateOptionsCoordinates (Settings settings, int *options_coords);

/*!
 * @brief Funzione principale del file, prende in input le impostazioni e avvia la selezione
 *
 * @param use_columns Accetta 0 o 1 e permette di scegliere l'uso di colonne nella griglia delle opzioni
 * @param use_rows Accetta 0 o 1 e permette di scegliere l'uso di righe nella griglia delle opzioni
 * @param max_options Accetta valori >= 2 e indica il numero di opzioni che comporrà la griglia
 * @param max_columns Accetta valori > 0 e permette la scelta del numero di colonne che comporranno la griglia
 * @param max_rows Accetta valori > 0 e permette la scelta del numero di righe che comporranno la griglia
 * @param max_option_string_length Accetta valori maggiori di 3, lunghezza effetiva della stringa più lunga + 2 (NECESSARIO PER IL CORRETTO FUNZIONAMENTO)
 * @param path Indica il percorso di destinazione del file che conterrà le stringhe delle opzioni
 * @param start_x Accetta valori > 0 e indica da quale colonna del terminale cominciare a stampare le opzioni
 * @param start_y Accetta valori > 0 e indica da quale riga del terminale cominciare a stampare le opzioni
 *
 * @returns Il valore dell'opzione selezionata (a partire da 0), mentre in caso di errore di qualsiasi tipo ne ritorna il codice
 */
int initializeSelection (int use_columns, int use_rows, int max_options, int max_columns, int max_rows, int max_option_string_length, char *path, int start_x, int start_y) {
	char key_input;
	int i = 0;
	int x = 0;
	int y = 0;
	int value = 0;
	char **options_strings;

	/**
	 * Contenuto del vettore: options_coords[n] = yyyxxx
	 * Dove: xxx = colonna di riferimento, yyy = riga di riferimento
	 */
	int *options_coords;

	Settings settings;
	setSettings(&settings, use_columns, use_rows, max_options, max_columns, max_rows, max_option_string_length, path, start_x, start_y);

	value = checkSettings(settings);
	if (value < 0) {
		free(settings.path);
		return value;
	}

	options_strings = malloc(sizeof(char*) * settings.max_options);
	options_coords = malloc (sizeof(int) * settings.max_options);

	for (i = 0; i < settings.max_options; i++) {
		options_strings[i] = malloc (sizeof(char) * settings.max_option_string_length);
	}

	printf("%s", CURSOR_VISIBILITY_FALSE);

	do{
		value = printOptionsStrings(settings, options_strings, value);
		if (value < 0) break;

		key_input = _getch();

		switch (key_input){
			case ENTER:
				break;
			case KEY_W:
				y--;
				break;
			case KEY_A:
				x--;
				break;
			case KEY_S:
				y++;
				break;
			case KEY_D:
				x++;
				break;
			default:
				value = ERR_INVALID_KEY_PRESSED;
				break;
		}

		if (value < 0) break;

		checkGridLimitOverflow (settings, &x, &y, key_input);

		value = verifySelectedOptionCoords(settings, options_coords, x, y);
		if (value < 0) break;

	}while(key_input != ENTER);


	for (i = 0; i < settings.max_options; i++) {
		free(options_strings[i]);
	}

	free(settings.path);
	free(options_coords);
	free(options_strings);

	printf("\033[%d;%dH", settings.start_y, settings.start_x);
	printf("%s", ERASE_FROM_CURSOR_TO_ENDSCREEN);
	printf("%s", CURSOR_VISIBILITY_TRUE);

	if(value >= 0) {
		value = value;
		return value;
	}

	return value;
}

static void setSettings (Settings *p_settings, int use_columns, int use_rows, int max_options, int max_columns, int max_rows, int max_option_string_length, char *path, int start_x, int start_y) {
	Settings settings = *p_settings;

	settings.use_columns = use_columns;
	settings.use_rows = use_rows;
	settings.max_options = max_options;
	settings.max_columns = max_columns;
	settings.max_rows = max_rows;
	settings.max_option_string_length = max_option_string_length;
	settings.start_x = start_x;
	settings.start_y = start_y;

	settings.path = malloc(strlen(path)+1);
	strcpy(settings.path, path);

	*p_settings = settings;
}

static int checkSettings (Settings settings) {
	int temporary;
	int file_error;
	FILE *file;

	file_error = fopen_s(&file, settings.path, "r");
	_fcloseall();

	if (file_error != 0) {
		return ERR_FILE_OPENING;
	}
	else if (settings.use_columns == FALSE && settings.use_rows == FALSE ) {
		return ERR_ROWS_AND_COLUMNS_DISABLED;
	}
	else if (settings.max_options < 2) {
		return ERR_TOO_FEW_OPTIONS;
	}
	else if (settings.max_columns <= 0 || settings.max_rows <= 0) {
		return ERR_TOO_FEW_ROWS_OR_COLUMNS;
	}
	else if ((settings.max_columns * settings.max_rows) < settings.max_options) {
		return ERR_GRID_TOO_SMALL;
	}
	else if ((settings.use_columns < 0 || settings.use_columns > 1) || (settings.use_rows < 0 || settings.use_rows > 1)) {
		return ERR_INVALID_VALUE_OF_USECOLUMNS_OR_USEROWS;
	}
	else if((settings.use_columns == 0 && settings.max_columns > 1) || (settings.use_rows == 0 && settings.max_rows > 1)) {
		return ERR_UNEXPECTED_VALUE_OF_MAXCOLUMNS_OR_MAXROWS_USECOLUMNS_OR_USEROWS_DISABLED;
	}
	else if(settings.max_option_string_length < 3) {
		return ERR_MAXOPTIONSTRINGLENGTH_TOO_SMALL;
	}
	else if ((settings.use_columns == 1 && settings.max_columns <= 1 ) || (settings.use_rows == 1 && settings.max_rows <= 1)) {
		return ERR_ROWS_OR_COLUMNS_ENABLED_AND_NUMBER_EQUALS_TO_ONE;
	}
	else if ((settings.max_columns * settings.max_rows) > settings.max_options) {
		temporary = ((settings.max_columns * settings.max_rows) - settings.max_options)-1;
		if ((temporary > settings.max_columns-2) 
			|| (settings.use_columns == TRUE && settings.use_rows == FALSE)
			|| (settings.use_columns == FALSE && settings.use_rows == TRUE)
		) return ERR_GRID_TOO_BIG;
	}
	else if (settings.start_x < 0 || settings.start_y < 0){
		return ERR_INVALID_VALUES_OF_STARTX_OR_STARTY;
	}

	return 0;
}

static int printOptionsStrings (Settings settings, char **options_strings, int selected_option) {
	int error_code;
	printf("\033[%d;%dH", settings.start_y, settings.start_x);
	printf("%s", ERASE_FROM_CURSOR_TO_ENDSCREEN);

	error_code = getStrings(settings, options_strings);

	if (error_code != 0) {
		return error_code;
	}

	if (settings.use_columns == TRUE && settings.use_rows == FALSE) {
		printOnOnlyColumnsGrid(settings, options_strings, selected_option);
	}
	else if (settings.use_columns == FALSE && settings.use_rows == TRUE) {
		printOnOnlyRowsGrid(settings, options_strings, selected_option);
	}
	else if (settings.use_columns == TRUE && settings.use_rows == TRUE) {
		printOnGrid(settings, options_strings, selected_option);
	}
	else {
		return ERR_ROWS_AND_COLUMNS_DISABLED;
	}

	return 0;
}

static int getStrings (Settings settings, char **options_strings) {
	FILE *file;
	int file_error;
	int i;
	char string[settings.max_option_string_length];
	size_t string_length;
	size_t j;
	int detected_newline = 0;

	file_error = fopen_s(&file, settings.path, "r");

	if (file_error != 0){
		return ERR_FILE_OPENING;
	}

	i = 0;
	while (fgets(string, settings.max_option_string_length, file) != NULL) {
		string_length = strlen(string);

		for ( j = 0; j < string_length; j++) {
			if(strcmp(&string[j], "\n") == 0){
				strcpy(&string[j], "\0");
				detected_newline = 1;
			}
		}

		if(detected_newline != 1) {
			return ERR_INVALID_STRING_DECLARATION;
		}

		if (i < settings.max_options) {
			strcpy(options_strings[i], string);
			i++;
		}
		else if (feof(file)) {
			break;
		}
		else if (!feof(file)){
			return ERR_FILE_NOT_FINISHED;
			break;
		}
	}

	_fcloseall();
	return 0;
}

static void printOnOnlyColumnsGrid (Settings settings, char **options_strings, int selected_option) {
	int j;

	for(j = 0; j < settings.max_columns; j++){
		printf("%s", SPACE_BEFORE_OPTIONS);

		if (j != selected_option) printOption(options_strings, j, 0);
		else printOption(options_strings, selected_option, 1);
	}
}

static void printOnOnlyRowsGrid (Settings settings, char **options_strings, int selected_option) {
	int j;

	for(j = 0; j < settings.max_rows; j++){
		if (j != 0) printf("\n");
		printf("\033[%dC", settings.start_x-1);// si usa "settings.start_x - 1" per evitare uno strano errore nella stampa, che fa risultare le opzioni sfalsate
		printf("%s", SPACE_BEFORE_OPTIONS);

		if (j != selected_option) printOption(options_strings, j, 0);
		else printOption(options_strings, selected_option, 1);
	}
}

static void printOnGrid (Settings settings, char **options_strings, int selected_option) {
	int i;
	int j;
	int current_option = 0;

	for (i = 0; i < settings.max_rows; i++) {
		if (i != 0) printf("\033[%dC", settings.start_x-1);// si usa "settings.start_x - 1" per evitare uno strano errore nella stampa, che fa risultare le opzioni sfalsate

		for (j = 0; j < settings.max_columns && current_option < settings.max_options; j++) {
			printf("%s", SPACE_BEFORE_OPTIONS);

			if (current_option != selected_option) printOption(options_strings, current_option, 0);
			else printOption(options_strings, selected_option, 1);

			current_option++;
		}

		if (i != settings.max_rows-1) printf("\n");
	}
}

static void printOption (char **options_strings, int option_number, int option_type) {

	if (option_type == 0) {
		printf("%s  %s ", UNSELECTED_OPTION_INDICATOR, options_strings[option_number]);
	}
	else if (option_type == 1){
		printf("%s %s %s %s", SELECTED_OPTION_INDICATOR, INVERT_COLORS_TRUE, options_strings[option_number], INVERT_COLORS_FALSE);
	}
}

static void checkGridLimitOverflow (Settings settings, int *p_x, int *p_y, char last_input) {
	int x = *p_x;
	int y = *p_y;
	int last_column_of_last_row;

	if(settings.use_columns == TRUE && settings.use_rows == TRUE){
		if ((settings.max_columns * settings.max_rows) > settings.max_options) {
			last_column_of_last_row = (settings.max_options - (settings.max_columns * (settings.max_rows-1)))-1;

			if((x < 0 && y == 0) || (x == 0 && y < 0)) {x = last_column_of_last_row; y = settings.max_rows-1;}
			else if(y > settings.max_rows-2 && x > last_column_of_last_row && last_input == KEY_S) {x = last_column_of_last_row; y = settings.max_rows-1;}
			else if((y > settings.max_rows-1 && x == last_column_of_last_row) && last_input == KEY_S) {x = 0; y = 0;}
			else if((y == settings.max_rows-1 && x > last_column_of_last_row) && last_input == KEY_D) {x = 0; y = 0;}
		}
		if((x < 0 && y == 0) || (x == 0 && y < 0)) {x = settings.max_columns-1; y = settings.max_rows-1;}
		if(y < 0 && x != 0) {x--; y = 0;}
		if(y > settings.max_rows-1 && x != settings.max_columns-1) {x++; y = settings.max_rows-1;}

		if(x > settings.max_columns-1) {x = 0; y++;}
		if(x < 0) {x = settings.max_columns-1; y--;}
		if(y > settings.max_rows-1) {x = 0; y = 0;}
		if(y < 0) {x = 0; y = settings.max_rows-1;}
	}
	else if(settings.use_columns == TRUE && settings.use_rows == FALSE){
		if(y > 0){x++; y = 0;}
		if(y < 0){x--; y = 0;}
		if(x > settings.max_columns-1) x = 0;
		if(x < 0) x = settings.max_columns-1;
	}
	else if(settings.use_columns == FALSE && settings.use_rows == TRUE){
		if(x > 0){x = 0; y++;}
		if(x < 0){x = 0; y--;}
		if(y > settings.max_rows-1) y = 0;
		if(y < 0) y = settings.max_rows-1;
	}

	*p_x = x;
	*p_y = y;
}

static int verifySelectedOptionCoords(Settings settings, int *options_coords, int x, int y){
	int current_option;
	int converted_y;
	int converted_x;
	int cursor_position;

	generateOptionsCoordinates(settings, options_coords);

	converted_y = y*1000;
	converted_x = x*1;
	cursor_position = converted_x + converted_y; // cursor_position = yyyxxx;

	for(current_option = 0; current_option < settings.max_options; current_option++){
		if (cursor_position == options_coords[current_option]) {
			return current_option;
		}
	}

	return ERR_COORDS_COMPARING_UNRESOLVED;
}

static void generateOptionsCoordinates(Settings settings, int *options_coords){
	int x = 0, y = 0, current_option = 0;

	for (y = 0; y < settings.max_rows; y++) {

		for (x = 0; x < settings.max_columns && current_option < settings.max_options; x++) {
			options_coords[current_option] = x + y*1000;
			current_option++;
		}
	}
}
