#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cse232editor.h"

extern struct node textbuffer[MAX_LINES];
extern int inuse_head;

void save(const char *filename) {
    //filename dosyasını a. stdio.h kütüphanesinde olan io sayesinde
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        //eğer dosyayı olusturamazssan yani acamazssan hata mesajı ver
        printf("Error: Could not open file for writing.\n");
        return;
    }
    int idx = inuse_head;
    //linkedlistteki bası al
    while (idx != -1) {
        //linkedlistin bası bos değilse yani boş depilse textin ici
        fprintf(fp, "%s\n", textbuffer[idx].statement);
        //linkedlistteki nodeun icindeki statementı dosyaya yaz
        idx = textbuffer[idx].next;
        //nodeu bir ilerlet
    }
    fclose(fp);
    //her sey bittikten sonra io ile dosyayı kapat 
    printf("File saved successfully: %s\n", filename);
}
