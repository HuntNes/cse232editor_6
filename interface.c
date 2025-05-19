#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#define MENU_OPTIONS 5
const char *menu[MENU_OPTIONS] = {
    "Edit File",
    "Insert Line",
    "Delete Line",
    "Save File",
    "Quit"
};

void draw_menu(int highlight) {
    clear();
    mvprintw(0, 0, "CSE232 Editor - ncurses Interface");
    for (int i = 0; i < MENU_OPTIONS; ++i) {
        if (i == highlight)
            attron(A_REVERSE);
        mvprintw(i + 2, 2, "%s", menu[i]);
        if (i == highlight)
            attroff(A_REVERSE);
    }
    refresh();
}


void run_interface() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int highlight = 0;
    int choice = 0;
    int ch;
    while (1) {
        draw_menu(highlight);
        ch = getch();
        switch (ch) {
            case KEY_UP:
                highlight = (highlight - 1 + MENU_OPTIONS) % MENU_OPTIONS;
                break;
            case KEY_DOWN:
                highlight = (highlight + 1) % MENU_OPTIONS;
                break;
            case '\n':
                choice = highlight;
                if (choice == MENU_OPTIONS - 1) { /
                    endwin();
                    return;
                } else {
                    mvprintw(MENU_OPTIONS + 3, 2, "Selected: %s (not implemented)", menu[choice]);
                    refresh();
                    getch();
                }
                break;
            default:
                break;
        }
    }
    endwin();
}

#ifdef TEST_INTERFACE
int main() {
    
    insert_line(0, "ddd");
    insert_line(1, "eee");
    insert_line(1, "aaa"); 


    delete(1);

  
    undo();

    
    redo();

    
    save("testout.txt");

    
    display();

   
    FILE *fp = fopen("testout.txt", "r");
    char buf[40];
    fgets(buf, sizeof(buf), fp);
    assert(strcmp(buf, "ddd\n") == 0);
    fgets(buf, sizeof(buf), fp);
    assert(strcmp(buf, "aaa\n") == 0);
    fclose(fp);

    printf("All tests passed!\n");
    return 0;
}
#endif 