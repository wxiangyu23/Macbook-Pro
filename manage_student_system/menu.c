#include <stdio.h>
#include "menu.h"
#include "student.h"


// 登录提示界面
void show_login_prompt() {
    printf("\n=================================\n");
    printf("         学生教师管理系统        \n");
    printf("=================================\n");
    printf("          请进行登录操作          \n");
}

// 欢迎界面
void show_welcome(const char *name, UserType type) {
    printf("\n=================================\n");
    if (type == STUDENT) {
        printf("        欢迎 %s 同学登录        \n", name);
    } else if (type == TEACHER) {
        printf("        欢迎 %s 老师登录        \n", name);
    } else if (type == ADMIN) {
        printf("        欢迎 %s 管理员登录      \n", name);
    }
    printf("=================================\n");
}

// 管理员主菜单
void show_admin_main_menu() {
    printf("\n===== 管理员操作菜单 =====");
    printf("\n1. 学生信息管理");
    printf("\n2. 教师信息管理");
    printf("\n3. 退出系统");
    printf("\n==========================");
    printf("\n请选择操作: ");
}

// 管理员学生子菜单
void show_admin_student_submenu() {
    printf("\n===== 学生信息管理 =====");
    printf("\n1. 添加学生");
    printf("\n2. 删除学生");
    printf("\n3. 修改学生");
    printf("\n4. 查找学生");
    printf("\n5. 显示所有学生");
    printf("\n6. 返回上一级");
    printf("\n========================");
    printf("\n请选择操作: ");
}

// 管理员教师子菜单
void show_admin_teacher_submenu() {
    printf("\n===== 教师信息管理 =====");
    printf("\n1. 添加教师");
    printf("\n2. 删除教师");
    printf("\n3. 修改教师");
    printf("\n4. 显示所有教师");
    printf("\n5. 返回上一级");
    printf("\n========================");
    printf("\n请选择操作: ");
}

// 教师主菜单
void show_teacher_main_menu() {
    printf("\n===== 教师操作菜单 =====");
    printf("\n1. 查看个人信息");
    printf("\n2. 修改个人密码");
    printf("\n3. 查看所有学生信息");
    printf("\n4. 修改学生成绩");
    printf("\n5. 退出系统");
    printf("\n========================");
    printf("\n请选择操作: ");
}

// 学生主菜单
void show_student_main_menu() {
    printf("\n===== 学生操作菜单 =====");
    printf("\n1. 查看个人信息");
    printf("\n2. 修改个人密码");
    printf("\n3. 修改个人基本信息");
    printf("\n4. 退出系统");
    printf("\n========================");
    printf("\n请选择操作: ");
}

// 学生信息排序子菜单
void show_student_sort_menu() {
    printf("\n1. 按学号顺序显示");
    printf("\n2. 按名次显示");
    printf("\n3. 按某学科成绩显示");
    printf("\n请选择显示方式: ");
}

// 学生查找子菜单
void show_find_student_menu() {
    printf("\n1. 按学号查找");
    printf("\n2. 按姓名查找");
    printf("\n3. 按班级查找");
    printf("\n请输入查找方式: ");
}
