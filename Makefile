include targets.mk


COMPILE = cc -Wall -Wextra -Werror
REMOVE = rm -f

.PHONY: all run valg clean fclean re t
.SILENT:

NAME = codexion

NUM_CODERS = 15

all: $(NAME)

$(NAME): $(OBJS)
	echo "Building $(NAME)."
	$(COMPILE) $(OBJS) -o $(NAME)

run: $(NAME)
	./$(NAME) $(NUM_CODERS)

valg: $(NAME)
	valgrind ./$(NAME) $(NUM_CODERS)

clean:
	printf "$(YELLOW)Cleaning objects.$(RESET)\n"
	$(REMOVE) $(OBJS)
	$(REMOVE) $(BONUS_OBJS)

fclean: clean
	printf "$(YELLOW)Cleaning binaries.$(RESET)\n"
	$(REMOVE) $(NAME)
	$(REMOVE) $(BONUS)

re: fclean all
