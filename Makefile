include targets.mk

ARGS	=


# COMPILE = clang -Wall -Wextra -Werror
COMPILE = cc -Wall -Wextra -Werror
REMOVE = rm -f

.PHONY: all run valg helg gdb clean fclean re
# .SILENT:

NAME = codexion

PARGS = 

NUM_CODERS		= 5
TT_BURNOUT		= 1000
TT_COMPILE		= 60
TT_DEBUG		= 60
TT_REFACTOR		= 60
MIN_COMPILE		= 10
DONGLE_CD		= 60
SCHED			= edf

ARGS = $(NUM_CODERS) $(TT_BURNOUT) $(TT_COMPILE) $(TT_DEBUG) $(TT_REFACTOR) $(MIN_COMPILE) $(DONGLE_CD) $(SCHED)

all: $(NAME)

$(NAME): $(OBJS)
	echo "Building $(NAME)."
	$(COMPILE) $(OBJS) -o $(NAME)

%.o: %.c
	@echo "$$< is $<"
	@echo "$$@ is $@"
	$(COMPILE) $(PARGS) -c $< -o $@

run: # $(NAME)
	./$(NAME) $(ARGS)

valg: 
	valgrind ./$(NAME) $(ARGS)

helg: # $(NAME)
	valgrind --tool=helgrind ./$(NAME) $(ARGS)

gdb:
	gdb --tui --args ./$(NAME) $(ARGS) 

clean:
	printf "$(YELLOW)Cleaning objects.$(RESET)\n"
	$(REMOVE) $(OBJS)
	$(REMOVE) $(BONUS_OBJS)

fclean: clean
	printf "$(YELLOW)Cleaning binaries.$(RESET)\n"
	$(REMOVE) $(NAME)
	$(REMOVE) $(BONUS)

re: fclean all
