#ifndef MENU_H
#define MENU_H

#include "tooler.h"  // 引入用户类型定义

// 主菜单及登录相关
void show_login_prompt();
void show_welcome(const char *name, UserType type);

// 管理员菜单
void show_admin_main_menu();
void show_admin_student_submenu();
void show_admin_teacher_submenu();

// 教师菜单
void show_teacher_main_menu();

// 学生菜单
void show_student_main_menu();

// 通用功能菜单
void show_student_sort_menu();
void show_find_student_menu();

// 输入缓冲区清理
void clear_input_buffer();

#endif
