#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS_NUM 1000 // ���ѧ������
#define MAX_ADMINS_NUM 20    // ������Ա����

// ѧ����Ϣ�ṹ��
struct student_info {


    struct attendance_record attendance_records[100];
    char username[20];
    char password[20];
    // ������Ϣ
};

struct student_info {
    char name[20];                // ѧ������
    int age;                      // ����
    char gender[10];              // �Ա�
    int xuehao[20];                //ѧ��
    char phone[20];               // ��ϵ�绰
    char email[50];               // ����
    char group[20];         //�������Ա��ɴ���
    int member[10];         //��Ա���
    int finish_num;              //��ɴ���
    int num_attendance_records;      //���ڼ�¼
    struct attendance_record attendance_records[100];     //��������
    int absent_num;                // ȱ�ڴ���
    char absent_reason[20];       // ȱ��ԭ��
    char penalty[20];             // �ͷ���ʩ
    char leave_date[20];          // �������
    char leave_reason[20];        // ���ԭ��
    char leave_status[10];        // ���״̬����ȷ�ϡ�δȷ�ϣ�
    int leave_num;                //��ٴ���
    int absent_penalty_up;               // ȱ�ڳͷ�����
};


//��ϯ����ṹ��
struct attendance_record {
    char date[20];
    char status[10];
};

// ����Ա��Ϣ�ṹ��
struct admin_info {
    char username[20];
    char password[20];
    // ������Ϣ
};

// ��������
void load_admins_from_file(struct admin_info admins[], int* num_admins_ptr);
//������1 ����
void load_students_from_file(struct student_info students[], int* num_students_ptr);
//������2  ����
void save_admins_to_file(const struct admin_info admins[], const int num_admins);
//������3  ����

void save_students_to_file(const struct student_info students[], const int num_students);
//������4 �½�

void show_login_page();
//������5  Cg
int student_login(const struct student_info students[], const int num_students);
//������6 Cg
int admin_login(const struct admin_info admins[], const int num_admins);
//������7  Cg

void show_student_info_page(const struct student_info students[], const int num_students, const int index);
//������8  ���
void show_student_page(const struct student_info students[], const int num_students, const int index);
//������9  ���

void add_student(struct student_info students[], int* num_students_ptr);
//������10  ��ʯ

void delete_student(struct student_info students[], int* num_students_ptr);
//������11 ��ʯ

void search_student(const struct student_info students[], const int num_students, const char search_criteria[]);
//������12  ��ʯ

void output_group_students_info(const struct student_info students[], const int num_students, const char group_name[]);
//������13 �½�

void save_student_info_to_file(const struct student_info students[], const int num_students, const char filename[]);
//������14 ����

void output_all_students_attendance(const struct student_info students[], const int num_students);
//������15 ��ˮ
void output_absent_students_info(const struct student_info students[], const int num_students);
//������16 ��ˮ
void write_leave(struct student_info students[], const int index);
//������17 ��ˮ

void export_attendance_record(const struct student_info students[], const int index);
//������18 ����
void show_admin_page(struct student_info students[], const int num_students, struct admin_info admins[], const int num_admins);
//������19 ����

void manage_leave(struct student_info students[], const int num_students);
//������20 �ߺ�
void modify_absent_info(struct student_info students[], const int index);
//������21 �ߺ�
void record_penalty(struct student_info students[], const int index);
//������22 �ߺ�

int main() {
    // �������
    struct student_info students[MAX_STUDENTS_NUM];
    int num_students = 0;
    struct admin_info admins[MAX_ADMINS_NUM];
    int num_admins = 0;

    // ���ļ��ж�ȡ����Ա��Ϣ��ѧ����Ϣ
    load_admins_from_file(admins, &num_admins);
    load_students_from_file(students, &num_students);

    // ��ʾ��½ҳ��
    show_login_page();

    // ��������ѧ����Ϣ�͹���Ա��Ϣ���ļ���
    save_admins_to_file(admins, num_admins);
    save_students_to_file(students, num_students);

    return 0;
}

