#ifndef CSE232EDITOR_H
#define CSE232EDITOR_H

#define MAX_LINES 25
#define MAX_LEN 40

struct node {
    int prev;                  
    char statement[MAX_LEN];   
    int next;                  
};

extern struct node textbuffer[MAX_LINES]; 
extern int free_head;                     
extern int inuse_head;                    

void edit(const char *filename);          
void insert_line(int line, const char *stat); 
void delete(int line);

#endif