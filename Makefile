TARGET_EXEC := gb

CC := cc
AR := ar
CFLAGS := -std=c99
CFLAGS += -Og -march=native
CFLAGS += -ggdb
CFLAGS += -Wall -Wextra -Wconversion -Wpedantic
CFLAGS += -MMD -MP # FIXME: non portable
LDFLAGS :=

SRC_DIR := src
LIB_DIR := $(SRC_DIR)/libgb
BUILD_DIR := build

LIB_SRCS := $(wildcard $(LIB_DIR)/*.c)
LIB_OBJS := $(LIB_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
LIB_DEPS := $(LIB_OBJS:.o=.d)

all: $(BUILD_DIR)/libgb.a

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/libgb.a: $(LIB_OBJS)
	$(AR) -rcs $@ $^

clean:
	rm -rf $(BUILD_DIR)

.SUFFIXES:

.PHONY: clean

-include $(DEPS)
