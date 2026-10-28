*This project has been created as part of the 42 curriculum by migteixe.*

# Codexion

## Description

Codexion is a project where the main goal is to simulate multiple coders sharing a limited number of USB dongles while performing three different activities: compiling, debugging, and refactoring.

Each coder is represented by an independent POSIX thread. Since compiling requires two adjacent dongles, the program must manage concurrent access to shared resources while preventing deadlocks, starvation, and premature burnout.

The project implements two scheduling algorithms:
- **FIFO (First In, First Out):** Requests are handled in the order they arrive.
- **EDF (Earliest Deadline First):** Requests are prioritized according to their burnout deadlines.

The simulation ends when either a coder burns out or every coder completes the required number of compilation cycles.

### Project Objectives

- Understand multithreading and concurrency in C.
- Implement thread synchronization using POSIX threads.
- Manage shared resources safely.
- Implement FIFO and EDF scheduling algorithms.
- Prevent deadlocks and starvation.
- Handle time-sensitive events and precise burnout detection.

## Instructions

### Requirements

- C compiler (`cc`)
- POSIX threads (`pthread`)
- Make

### Compilation

Clone the repository:

```bash
git clone <repo_url> Codexion
cd Codexion
```

Compile the project:

```bash
make
```

Other available Makefile rules:

```bash
make run
make clean
make fclean
make gdb
make valg
make helg
make re
```

### Execution

Run the program using the following syntax:

```bash
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

### Arguments

| Argument | Description |
|---|---|
| `number_of_coders` | Number of coders and USB dongles. |
| `time_to_burnout` | Maximum time (ms) between the beginning of consecutive compilations. |
| `time_to_compile` | Time (ms) required to compile. |
| `time_to_debug` | Time (ms) spent debugging. |
| `time_to_refactor` | Time (ms) spent refactoring. |
| `number_of_compiles_required` | Minimum number of compilations required per coder. |
| `dongle_cooldown` | Time (ms) a dongle remains unavailable after being released. |
| `scheduler` | Scheduling algorithm: `fifo` or `edf`. |

All arguments are mandatory.

### Examples

```bash
./codexion 5 1000 400 200 200 5 100 fifo
```

```bash
./codexion 4 1750 1000 500 500 100 100 edf
```

### Expected Output

The logs follow the following format.
```text
[timestamp] [coder_id] has taken a dongle
[timestamp] [coder_id] has taken a dongle
[timestamp] [coder_id] is compiling
[timestamp] [coder_id] is debugging
[timestamp] [coder_id] is refactoring
[timestamp] [coder_id] burned out
```

Given the following input, the expected output should be:
```bash
./codexion 5 1000 200 100 100 3 100 edf
```
```text
1 1 has taken a dongle
1 1 has taken a dongle
1 1 is compiling
201 1 is debugging
201 2 has taken a dongle
201 4 has taken a dongle
201 4 has taken a dongle
201 4 is compiling
201 3 has taken a dongle
201 3 has taken a dongle
201 3 is compiling
301 1 is refactoring
302 2 has taken a dongle
302 2 is compiling
401 3 is debugging
401 4 is debugging
501 3 is refactoring
501 4 is refactoring
502 2 is debugging
502 5 has taken a dongle
502 5 has taken a dongle
502 5 is compiling
602 2 is refactoring
702 5 is debugging
702 1 has taken a dongle
802 5 is refactoring
803 1 has taken a dongle
803 1 is compiling
1003 1 is debugging
1003 2 has taken a dongle
1003 4 has taken a dongle
1003 4 has taken a dongle
1003 4 is compiling
1103 1 is refactoring
1104 2 has taken a dongle
1104 2 is compiling
1203 4 is debugging
1303 4 is refactoring
1304 2 is debugging
1304 5 has taken a dongle
1304 5 has taken a dongle
1304 5 is compiling
1304 3 has taken a dongle
1404 2 is refactoring
1405 3 has taken a dongle
1405 3 is compiling
1504 5 is debugging
1604 5 is refactoring
1605 3 is debugging
1605 1 has taken a dongle
1605 1 has taken a dongle
1605 1 is compiling
1705 3 is refactoring
1805 1 is debugging
1805 4 has taken a dongle
1805 4 has taken a dongle
1805 4 is compiling
1805 2 has taken a dongle
1905 1 is refactoring
1906 2 has taken a dongle
1906 2 is compiling
2005 4 is debugging
2105 4 is refactoring
2106 2 is debugging
2106 5 has taken a dongle
2106 5 has taken a dongle
2106 5 is compiling
2106 3 has taken a dongle
2206 2 is refactoring
2207 3 has taken a dongle
2207 3 is compiling
2306 5 is debugging
2406 5 is refactoring
2407 3 is debugging
```

## Architecture and Technical Choices

### Thread Management

- Each coder thread is placed in circular double linked list, where the right dongle of coder x points to the left dongle of coder x+1.
- The monitor is a thread that will manage what and when the coders do anything.
- Every thread is joined by iterating over the table linked list, except for the monitor that is joined before the rest of the coders.

### Resource Management

Each dongle is represented by a structure that stores the last time the dongle was dropped and the dongle mutex itself, used only to change this value.

The monitor tells which coder is going to compile, not allowing any other neighbouring coder to try to pick up any dongle before the one that was selected finishes the compilation process.

```c
static void	set_conditions(t_node *curr, int *cond1, int *cond2)
{
    pthread_mutex_lock(curr->coder->prev->self_mutex);
    *cond1 = !curr->coder->prev->compiling;
    pthread_mutex_unlock(curr->coder->prev->self_mutex);
    pthread_mutex_lock(curr->coder->next->self_mutex);
    *cond2 = !curr->coder->next->compiling;
    pthread_mutex_unlock(curr->coder->next->self_mutex);
}

