######################################################################
# Generic makefile
#
#
#######################################################################
# Customising
# 
# Adjust the following if necessary 
EXECUTABLE := grpc_client
LIBDIR := ./lib
LIBS := pthread grpc cJSON rt stdc++ resolv m
INCLUDES := 
SRC_DIR :=


# Flags
CC := gcc
CFLAGS := -g -Wall
CPPFLAGS := $(CFLAGS)
CPPFLAGS += $(addprefix -I, $(INCLUDES))
CPPFLAGS += -MMD

RM-F := rm -f

# # You should't need to change anything below this points
SRCS := $(wildcard *.c) $(wildcard $(addsuffix /*.c, $(SRC_DIR)))
OBJS := $(patsubst %.c, %.o, $(SRCS))
DEPS := $(patsubst %.o, %.d, $(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)), $(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %d, %c, $(MISSING_DEPS)))

.PHONY : all deps objs clean veryclean rebuild info
all : $(EXECUTABLE)

deps : $(DEPS)

objs : $(OBJS)

clean :
	@$(RM-F) *.o
	@$(RM-F) *.d

veryclean: clean
	@$(RM-F) $(EXECUTABLE)

rebuild: veryclean all
ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS) :
	@$(RM-F) $(patsubst %d, %o, $@)
endif

-include $(DEPS)

$(EXECUTABLE) : $(OBJS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJS) $(addprefix -L, $(LIBDIR)) $(addprefix -l, $(LIBS))

info:
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(DEPS)
	@echo $(MISSING_DEPS)
	@echo $(MISSING_DEPS_SOURCES)
