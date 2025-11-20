#ifndef STUDENT_H  // 防止头文件重复包含（必须加，避免编译错误）
#define STUDENT_H

// 保留原结构体名student，所有字段名、字段顺序完全不变
struct student {
    char number[10];    // 保留原长度（可存9位学号+结束符）
    char name[32];      // 保留原长度（可存31位姓名+结束符）
    char pwd[10];       // 保留原长度（可存9位密码+结束符）
    char age[10];       // 保留原类型（若后续想改int，直接改这里类型即可，字段名不变）
    char group[10];     // 仅修改长度：从char[1]改为char[10]（不改字段名），可存班级信息
    float math;         // 保留原类型
    float c;            // 保留原字段名和类型
    float chinese;      // 保留原字段名和类型
    int rank;
};



extern struct student stu[1000];  // 外部可见的学生数组
extern int len;


// 保留所有原函数名，补充完整的函数原型（参数类型+返回值类型）
void add_student(void);  // 明确无参数，避免编译器警告
void stu_wfile(int len); // 明确参数类型（原可能缺失）
int stu_rfile(void);     // 明确无参数，返回int类型
void show_stu(void);     // 明确无参数
void calculate_rank();

// 新增函数声明
void clear_input_buffer(void);
void del_student(void);               // 删除学生
void edit_student(void);              // 修改学生
void find_student(void);              // 查找学生入口
void find_by_number(const char *num); // 按学号查找
void find_by_name(const char *name);  // 按姓名查找
void find_by_group(const char *group);// 按班级查找
void sort_by_number(void);            // 按学号排序
void sort_by_rank(void);              // 按名次排序
void sort_by_subject(int subject);    // 按科目排序
float calculate_average(int subject); // 计算科目平均分
void student_view_info(int id);
void student_edit_info(int id);
#endif
