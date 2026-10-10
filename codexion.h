#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>


#ifndef CODEXION_H
# define CODEXION_H

# define DUMP 2
# define ALLOC 1
# define INT_MAX 2147483647

# include "garbage_collector/garbage_collector.h"
# include "parsing/parser.h"
# include "coders/coders.h"
# include "queue/queue.h"
# include "simulation/simulation.h"
# include "utils/utils.h"

#endif