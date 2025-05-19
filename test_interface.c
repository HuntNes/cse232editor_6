#define TEST_INTERFACE
#include <curses.h>
#include <stdio.h>
#include <string.h>
#include "cse232editor.h"

void run_interface() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    char command[256];
    int running = 1;
    while (running) {
        mvprintw(0, 0, "Komut girin (I, D, P, U, R, S, Q): ");
        getstr(command);

        switch (command[0]) {
            case 'I': {
                char text[40];
                sscanf(command + 1, "%39[^\n]", text);
                insert_line(-1, text); 
                break;
            }
            case 'D':
                delete(-1); 
                break;
            case 'P':
                display();
                break;
            case 'U':
                undo();
                break;
            case 'R':
                redo();
                break;
            case 'S':
                save("mytext");
                break;
            case 'Q':
                running = 0;
                break;
        }
        refresh();
    }
    endwin();
}

#ifdef TEST_INTERFACE
int main() {
    run_interface();
    return 0;
}
#endif
