#ifndef TOOLER_H
#define TOOLER_H

// 用户类型定义
typedef enum {
    STUDENT,
    TEACHER,
    ADMIN,
    INVALID
} UserType;

// 登录验证函数
UserType login(int *user_id, char *user_name);

// 密码修改函数
void change_password(UserType type, int user_id, const char *old_pwd, const char *new_pwd);

#endif
