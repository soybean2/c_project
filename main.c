#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 200 // ���ѧ����
#define MAX_NAME 20 //�������
#define MAX_SEX 5 //����Ա�
#define MAX_SNO 20 //���ѧ��
#define MAX_TELE 15  //���绰����
#define MAX_ADDR 50 //����ַ
#define MAX_USERS 100   // ����û���
#define MAX_NAME_LEN 20 // �û�����󳤶�
#define MAX_PASS_LEN 20 // ������󳤶�

// ����ѧ���ṹ��
struct Student {
    char name[MAX_NAME];
    char gender[MAX_SEX];
    char id[MAX_SNO];
    int age;
    char birthday[20];
    char phone[MAX_TELE];
    char address[MAX_ADDR];
};

struct user {
    char name[MAX_NAME_LEN];
    char pass[MAX_PASS_LEN];
    struct Student students[MAX_STUDENTS];
    int studentCount;
};
struct user users[MAX_USERS]; // �û��б�
int num_users = 0;            // �û���Ŀ


void printStudentInfo(int index);



//����Ա�˺�
//char adminUsername[20] = "admin";
//char adminPassword[20] = "123456";

char isLogin = 0; //�Ƿ��Ѿ���¼
char current_user = -1; //��ǰ��¼���û�

//�û���¼
void loginUser();

//�û�ע��
void register_user();

// ���ļ��ж�ȡ�û���Ϣ
void read_users();

//���û���Ϣд���ļ���
void write_users();

//���浽�ļ�
void saveToFile();

//���ļ��м���
void initSystem();

// ���ѧ��
void addStudent();

// ����ѧ��
void findStudent();

// ��ʾ����ѧ����Ϣ
void showAllStudents();

// ɾ��ѧ����Ϣ
void deleteStudent();

//ģ������
void fuzzyFind();

//��ʾ����ѧ����Ϣ
void printStudentInfo(int index);

//����
void sortStudent();

//�޸�ѧ����Ϣ
void editStudent();

//�ַ���ת��Ϊ����
int stringToInt(char* str);

//�жϳ��������Ƿ���ȷ
int checkBirthday(char* birthday);

//�˵���
void menu();




// ������
int main() {
    read_users(); // ��������ʱ���ļ��ж�ȡ�û���Ϣ
    int choice;
    do {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(); // ���ѧ��
                system("pause");
                system("cls");
                break;
            case 2:
                findStudent(); // ����ѧ��
                system("pause");
                system("cls");
                break;
            case 3:
                showAllStudents(); // ��ʾ����ѧ����Ϣ
                system("pause");
                system("cls");
                break;
            case 4:
                deleteStudent();//ɾ��ѧ����Ϣ
                system("pause");
                system("cls");
                break;
            case 5:
                fuzzyFind();//ģ������
                system("pause");
                system("cls");
                break;
            case 6:
                sortStudent();//����ѧ����Ϣ
                system("pause");
                system("cls");
                break;
            case 7:
                editStudent();//�޸�ѧ����Ϣ
                system("pause");
                system("cls");
                break;
            case 8:
                register_user();//�û�ע��
                system("pause");
                system("cls");
                break;
            case 9:
                loginUser();//�û���¼
                system("pause");
                system("cls");
                break;
            case 10:
                if (isLogin == 1) {
                    printf("�û��ѵǳ�\n");
                    isLogin = 0;
                    current_user = -1;
                }
                else {
                    printf("���ȵ�¼�˺š�\n");
                }
                system("pause");
                system("cls");
                break;
            case 0:
                printf("�������˳���\n");
                saveToFile(); // ���浽�ļ�
                break;
            default:
                printf("��������������ѡ��\n");
                break;
        }
    } while (choice != 0);

    return 0;

}

