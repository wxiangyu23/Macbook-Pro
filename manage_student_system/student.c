#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"student.h"
#include"teacher.h"
// 完全保留你的命名，不修改任何变量/函数名
 struct student stu[1000];
 int len = 0;  // 保留原全局变量名

// 新增：清理输入缓冲区（解决残留字符问题，不影响原有命名）
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 新增：检查学号是否重复
int is_number_exist(const char *number) {
    for (int i = 0; i < len; i++) {
        if (strcmp(stu[i].number, number) == 0) {
            return 1; // 存在
        }
    }
    return 0; // 不存在
}
// 新增：计算学生名次（按总分排序）
void calculate_rank() {
    // 计算总分并排序
    for (int i = 0; i < len; i++) {
        float total1 = stu[i].math + stu[i].c + stu[i].chinese;
        int rank = 1;
        
        for (int j = 0; j < len; j++) {
            float total2 = stu[j].math + stu[j].c + stu[j].chinese;
            if (total2 > total1) {
                rank++;
            }
        }
        stu[i].rank = rank;
    }
}


// 保留函数名add_student，仅修复内部错误
void add_student() {
    len = stu_rfile();  // 复用原全局变量，读取已有学生数量
    if (len >= 1000) {
        printf("学生数量已达上限，无法添加！\n");
        return;
    }

    printf("请输入学生的学号：\n");
    char number[10];
    scanf("%9s",number);  // 限制长度防溢出（假设number是char[10]）
    
    // 检查学号是否重复
      if (is_number_exist(number)) {
          printf("学号已存在，请重新输入！\n");
          clear_input_buffer();
          return;
      }
      strcpy(stu[len].number, number);
    
    printf("请输入学生的姓名：\n");
    scanf("%31s", stu[len].name);   // 限制长度（假设name是char[32]）
    
    printf("请输入学生的密码：\n");
    scanf("%9s", stu[len].pwd);     // 限制长度（假设pwd是char[10]）
    
    printf("请输入学生的年龄：\n");
    scanf("%9s", stu[len].age);     // 保留原age字段类型（若为char[10]）
    
    // 关键修复：group字段若为char[1]无法存有效数据，临时兼容输入（建议后续改char[10]）
    printf("请输入学生的班级：\n");
    scanf("%1s", stu[len].group);   // 限制输入1个字符，匹配原char[1]定义
    
    printf("请输入学生的数学成绩：\n");
    scanf("%f", &stu[len].math);    // 修复：补充&，格式符匹配float类型
    
    printf("请输入学生的c语言成绩：\n");
    scanf("%f", &stu[len].c);       // 修复：补充&，格式符匹配float类型
    
    printf("请输入学生的语文成绩：\n");
    scanf("%f", &stu[len].chinese); // 修复：补充&，格式符匹配float类型
   
    len++;
    calculate_rank();
    printf("录入成功！\n");
    stu_wfile(len);  // 保留原函数名，传入当前学生数量
    clear_input_buffer();  // 清理缓冲区，避免后续输入异常
}

// 保留函数名stu_wfile，仅修复文件操作错误
void stu_wfile(int len) {
    FILE *fp = fopen("stu.txt", "wb");  // 二进制模式更稳定，避免文本格式错乱
    if (fp == NULL) {
        printf("文件打开失败，无法保存数据！\n");
        return;
    }

    fwrite(stu, sizeof(struct student), len, fp);
    fclose(fp);  // 确保关闭文件，避免资源泄露
}

// 保留函数名stu_rfile，仅修复空指针问题
int stu_rfile() {
    FILE *fp = fopen("stu.txt", "rb");  // 二进制模式读取，与写入模式对应
    if (fp == NULL) {
        return 0;  // 文件不存在时返回0，避免空指针操作
    }

    int read_len = 0;
    // 限制读取数量，避免数组越界（最多读1000个学生）
    while (read_len < 1000 && fread(&stu[read_len], sizeof(struct student), 1, fp)) {
        read_len++;
    }
    fclose(fp);  // 确保关闭文件
    return read_len;
}

// 保留函数名show_stu，仅修复排序逻辑和输出错误

