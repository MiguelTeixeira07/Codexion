# Directories
CODERS_DIR = ./coders
GC_DIR = ./garbage_collector
UTIL_DIR = ./utils
Q_DIR = ./queue
PARSE_DIR = ./parsing
SIM_DIR = ./simulation

SRCS = $(addsuffix .c, \
	main \
	$(addprefix $(CODERS_DIR)/, coders actions) \
	$(addprefix $(GC_DIR)/, garbage_collector) \
	$(addprefix $(Q_DIR)/,  queue_functions1 queue_functions2) \
	$(addprefix $(UTIL_DIR)/, utils1 utils2) \
	$(addprefix $(PARSE_DIR)/, parser) \
	$(addprefix $(SIM_DIR)/, simulation) \
)

OBJS = $(SRCS:%.c=%.o)