void	allow_compiles(t_queue *queue)
{
    ...
    while (curr_q)
    {
        ...
        if (cond1 && cond2)
            order_compile(curr_q);
        ...
    }
}
```

When a coder is given authorization to compile, they will go to a while loop that will only be exited when either the simulation ends or both dongle's cooldown time has passed, as soon as the cooldown of one dongle ends, a message stating the coder has picked up that dongle will be displayed.

```c
while (1)
{
    if (check_end(coder->table))
        return (1);
    if (coder->left_dongle->last_used + coder->table->args->dongle_cooldown < gettime() && !lflag)
    {
        lflag = 1;
        log_msg("has taken a dongle", coder->table, coder->number);
    }
    if (coder->right_dongle->last_used + coder->table->args->dongle_cooldown < gettime() && !rflag && coder->table->args->num_coders != 1)
    {
        rflag = 1;
        log_msg("has taken a dongle", coder->table, coder->number);
    }
    if (lflag && rflag)
        break ;
}
```

### Scheduling Algorithms

When a coder starts executing the compile() function, they will start a conditional wait to symbolize waiting to be added to the queue.
```c
static void	wait_in_list(t_coder *coder)
{
	pthread_mutex_lock(coder->table->table_mutex);
	coder->waiting = 1;
	pthread_cond_wait(coder->condition, coder->table->table_mutex);
	coder->waiting = 0;
	coder->in_queue = 1;
	pthread_mutex_unlock(coder->table->table_mutex);
	pthread_mutex_lock(coder->self_mutex);
	pthread_cond_wait(coder->condition, coder->self_mutex);
	coder->compiling = 1;
	pthread_mutex_unlock(coder->self_mutex);
	pthread_mutex_lock(coder->table->table_mutex);
	coder->table->coders_compiling++;
	pthread_mutex_unlock(coder->table->table_mutex);
}

