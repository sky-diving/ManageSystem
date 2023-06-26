#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS_NUM 1000 // 最大学生数量
#define MAX_ADMINS_NUM 20    // 最大管理员数量

// 学生信息结构体
struct student_info {


    struct attendance_record attendance_records[100];
    char username[20];
    char password[20];
    // 其他信息
};

struct student_info {
    char name[20];                // 学生姓名
    int age;                      // 年龄
    char gender[10];              // 性别
    int xuehao[20];                //学号
    char phone[20];               // 联系电话
    char email[50];               // 邮箱
    char group[20];         //组名组成员完成次数
    int member[10];         //成员身份
    int finish_num;              //完成次数
    int num_attendance_records;      //出勤记录
    struct attendance_record attendance_records[100];     //出勤详情
    int absent_num;                // 缺勤次数
    char absent_reason[20];       // 缺勤原因
    char penalty[20];             // 惩罚措施
    char leave_date[20];          // 请假日期
    char leave_reason[20];        // 请假原因
    char leave_status[10];        // 请假状态（已确认、未确认）
    int leave_num;                //请假次数
    int absent_penalty_up;               // 缺勤惩罚次数
};


//出席情况结构体
struct attendance_record {
    char date[20];
    char status[10];
};

// 管理员信息结构体
struct admin_info {
    char username[20];
    char password[20];
    // 其他信息
};

// 函数声明
void load_admins_from_file(struct admin_info admins[], int* num_admins_ptr);
//负责人1 正道
void load_students_from_file(struct student_info students[], int* num_students_ptr);
//负责人2  正道
void save_admins_to_file(const struct admin_info admins[], const int num_admins);
//负责人3  正道

void save_students_to_file(const struct student_info students[], const int num_students);
//负责人4 衣锦

void show_login_page();
//负责人5  Cg
int student_login(const struct student_info students[], const int num_students);
//负责人6 Cg
int admin_login(const struct admin_info admins[], const int num_admins);
//负责人7  Cg

void show_student_info_page(const struct student_info students[], const int num_students, const int index);
//负责人8  红茶
void show_student_page(const struct student_info students[], const int num_students, const int index);
//负责人9  红茶

void add_student(struct student_info students[], int* num_students_ptr);
//负责人10  钻石

void delete_student(struct student_info students[], int* num_students_ptr);
//负责人11 钻石

void search_student(const struct student_info students[], const int num_students, const char search_criteria[]);
//负责人12  钻石

void output_group_students_info(const struct student_info students[], const int num_students, const char group_name[]);
//负责人13 衣锦

void save_student_info_to_file(const struct student_info students[], const int num_students, const char filename[]);
//负责人14 三号

void output_all_students_attendance(const struct student_info students[], const int num_students);
//负责人15 龙水
void output_absent_students_info(const struct student_info students[], const int num_students);
//负责人16 龙水
void write_leave(struct student_info students[], const int index);
//负责人17 龙水

void export_attendance_record(const struct student_info students[], const int index);
//负责人18 三号
void show_admin_page(struct student_info students[], const int num_students, struct admin_info admins[], const int num_admins);
//负责人19 三号

void manage_leave(struct student_info students[], const int num_students);
//负责人20 七号
void modify_absent_info(struct student_info students[], const int index);
//负责人21 七号
void record_penalty(struct student_info students[], const int index);
//负责人22 七号

int main() {
    // 定义变量
    struct student_info students[MAX_STUDENTS_NUM];
    int num_students = 0;
    struct admin_info admins[MAX_ADMINS_NUM];
    int num_admins = 0;

    // 从文件中读取管理员信息和学生信息
    load_admins_from_file(admins, &num_admins);
    load_students_from_file(students, &num_students);

    // 显示登陆页面
    show_login_page();

    // 保存所有学生信息和管理员信息到文件中
    save_admins_to_file(admins, num_admins);
    save_students_to_file(students, num_students);

    return 0;
}

