# Directories
CODERS_DIR = ./coders
GC_DIR = ./garbage_collector
UTIL_DIR = ./utils
Q_DIR = ./queue
PARSE_DIR = ./parsing

SRCS = $(addsuffix .c, \
	main \
	$(addprefix $(CODERS_DIR)/, coders actions) \
	$(addprefix $(GC_DIR)/, garbage_collector) \
	$(addprefix $(Q_DIR)/,  queue_functions) \
	$(addprefix $(UTIL_DIR)/, utils) \
	$(addprefix $(PARSE_DIR)/, parser) \
)

OBJS = $(SRCS:%.c=%.o)