void loginUser() {
    if (isLogin == 1) {
        printf("���Ѿ���¼��\n");
        return;
    }
    if(num_users == 0) {
        printf("��ǰû���û�������ע�ᣡ\n");
        return;
    }
    char name[MAX_NAME_LEN];
    char pass[MAX_PASS_LEN];

    printf("�����������û�����");
    scanf("%s", name);

    printf("�������������룺");
    scanf("%s", pass);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(name, users[i].name) == 0 && strcmp(pass, users[i].pass) == 0) {
            current_user = i;
            printf("��¼�ɹ���\n");
            isLogin = 1;
            //��ȡ�ļ�
            initSystem();
            printf("��ǰ��¼�û�Ϊ��%s\n", users[current_user].name);
            printf("��ǰ�û�ͨѶ¼ѧ������%d\n", users[current_user].studentCount);
            return;
        }
    }
    printf("�û������������!\n");
}
void menu() {

    printf("**************ѧ��ͨѶ¼����ϵͳ*****************\n");
    printf("*************************************************\n");
    printf("********1.���ѧ��          2. ����ѧ��**********\n");
    printf("********3.��ʾ����ѧ����Ϣ  4. ɾ��ѧ����Ϣ******\n");
    printf("********5.ģ������          6. ����ѧ����Ϣ******\n");
    printf("********7.�޸�ѧ����Ϣ      8. �û�ע��**********\n");
    printf("********9.�û���¼          10. �û��ǳ�*********\n");
    printf("**************  0.�˳�ϵͳ  *********************\n");
    printf("*************************************************\n");
    printf("��ѡ��Ҫִ�еĲ�����\n");
}

// ע�����û�
void register_user() {
    if (num_users == MAX_USERS) {
        printf("�û�����������ע��\n");
        return;
    }
    printf("�����������û�����");
    char name[MAX_NAME_LEN];
    scanf("%s", name);
    //�ж��û����Ƿ��ظ�
    for (int i = 0; i < num_users; i++) {
        if (strcmp(name, users[i].name) == 0) {
            printf("�û����Ѵ���,���������룡\n");
            do {
                scanf("%s", name);
                if (strcmp(name, users[i].name) == 0) {
                    printf("�û����Ѵ���,���������룡\n");
                }else{
                    break;
                }
            } while (strcmp(name, users[i].name) == 0);
        }
    }
    strcpy(users[num_users].name, name);
    printf("�������������룺");
    scanf("%s", users[num_users].pass);
    num_users++;
    printf("ע��ɹ���\n");
    printf("��ǰ�û�����%d\n", num_users);
    write_users(); // ���û���Ϣд���ļ�
}


// ���ļ��ж�ȡ�û���Ϣ
void read_users() {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
//        printf("�ļ���ʧ�ܣ�\n");
        return;
    }

    while (fscanf(fp, "%s %s", users[num_users].name, users[num_users].pass) == 2) {
        num_users++;
    }
    fclose(fp);
}


// ���û���Ϣд���ļ�
void write_users() {
    FILE *fp = fopen("users.txt", "w");
    if (fp == NULL) {
//        printf("�ļ���ʧ��\n");
        return;
    }
    int i;
    for (i = 0; i < num_users; i++) {
        fprintf(fp, "%s %s\n", users[i].name, users[i].pass);
    }
    fclose(fp);
}

//���浽�ļ�
void saveToFile() {
    FILE* fp;
    //�ļ���=contactor_+��ǰ�û����û���.txt
    char filename[100];
    strcpy(filename, "contactor_");
    strcat(filename, users[current_user].name);
    strcat(filename, ".txt");

    fp = fopen(filename, "w"); // ���ļ��������������½�

    fprintf(fp, "%d\n", users[current_user].studentCount); // ��д��ѧ������
    for (int i = 0; i < users[current_user].studentCount; i++) {
        fprintf(fp, "%s %s %s %d %s %s %s\n",
                users[current_user].students[i].name, users[current_user].students[i].gender, users[current_user].students[i].id, users[current_user].students[i].age,
                users[current_user].students[i].birthday, users[current_user].students[i].phone, users[current_user].students[i].address);
    }

    fclose(fp); // �ر��ļ�
}

