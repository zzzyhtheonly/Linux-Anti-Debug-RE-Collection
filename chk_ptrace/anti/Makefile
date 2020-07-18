
CC := gcc
CCFLAG := -pthread
DBGFLAG := -G
CCOBJFLAG := $(CCFLAG) -c

TARGET = test
SRC := $(foreach x, ., $(wildcard $(addprefix $(x)/*, .c*)))
OBJ := $(addsuffix .o, $(notdir $(basename $(SRC))))

CLEAN_LIST := $(TARGET) $(OBJ)

defalut: all

$(TARGET): $(OBJ)
	$(CC) $(CCFLAG) -o $@ $?

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)
