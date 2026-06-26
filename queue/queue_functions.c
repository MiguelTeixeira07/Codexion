#include "queue.h"
#include "../garbage_collector/garbage_collector.h"


t_queue *init_queue() {
    t_queue *queue;
    
    queue = gar_col(ALLOC, sizeof(t_queue));
    if (!queue)
        return NULL;
    
    queue->top = NULL;
    queue->bottom = NULL;
    
    return queue;
}

void queue_push(t_queue **self, char *data) {
    t_node *new;
    
    new = gar_col(ALLOC, sizeof(t_node));
    if(!new)
        return;
    
	new->data = data;
	new->previous = NULL;
	new->next = (*self)->top;
    
	if ((*self)->top)
		(*self)->top->previous = new;
	else
		(*self)->bottom = new;
    
	(*self)->top = new;
}

void queue_pop(t_queue **self) {
    t_node *remove;
    
    if ((*self)->top == (*self)->bottom) {
        (*self)->top = NULL;
        (*self)->bottom = NULL;
        
        return;
    }
    
    remove = (*self)->bottom;
    if(remove->previous) {
        (*self)->bottom = remove->previous;
        printf("%s\n", remove->data);
        remove = NULL;
        (*self)->bottom->next = NULL;
    } else {
        (*self)->bottom = NULL;
    }
}

void print_queue(t_queue *self) {
	t_node *node;
    
    if(!self->top) {
        printf("Queue is empty\n");
        return;
    }
    
	node = self->top;
    printf("Front | ");
	while(node)
	{
		printf("%s ", node->data);
		node = node->next;
	}
    printf("| Back\n");
}
