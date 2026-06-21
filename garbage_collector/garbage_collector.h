#include "../codexion.h"


typedef struct s_garbage {
    void *garbage;
    struct s_garbage *next;
} t_garbage;


void *gar_col(int action, size_t bytes);
