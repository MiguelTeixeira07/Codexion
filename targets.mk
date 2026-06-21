# Directories
CODERS_DIR = ./coders
GC_DIR = ./garbage_collector
UTIL_DIR = ./utils
Q_DIR = ./queue

SRCS = $(addsuffix .c, \
	main \
	$(addprefix $(CODERS_DIR)/, coders) \
	$(addprefix $(GC_DIR)/, garbage_collector) \
	$(addprefix $(Q_DIR)/,  queue_functions) \
	$(addprefix $(UTIL_DIR)/, utils) \
)

OBJS = $(SRCS:%.c=%.o)
