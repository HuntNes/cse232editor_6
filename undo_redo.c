#include "cse232editor.h"
#include <string.h>
#include <stdio.h>

Operation undo_stack[MAX_HISTORY];
int undo_top = -1;
Operation redo_stack[MAX_HISTORY];
int redo_top = -1;

void push_undo(Operation op) {
    if (undo_top < MAX_HISTORY - 1)
        undo_stack[++undo_top] = op;
}

Operation pop_undo() {
    if (undo_top >= 0)
        return undo_stack[undo_top--];
    Operation empty = {0};
    return empty;
}

void push_redo(Operation op) {
    if (redo_top < MAX_HISTORY - 1)
        redo_stack[++redo_top] = op;
}

Operation pop_redo() {
    if (redo_top >= 0)
        return redo_stack[redo_top--];
    Operation empty = {0};
    return empty;
}

// Prototipler (insert_line ve delete fonksiyonları başka dosyada)
void insert_line(int line, const char *stat);
void delete(int line);

void undo() {
    if (undo_top < 0) {
        printf("Nothing to undo.\n");
        return;
    }
    Operation op = pop_undo();
    Operation redo_op;
    if (op.type == OP_INSERT) {
        // Eklenen satırı sil
        delete(op.line);
        // Redo için tekrar ekleme kaydı
        redo_op.type = OP_INSERT;
        redo_op.line = op.line;
        strncpy(redo_op.statement, op.statement, MAX_LEN);
        push_redo(redo_op);
    } else if (op.type == OP_DELETE) {
        // Silinen satırı tekrar ekle
        insert_line(op.line, op.statement);
        // Redo için tekrar silme kaydı
        redo_op.type = OP_DELETE;
        redo_op.line = op.line;
        strncpy(redo_op.statement, op.statement, MAX_LEN);
        push_redo(redo_op);
    }
}

void redo() {
    if (redo_top < 0) {
        printf("Nothing to redo.\n");
        return;
    }
    Operation op = pop_redo();
    Operation undo_op;
    if (op.type == OP_INSERT) {
        insert_line(op.line, op.statement);
        undo_op.type = OP_INSERT;
        undo_op.line = op.line;
        strncpy(undo_op.statement, op.statement, MAX_LEN);
        push_undo(undo_op);
    } else if (op.type == OP_DELETE) {
        delete(op.line);
        undo_op.type = OP_DELETE;
        undo_op.line = op.line;
        strncpy(undo_op.statement, op.statement, MAX_LEN);
        push_undo(undo_op);
    }
}