// 从文件中读取管理员信息
void load_admins_from_file(struct admin_info admins[], int* num_admins_ptr) {
    // TODO: 从文件中读取管理员信息并存储在admins数组中，并将管理员数量存储在num_admins_ptr指针指向的变量中
    int cnt = 0;
    FILE* fp1;
    fopen_s(&fp1, "admins_data.txt", "r+");
    if (fp1 == NULL) {//若打开文件失败则退出
        puts("fp1不能打开文件！");
        return;
    }

    for (int i = 0; !feof(fp1); i++) {
        fscanf(fp1, "%s %s", admins[i].username, admins[i].password);
        cnt++;
    }
    fclose(fp1); //关闭文件
    *num_admins_ptr = cnt;

    return;
}

// 从文件中读取学生信息
void load_students_from_file(struct student_info students[], int* num_students_ptr) {
    // TODO: 从文件中读取学生信息并存储在students数组中，并将学生数量存储在num_students_ptr指针指向的变量中
    int cnt = 0;
    FILE* fp2;
    fopen_s(&fp2, "students_data.txt", "r+");
    if (fp2 == NULL) {      //若打开文件失败则退出
        puts("fp2不能打开文件！");
        return;
    }

    for (int i = 0; !feof(fp2); i++) {
        fscanf(fp2, "%s %d %s %s %d %s %s",
            students[i].name, students[i].age, students[i].gender, students[i].group,
            students[i].xuehao, students[i].username, students[i].password);
        cnt++;
    }
    fclose(fp2); //关闭文件
    *num_students_ptr = cnt;

    return;
}

// 将所有管理员信息保存到文件中
void save_admins_to_file(const struct admin_info admins[], const int num_admins) {
    // TODO: 将所有管理员信息保存到文件中
    FILE* fp3;
    fopen_s(&fp3, "admins_data.txt", "wt+");    //打开文件
    if (fp3 == NULL) {//若打开文件失败则退出
        puts("fp3不能打开文件！");
        return;
    }

    for (int i = 0; i < num_admins; i++)            //将num_admins条信息存储进去
    {
        fprintf(fp3, "%s %s\n", admins[i].username, admins[i].password);
    }

    fclose(fp3); //关闭文件
    return;
}

// 将所有学生信息保存到文件中
void save_students_to_file(const struct student_info students[], const int num_students) {

    FILE* fp;
    fp = fopen("D:\\学生小组.txt", "w");  // 以只写的方式打开文件
    if (fp == NULL) {
        printf("Failed to open file.\n");//若文件不存在，则输出信息，创建新文件
        return;
    }
    for (int i = 0; i < num_students; i++) {
        fprintf(fp, "%s %d %s %s\n", students[i].name, students[i].age, students[i].gender, students[i].group);  // 写入数据到文件
    }//若文件存在则清空，输入每个学生的信息
    fclose(fp);  // 关闭文件
    return;
}

// 显示登陆页面
void show_login_page() {
    // TODO: 显示登陆页面，根据用户选择调用student_login()或admin_login()

    int x = 0, i = 0;
    system("cls");
    printf("===========\n");
    printf("1.管理员登录\n");
    printf("2.学员登录\n");
    printf("===========\n");
    printf("请选择你的身份（输入1或2）：");
    scanf("%d", &x);
    if (x == 1) {
        admin_login();

    }
    if (x == 2) {
        student_login();
    }
    else {
        printf("输入错误。");
        system("pause");
        show_login_page();
    }
}