// 删除学生信息
void del_student() {
    len = stu_rfile();
    if (len == 0) {
        printf("暂无学生信息！\n");
        return;
    }

    char number[10];
    printf("请输入要删除的学生学号：\n");
    scanf("%9s", number);
    clear_input_buffer();

    int i, found = 0;
    for (i = 0; i < len; i++) {
        if (strcmp(stu[i].number, number) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("未找到该学生！\n");
        return;
    }

    // 移动数组元素覆盖要删除的学生
    for (; i < len - 1; i++) {
        stu[i] = stu[i + 1];
    }
    len--;
    calculate_rank();  // 重新计算名次
    stu_wfile(len);
    printf("删除成功！\n");
}

// 修改学生信息
void edit_student() {
    len = stu_rfile();
    if (len == 0) {
        printf("暂无学生信息！\n");
        return;
    }

    char number[10];
    printf("请输入要修改的学生学号：\n");
    scanf("%9s", number);
    clear_input_buffer();

    int i, found = 0;
    for (i = 0; i < len; i++) {
        if (strcmp(stu[i].number, number) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("未找到该学生！\n");
        return;
    }

    printf("请输入新的姓名：\n");
    scanf("%31s", stu[i].name);
    
    printf("请输入新的密码：\n");
    scanf("%9s", stu[i].pwd);
    
    printf("请输入新的年龄：\n");
    scanf("%9s", stu[i].age);
    
    printf("请输入新的班级：\n");
    scanf("%9s", stu[i].group);
    
    printf("请输入新的数学成绩：\n");
    scanf("%f", &stu[i].math);
    
    printf("请输入新的c语言成绩：\n");
    scanf("%f", &stu[i].c);
    
    printf("请输入新的语文成绩：\n");
    scanf("%f", &stu[i].chinese);
    
    calculate_rank();  // 重新计算名次
    stu_wfile(len);
    printf("修改成功！\n");
    clear_input_buffer();
}


// 按学号查找
void find_by_number(const char *num) {
    int found = 0;
    for (int i = 0; i < len; i++) {
        if (strcmp(stu[i].number, num) == 0) {
            printf("找到学生信息：\n");
            printf("学号：%s\n", stu[i].number);
            printf("姓名：%s\n", stu[i].name);
            printf("密码：%s\n", stu[i].pwd);
            printf("年龄：%s\n", stu[i].age);
            printf("班级：%s\n", stu[i].group);
            printf("数学成绩：%.1f\n", stu[i].math);
            printf("C语言成绩：%.1f\n", stu[i].c);
            printf("语文成绩：%.1f\n", stu[i].chinese);
            printf("名次：%d\n", stu[i].rank);
            printf("-------------------------\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("未找到该学号的学生！\n");
    }
}


// 按姓名查找
void find_by_name(const char *name) {
    int found = 0;
    for (int i = 0; i < len; i++) {
        if (strcmp(stu[i].name, name) == 0) {
            printf("找到学生信息：\n");
            printf("学号：%s\n", stu[i].number);
            printf("姓名：%s\n", stu[i].name);
            printf("密码：%s\n", stu[i].pwd);
            printf("年龄：%s\n", stu[i].age);
            printf("班级：%s\n", stu[i].group);
            printf("数学成绩：%.1f\n", stu[i].math);
            printf("C语言成绩：%.1f\n", stu[i].c);
            printf("语文成绩：%.1f\n", stu[i].chinese);
            printf("名次：%d\n", stu[i].rank);
            printf("-------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("未找到该姓名的学生！\n");
    }
}

// 按班级查找
void find_by_group(const char *group) {
    int found = 0;
    for (int i = 0; i < len; i++) {
        if (strcmp(stu[i].group, group) == 0) {
            if (!found) {
                printf("找到以下%s班的学生：\n", group);
            }
            printf("学号：%s\n", stu[i].number);
            printf("姓名：%s\n", stu[i].name);
            printf("年龄：%s\n", stu[i].age);
            printf("数学成绩：%.1f\n", stu[i].math);
            printf("C语言成绩：%.1f\n", stu[i].c);
            printf("语文成绩：%.1f\n", stu[i].chinese);
            printf("名次：%d\n", stu[i].rank);
            printf("-------------------------\n");
            found = 1;
        }
    }
    if (!found) {
        printf("未找到该班级的学生！\n");
    }
}

// 查找学生入口
void find_student() {
    len = stu_rfile();
    if (len == 0) {
        printf("暂无学生信息！\n");
        return;
    }

    char choice;
    printf("1. 按学号查找\n");
    printf("2. 按姓名查找\n");
    printf("3. 按班级查找\n");
    printf("请输入查找方式：");
    scanf("%c", &choice);
    clear_input_buffer();

    char key[32];
    switch (choice) {
        case '1':
            printf("请输入要查找的学号：");
            scanf("%9s", key);
            find_by_number(key);
            break;
        case '2':
            printf("请输入要查找的姓名：");
            scanf("%31s", key);
            find_by_name(key);
            break;
        case '3':
            printf("请输入要查找的班级：");
            scanf("%9s", key);
            find_by_group(key);
            break;
        default:
            printf("无效选择！\n");
    }
    clear_input_buffer();
}

// 新增：按学号排序
void sort_by_number() {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (strcmp(stu[j].number, stu[j+1].number) > 0) {
                struct student temp = stu[j];
                stu[j] = stu[j+1];
                stu[j+1] = temp;
            }
        }
    }
}

// 按名次排序
void sort_by_rank() {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (stu[j].rank > stu[j+1].rank) {
                struct student temp = stu[j];
                stu[j] = stu[j+1];
                stu[j+1] = temp;
            }
        }
    }
}

// 按科目排序（1:数学, 2:C语言, 3:语文）
void sort_by_subject(int subject) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            float score1, score2;
            switch (subject) {
                case 1:
                    score1 = stu[j].math;
                    score2 = stu[j+1].math;
                    break;
                case 2:
                    score1 = stu[j].c;
                    score2 = stu[j+1].c;
                    break;
                case 3:
                    score1 = stu[j].chinese;
                    score2 = stu[j+1].chinese;
                    break;
            }
            if (score1 < score2) {  // 降序排列
                struct student temp = stu[j];
                stu[j] = stu[j+1];
                stu[j+1] = temp;
            }
        }
    }
}

