#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "cse232editor.h"

struct node textbuffer[MAX_LINES];
int free_head = 0;
int inuse_head = -1;

void initialize_buffer() {
    for (int i = 0; i < MAX_LINES; i++) {
        textbuffer[i].prev = -1;
        textbuffer[i].next = i + 1;
        strcpy(textbuffer[i].statement, "");
    }
    textbuffer[MAX_LINES - 1].next = -1;
    inuse_head = -1;
    free_head = 0;
}

#define MENU_OPTIONS 8
const char *menu[MENU_OPTIONS] = {
    "Edit File",
    "Insert Line",
    "Delete Line",
    "Save File",
    "Display Text",
    "Undo",
    "Redo",
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

void get_input(const char *prompt, char *buf, int buflen) {
    echo();
    curs_set(1);
    mvprintw(10, 2, "%s", prompt);
    clrtoeol();
    move(11, 2);
    getnstr(buf, buflen - 1);
    noecho();
    curs_set(0);
    move(10, 2); clrtoeol();
    move(11, 2); clrtoeol();
}

int main(int argc, char *argv[]) {
    initialize_buffer();
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int highlight = 0;
    int choice = 0;
    int ch;
    char filename[256];
    char text[256];
    int line;
    
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
                if (choice == 0) { 
                    get_input("Enter filename:", filename, sizeof(filename));
                    edit(filename);
                    mvprintw(MENU_OPTIONS + 4, 2, "File loaded: %s", filename);
                } else if (choice == 1) { 
                    get_input("Enter line number:", text, sizeof(text));
                    line = atoi(text);
                    get_input("Enter text:", text, sizeof(text));
                    insert_line(line, text);
                    mvprintw(MENU_OPTIONS + 4, 2, "Inserted at line %d", line);
                } else if (choice == 2) { 
                    get_input("Enter line number:", text, sizeof(text));
                    line = atoi(text);
                    delete(line);
                    mvprintw(MENU_OPTIONS + 4, 2, "Deleted line %d", line);
                } else if (choice == 3) { 
                    get_input("Enter filename:", filename, sizeof(filename));
                    save(filename);
                    mvprintw(MENU_OPTIONS + 4, 2, "File saved: %s", filename);
                } else if (choice == 4) {
                    endwin();
                    display();
                    initscr();
                    cbreak();
                    noecho();
                    keypad(stdscr, TRUE);
                    curs_set(0);
                } else if (choice == 5) {
                    undo();
                    mvprintw(MENU_OPTIONS + 4, 2, "Undo operation completed");
                } else if (choice == 6) {
                    redo();
                    mvprintw(MENU_OPTIONS + 4, 2, "Redo operation completed");
                } else if (choice == 7) { 
                    endwin();
                    return 0;
                }
                mvprintw(MENU_OPTIONS + 5, 2, "Press any key to continue...");
                refresh();
                getch();
                break;
            default:
                break;
        }
    }
    endwin();
    return 0;
}