int	compile(t_coder *coder)
{
	wait_in_list(coder);
    ...
}
```
When the monitor adds that coder to the queue, the condition will be signalled and the coder will, once again, start another consitional wait, this one represents being added to the queue and waiting to be authorized to pick up the dongles and finally compile. When this coder meets all the conditions to compile, the monitor will grant it's access to the dongles and the coder will start the compilation process.

#### FIFO (First In, First Out)

With FIFO, every coder is added to the back of the queue automatically.

#### EDF (Earliest Deadline First)

The coder deadline is calculated in the following way:

`deadline = last_compile_start + time_to_burnout`

With EDF, every coder is added to the back of the queue and then moved forward until it is in the right place based on it's current deadline.

### Data Structures

The data structures used in this project were the following:

- A **Double Linked List** was used to make the queue;
- A **Circular Double Linked List** was used to make the table where every coder sits;
- A **Linked List** was used in the garbage collector, to store all the pointers to all the memory dynalically allocated.

## Blocking Cases Handled



### 1. Deadlock and Starvation Prevention

Because of the way the program is structured and the solution that is implemented, all avoidable deadlocks, blockages or starvation possibilities are prevented by the monitor itself. Coders will not act on their own, instead, they will ask for permission for any major action and they will be doing that unbothered. Once they ask to start compiling, they will be added to a general queue, where every coder will be in at least once on the execution of the program. The monitor iterates this queue from the front to the back whenever there is no coder compiling on the table and first orders the coders still in the queue to compile, checking if the neighbouring ones are compiling or not, and after one iteration it will add the coders that have requested to be added to the queue in the mean time.

### 4. Precise Burnout Detection

For every cycle of the monitor routine, the monitor will iterate every coder on the table and update the simulation ending conditions. If a coder has burned out, the monitor itself prints the burnout message for the coder and updates the table condition, this way all the coders know the simulation has ended and will terminate themselves. Once every coder has been terminated, the monitor terminates and the program execution comes to an end.

### 5. Race Conditions

Any possible race condition is prevented with the use of mutexes.

## Thread Synchronization Mechanisms

Explain the threading primitives and synchronization mechanisms used in your implementation.

### 1. Mutexes (`pthread_mutex_t`)

Describe the mutexes used in your project and their purposes.

| Mutex | Purpose |
|---|---|
| Dongle | Used for changing the last time the dongle was used |
| log_mutex | Used for writing log messages on the standard output |
| Coder->self_mutex | Mutex unique to each coder, used to tamper with values related to the coder itself |
| table_mutex | Used for anything that checks or alters values shared by the whole table |

Explain how mutexes protect shared resources and prevent race conditions.

### 2. Condition Variables (`pthread_cond_t`)

Condition variable were used in this program for 3 main purposes.

- When the simulation starts every thread will enter a conditional wait with the shared condition and mutex. Every coder and the monitor will be waken up at the same time once every thread is created with a pthread_cond_broadcast();
    
    coders + monitor:
    ```c
    pthread_mutex_lock(coder->table->table_mutex);
	pthread_cond_wait(coder->table->condition, coder->table->table_mutex);
	pthread_mutex_unlock(coder->table->table_mutex);
    ```
    main thread:
    ```c
    void	wake_em_up(t_table *table)
    {
        pthread_mutex_lock(table->table_mutex);
        pthread_cond_broadcast(table->condition);
        pthread_mutex_unlock(table->table_mutex);
    }
    ```

- When waiting to be added to the queue, coders will enter a conditional wait;
    
    coder:
    ```c
    pthread_mutex_lock(coder->table->table_mutex);
	coder->waiting = 1;
	pthread_cond_wait(coder->condition, coder->table->table_mutex);
    ```
    monitor:
    ```c
    if (waiting)
    {
        queue_push(queue, curr, curr->table->args->scheduler);
        pthread_mutex_lock(curr->self_mutex);
        pthread_cond_signal(curr->condition);
        pthread_mutex_unlock(curr->self_mutex);
        pthread_mutex_unlock(table->table_mutex);
        usleep(10);
        pthread_mutex_lock(table->table_mutex);
    }
    ```

- When waiting for permission to start the compilation proces, coders will enter another conditional wait.

    coder:
    ```c
	coder->in_queue = 1;
	pthread_mutex_unlock(coder->table->table_mutex);
	pthread_mutex_lock(coder->self_mutex);
	pthread_cond_wait(coder->condition, coder->self_mutex);
    ```
    monitor:
    ```c
    void	order_compile(t_node *curr)
    {
        pthread_mutex_lock(curr->coder->self_mutex);
        curr->n_compiles = curr->coder->compile_ammount;
        pthread_cond_signal(curr->coder->condition);
        pthread_mutex_unlock(curr->coder->self_mutex);
        usleep(10);
    }
    ```

## Resources

For this project I did not resource to online searches at all. All the information I gathered came either from the Linux programmer's manual or my peers in school.

### AI Usage

AI tools were used only for the generation of the main structure on this README.md file as a template.