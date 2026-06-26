#include "garbage_collector/garbage_collector.h"
#include "queue/queue.h"
#include "utils/utils.h"
#include "coders/coders.h"


int main(int argc, char **argv) {
    t_table *table;
    int num_coders;
    
    if(argc != 2)
        return 0;
    
    table = init_table();
    num_coders = atoi(argv[1]);
    for(int i = 1; i <= num_coders; i++) {
        table_push(&table, itoa(i));
    }
    
    create_threads(table);
    
    gar_col(DUMP, 0);
    
    return 0;
}

/* int i = 0;
int operation;
int ammount;
char data[50];
t_node *top;
t_node *bottom;
t_queue *queue;


queue = queue_init();

do {
    system("clear");
    print_queue(queue);
    
    printf("Pick an action:\n");
    printf("1 - Add to queue\n");
    printf("2 - Pop from queue\n");
    printf("3 - Quit\n\n");
    do {
        scanf("%d", &operation);
    } while(operation < 1 || operation > 3);
    
    switch(operation) {
        case 1:
            printf("Write how many elements you want to add to your queue: ");
            do {
                scanf("%d", &ammount);
            } while(!ammount);
            
            i = 0;
            while(++i <= ammount) {
                printf("Element nº %d: ", i);
                scanf("%s", data);
                
                push(&queue, ft_strdup(data));
                printf("Added %s to the queue.\n", data);
            }
            break;
        case 2:
            pop(&queue);
            break;
        case 3:
            gar_col(DUMP, 0);
            exit(0);
    }
} while(operation != 3); */