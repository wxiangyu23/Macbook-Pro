# 定义编译器和编译选项
CC = gcc
CFLAGS = -Wall -g  # -Wall 显示警告，-g 生成调试信息

# 定义目标程序名
TARGET = student_teacher_system

# 定义所有源文件（.c 文件）
SRCS = main.c student.c teacher.c menu.c tooler.c 

# 将源文件列表（.c）转换为目标文件列表（.o）
OBJS = $(SRCS:.c=.o)

# 默认目标：编译并链接生成可执行文件
all: $(TARGET)

# 链接：将所有 .o 文件合并为可执行文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译：将每个 .c 文件编译为 .o 目标文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理编译生成的文件（.o 和可执行文件）
clean:
	rm -f $(OBJS) $(TARGET)
