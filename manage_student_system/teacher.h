#ifndef TEACHER_H
#define TEACHER_H

struct teacher {
    int id;             // 教员序号（唯一）
    char name[128];     // 教员姓名
    char pwd[32];       // 教员密码
    int class_num;      // 所任班级
};




extern struct teacher tea[100];  // 最多存储100名教师信息
extern int tea_len ;



// 教师信息管理函数声明
void add_teacher(void);        // 添加教师
void del_teacher(void);        // 删除教师
void edit_teacher(void);       // 修改教师
void show_teacher(void);       // 显示所有教师
int teacher_rfile(void);       // 从文件读取教师信息
void teacher_wfile(int len);   // 将教师信息写入文件
void teacher_view_info(int id);
void teacher_edit_score();
#endif