// 计算科目平均分
float calculate_average(int subject) {
    float sum = 0;
    for (int i = 0; i < len; i++) {
        switch (subject) {
            case 1:
                sum += stu[i].math;
                break;
            case 2:
                sum += stu[i].c;
                break;
            case 3:
                sum += stu[i].chinese;
                break;
        }
    }
    return sum / len;
}


void show_stu() {
    len = stu_rfile();  // 读取最新学生数据
    if (len == 0) {
        printf("暂无学生信息！\n");
        return;
    }
    calculate_rank();
    char choice;
    printf("1. 按学号顺序显示\n");
       printf("2. 按名次显示\n");
       printf("3. 按某学科成绩显示\n");
       printf("请选择显示方式：");
       scanf("%c", &choice);
       clear_input_buffer();
    
    int subject = 0;
        switch (choice) {
            case '1':
                sort_by_number();
                break;
            case '2':
                sort_by_rank();
                break;
            case '3':
                printf("1. 数学\n2. C语言\n3. 语文\n请选择学科：");
                scanf("%d", &subject);
                clear_input_buffer();
                if (subject < 1 || subject > 3) {
                    printf("无效选择！\n");
                    return;
                }
                sort_by_subject(subject);
                break;
            default:
                printf("无效选择！\n");
                return;
        }
    // 显示学生信息
      for (int i = 0; i < len; i++) {
          printf("序号：%d\n", i + 1);
          printf("学号：%s\n", stu[i].number);
          printf("姓名：%s\n", stu[i].name);
          printf("年龄：%s\n", stu[i].age);
          printf("班级：%s\n", stu[i].group);
          printf("数学成绩：%.1f\n", stu[i].math);
          printf("C语言成绩：%.1f\n", stu[i].c);
          printf("语文成绩：%.1f\n", stu[i].chinese);
          printf("名次：%d\n", stu[i].rank);
          printf("-------------------------\n");
      }

      // 显示学科平均分（如果选择了按学科显示）
      if (choice == '3') {
          float avg = calculate_average(subject);
          const char *subject_name[] = {"", "数学", "C语言", "语文"};
          printf("%s平均分：%.1f\n", subject_name[subject], avg);
      }
    
    
    
    
    /*
    // 修复排序逻辑（冒泡排序，按c语言成绩降序），不改动变量名
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (stu[j].c < stu[j+1].c) {  // 原逻辑修正，正确比较相邻元素
                struct student temp = stu[j];
                stu[j] = stu[j+1];
                stu[j+1] = temp;
            }
        }
    }

    // 保留原输出字段，仅修正格式符（float用%f，字符串用%s）
    for (int i = 0; i < len; i++) {
        printf("序号：%d\n", i + 1);
        printf("学号：%s\n", stu[i].number);
        printf("姓名：%s\n", stu[i].name);
        printf("密码：%s\n", stu[i].pwd);
        printf("年龄：%s\n", stu[i].age);
        printf("班级：%s\n", stu[i].group);
        printf("数学成绩：%.1f\n", stu[i].math);  // 保留1位小数，提升可读性
        printf("C语言成绩：%.1f\n", stu[i].c);
        printf("语文成绩：%.1f\n", stu[i].chinese);
        printf("-------------------------\n");
    }*/
}
// 学生查看个人信息
void student_view_info(int id) {
    int len = stu_rfile();
    char id_str[10];
    sprintf(id_str, "%d", id);
    for (int i = 0; i < len; i++) {
        if (strcmp(stu[i].number, id_str) == 0) {
            printf("\n===== 个人信息 =====");
            printf("\n学号: %s", stu[i].number);
            printf("\n姓名: %s", stu[i].name);
            printf("\n年龄: %s", stu[i].age);
            printf("\n班级: %s", stu[i].group);
            printf("\n数学成绩: %.1f", stu[i].math);
            printf("\nC语言成绩: %.1f", stu[i].c);
            printf("\n语文成绩: %.1f", stu[i].chinese);
            printf("\n名次: %d", stu[i].rank);
            printf("\n====================");
            return;
        }
    }
    printf("未找到个人信息!\n");
}

// 学生修改基本信息
void student_edit_info(int id) {
    int len = stu_rfile();
    char id_str[10];
    sprintf(id_str, "%d", id);
    for (int i = 0; i < len; i++) {
        if (strcmp(stu[i].number, id_str) == 0) {
            printf("请输入新姓名: ");
            scanf("%s", stu[i].name);
            printf("请输入新年龄: ");
            scanf("%s", stu[i].age);
            printf("请输入新班级: ");
            scanf("%s", stu[i].group);
            stu_wfile(len);
            calculate_rank(); // 可能影响名次
            printf("信息修改成功!\n");
            return;
        }
    }
    printf("修改失败!\n");
}
