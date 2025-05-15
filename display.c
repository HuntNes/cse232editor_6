#include <curses.h>
#include <stdio.h>
#include "cse232editor.h"

extern struct node textbuffer[MAX_LINES];
extern int inuse_head;

void display()
{
    initscr();
    keypad(stdscr, TRUE); // Enable arrow keys
    noecho();
    curs_set(0);

    int max_rows, max_cols;
    getmaxyx(stdscr, max_rows, max_cols);

    // Count total lines
    int total_lines = 0;
    int idx = inuse_head;
    while (idx != -1) {
        total_lines++;
        idx = textbuffer[idx].next;
    }

    int start_line = 0;
    int ch;
    do {
        clear();
        idx = inuse_head;
        int skip = 0;
        int row = 0;
        int line = 1;
        // Skip lines before start_line
        while (idx != -1 && skip < start_line) {
            idx = textbuffer[idx].next;
            skip++;
            line++;
        }
        // Print visible lines
        while (idx != -1 && row < max_rows - 2) {
            mvprintw(row, 0, "%d: %s", line, textbuffer[idx].statement);
            idx = textbuffer[idx].next;
            row++;
            line++;
        }
        mvprintw(max_rows - 1, 0, "Use UP/DOWN to scroll, q to quit.");
        refresh();
        ch = getch();
        if (ch == KEY_DOWN && start_line < total_lines - (max_rows - 2))
            start_line++;
        else if (ch == KEY_UP && start_line > 0)
            start_line--;
    } while (ch != 'q' && ch != 'Q');

    endwin();
}