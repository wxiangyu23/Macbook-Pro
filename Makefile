CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./include
LDFLAGS = -lpthread -lncurses

SRCDIR = src
INCDIR = include
BINDIR = bin
OBJDIR = obj

# Source files
SOURCES = $(SRCDIR)/main.c \
          $(SRCDIR)/alert-manager.c \
          $(SRCDIR)/data_processor.c \
          $(SRCDIR)/display_ui.c \
          $(SRCDIR)/file_logger.c \
          $(SRCDIR)/sensor_simulator.c

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Executable name
EXECUTABLE = $(BINDIR)/factory

# Targets
.PHONY: all clean run

all: $(EXECUTABLE)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXECUTABLE): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "编译完成: $@"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo "编译: $<"

run: $(EXECUTABLE)
	@echo "运行程序..."
	./$(EXECUTABLE)

clean:
	rm -rf $(OBJDIR) $(BINDIR)
	@echo "清理完成"

help:
	@echo "使用说明:"
	@echo "  make          - 编译项目"
	@echo "  make run      - 编译并运行项目"
	@echo "  make clean    - 清理编译文件"
	@echo "  make help     - 显示此帮助信息"
