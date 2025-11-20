#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teacher.h"
#include "student.h"
//struct student stu[1000];
 struct teacher tea[100];  // 最多存储100名教师信息
 int tea_len = 0;          // 当前教师数量

// 清空输入缓冲区
void clear_tea_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 检查教员序号是否重复
int is_id_exist(int id) {
    for (int i = 0; i < tea_len; i++) {
        if (tea[i].id == id) {
            return 1;  // 存在
        }
    }
    return 0;  // 不存在
}

// 添加教师信息
void add_teacher() {
    tea_len = teacher_rfile();
    if (tea_len >= 100) {
        printf("教师数量已达上限，无法添加！\n");
        return;
    }

    int id;
    printf("请输入教员序号：");
    scanf("%d", &id);
    clear_tea_buffer();

    // 检查序号是否重复
    if (is_id_exist(id)) {
        printf("教员序号已存在，请重新输入！\n");
        return;
    }
    tea[tea_len].id = id;

    printf("请输入教员姓名：");
    fgets(tea[tea_len].name, 127, stdin);
    // 去除换行符
    tea[tea_len].name[strcspn(tea[tea_len].name, "\n")] = '\0';

    printf("请输入教员密码：");
    fgets(tea[tea_len].pwd, 31, stdin);
    tea[tea_len].pwd[strcspn(tea[tea_len].pwd, "\n")] = '\0';

    printf("请输入所任班级：");
    scanf("%d", &tea[tea_len].class_num);
    clear_tea_buffer();

    tea_len++;
    teacher_wfile(tea_len);
    printf("教师信息添加成功！\n");
}

// 删除教师信息
void del_teacher() {
    tea_len = teacher_rfile();
    if (tea_len == 0) {
        printf("暂无教师信息！\n");
        return;
    }

    int id;
    printf("请输入要删除的教员序号：");
    scanf("%d", &id);
    clear_tea_buffer();

    int i, found = 0;
    for (i = 0; i < tea_len; i++) {
        if (tea[i].id == id) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("未找到该教师信息！\n");
        return;
    }

    // 覆盖删除的教师信息
    for (; i < tea_len - 1; i++) {
        tea[i] = tea[i + 1];
    }
    tea_len--;
    teacher_wfile(tea_len);
    printf("教师信息删除成功！\n");
}

// 修改教师信息
void edit_teacher() {
    tea_len = teacher_rfile();
    if (tea_len == 0) {
        printf("暂无教师信息！\n");
        return;
    }

    int id;
    printf("请输入要修改的教员序号：");
    scanf("%d", &id);
    clear_tea_buffer();

    int i, found = 0;
    for (i = 0; i < tea_len; i++) {
        if (tea[i].id == id) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("未找到该教师信息！\n");
        return;
    }

    printf("请输入新的教员姓名：");
    fgets(tea[i].name, 127, stdin);
    tea[i].name[strcspn(tea[i].name, "\n")] = '\0';

    printf("请输入新的教员密码：");
    fgets(tea[i].pwd, 31, stdin);
    tea[i].pwd[strcspn(tea[i].pwd, "\n")] = '\0';

    printf("请输入新的所任班级：");
    scanf("%d", &tea[i].class_num);
    clear_tea_buffer();

    teacher_wfile(tea_len);
    printf("教师信息修改成功！\n");
}

// 显示所有教师信息
void show_teacher() {
    tea_len = teacher_rfile();
    if (tea_len == 0) {
        printf("暂无教师信息！\n");
        return;
    }

    printf("=== 教师信息列表 ===\n");
    for (int i = 0; i < tea_len; i++) {
        printf("教员序号：%d\n", tea[i].id);
        printf("教员姓名：%s\n", tea[i].name);
        printf("所任班级：%d\n", tea[i].class_num);
        printf("-------------------------\n");
    }
}

// 从文件读取教师信息
int teacher_rfile() {
    FILE *fp = fopen("teacher.txt", "rb");
    if (fp == NULL) {
        return 0;  // 文件不存在时返回0
    }

    int read_len = 0;
    while (read_len < 100 && fread(&tea[read_len], sizeof(struct teacher), 1, fp)) {
        read_len++;
    }
    fclose(fp);
    return read_len;
}

// 将教师信息写入文件
void teacher_wfile(int len) {
    FILE *fp = fopen("teacher.txt", "wb");
    if (fp == NULL) {
        printf("文件打开失败，无法保存数据！\n");
        return;
    }

    fwrite(tea, sizeof(struct teacher), len, fp);
    fclose(fp);
}

// 教师查看个人信息
void teacher_view_info(int id) {
    int len = teacher_rfile();
    for (int i = 0; i < len; i++) {
        if (tea[i].id == id) {
            printf("\n===== 个人信息 =====");
            printf("\n教员序号: %d", tea[i].id);
            printf("\n姓名: %s", tea[i].name);
            printf("\n所任班级: %d", tea[i].class_num);
            printf("\n====================");
            return;
        }
    }
    printf("未找到个人信息!\n");
}

// 教师修改学生成绩
void teacher_edit_score() {
    char number[10];
    printf("请输入要修改成绩的学生学号: ");
    scanf("%s", number);
    
    int len = stu_rfile();
    for (int i = 0; i < len; i++) {
        if (strcmp(stu[i].number, number) == 0) {
            printf("当前数学成绩: %.1f, 请输入新成绩: ", stu[i].math);
            scanf("%f", &stu[i].math);
            printf("当前C语言成绩: %.1f, 请输入新成绩: ", stu[i].c);
            scanf("%f", &stu[i].c);
            printf("当前语文成绩: %.1f, 请输入新成绩: ", stu[i].chinese);
            scanf("%f", &stu[i].chinese);
            
            stu_wfile(len);
            calculate_rank();
            printf("成绩修改成功!\n");
            return;
        }
    }
    printf("未找到该学生!\n");
}
