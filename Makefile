include targets.mk

ARGS	=


# COMPILE = cc -Wall -Wextra -Werror -g
COMPILE = clang -Wall -Wextra -Werror -g
REMOVE = rm -f

.PHONY: all run valg clean fclean re t
# .SILENT:

NAME = codexion

PARGS = 

NUM_CODERS		= 5
TT_BURNOUT		= 10000
TT_COMPILE		= 1000
TT_DEBUG		= 1000
TT_REFACTOR		= 1000
MIN_COMPILE		= 5
DONGLE_CD		= 1
SCHED			= fifo

ARGS = $(NUM_CODERS) $(TT_BURNOUT) $(TT_COMPILE) $(TT_DEBUG) $(TT_REFACTOR) $(MIN_COMPILE) $(DONGLE_CD) $(SCHED)

all: $(NAME)

$(NAME): $(OBJS)
	echo "Building $(NAME)."
	$(COMPILE) $(OBJS) -o $(NAME)

%.o: %.c
	@echo "$$< is $<"
	@echo "$$@ is $@"
	$(COMPILE) $(PARGS) -c $< -o $@

debug: fclean $(OBJS)
	$(COMPILE) $(OBJS) -DDEBUG=1 -o $(NAME)

run: $(NAME)
	./$(NAME) $(ARGS)

valg: $(NAME)
	valgrind ./$(NAME) $(ARGS)

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
