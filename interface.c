#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "cse232editor.h"

extern struct node textbuffer[MAX_LINES];
extern int inuse_head;

#define MENU_OPTIONS 8
const char *menu[MENU_OPTIONS] = {
    "E (edit): Opens the specified file and reads it into the text buffer",
    "I (insert): Inserts a line in text buffer",
    "D (delete): Deletes a line",
    "U (undo): Reverses the effects of the last command",
    "R (redo): If used after an Undo, Redo does the last command again",
    "P (display): Displays the current text on the screen",
    "S (save): Saves the file",
    "Q (quit): exits the editor"
};

void draw_menu(int highlight) {
    clear();
    mvprintw(0, 0, "CSE232 Editor - Help Menu");
    mvprintw(1, 0, "Press ESC to return to editor");
    for (int i = 0; i < MENU_OPTIONS; ++i) {
        if (i == highlight)
            attron(A_REVERSE);
        mvprintw(i + 3, 2, "%s", menu[i]);
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

void show_help() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int highlight = 0;
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
            case 27:
                endwin();
                return;
            default:
                break;
        }
    }
}

void run_interface() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    char command[256];
    char filename[256];
    char text[256];
    int line;

    while (1) {
        clear();
        mvprintw(0, 0, "CSE232 Editor - Type 'H' for help menu");
        mvprintw(1, 0, "Enter command: ");
        echo();
        curs_set(1);
        getnstr(command, sizeof(command) - 1);
        noecho();
        curs_set(0);

        switch (command[0]) {
            case 'H':
            case 'h':
                endwin();
                show_help();
                initscr();
                cbreak();
                noecho();
                keypad(stdscr, TRUE);
                curs_set(0);
                break;

            case 'E':
            case 'e':
                if (sscanf(command + 1, "%s", filename) == 1) {
                    edit(filename);
                    mvprintw(3, 0, "File loaded: %s", filename);
                } else {
                    mvprintw(3, 0, "Usage: E <filename>");
                }
                break;

            case 'I':
            case 'i':
                if (sscanf(command + 1, "%d %[^\n]", &line, text) == 2) {
                    insert_line(line, text);
                    mvprintw(3, 0, "Inserted at line %d", line);
                } else {
                    mvprintw(3, 0, "Usage: I <line> <text>");
                }
                break;

            case 'D':
            case 'd':
                if (sscanf(command + 1, "%d", &line) == 1) {
                    delete(line);
                    mvprintw(3, 0, "Deleted line %d", line);
                } else {
                    mvprintw(3, 0, "Usage: D <line>");
                }
                break;

            case 'U':
            case 'u':
                undo();
                mvprintw(3, 0, "Undo operation completed");
                break;

            case 'R':
            case 'r':
                redo();
                mvprintw(3, 0, "Redo operation completed");
                break;

            case 'P':
            case 'p':
                endwin();
                display();
                initscr();
                cbreak();
                noecho();
                keypad(stdscr, TRUE);
                curs_set(0);
                break;

            case 'S':
            case 's':
                if (sscanf(command + 1, "%s", filename) == 1) {
                    save(filename);
                    mvprintw(3, 0, "File saved: %s", filename);
                } else {
                    mvprintw(3, 0, "Usage: S <filename>");
                }
                break;

            case 'Q':
            case 'q':
                endwin();
                return;

            default:
                mvprintw(3, 0, "Unknown command. Type 'H' for help menu");
        }
        mvprintw(4, 0, "Press any key to continue...");
        refresh();
        getch();
    }
    endwin();
}