// 验证学员账号和密码的正确性，并返回结果
int student_login(const struct student_info students[], const int num_students) {

    int flag = 0, i = 0, j = 0, zh = 0, mm = 0;
    while (1) {
        system("cls");
        printf("账号:");
        scanf("%c", &zh);

        for (i = 0; i < 1000; i++) {
            if (zh == x[i].zh) {
                flag = 1;//flag==1表示找到对应的账户
                break;
            }
            else if (i == 999) {
                printf("未找到对应的管理员账号。\n");
                system("pause");

            }

        }
    }
    if (flag == 1) {
        printf("\n");
        while (flag != 2) {
            system("cls");
            printf("账号:%d\n", x[i].zh);
            printf("密码:");
            scanf("%d", &mm);
            if (x[i].mm == mm) {
                flag = 2;
                break;
            }
            else {
                printf("密码不正确，请重新输入");
                system("pause");
            }
        }

        // TODO: 实现学员登录验证功能，返回值为int类型，成功返回1，失败返回0
    }

    // 验证管理账号和密码的正确性，并返回结果
    int admin_login(const struct admin_info admins[], const int num_admins) {

        // TODO: 实现管理登录验证功能，返回值为int类型，成功返回1，失败返回0
        int flag = 0, i = 0, j = 0, zh = 0, mm = 0;
        while (flag != 1) {
            system("cls");
            printf("输入0反回上一界面\n");
            printf("账号:");

            scanf("%d", &zh);
            if (zh == 0) {
                show_login_page();
            }
            for (i = 0; i < 1000; i++) {
                if (zh == g[i].zh) {
                    flag = 1;//flag==1表示找到对应的账户
                    break;
                }
                else if (i == 999) {
                    printf("未找到对应的管理员账号。\n");
                    system("pause");
                }
            }

        }


        if (flag == 1) {
            printf("\n");
            while (flag != 2) {
                system("cls");
                printf("输入 0 重新输入账号\n");
                printf("账号：%d\n", g[i].zh);
                printf("密码:");
                scanf("%d", &mm);
                if (mm == 0) {
                    admin_login();
                }
                if (g[i].mm == mm) {
                    flag = 2;
                    break;
                }
                else {
                    printf("密码不正确，请重新输入");
                    system("pause");
                }
            }
        }
        if (flag == 2) {

        }
    }

    // 显示学员基本信息界面
    void show_student_info_page(const struct student_info students[], const int num_students, const int index) {
        // TODO: 显示学员基本信息界面，根据用户选择调用show_student_page()、write_leave()、export_attendance_record()等函数
        int i;
        do {
            printf("1.查看学员详细信息\n");
            printf("2.添加请假记录\n");
            printf("3.导出考勤记录\n");
            printf("请选择要进行的操作:");
            scanf("%d", &i);
            if (i == 1)
                show_student_page();
            else if (i == 2)
                write_leave();
            else if (i == 3)
                export_attendance_record();
            else
                printf("该操作不存在，请重新输入");
        } while (i <= 3);
    }

    // 显示某个学员的详细信息
    void show_student_page(const struct student_info students[], const int num_students, const int index) {
        // TODO: 显示某个学员的详细信息，包括姓名、年龄、性别、所在组别等等
        printf("请选择你要查看的学员信息");
        int i;//定义学号变量

        scanf("%d", &i);
        if (i <= num_students && i > 0)
        {
            printf("学号：%d\n", students[i].xuehao);
            printf("姓名：%s\n", students[i].name);
            printf("年龄：%d\n", students[i].age);
            printf("性别：%s\n", students[i].gender);
            printf("小组：%s\n", students[i].group);
        }
        else
            printf("该同学不存在,请重新输入");
    }

    // 添加一个学员
    void add_student(struct student_info students[], int* num_students_ptr) {
        // TODO: 添加一个学员，包括姓名、年龄、性别、所在组别等信息
        if (*num_students_ptr > MAX_STUDENTS_NUM) {
            printf("超过最大学生数");
            return;
        }
        struct student_info new_student;
        printf("请输入新学生的姓名：");
        scanf("%s", new_student.name);
        printf("请输入新学生的年龄：");
        scanf("%d", new_student.age);
        printf("请输入新学生的性别：");
        scanf("%s", new_student.gender);
        printf("请输入新学生的所在组别：");
        scanf("%s", new_student.group);
        printf("请输入新学生的学号：");
        scanf("%s", new_student.xuehao);

        for (int i = 0; i < *num_students_ptr; i++) {
            if (students[i].xuehao == new_student.xuehao) {//查找学号是否存在
                printf("学号已经存在");
                return;
            }
        }
        students[*num_students_ptr] = new_student;//添加学生
        (*num_students_ptr)++;

        for (int i = 0; i < *num_students_ptr; i++)
            for (int j = i + 1; j < *num_students_ptr; j++) {//按照学号排序
                struct student_info temp = students[i];
                if (students[i].xuehao > students[j].xuehao) {
                    students[i] = students[j];
                    students[j] = temp;
                }

            }
        return;
    }

    // 删除一个学员
    void delete_student(struct student_info students[], int* num_students_ptr) {
        // TODO: 删除一个学员，可根据学员姓名或其它标识来查找并删除
        int  xuehao_to_delete, index_to_delete = -1;//要删除的学号和下标初始化为-1

        printf("请输入要删除的学生的学号：");
        for (int i = 0; i < *num_students_ptr; i++) {

            if ((int)students[i].xuehao == xuehao_to_delete) {
                index_to_delete = i;
                break;
            }
        }
        if (index_to_delete == -1) {
            printf("未找到学号为%d的学生", xuehao_to_delete);
            return;
        }
        for (int i = xuehao_to_delete; i < *num_students_ptr - 1; i++) {
            students[i] = students[i + 1];
        }
        *num_students_ptr--;
        for (int i = 0; i < *num_students_ptr; i++)
            for (int j = i + 1; j < *num_students_ptr; j++) {//按照学号排序
                struct student_info temp = students[i];
                if (students[i].xuehao > students[j].xuehao) {
                    students[i] = students[j];
                    students[j] = temp;
                }

            }
        printf("学号为%d的学生已删除", xuehao_to_delete);
        return;
    }

    // 查找学员
    void search_student(const struct student_info students[], const int num_students, const char search_criteria[]) {
        // TODO: 根据输入的查找条件在学生信息列表中查找学员，并输出相关信息
        int found = 0, tiaojian = 0;//定义查找
        printf("请选择查找条件：\n");
        printf("输入1：学号查找\n");
        printf("输入2：姓名查找\n");
        printf("输入3：性别查找\n");
        printf("输入4：组别查找\n");
        scanf("%d", &tiaojian);
        while (1) {
            if (tiaojian != 1 && tiaojian != 2 && tiaojian != 3 && tiaojian != 4) {
                printf("条件错误，请重试：\n");
                scanf("%d", &tiaojian);
            }
            else {
                break;
            }
        }
        printf("请输入要查找的内容：\n");
        char search_text[20];
        scanf("%s", search_text);
        printf("符合条件的学生信息如下：\n");
        printf("学号\t姓名\t年龄\t性别\t组别\n");
        for (int i = 0; i < num_students; i++) {
            if (tiaojian == 1 && strstr(students[i].xuehao, search_text) != NULL) {
                printf("%s\t%s\t%d\t%s\t%s\n", students[i].xuehao, students[i].name, students[i].age, students[i].gender, students[i].group);
                found = 1;
            }
            else if (tiaojian == 2 && strstr(students[i].name, search_text) != NULL) {
                printf("%s\t%s\t%d\t%s\t%s\n", students[i].xuehao, students[i].name, students[i].age, students[i].gender, students[i].group);
                found = 1;
            }
            else if (tiaojian == 3 && strstr(students[i].gender, search_text) != NULL) {
                printf("%s\t%s\t%d\t%s\t%s\n", students[i].xuehao, students[i].name, students[i].age, students[i].gender, students[i].group);
                found = 1;
            }
            else if (tiaojian == 4 && strstr(students[i].group, search_text) != NULL) {
                printf("%s\t%s\t%d\t%s\t%s\n", students[i].xuehao, students[i].name, students[i].age, students[i].gender, students[i].group);
                found = 1;
            }
        }
        if (!found) {
            printf("未找到符合条件的学生信息。\n");
        }
    }

    // 输出某小组的学员信息
    void output_group_students_info(const struct student_info students[], const int num_students, const char group_name[]) {
        // TODO: 输出某小组的学员信息，包括姓名、年龄、性别等
        int i;
        int found = 0; // 标记是否找到符合条件的学生记录

        // 输出表头
        printf("姓名\t年龄\t性别\t小组\n");

        // 遍历学生信息结构体数组
        for (i = 0; i < num_students; i++) {
            // 如果所属组别与指定组别名称一致，则输出学生信息
            if (strcmp(students[i].group, group_name) == 0) {
                printf("%s\t%d\t%c\t%s\n", students[i].name, students[i].age, students[i].gender, students[i].group);
                found = 1; // 标记已找到符合条件的学生记录
            }
        }

        // 如果未找到符合条件的学生记录，则输出相应的错误提示
        if (!found) {
            printf("未找到组别为%s的学生记录\n", group_name);
        }
    }

    // 保存所有学生信息到文件中
    void save_student_info_to_file(const struct student_info students[], const int num_students, const char filename[]) {
        // TODO: 将指定的学生信息保存到指定的文件中，可使用文件I/O相关函数实现
        FILE* file = fopen(filename, "w");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }

        for (int i = 0; i < num_students; i++) {
            fprintf(file, "Name: %s\n", students[i].name);
            fprintf(file, "Age: %d\n", students[i].age);
            fprintf(file, "Gender: %s\n", students[i].gender);
            fprintf(file, "Group: %s\n", students[i].group);
            fprintf(file, "\n");
        }

        fclose(file);
        printf("Student information saved to file: %s\n", filename);
    }

    // 输出所有学员的打卡信息
    void output_all_students_attendance(const struct student_info students[], const int num_students) {
        // TODO: 输出所有学员的打卡信息，包括考勤状态（出勤、迟到或旷课）和旷课次数等信息
    }

    // 输出所有缺勤人员信息
    void output_absent_students_info(const struct student_info students[], const int num_students) {
        // TODO: 输出所有缺勤人员信息，包括姓名、所在组别、缺勤原因等信息
    }

    // 添加请假记录
    void write_leave(struct student_info students[], const int index) {
        // TODO: 根据用户输入添加请假记录，并在学生信息中相应地标注该学生已请假
    }

    // 导出某学员的打卡记录
    void export_attendance_record(const struct student_info students[], const int index) {
        // TODO: 导出某学员的打卡记录，以便学员、家长或者老师查看
        const struct student_info* student_ptr = &students[index];

        FILE* file = fopen("attendance_record.txt", "w");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }

        fprintf(file, "Name: %s\n", student_ptr->name);
        fprintf(file, "Group: %s\n", student_ptr->group);
        fprintf(file, "\nAttendance Record:\n");

        for (int i = 0; i < student_ptr->num_attendance_records; i++) {
            const struct attendance_record* record = &(student_ptr->attendance_records[i]);
            fprintf(file, "Date: %s\n", record->date);
            fprintf(file, "Status: %s\n", record->status);
            fprintf(file, "\n");
        }

        fclose(file);
        printf("Attendance record exported to attendance_record.txt\n");
    }

    // 显示管理员界面
    void show_admin_page(struct student_info students[], const int num_students, struct admin_info admins[], const int num_admins) {
        // TODO: 显示管理员界面，包括各种操作选项和菜单，根据用户选择调用相应函数
        int choice;
        int student_index;
        while (1) {
            printf("Admin Page\n");
            printf("1. Manage Student Attendance\n");
            printf("2. Manage Student Leaves\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
            case 1:
                printf("Enter student index: ");
                scanf("%d", &student_index);
                if (student_index >= 0 && student_index < num_students) {
                    export_attendance_record(students, student_index);
                }
                else {
                    printf("Invalid student index.\n");
                }
                break;
            case 2:
                printf("Enter student index: ");
                scanf("%d", &student_index);
                if (student_index >= 0 && student_index < num_students) {
                    manage_leave(students, student_index);
                }
                else {
                    printf("Invalid student index.\n");
                }
                break;
            case 3:
                printf("Exiting admin page.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    }




    void manage_record(struct student_info students[], const int num_students，const int index) {
        int record_type;
        printf("请选择您要进行的操作：\n1. 查询请假记录\n2. 管理请假记录\n3. 查询缺勤记录\n4. 管理缺勤记录\n5. 查询惩罚记录\n6. 管理惩罚记录\n");
        scanf("%d", &record_type);

        switch (record_type) {
        case 1:
            printf("请输入学员姓名：");
            char name[20];
            scanf("%s", name);
            int flag = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].name, name) == 0)
                {
                    printf("该学员请假记录如下：\n");
                    for (int i = 0; i < students[index].leave_num; i++) {
                        printf("第%d次请假：日期：%s，原因：%s\n", i + 1, students[index].leave_dates[i], students[index].leave_reasons[i]);
                    }
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                printf("未找到该学员，请重新输入。\n");
            }
            break;
        case 2:
            printf("请输入学员姓名：");
            char name2[20];
            scanf("%s", name2);
            int flag2 = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].name, name2) == 0) {
                    if (students[i].leave_num >= 3) { //增加对学生请假次数的判断
                        printf("该学员已达到最大请假次数，请勿再次请假！\n");
                    }
                    else {
                        printf("请输入请假日期：");
                        scanf("%s", students[index].leave_dates[students[index].leave_num]);
                        printf("请输入请假原因：");
                        scanf("%s", students[index].leave_reasons[students[index].leave_num]);
                        students[index].leave_num++;
                        printf("请假申请已审核通过！\n");
                    }
                    flag2 = 1;
                    break;
                }
            }
            if (flag2 == 0) {
                printf("未找到该学员，请重新输入。\n");
            }
            break;
        case 3:
            printf("请输入学员姓名：");
            char name3[20];
            scanf("%s", name3);
            int flag3 = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].name, name3) == 0) {
                    printf("该学员缺勤记录如下：\n");
                    for (int i = 0; i < students[index].absence_num; i++) {
                        printf("第%d次缺勤：日期：%s，原因：%s\n", i + 1, students[index].absence_dates[i], students[index].absence_reasons[i]);
                    }
                    flag3 = 1;
                    break;
                }
            }
            if (flag3 == 0) {
                printf("未找到该学员，请重新输入。\n");
            }
            break;
        case 4:
            printf("请输入学员姓名：");
            char name4[20];
            scanf("%s", name4);
            int flag4 = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].name, name4) == 0) {


                    int choice;
                    printf("请选择您要进行的操作：\n1. 添加缺勤记录\n2. 修改缺勤记录\n3. 删除缺勤记录\n");
                    scanf("%d", &choice);

                    switch (choice) {
                    case 1:
                        if (students[index].absence_num < MAX_ABSENCE_NUM) {
                            printf("请输入缺勤日期：");
                            scanf("%s", students[index].absence_dates[students[index].absence_num]);
                            printf("请输入缺勤原因：");
                            scanf("%s", students[index].absence_reasons[students[index].absence_num]);
                            students[index].absence_num++;
                            printf("添加成功！\n");
                        }
                        else {
                            printf("缺勤记录已满，无法添加更多记录！\n");
                        }
                        break;
                    case 2:
                        printf("请输入要修改的缺勤记录编号（1-%d）：", students[index].absence_num);
                        int modify_index;
                        scanf("%d", &modify_index);
                        if (modify_index >= 1 && modify_index <= students[index].absence_num) {
                            printf("请输入新的缺勤日期：");
                            scanf("%s", students[index].absence_dates[modify_index - 1]);
                            printf("请输入新的缺勤原因：");
                            scanf("%s", students[index].absence_reasons[modify_index - 1]);
                            printf("修改成功！\n");
                        }
                        else {
                            printf("无效的缺勤记录编号！\n");
                        }
                        break;
                    case 3:
                        printf("请输入要删除的缺勤记录编号（1-%d）：", students[index].absence_num);
                        int delete_index;
                        scanf("%d", &delete_index);
                        if (delete_index >= 1 && delete_index <= students[index].absence_num) {
                            for (int i = delete_index - 1; i < students[index].absence_num - 1; i++) {
                                strcpy(students[index].absence_dates[i], students[index].absence_dates[i + 1]);
                                strcpy(students[index].absence_reasons[i], students[index].absence_reasons[i + 1]);
                            }
                            students[index].absence_num--;
                            printf("删除成功！\n");
                        }
                        else {
                            printf("无效的缺勤记录编号！\n");
                        }
                        break;
                    default:
                        printf("输入有误，请重新输入。\n");
                        break;
                    }


                    flag4 = 1;
                    break;
                }
            }
            if (flag4 == 0) {
                printf("未找到该学员，请重新输入。\n");
            }
            break;
        case 5:
            printf("请输入学员姓名：");
            char name5[20];
            scanf("%s", name5);
            int flag5 = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].name, name5) == 0) {
                    printf("该学员惩罚记录如下：\n");
                    for (int i = 0; i < students[index].punishment_num; i++) {
                        printf("第%d次惩罚：日期：%s，行为：%s\n", i + 1, students[index].punishment_dates[i], students[index].punishment_behaviors[i]);
                    }
                    flag5 = 1;
                    break;
                }
            }
            if (flag5 == 0) {
                printf("未找到该学员，请重新输入。\n");
            }
            break;
        case 6:
            printf("请输入学员姓名：");
            char name6[20];
            scanf("%s", name6);
            int flag6 = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].name, name6) == 0) {

                    int choice;
                    printf("请选择您要进行的操作：\n1. 添加惩罚记录\n2. 修改惩罚记录\n3. 删除惩罚记录\n");
                    scanf("%d", &choice);

                    switch (choice) {
                    case 1:
                        if (students[index].punishment_num < MAX_PUNISHMENT_NUM) {
                            printf("请输入惩罚日期：");
                            scanf("%s", students[index].punishment_dates[students[index].punishment_num]);
                            printf("请输入惩罚行为：");
                            scanf("%s", students[index].punishment_behaviors[students[index].punishment_num]);
                            students[index].punishment_num++;
                            printf("添加成功！\n");
                        }
                        else {
                            printf("惩罚记录已满，无法添加更多记录！\n");
                        }
                        break;
                    case 2:
                        printf("请输入要修改的惩罚记录编号（1-%d）：", students[index].punishment_num);
                        int modify_index;
                        scanf("%d", &modify_index);
                        if (modify_index >= 1 && modify_index <= students[index].punishment_num) {
                            printf("请输入新的惩罚日期：");
                            scanf("%s", students[index].punishment_dates[modify_index - 1]);
                            printf("请输入新的惩罚行为：");
                            scanf("%s", students[index].punishment_behaviors[modify_index - 1]);
                            printf("修改成功！\n");
                        }
                        else {
                            printf("无效的惩罚记录编号！\n");
                        }
                        break;
                    case 3:
                        printf("请输入要删除的惩罚记录编号（1-%d）：", students[index].punishment_num);
                        int delete_index;
                        scanf("%d", &delete_index);
                        if (delete_index >= 1 && delete_index <= students[index].punishment_num) {
                            for (int i = delete_index - 1; i < students[index].punishment_num - 1; i++) {
                                strcpy(students[index].punishment_dates[i], students[index].punishment_dates[i + 1]);
                                strcpy(students[index].punishment_behaviors[i], students[index].punishment_behaviors[i + 1]);
                            }
                            students[index].punishment_num--;
                            printf("删除成功！\n");
                        }
                        else {
                            printf("无效的惩罚记录编号！\n");
                        }
                        break;
                    default:
                        printf("输入有误，请重新输入。\n");
                        break;
                    }

                    flag6 = 1;
                    break;
                }
            }
            if (flag6 == 0) {
                printf("未找到该学员，请重新输入。\n");
            }
            break);
        default:
            printf("输入有误，请重新输入。\n");
            break;
        }
    }



