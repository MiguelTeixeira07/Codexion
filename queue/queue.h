#include "../codexion.h"


typedef struct s_node {
    char *data;
    struct s_node *previous;
    struct s_node *next;
} t_node;

typedef struct s_queue {
    t_node *top;
    t_node *bottom;
} t_queue;


t_queue *queue_init();

void queue_push(t_queue **self, char *data);

void queue_pop(t_queue **self);

void print_queue(t_queue *self);