//���ļ��м��ص�ǰ�û�ͨѶ¼��Ϣ
void initSystem() {
    FILE* fp;
    //�ļ���=contactor_+��ǰ�û����û���.txt
    char filename[100];
    strcpy(filename, "contactor_");
    strcat(filename, users[current_user].name);
    strcat(filename, ".txt");

    fp = fopen(filename, "r"); // ���ļ�

    if (fp == NULL) { // ����ļ������ڣ��򲻽��ж�ȡ����
        return;
    }

    fscanf(fp, "%d", &users[current_user].studentCount); // ����ѧ������
    for (int i = 0; i < users[current_user].studentCount; i++) {
        fscanf(fp, "%s %s %s %d %s %s %s",
               users[current_user].students[i].name, &users[current_user].students[i].gender, &users[current_user].students[i].id, &users[current_user].students[i].age,
               users[current_user].students[i].birthday, users[current_user].students[i].phone, users[current_user].students[i].address);
    }

    fclose(fp); // �ر��ļ�
}

// ���ѧ��
void addStudent() {

    if (!isLogin) {
        printf("��δ��¼���޷����ѧ����Ϣ\n");
        return;
    }
    if (users[current_user].studentCount >= MAX_STUDENTS) {
        printf("ѧ�����������޷�����µ�ѧ����\n");
        return;
    }
    printf("**************�����ϵ��*****************\n");
    struct Student student;
    printf("������ѧ��������");
    scanf("%s", student.name);
    printf("������ѧ���Ա�");
    scanf("%s", student.gender);
    printf("������ѧ��ѧ�ţ�");
    char id[20];
    scanf("%s", id);
    // �ж�ѧ���Ƿ��ظ�
    for (int i = 0; i < users[current_user].studentCount; i++) {
        if (strcmp(users[current_user].students[i].id, id) == 0) {
            do {
                printf("ѧ���ظ�������������:");
                scanf("%s", id);
            } while (strcmp(users[current_user].students[i].id, id) == 0);
        }
    }
    strcpy(student.id, id);

    printf("������ѧ�����䣺");
    int age;
    scanf("%d", &age);
    //�ж������Ƿ���ȷ
    while (age < 0 || age > 100) {
        printf("�����������������:");
        scanf("%d", &age);
    }
    student.age = age;

    printf("������ѧ����������(��2000-01-01):");
    char birthday[20];
    scanf("%s", birthday);
    //�ж����ڸ�ʽ�Ƿ���ȷ
    while (strlen(birthday) != 10 || !checkBirthday(birthday)) {
        printf("�����������������:");
        scanf("%s", birthday);
    }

    strcpy(student.birthday, birthday);

    printf("������绰����(11λ�绰����)��");
    char phone[20];
    scanf("%s", phone);
    //�жϵ绰�����ʽ�Ƿ���ȷ
    while (strlen(phone) != 11) {
        printf("�����������������");
        scanf("%s", phone);
    }
    strcpy(student.phone, phone);
    printf("������ѧ����ַ��");
    scanf("%s", student.address);

    users[current_user].students[users[current_user].studentCount] = student;
    users[current_user].studentCount++;

    printf("��ӳɹ���\n");
    saveToFile(); // �����ɺ󱣴浽�ļ�
}

// ����ѧ��
void findStudent() {
    if (!isLogin) {
        printf("��δ��¼���޷��鿴ѧ����Ϣ\n");
        return;
    }
    printf("**********************������ϵ��*************************\n");
    if(users[current_user].studentCount == 0){
        printf("��ǰ��ѧ����Ϣ\n");
        return;
    }
    char name[20];
    printf("������Ҫ���ҵ�ѧ��������");
    scanf("%s", name);
    int i;
    for (i = 0; i < users[current_user].studentCount; i++) {
        if (strcmp(name, users[current_user].students[i].name) == 0) {
            printf("������%s���Ա�%s��ѧ�ţ�%s�����䣺%d���������ڣ�%s���绰��%s����ַ��%s\n", users[current_user].students[i].name,
                   users[current_user].students[i].gender, users[current_user].students[i].id, users[current_user].students[i].age, users[current_user].students[i].birthday, users[current_user].students[i].phone,
                   users[current_user].students[i].address);
            return;
        }
    }

    printf("δ�ҵ���Ϊ%s��ѧ����\n", name);
}

