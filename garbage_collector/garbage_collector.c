#include "garbage_collector.h"


static t_garbage *add(t_garbage **list, void *garbage)
{
    t_garbage *new_node;
    t_garbage *curr;
    
    
    new_node = malloc(sizeof(t_garbage));
    if (!new_node)
        return NULL;
    
    new_node->garbage = garbage;
    new_node->next = NULL;
    
    if (!*list)
    {
        *list = new_node;
        return new_node;
    }
    
    curr = *list;
    while (curr->next)
        curr = curr->next;
    
    curr->next = new_node;
    return new_node;
}

static void dump(t_garbage **garbage) {
    t_garbage *node;
    t_garbage *temp;
    
    if(!*garbage)
        return;
    
    node = *garbage;
    while(node)
    {
        free(node->garbage);
        temp = node->next;
        free(node);
        node = temp;
    }
}

void *gar_col(int action, size_t bytes) {
    static t_garbage *garbage_list;
    void *data;
    
    
    if(action == 1) {
        data = malloc(bytes);
        add(&garbage_list, data);
        return data;
    } else {
        dump(&garbage_list);
    }
    
    return NULL;
}
