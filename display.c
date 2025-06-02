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
    //initscr ile ilklendirme yani bi bakıma baslatma vardır
    keypad(stdscr, TRUE);
     //keypad ise ekranda ileri geri gibi tuşların inputunun alınması ve stdscr yani ekrarn icin alınmasını TRUE yapar yani mümkün kılar
    noecho();
    //noecho kullanıcıların yazdıklarını ekrana yazdırmamak icin
    curs_set(1);
     //curs set 1 ise bi karakterin yanındaki imlecin ynaıp sönmesini 2 ise sürekli yanmasını 0 ise hic yanmamasını sağlar

    int max_rows, max_cols;
    getmaxyx(stdscr, max_rows, max_cols);
    //yazılaron  enlemesi ve boylaması alınır açılacak ekran icin
    (void)max_cols;

    int node_indices[MAX_LINES];
    int total_lines = 0;
    int idx = inuse_head;
    //inuse head benim doubly linked list yapısında yazıların bulundugu linklistedin basını gösterir
    
    while (idx != -1 && total_lines < MAX_LINES) {
        //idx 1 e eşit değilse yani yazın boş değilse ve yazma sınırına ulaşmamışsan
        node_indices[total_lines++] = idx;
        idx = textbuffer[idx].next;
        //diğer linklist elemanına geç
    }

    int y = 0;
    int ch;
    while (1) {
        clear();
        for (int row = 0; row < total_lines && row < max_rows - 2; ++row) {
            //son yazıya kadar for loopu calıstır 
            int node_idx = node_indices[row];
            if (row == y) {
                //secilmis satırları ters yaz
                attron(A_REVERSE);
                //ters renki yazıyı yazmayı baslat
                mvprintw(row, 0, "%s", textbuffer[node_idx].statement);
                //seçili nodedaki statementı(yazıyı) yaz
                
                attroff(A_REVERSE);
                //ters renkli yazı yazmayı kapat
            } else {
                mvprintw(row, 0, "%s", textbuffer[node_idx].statement);
                //seçilmemis satırları normal yaz
            }
        }
        
        move(y, 0);
        //y ye göre sürekli oynat x sabit kalsın yani ilk basta kalsın
        
        mvprintw(max_rows - 1, 0, "Use UP/DOWN to move, Q to quit...");
        //while ile sürekli yenile refreshle yani
        refresh();
        

        ch = getch();
        //ch tuş seçimi
        //getch ile tuş inputunu al
        if (ch == 'Q' || ch == 'q') {
            last_selected_line = y;
            break;
        } else if (ch == KEY_UP) {
            //eğer yukarı tusuna basılırsa y yi azalt yani yukarıdaki linelara git 
            if (y > 0) y--;
            //eğer 0 dan büyükse yani en üstteyse  ((0) en üst ) daha da elleme yani oynatma
        } else if (ch == KEY_DOWN) {
            //eğer aşağı tuşuna basılırsa y yi arttır yani aşağıdaki linelara git 
            
            if (y < total_lines - 1) y++;

            //eğer max linedan kücüse yani en alttaysa (max line -1 en aşağı) daha da elleme ayani oynatma
        }
    }
    endwin();
}
