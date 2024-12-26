#ifndef SELECTION_H    
#define SELECTION_H    
    int initializeSelection (int requested_option_list);
    void getSettings (int list_choice);
    int getStrings (char **options_strings);
    int printOptionsStrings (char **options_strings, int selected_option);
    void printOnOnlyColumnsGrid (char **options_strings, int selected_option);
    void printOnOnlyRowsGrid (char **options_strings, int selected_option);
    void printOnGrid (char **options_strings, int selected_option);
    void checkGridLimitOverflow (int *x, int *y);
    int verifySelectedOptionCoords (int *options_coords, int x, int y);
    void coordGenerator (int *options_coords);
#endif