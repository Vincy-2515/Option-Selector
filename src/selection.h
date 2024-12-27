#ifndef SELECTION_H
#define SELECTION_H
    typedef struct {
        int use_columns;
        int use_rows;
        int max_options;
        int max_columns;
        int max_rows;
        int max_line_length;

        //percorso dei file di impostazioni
        char strings_filename[200];
    } Settings;

    int initializeSelection (Settings settings);
    //void checkSettings (Settings settings);
    int printOptionsStrings (Settings settings, char **options_strings, int selected_option);
    int getStrings (Settings settings, char **options_strings);
    void printOnOnlyColumnsGrid (Settings settings, char **options_strings, int selected_option);
    void printOnOnlyRowsGrid (Settings settings, char **options_strings, int selected_option);
    void printOnGrid (Settings settings, char **options_strings, int selected_option);
    void checkGridLimitOverflow (Settings settings, int *x, int *y);
    int verifySelectedOptionCoords (Settings settings, int *options_coords, int x, int y);
    void coordGenerator (Settings settings, int *options_coords);
#endif