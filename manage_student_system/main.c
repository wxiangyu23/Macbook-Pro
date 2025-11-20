#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "student.h"
#include "teacher.h"
#include "tooler.h"
//void add_student();
//void del_student();
//void edit_student();
//char show_stu();

int main(int argc,const char *argv[])
{
   // main_menu();
  /*  char choice;
    while(1){
        //printf("------请输入你的选择------\n");
        printf("\n------请输入你的选择------\n");
        printf("1. 学生信息管理\n");
        printf("2. 教师信息管理\n");
        printf("3. 退出系统\n");
        printf("请选择：");
        scanf("%c", &choice);
        clear_input_buffer();  // 使用学生模块中的缓冲区清理函数或自行实现*/
        
        int user_id;
        char user_name[128];
        
        // 显示登录界面并验证
        show_login_prompt();
        UserType user_type = login(&user_id, user_name);
        
        // 显示欢迎界面
        show_welcome(user_name, user_type);
        
        while (1) {
            if (user_type == ADMIN) {
                show_admin_main_menu();
                char choice;
                scanf("%c", &choice);
                clear_input_buffer();
                
                switch (choice) {
                    case '1':show_admin_student_submenu();                   // 学生信息管理（原有功能）
                        scanf("%c",&choice);
                        while(getchar() !='\n');
                        switch(choice)
                        {
                            case '1':add_student();break;
                            case '2':del_student();break;      // 启用删除功能
                            case '3':edit_student();break;     // 启用修改功能
                            case '4':find_student();break;     // 改为查找功能
                            case '5':show_stu();break;         // 显示所有学生信息
                            case '6':return 0;break;                // 退出选项后移
                            default:printf("error\n");break;
                        }break;
                        
                        
                    case '2':show_admin_teacher_submenu();
                        char tea_choice;
                        printf("请选择教师操作：");
                        scanf("%c", &tea_choice);
                        clear_input_buffer();
                        switch (tea_choice) {
                            case '1': add_teacher(); break;
                            case '2': del_teacher(); break;
                            case '3': edit_teacher(); break;
                            case '4': show_teacher(); break;
                            case '5': break;
                            default: printf("无效选择！\n");
                        }break;
                        
                    case '3':  // 退出系统
                        printf("系统已退出！\n");
                        return 0;
                        
                    default:
                        printf("无效选择，请重新输入！\n");
                        
                        
                } }
            else if (user_type == TEACHER) {
                show_teacher_main_menu();
                char choice;
                scanf("%c", &choice);
                clear_input_buffer();
                
                switch (choice) {
                    case '1': teacher_view_info(user_id); break;
                    case '2': {
                        char old_pwd[32], new_pwd[32];
                        printf("请输入原密码: ");
                        scanf("%s", old_pwd);
                        printf("请输入新密码: ");
                        scanf("%s", new_pwd);
                        change_password(TEACHER, user_id, old_pwd, new_pwd);
                        break;
                    }
                    case '3': show_stu(); break;
                    case '4': teacher_edit_score(); break;
                    case '5': printf("系统已退出!\n"); return 0;
                    default: printf("无效选择!\n");
                }
            }
            else if (user_type == STUDENT) {
                show_student_main_menu();
                char choice;
                scanf("%c", &choice);
                clear_input_buffer();
                
                switch (choice) {
                    case '1': student_view_info(user_id); break;
                    case '2': {
                        char old_pwd[32], new_pwd[32];
                        printf("请输入原密码: ");
                        scanf("%s", old_pwd);
                        printf("请输入新密码: ");
                        scanf("%s", new_pwd);
                        change_password(STUDENT, user_id, old_pwd, new_pwd);
                        break;
                    }
                    case '3': student_edit_info(user_id); break;
                    case '4': printf("系统已退出!\n"); return 0;
                    default: printf("无效选择!\n");
                }
            }
        }
    
    return 0;
}
