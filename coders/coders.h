#include "../codexion.h"
#include "../garbage_collector/garbage_collector.h"


typedef struct s_coders {
    pthread_t thread;
    void *name;
    struct s_coders *next;
    struct s_coders *prev;
} t_coders;

typedef struct s_table {
    t_coders *first;
    t_coders *last;
} t_table;


void *coder(void *ptr);

t_table *init_table();

void table_push(t_table **self, char *name);

void create_threads(t_table *table);