// ��ʾ����ѧ����Ϣ
void showAllStudents() {
    if (!isLogin) {
        printf("��δ��¼���޷��鿴ѧ����Ϣ\n");
        return;
    }
    printf("*******************************��ʾ����ѧ����Ϣ********************************** \n");
    if(users[current_user].studentCount == 0){
        printf("��ǰ��ѧ����Ϣ\n");
        return;
    }
    int i;
    printf("����\t�Ա�\tѧ��\t\t����\t��������\t�绰\t\t��ַ\n");
    for (i = 0; i < users[current_user].studentCount; i++) {
        printf("%-6s\t%-5s\t%-8s\t%d\t%-10s\t%-10s\t%-10s\n", users[current_user].students[i].name, users[current_user].students[i].gender,
               users[current_user].students[i].id, users[current_user].students[i].age, users[current_user].students[i].birthday, users[current_user].students[i].phone, users[current_user].students[i].address);
    }
    printf("********************************************************************************* \n");
}

// ɾ��ѧ����Ϣ
void deleteStudent() {

    if (!isLogin) {
        printf("��δ��¼���޷�ɾ��ѧ����Ϣ\n");
        return;
    }
    if (users[current_user].studentCount == 0) {
        printf("ѧ������Ϊ0���޷�ɾ��ѧ����Ϣ��\n");
        return;
    }
    printf("**********************ɾ����ϵ��*************************\n");
    int i;
    printf("���\t����\t�Ա�\tѧ��\t\t����\t��������\t�绰\t\t��ַ\n");
    for (i = 0; i < users[current_user].studentCount; i++) {
        printf("%d\t%-6s\t%-5s\t%-8s\t%d\t%-10s\t%-10s\t%-10s\n", i, users[current_user].students[i].name, users[current_user].students[i].gender,
               users[current_user].students[i].id, users[current_user].students[i].age, users[current_user].students[i].birthday, users[current_user].students[i].phone, users[current_user].students[i].address);
    }
    printf("������Ҫɾ��ѧ������ţ�");
    scanf("%d", &i);
    do {
        if (i < 0 || i >= users[current_user].studentCount) {
            printf("�����������������\n");
            scanf("%d", &i);
        }
    } while (i < 0 || i >= users[current_user].studentCount);
    printf("ȷ��ɾ��ѧ��%s��(y/n)", users[current_user].students[i].name);
    char c;
    scanf(" %c", &c);
    if (c == 'n') {
        printf("ȡ��ɾ����\n");
        return;
    }
    for (int j = i; j < users[current_user].studentCount - 1; j++) {
        users[current_user].students[j] = users[current_user].students[j + 1];
    }
    users[current_user].studentCount--;
    printf("ɾ���ɹ���\n");
    saveToFile(); // ɾ����ɺ󱣴浽�ļ�
}

//ģ������
void fuzzyFind() {
    if (!isLogin) {
        printf("��δ��¼���޷�����ѧ����Ϣ\n");
        return;
    }
    if (users[current_user].studentCount == 0) {
        printf("ѧ��ͨѶ¼Ϊ��\n");
        return;
    }
    printf("**********************ģ������*************************\n");
    char keyword[20];
    printf("������Ҫ���ҵĹؼ��֣�");
    scanf("%s", keyword);

    int count = 0;
    for (int i = 0; i < users[current_user].studentCount; i++) {
        if (strstr(users[current_user].students[i].name, keyword) != NULL || strstr(users[current_user].students[i].id, keyword) != NULL ||
            strstr(users[current_user].students[i].phone, keyword) != NULL || strstr(users[current_user].students[i].address, keyword) != NULL ||
            strstr(users[current_user].students[i].birthday, keyword) != NULL) {
            printStudentInfo(i);
            count++;
        }
        if (users[current_user].students[i].age == stringToInt(keyword)) {
            printStudentInfo(i);
            count++;
        }
    }

    if (count == 0) {
        printf("û���ҵ�ƥ���ѧ����Ϣ\n");
    }
    else {
        printf("���ҵ�%d��ƥ���ѧ����Ϣ\n", count);
    }
}

