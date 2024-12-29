#ifndef OPTION_SELECTOR_H
    #define OPTION_SELECTOR_H
    typedef struct {
        int use_columns;
        int use_rows;
        int max_options;
        int max_columns;
        int max_rows;
        int max_option_string_length;
        char *path;
    } Settings;

    int initializeSelection (int use_columns, int use_rows, int max_options, int max_columns, int max_rows, int max_option_string_length, char *path, int start_x, int start_y);
    void setSettings (Settings *p_settings,int use_columns, int use_rows, int max_options, int max_columns, int max_rows, int max_option_string_length, char *path, int start_x, int start_y);
    int checkSettings (Settings settings);
    int printOptionsStrings (Settings settings, char **options_strings, int selected_option);
    int getStrings (Settings settings, char **options_strings);
    void printOnOnlyColumnsGrid (Settings settings, char **options_strings, int selected_option);
    void printOnOnlyRowsGrid (Settings settings, char **options_strings, int selected_option);
    void printOnGrid (Settings settings, char **options_strings, int selected_option);
    void printOption (char **options_strings, int option_number, int option_type);
    void checkGridLimitOverflow (Settings settings, int *p_x, int *p_y, char last_input);
    int verifySelectedOptionCoords (Settings settings, int *options_coords, int x, int y);
    void coordGenerator (Settings settings, int *options_coords);
#endif