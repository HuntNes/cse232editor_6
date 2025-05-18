#ifndef CSE232EDITOR_H
#define CSE232EDITOR_H

#define MAX_LINES 25
#define MAX_LEN 40

struct node {
    int prev;
    char statement[MAX_LEN];
    int next;
};

typedef enum { OP_INSERT, OP_DELETE } OperationType;

typedef struct {
    OperationType type;
    int line;
    char statement[MAX_LEN];
} Operation;

#define MAX_HISTORY 100

extern struct node textbuffer[MAX_LINES];
extern int free_head;
extern int inuse_head;

extern Operation undo_stack[MAX_HISTORY];
extern int undo_top;
extern Operation redo_stack[MAX_HISTORY];
extern int redo_top;

void edit(const char *filename);
void insert_line(int line, const char *stat);
void delete(int line);
void display();
void save(const char *filename);

void push_undo(Operation op);
Operation pop_undo();
void push_redo(Operation op);
Operation pop_redo();
void undo();
void redo();

#endif