//��ӡ����ѧ����Ϣ
void printStudentInfo(int index) {
    int i;
    for (i = 0; i < users[current_user].studentCount; i++) {
        if (i == index) {
            printf("������%s���Ա�%s��ѧ�ţ�%s�����䣺%d���������ڣ�%s���绰��%s����ַ��%s\n", users[current_user].students[i].name,
                   users[current_user].students[i].gender, users[current_user].students[i].id, users[current_user].students[i].age, users[current_user].students[i].birthday, users[current_user].students[i].phone,
                   users[current_user].students[i].address);
        }
    }
}

//����
void sortStudent() {
    if (!isLogin) {
        printf("��δ��¼���޷���ѧ����Ϣ��������\n");
        return;
    }
    //���ͨѶ¼Ϊ�գ��޷�����
    if (users[current_user].studentCount == 0) {
        printf("ѧ������Ϊ0���޷�����\n");
        return;
    }
    printf("**********************��ϵ������*************************\n");
    int i, j;
    struct Student temp;
    printf("����������ķ�ʽ\n");
    printf("1.����������\n");
    printf("2.��ѧ������\n");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            //����������
            for (i = 0; i < users[current_user].studentCount - 1; i++) {
                for (j = 0; j < users[current_user].studentCount - 1 - i; j++) {
                    if (users[current_user].students[j].age > users[current_user].students[j + 1].age) {
                        temp = users[current_user].students[j];
                        users[current_user].students[j] = users[current_user].students[j + 1];
                        users[current_user].students[j + 1] = temp;
                    }
                }
            }
            printf("������ɣ�\n");
            showAllStudents();
            return;
        case 2:
            //��ѧ������,ѧ��Ϊ�ַ�������
            for (int i = 0; i < users[current_user].studentCount - 1; i++) {
                for (int j = 0; j < users[current_user].studentCount - 1 - i; j++) {
                    if (strlen(users[current_user].students[j].id) > strlen(users[current_user].students[j + 1].id) ||
                        (strlen(users[current_user].students[j].id) == strlen(users[current_user].students[j + 1].id)
                         && strcmp(users[current_user].students[j].id, users[current_user].students[j + 1].id) > 0)) {
                        struct Student temp = users[current_user].students[j];
                        users[current_user].students[j] = users[current_user].students[j + 1];
                        users[current_user].students[j + 1] = temp;
                    }
                }
            }
            printf("������ɣ�\n");
            showAllStudents();
            return;

        default:
            printf("�������\n");
            return;
    }
}


/**
 * �޸�ѧ����Ϣ
 */
