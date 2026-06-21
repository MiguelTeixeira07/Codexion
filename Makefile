include targets.mk


COMPILE = cc -Wall -Wextra -Werror
REMOVE = rm -f

.PHONY: all clean fclean re t
.SILENT:

NAME = codexion

all: $(NAME)

$(NAME): $(OBJS)
	echo "Building $(NAME)."
	$(COMPILE) $(OBJS) -o $(NAME)

run: $(NAME)
	./$(NAME)

valg: $(NAME)
	valgrind ./$(NAME)

clean:
	printf "$(YELLOW)Cleaning objects.$(RESET)\n"
	$(REMOVE) $(OBJS)
	$(REMOVE) $(BONUS_OBJS)

fclean: clean
	printf "$(YELLOW)Cleaning binaries.$(RESET)\n"
	$(REMOVE) $(NAME)
	$(REMOVE) $(BONUS)

re: fclean all