// ���ļ��ж�ȡ����Ա��Ϣ
void load_admins_from_file(struct admin_info admins[], int* num_admins_ptr) {
    // TODO: ���ļ��ж�ȡ����Ա��Ϣ���洢��admins�����У���������Ա�����洢��num_admins_ptrָ��ָ��ı�����
    int cnt = 0;
    FILE* fp1;
    fopen_s(&fp1, "admins_data.txt", "r+");
    if (fp1 == NULL) {//�����ļ�ʧ�����˳�
        puts("fp1���ܴ��ļ���");
        return;
    }

    for (int i = 0; !feof(fp1); i++) {
        fscanf(fp1, "%s %s", admins[i].username, admins[i].password);
        cnt++;
    }
    fclose(fp1); //�ر��ļ�
    *num_admins_ptr = cnt;

    return;
}

// ���ļ��ж�ȡѧ����Ϣ
void load_students_from_file(struct student_info students[], int* num_students_ptr) {
    // TODO: ���ļ��ж�ȡѧ����Ϣ���洢��students�����У�����ѧ�������洢��num_students_ptrָ��ָ��ı�����
    int cnt = 0;
    FILE* fp2;
    fopen_s(&fp2, "students_data.txt", "r+");
    if (fp2 == NULL) {      //�����ļ�ʧ�����˳�
        puts("fp2���ܴ��ļ���");
        return;
    }

    for (int i = 0; !feof(fp2); i++) {
        fscanf(fp2, "%s %d %s %s %d %s %s",
            students[i].name, students[i].age, students[i].gender, students[i].group,
            students[i].xuehao, students[i].username, students[i].password);
        cnt++;
    }
    fclose(fp2); //�ر��ļ�
    *num_students_ptr = cnt;

    return;
}

// �����й���Ա��Ϣ���浽�ļ���
void save_admins_to_file(const struct admin_info admins[], const int num_admins) {
    // TODO: �����й���Ա��Ϣ���浽�ļ���
    FILE* fp3;
    fopen_s(&fp3, "admins_data.txt", "wt+");    //���ļ�
    if (fp3 == NULL) {//�����ļ�ʧ�����˳�
        puts("fp3���ܴ��ļ���");
        return;
    }

    for (int i = 0; i < num_admins; i++)            //��num_admins����Ϣ�洢��ȥ
    {
        fprintf(fp3, "%s %s\n", admins[i].username, admins[i].password);
    }

    fclose(fp3); //�ر��ļ�
    return;
}

// ������ѧ����Ϣ���浽�ļ���
void save_students_to_file(const struct student_info students[], const int num_students) {

    FILE* fp;
    fp = fopen("D:\\ѧ��С��.txt", "w");  // ��ֻд�ķ�ʽ���ļ�
    if (fp == NULL) {
        printf("Failed to open file.\n");//���ļ������ڣ��������Ϣ���������ļ�
        return;
    }
    for (int i = 0; i < num_students; i++) {
        fprintf(fp, "%s %d %s %s\n", students[i].name, students[i].age, students[i].gender, students[i].group);  // д�����ݵ��ļ�
    }//���ļ���������գ�����ÿ��ѧ������Ϣ
    fclose(fp);  // �ر��ļ�
    return;
}

// ��ʾ��½ҳ��
void show_login_page() {
    // TODO: ��ʾ��½ҳ�棬�����û�ѡ�����student_login()��admin_login()

    int x = 0, i = 0;
    system("cls");
    printf("===========\n");
    printf("1.����Ա��¼\n");
    printf("2.ѧԱ��¼\n");
    printf("===========\n");
    printf("��ѡ�������ݣ�����1��2����");
    scanf("%d", &x);
    if (x == 1) {
        admin_login();

    }
    if (x == 2) {
        student_login();
    }
    else {
        printf("�������");
        system("pause");
        show_login_page();
    }
}