void editStudent() {
    if (!isLogin) {
        printf("��δ��¼���޷��޸�ѧ����Ϣ\n");
        return;
    }
    printf("**********************�޸���ϵ��*************************\n");
    if (users[current_user].studentCount == 0) {
        printf("ѧ��ͨѶ¼Ϊ��\n");
        return;
    }
    //    showAllStudents();
    int i;
    printf("���\t����\t�Ա�\tѧ��\t\t����\t��������\t�绰\t\t��ַ\n");
    for (i = 0; i < users[current_user].studentCount; i++) {
        printf("%d\t%-6s\t%-5s\t%-8s\t%d\t%-10s\t%-10s\t%-10s\n", i, users[current_user].students[i].name, users[current_user].students[i].gender,
               users[current_user].students[i].id, users[current_user].students[i].age, users[current_user].students[i].birthday, users[current_user].students[i].phone, users[current_user].students[i].address);
    }
    printf("������Ҫ�޸�ѧ������ţ�");
    scanf("%d", &i);
    do {
        if (i < 0 || i >= users[current_user].studentCount) {
            printf("�����������������\n");
            scanf("%d", &i);
        }
    } while (i < 0 || i >= users[current_user].studentCount);

    printf("1.����\n");
    printf("2.�Ա�\n");
    printf("3.ѧ��\n");
    printf("4.����\n");
    printf("5.��������\n");
    printf("6.�绰\n");
    printf("7.��ַ\n");
    char flag = 'n';
    do {
        printf("��������Ҫ�޸ĵ���Ϣ:\n");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("�������µ�������");
                scanf("%s", users[current_user].students[i].name);
                printf("���޸ĸ�ѧ��������\n");
                printStudentInfo(i);
                break;
            case 2:
                printf("�������µ��Ա�");
                scanf("%s", users[current_user].students[i].gender);
                printf("���޸ĸ�ѧ�����Ա�\n");
                printStudentInfo(i);
                break;
            case 3:
                printf("�������µ�ѧ�ţ�");
                char id[20];
                scanf("%s", id);
                // �ж�ѧ���Ƿ��ظ�
                for (int j = 0; j < users[current_user].studentCount; j++) {
                    if (strcmp(users[current_user].students[j].id, id) == 0) {
                        do {
                            printf("ѧ���ظ�������������");
                            scanf("%s", id);
                        } while (strcmp(users[current_user].students[j].id, id) == 0);
                    }
                }
                strcpy(users[current_user].students[i].id, id);
                printf("���޸ĸ�ѧ��ѧ�š�\n");
                printStudentInfo(i);
                break;
            case 4:
                printf("�������µ����䣺");
                int age;
                scanf("%d", &age);
                while (age < 0 || age > 100) {
                    printf("�����������������:");
                    scanf("%d", age);
                }
                users[current_user].students[i].age = age;
                printf("���޸ĸ�ѧ�������䡣\n");
                printStudentInfo(i);
                break;
            case 5:
                printf("�������µĳ������ڣ�(��2000-01-01)");
                char birthday[20];
                scanf("%s", birthday);
                while (strlen(birthday) != 10 || !checkBirthday(birthday)) {
                    printf("�����������������");
                    scanf("%s", birthday);
                }
                strcpy(users[current_user].students[i].birthday, birthday);
                printf("���޸ĸ�ѧ���ĳ������ڡ�\n");
                printStudentInfo(i);
                break;
            case 6:
                printf("�������µĵ绰��(11λ)");
                char phone[20];
                scanf("%s", phone);
                //�жϵ绰�����ʽ�Ƿ���ȷ
                while (strlen(phone) != 11) {
                    printf("�����������������");
                    scanf("%s", phone);
                }
                strcpy(users[current_user].students[i].phone, phone);
                break;
            case 7:
                printf("�������µĵ�ַ��");
                scanf("%s", users[current_user].students[i].address);
                break;
            default:
                printf("�������\n");
                break;
        }

        printf("�Ƿ�����޸ĸ�ѧ����(y/n)");
        scanf("%s", &flag);

    } while (flag == 'y');
    saveToFile(); // �޸���ɺ󱣴浽�ļ�
    printf("�Ƿ��޸�����ѧ����(y/n)");
    scanf("%s", &flag);
    if (flag == 'y') {
        editStudent();
    }
    else {
        return;
    }
}

/**
 *�ַ���ת��Ϊ����
 * @param str �ַ���
 * @return num ����
 */
int stringToInt(char* str) {
    int i = 0;
    int num = 0;
    while (str[i] != '\0') {
        num = num * 10 + str[i] - '0';
        i++;
    }
    return num;
}

/**
 * �жϳ��������Ƿ���ȷ
 * @param birthday ��������
 * @return 0 ����ȷ 1 ��ȷ
 */
int checkBirthday(char* birthday) {
    char year[5];
    strncpy(year, birthday, 4);
    year[4] = '\0';
    int yearInt = stringToInt(year);
    //��ȡ��
    char month[3];
    strncpy(month, birthday + 5, 2);
    month[2] = '\0';
    int monthInt = stringToInt(month);
    //��ȡ��
    char day[3];
    strncpy(day, birthday + 8, 2);
    day[2] = '\0';
    int dayInt = stringToInt(day);
    if (monthInt == 2) {
        if (yearInt % 4 == 0 && yearInt % 100 != 0 || yearInt % 400 == 0) {
            if (dayInt > 29) {
                return 0;
            }
        }
        else {
            if (dayInt > 28) {
                return 0;
            }
        }
    }
    if (monthInt == 4 || monthInt == 6 || monthInt == 9 || monthInt == 11) {
        if (dayInt > 30) {
            return 0;
        }
    }
    if (yearInt < 1900 || yearInt > 2024) {
        return 0;
    }
    if (monthInt < 1 || monthInt > 12) {
        return 0;
    }
    if (dayInt < 1 || dayInt > 31) {
        return 0;
    }
    return 1;
}
