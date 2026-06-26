#include "coders.h"


void *coder(void *name) {
    printf("%s thread created\n", name);
    sleep(1.5);
    printf("%s thread ended\n", name);
}

t_table *init_table() {
    t_table *table;
    
    table = gar_col(ALLOC, sizeof(t_table));
    if (!table)
        return NULL;
    
    table->first = NULL;
    table->last = NULL;
    
    return table;
}

void table_push(t_table **self, char *name) {
    t_coders *new;
    pthread_t thread;
    
    new = gar_col(ALLOC, sizeof(t_coders));
    if(!new)
        return;
    
	new->thread = thread;
    new->name = name;
    
	if (!(*self)->first) {
        (*self)->first = new;
        (*self)->last = new;
        
        new->next = new;
        new->prev = new;
    } else {
        new->prev = (*self)->last;
        new->next = (*self)->first;
        new->left_dongle = new->prev->right_dongle;
        
        (*self)->last->next = new;
        (*self)->first->prev = new;
        
        (*self)->last = new;
    }
	return;
}

void create_threads(t_table *table) {
    t_coders *curr;
    
    curr = table->first;
    do {
        pthread_create(&curr->thread, NULL, &coder, curr->name);
        curr = curr->next;
    } while(curr != table->first);
    do {
        pthread_join(curr->thread, NULL);
        curr = curr->next;
    } while(curr != table->first);
}