// ��֤ѧԱ�˺ź��������ȷ�ԣ������ؽ��
int student_login(const struct student_info students[], const int num_students) {

    int flag = 0, i = 0, j = 0, zh = 0, mm = 0;
    while (1) {
        system("cls");
        printf("�˺�:");
        scanf("%c", &zh);

        for (i = 0; i < 1000; i++) {
            if (zh == x[i].zh) {
                flag = 1;//flag==1��ʾ�ҵ���Ӧ���˻�
                break;
            }
            else if (i == 999) {
                printf("δ�ҵ���Ӧ�Ĺ���Ա�˺š�\n");
                system("pause");

            }

        }
    }
    if (flag == 1) {
        printf("\n");
        while (flag != 2) {
            system("cls");
            printf("�˺�:%d\n", x[i].zh);
            printf("����:");
            scanf("%d", &mm);
            if (x[i].mm == mm) {
                flag = 2;
                break;
            }
            else {
                printf("���벻��ȷ������������");
                system("pause");
            }
        }

        // TODO: ʵ��ѧԱ��¼��֤���ܣ�����ֵΪint���ͣ��ɹ�����1��ʧ�ܷ���0
    }

    // ��֤�����˺ź��������ȷ�ԣ������ؽ��
    int admin_login(const struct admin_info admins[], const int num_admins) {

        // TODO: ʵ�ֹ����¼��֤���ܣ�����ֵΪint���ͣ��ɹ�����1��ʧ�ܷ���0
        int flag = 0, i = 0, j = 0, zh = 0, mm = 0;
        while (flag != 1) {
            system("cls");
            printf("����0������һ����\n");
            printf("�˺�:");

            scanf("%d", &zh);
            if (zh == 0) {
                show_login_page();
            }
            for (i = 0; i < 1000; i++) {
                if (zh == g[i].zh) {
                    flag = 1;//flag==1��ʾ�ҵ���Ӧ���˻�
                    break;
                }
                else if (i == 999) {
                    printf("δ�ҵ���Ӧ�Ĺ���Ա�˺š�\n");
                    system("pause");
                }
            }

        }


        if (flag == 1) {
            printf("\n");
            while (flag != 2) {
                system("cls");
                printf("���� 0 ���������˺�\n");
                printf("�˺ţ�%d\n", g[i].zh);
                printf("����:");
                scanf("%d", &mm);
                if (mm == 0) {
                    admin_login();
                }
                if (g[i].mm == mm) {
                    flag = 2;
                    break;
                }
                else {
                    printf("���벻��ȷ������������");
                    system("pause");
                }
            }
        }
        if (flag == 2) {

        }
    }

    // ��ʾѧԱ������Ϣ����
    void show_student_info_page(const struct student_info students[], const int num_students, const int index) {
        // TODO: ��ʾѧԱ������Ϣ���棬�����û�ѡ�����show_student_page()��write_leave()��export_attendance_record()�Ⱥ���
        int i;
        do {
            printf("1.�鿴ѧԱ��ϸ��Ϣ\n");
            printf("2.�����ټ�¼\n");
            printf("3.�������ڼ�¼\n");
            printf("��ѡ��Ҫ���еĲ���:");
            scanf("%d", &i);
            if (i == 1)
                show_student_page();
            else if (i == 2)
                write_leave();
            else if (i == 3)
                export_attendance_record();
            else
                printf("�ò��������ڣ�����������");
        } while (i <= 3);
    }

    // ��ʾĳ��ѧԱ����ϸ��Ϣ
    void show_student_page(const struct student_info students[], const int num_students, const int index) {
        // TODO: ��ʾĳ��ѧԱ����ϸ��Ϣ���������������䡢�Ա��������ȵ�
        printf("��ѡ����Ҫ�鿴��ѧԱ��Ϣ");
        int i;//����ѧ�ű���

        scanf("%d", &i);
        if (i <= num_students && i > 0)
        {
            printf("ѧ�ţ�%d\n", students[i].xuehao);
            printf("������%s\n", students[i].name);
            printf("���䣺%d\n", students[i].age);
            printf("�Ա�%s\n", students[i].gender);
            printf("С�飺%s\n", students[i].group);
        }
        else
            printf("��ͬѧ������,����������");
    }

    // ���һ��ѧԱ
    void add_student(struct student_info students[], int* num_students_ptr) {
        // TODO: ���һ��ѧԱ���������������䡢�Ա�����������Ϣ
        if (*num_students_ptr > MAX_STUDENTS_NUM) {
            printf("�������ѧ����");
            return;
        }
        struct student_info new_student;
        printf("��������ѧ����������");
        scanf("%s", new_student.name);
        printf("��������ѧ�������䣺");
        scanf("%d", new_student.age);
        printf("��������ѧ�����Ա�");
        scanf("%s", new_student.gender);
        printf("��������ѧ�����������");
        scanf("%s", new_student.group);
        printf("��������ѧ����ѧ�ţ�");
        scanf("%s", new_student.xuehao);

        for (int i = 0; i < *num_students_ptr; i++) {
            if (students[i].xuehao == new_student.xuehao) {//����ѧ���Ƿ����
                printf("ѧ���Ѿ�����");
                return;
            }
        }
        students[*num_students_ptr] = new_student;//���ѧ��
        (*num_students_ptr)++;

        for (int i = 0; i < *num_students_ptr; i++)
            for (int j = i + 1; j < *num_students_ptr; j++) {//����ѧ������
                struct student_info temp = students[i];
                if (students[i].xuehao > students[j].xuehao) {
                    students[i] = students[j];
                    students[j] = temp;
                }

            }
        return;
    }

    // ɾ��һ��ѧԱ
    void delete_student(struct student_info students[], int* num_students_ptr) {
        // TODO: ɾ��һ��ѧԱ���ɸ���ѧԱ������������ʶ�����Ҳ�ɾ��
        int  xuehao_to_delete, index_to_delete = -1;//Ҫɾ����ѧ�ź��±��ʼ��Ϊ-1

        printf("������Ҫɾ����ѧ����ѧ�ţ�");
        for (int i = 0; i < *num_students_ptr; i++) {

            if ((int)students[i].xuehao == xuehao_to_delete) {
                index_to_delete = i;
                break;
            }
        }
        if (index_to_delete == -1) {
            printf("δ�ҵ�ѧ��Ϊ%d��ѧ��", xuehao_to_delete);
            return;
        }
        for (int i = xuehao_to_delete; i < *num_students_ptr - 1; i++) {
            students[i] = students[i + 1];
        }
        *num_students_ptr--;
        for (int i = 0; i < *num_students_ptr; i++)
            for (int j = i + 1; j < *num_students_ptr; j++) {//����ѧ������
                struct student_info temp = students[i];
                if (students[i].xuehao > students[j].xuehao) {
                    students[i] = students[j];
                    students[j] = temp;
                }

            }
        printf("ѧ��Ϊ%d��ѧ����ɾ��", xuehao_to_delete);
        return;
    }

    // ����ѧԱ
    void search_student(const struct student_info students[], const int num_students, const char search_criteria[]) {
        // TODO: ��������Ĳ���������ѧ����Ϣ�б��в���ѧԱ������������Ϣ
        int found = 0, tiaojian = 0;//�������
        printf("��ѡ�����������\n");
        printf("����1��ѧ�Ų���\n");
        printf("����2����������\n");
        printf("����3���Ա����\n");
        printf("����4��������\n");
        scanf("%d", &tiaojian);
        while (1) {
            if (tiaojian != 1 && tiaojian != 2 && tiaojian != 3 && tiaojian != 4) {
                printf("�������������ԣ�\n");
                scanf("%d", &tiaojian);
            }
            else {
                break;
            }
        }
        printf("������Ҫ���ҵ����ݣ�\n");
        char search_text[20];
        scanf("%s", search_text);
        printf("����������ѧ����Ϣ���£�\n");
        printf("ѧ��\t����\t����\t�Ա�\t���\n");
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
            printf("δ�ҵ�����������ѧ����Ϣ��\n");
        }
    }

    // ���ĳС���ѧԱ��Ϣ
    void output_group_students_info(const struct student_info students[], const int num_students, const char group_name[]) {
        // TODO: ���ĳС���ѧԱ��Ϣ���������������䡢�Ա��
        int i;
        int found = 0; // ����Ƿ��ҵ�����������ѧ����¼

        // �����ͷ
        printf("����\t����\t�Ա�\tС��\n");

        // ����ѧ����Ϣ�ṹ������
        for (i = 0; i < num_students; i++) {
            // ������������ָ���������һ�£������ѧ����Ϣ
            if (strcmp(students[i].group, group_name) == 0) {
                printf("%s\t%d\t%c\t%s\n", students[i].name, students[i].age, students[i].gender, students[i].group);
                found = 1; // ������ҵ�����������ѧ����¼
            }
        }

        // ���δ�ҵ�����������ѧ����¼���������Ӧ�Ĵ�����ʾ
        if (!found) {
            printf("δ�ҵ����Ϊ%s��ѧ����¼\n", group_name);
        }
    }

    // ��������ѧ����Ϣ���ļ���
    void save_student_info_to_file(const struct student_info students[], const int num_students, const char filename[]) {
        // TODO: ��ָ����ѧ����Ϣ���浽ָ�����ļ��У���ʹ���ļ�I/O��غ���ʵ��
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

    // �������ѧԱ�Ĵ���Ϣ
    void output_all_students_attendance(const struct student_info students[], const int num_students) {
        // TODO: �������ѧԱ�Ĵ���Ϣ����������״̬�����ڡ��ٵ�����Σ��Ϳ��δ�������Ϣ
    }

    // �������ȱ����Ա��Ϣ
    void output_absent_students_info(const struct student_info students[], const int num_students) {
        // TODO: �������ȱ����Ա��Ϣ�������������������ȱ��ԭ�����Ϣ
    }

    // �����ټ�¼
    void write_leave(struct student_info students[], const int index) {
        // TODO: �����û����������ټ�¼������ѧ����Ϣ����Ӧ�ر�ע��ѧ�������
    }

    // ����ĳѧԱ�Ĵ򿨼�¼
    void export_attendance_record(const struct student_info students[], const int index) {
        // TODO: ����ĳѧԱ�Ĵ򿨼�¼���Ա�ѧԱ���ҳ�������ʦ�鿴
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

    // ��ʾ����Ա����
    void show_admin_page(struct student_info students[], const int num_students, struct admin_info admins[], const int num_admins) {
        // TODO: ��ʾ����Ա���棬�������ֲ���ѡ��Ͳ˵��������û�ѡ�������Ӧ����
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




    void manage_record(struct student_info students[], const int num_students��const int index) {
        int record_type;
        printf("��ѡ����Ҫ���еĲ�����\n1. ��ѯ��ټ�¼\n2. ������ټ�¼\n3. ��ѯȱ�ڼ�¼\n4. ����ȱ�ڼ�¼\n5. ��ѯ�ͷ���¼\n6. ����ͷ���¼\n");
        scanf("%d", &record_type);

        switch (record_type) {
        case 1:
            printf("������ѧԱ������");
            char name[20];
            scanf("%s", name);
            int flag = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].name, name) == 0)
                {
                    printf("��ѧԱ��ټ�¼���£�\n");
                    for (int i = 0; i < students[index].leave_num; i++) {
                        printf("��%d����٣����ڣ�%s��ԭ��%s\n", i + 1, students[index].leave_dates[i], students[index].leave_reasons[i]);
                    }
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                printf("δ�ҵ���ѧԱ�����������롣\n");
            }
            break;
        case 2:
            printf("������ѧԱ������");
            char name2[20];
            scanf("%s", name2);
            int flag2 = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].name, name2) == 0) {
                    if (students[i].leave_num >= 3) { //���Ӷ�ѧ����ٴ������ж�
                        printf("��ѧԱ�Ѵﵽ�����ٴ����������ٴ���٣�\n");
                    }
                    else {
                        printf("������������ڣ�");
                        scanf("%s", students[index].leave_dates[students[index].leave_num]);
                        printf("���������ԭ��");
                        scanf("%s", students[index].leave_reasons[students[index].leave_num]);
                        students[index].leave_num++;
                        printf("������������ͨ����\n");
                    }
                    flag2 = 1;
                    break;
                }
            }
            if (flag2 == 0) {
                printf("δ�ҵ���ѧԱ�����������롣\n");
            }
            break;
        case 3:
            printf("������ѧԱ������");
            char name3[20];
            scanf("%s", name3);
            int flag3 = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].name, name3) == 0) {
                    printf("��ѧԱȱ�ڼ�¼���£�\n");
                    for (int i = 0; i < students[index].absence_num; i++) {
                        printf("��%d��ȱ�ڣ����ڣ�%s��ԭ��%s\n", i + 1, students[index].absence_dates[i], students[index].absence_reasons[i]);
                    }
                    flag3 = 1;
                    break;
                }
            }
            if (flag3 == 0) {
                printf("δ�ҵ���ѧԱ�����������롣\n");
            }
            break;
        case 4:
            printf("������ѧԱ������");
            char name4[20];
            scanf("%s", name4);
            int flag4 = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].name, name4) == 0) {


                    int choice;
                    printf("��ѡ����Ҫ���еĲ�����\n1. ���ȱ�ڼ�¼\n2. �޸�ȱ�ڼ�¼\n3. ɾ��ȱ�ڼ�¼\n");
                    scanf("%d", &choice);

                    switch (choice) {
                    case 1:
                        if (students[index].absence_num < MAX_ABSENCE_NUM) {
                            printf("������ȱ�����ڣ�");
                            scanf("%s", students[index].absence_dates[students[index].absence_num]);
                            printf("������ȱ��ԭ��");
                            scanf("%s", students[index].absence_reasons[students[index].absence_num]);
                            students[index].absence_num++;
                            printf("��ӳɹ���\n");
                        }
                        else {
                            printf("ȱ�ڼ�¼�������޷���Ӹ����¼��\n");
                        }
                        break;
                    case 2:
                        printf("������Ҫ�޸ĵ�ȱ�ڼ�¼��ţ�1-%d����", students[index].absence_num);
                        int modify_index;
                        scanf("%d", &modify_index);
                        if (modify_index >= 1 && modify_index <= students[index].absence_num) {
                            printf("�������µ�ȱ�����ڣ�");
                            scanf("%s", students[index].absence_dates[modify_index - 1]);
                            printf("�������µ�ȱ��ԭ��");
                            scanf("%s", students[index].absence_reasons[modify_index - 1]);
                            printf("�޸ĳɹ���\n");
                        }
                        else {
                            printf("��Ч��ȱ�ڼ�¼��ţ�\n");
                        }
                        break;
                    case 3:
                        printf("������Ҫɾ����ȱ�ڼ�¼��ţ�1-%d����", students[index].absence_num);
                        int delete_index;
                        scanf("%d", &delete_index);
                        if (delete_index >= 1 && delete_index <= students[index].absence_num) {
                            for (int i = delete_index - 1; i < students[index].absence_num - 1; i++) {
                                strcpy(students[index].absence_dates[i], students[index].absence_dates[i + 1]);
                                strcpy(students[index].absence_reasons[i], students[index].absence_reasons[i + 1]);
                            }
                            students[index].absence_num--;
                            printf("ɾ���ɹ���\n");
                        }
                        else {
                            printf("��Ч��ȱ�ڼ�¼��ţ�\n");
                        }
                        break;
                    default:
                        printf("�����������������롣\n");
                        break;
                    }


                    flag4 = 1;
                    break;
                }
            }
            if (flag4 == 0) {
                printf("δ�ҵ���ѧԱ�����������롣\n");
            }
            break;
        case 5:
            printf("������ѧԱ������");
            char name5[20];
            scanf("%s", name5);
            int flag5 = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].name, name5) == 0) {
                    printf("��ѧԱ�ͷ���¼���£�\n");
                    for (int i = 0; i < students[index].punishment_num; i++) {
                        printf("��%d�γͷ������ڣ�%s����Ϊ��%s\n", i + 1, students[index].punishment_dates[i], students[index].punishment_behaviors[i]);
                    }
                    flag5 = 1;
                    break;
                }
            }
            if (flag5 == 0) {
                printf("δ�ҵ���ѧԱ�����������롣\n");
            }
            break;
        case 6:
            printf("������ѧԱ������");
            char name6[20];
            scanf("%s", name6);
            int flag6 = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].name, name6) == 0) {

                    int choice;
                    printf("��ѡ����Ҫ���еĲ�����\n1. ��ӳͷ���¼\n2. �޸ĳͷ���¼\n3. ɾ���ͷ���¼\n");
                    scanf("%d", &choice);

                    switch (choice) {
                    case 1:
                        if (students[index].punishment_num < MAX_PUNISHMENT_NUM) {
                            printf("������ͷ����ڣ�");
                            scanf("%s", students[index].punishment_dates[students[index].punishment_num]);
                            printf("������ͷ���Ϊ��");
                            scanf("%s", students[index].punishment_behaviors[students[index].punishment_num]);
                            students[index].punishment_num++;
                            printf("��ӳɹ���\n");
                        }
                        else {
                            printf("�ͷ���¼�������޷���Ӹ����¼��\n");
                        }
                        break;
                    case 2:
                        printf("������Ҫ�޸ĵĳͷ���¼��ţ�1-%d����", students[index].punishment_num);
                        int modify_index;
                        scanf("%d", &modify_index);
                        if (modify_index >= 1 && modify_index <= students[index].punishment_num) {
                            printf("�������µĳͷ����ڣ�");
                            scanf("%s", students[index].punishment_dates[modify_index - 1]);
                            printf("�������µĳͷ���Ϊ��");
                            scanf("%s", students[index].punishment_behaviors[modify_index - 1]);
                            printf("�޸ĳɹ���\n");
                        }
                        else {
                            printf("��Ч�ĳͷ���¼��ţ�\n");
                        }
                        break;
                    case 3:
                        printf("������Ҫɾ���ĳͷ���¼��ţ�1-%d����", students[index].punishment_num);
                        int delete_index;
                        scanf("%d", &delete_index);
                        if (delete_index >= 1 && delete_index <= students[index].punishment_num) {
                            for (int i = delete_index - 1; i < students[index].punishment_num - 1; i++) {
                                strcpy(students[index].punishment_dates[i], students[index].punishment_dates[i + 1]);
                                strcpy(students[index].punishment_behaviors[i], students[index].punishment_behaviors[i + 1]);
                            }
                            students[index].punishment_num--;
                            printf("ɾ���ɹ���\n");
                        }
                        else {
                            printf("��Ч�ĳͷ���¼��ţ�\n");
                        }
                        break;
                    default:
                        printf("�����������������롣\n");
                        break;
                    }

                    flag6 = 1;
                    break;
                }
            }
            if (flag6 == 0) {
                printf("δ�ҵ���ѧԱ�����������롣\n");
            }
            break);
        default:
            printf("�����������������롣\n");
            break;
        }
    }



