#ifndef SELECTION_H    
#define SELECTION_H    
    int initializeSelection(int requested_option_list);
    int verifySelectedOptionCoords(int x, int y, int max_options, int max_rows, int max_columns);
    void checkGridLimitOverflow (int* p_x, int* p_y, int use_columns, int use_rows, int max_columns, int max_rows);
    void printOptionsStrings(char strings_filename[], int selected_option, int use_columns, int use_rows, int max_options, int max_columns, int max_rows, int max_line_length);
    void printOnOnlyColumnsGrid (char **options_strings, int selected_option, int max_columns);
    void printOnOnlyRowsGrid (char **options_strings, int selected_option, int max_rows);
    void printOnGrid (char **options_strings, int selected_option, int max_options, int max_columns);
    char **getStrings(char strings_filename[], int max_options, int max_line_length);
    void getSettings(char settings_filename[], char strings_filename[],int list_choice, int *p_use_columns, int *p_use_rows, int *p_max_options, int *p_max_columns, int *p_max_rows, int *p_max_line_length);
    void coord_generator(int options_coords[], int max_rows, int max_columns);
#endif