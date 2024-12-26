#ifndef SELECTION_H    
#define SELECTION_H    
    int initializeSelection(int requested_option_list);
    void getSettings(int list_choice);
    int verifySelectedOptionCoords(int x, int y);
    void checkGridLimitOverflow (int *x, int *y);
    char **getStrings(char **options_strings);
    void printOptionsStrings(char **options_strings, int selected_option);
    void printOnOnlyColumnsGrid (char **options_strings, int selected_option);
    void printOnOnlyRowsGrid (char **options_strings, int selected_option);
    void printOnGrid (char **options_strings, int selected_option);
#endif