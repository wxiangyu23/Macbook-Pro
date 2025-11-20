#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tooler.h"
#include "student.h"
#include "teacher.h"

// 超级管理员信息(固定)
#define ADMIN_NAME "admin"
#define ADMIN_PWD "admin123"
//struct student stu[1000];
//struct teacher tea[1000];
// 登录验证实现
UserType login(int *user_id, char *user_name) {
    int attempt = 0;
    char input_name[128];
    char input_pwd[32];

    while (attempt < 3) {
        printf("\n===== 系统登录 =====");
        printf("\n请输入用户名: ");
        scanf("%s", input_name);
        printf("请输入密码: ");
        scanf("%s", input_pwd);

        // 验证超级管理员
        if (strcmp(input_name, ADMIN_NAME) == 0) {
            if (strcmp(input_pwd, ADMIN_PWD) == 0) {
                strcpy(user_name, ADMIN_NAME);
                return ADMIN;
            }
        }
        // 验证教师
        else {
            int tea_len = teacher_rfile();
            for (int i = 0; i < tea_len; i++) {
                if (strcmp(input_name, tea[i].name) == 0) {
                    if (strcmp(input_pwd, tea[i].pwd) == 0) {
                        *user_id = tea[i].id;
                        strcpy(user_name, tea[i].name);
                        return TEACHER;
                    }
                }
            }
            // 验证学生
            int stu_len = stu_rfile();
            for (int i = 0; i < stu_len; i++) {
                if (strcmp(input_name, stu[i].name) == 0) {
                    if (strcmp(input_pwd, stu[i].pwd) == 0) {
                        *user_id = atoi(stu[i].number); // 学号转为整数ID
                        strcpy(user_name, stu[i].name);
                        return STUDENT;
                    }
                }
            }
        }

        attempt++;
        printf("用户名或密码错误，剩余尝试次数: %d\n", 3 - attempt);
    }

    printf("错误次数过多，系统退出!\n");
    exit(0);
}

// 密码修改实现
void change_password(UserType type, int user_id, const char *old_pwd, const char *new_pwd) {
    if (type == TEACHER) {
        int len = teacher_rfile();
        for (int i = 0; i < len; i++) {
            if (tea[i].id == user_id && strcmp(tea[i].pwd, old_pwd) == 0) {
                strcpy(tea[i].pwd, new_pwd);
                teacher_wfile(len);
                printf("密码修改成功!\n");
                return;
            }
        }
    }
    else if (type == STUDENT) {
        int len = stu_rfile();
        char id_str[10];
        sprintf(id_str, "%d", user_id);
        for (int i = 0; i < len; i++) {
            if (strcmp(stu[i].number, id_str) == 0 && strcmp(stu[i].pwd, old_pwd) == 0) {
                strcpy(stu[i].pwd, new_pwd);
                stu_wfile(len);
                printf("密码修改成功!\n");
                return;
            }
        }
    }
    printf("原密码错误，修改失败!\n");
}
