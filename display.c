#include <curses.h>
#include <stdio.h>
#include <string.h>
#include "cse232editor.h"

int last_selected_line = 0;

extern struct node textbuffer[MAX_LINES];
extern int inuse_head;

void display()
{
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(1);

    int max_rows, max_cols;
    getmaxyx(stdscr, max_rows, max_cols);
    (void)max_cols;

    int node_indices[MAX_LINES];
    int total_lines = 0;
    int idx = inuse_head;
    while (idx != -1 && total_lines < MAX_LINES) {
        node_indices[total_lines++] = idx;
        idx = textbuffer[idx].next;
    }

    int y = 0;
    int ch;
    while (1) {
        clear();
        for (int row = 0; row < total_lines && row < max_rows - 2; ++row) {
            int node_idx = node_indices[row];
            if (row == y) {
                attron(A_REVERSE);
                mvprintw(row, 0, "%s", textbuffer[node_idx].statement);
                attroff(A_REVERSE);
            } else {
                mvprintw(row, 0, "%s", textbuffer[node_idx].statement);
            }
        }
        move(y, 0);
        mvprintw(max_rows - 1, 0, "Use UP/DOWN to move, Q to quit...");
        refresh();

        ch = getch();
        if (ch == 'Q' || ch == 'q') {
            last_selected_line = y;
            break;
        } else if (ch == KEY_UP) {
            if (y > 0) y--;
        } else if (ch == KEY_DOWN) {
            if (y < total_lines - 1) y++;
        }
    }
    endwin();
}