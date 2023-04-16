#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 200 // 最大学生数
#define MAX_NAME 20 //最大姓名
#define MAX_SEX 5 //最大性别
#define MAX_SNO 20 //最大学号
#define MAX_TELE 15  //最大电话号码
#define MAX_ADDR 50 //最大地址
#define MAX_USERS 100   // 最大用户数
#define MAX_NAME_LEN 20 // 用户名最大长度
#define MAX_PASS_LEN 20 // 密码最大长度

// 定义学生结构体
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
struct user users[MAX_USERS]; // 用户列表
int num_users = 0;            // 用户数目


void printStudentInfo(int index);



//管理员账号
//char adminUsername[20] = "admin";
//char adminPassword[20] = "123456";

char isLogin = 0; //是否已经登录
char current_user = -1; //当前登录的用户

//用户登录
void loginUser();

//用户注册
void register_user();

// 从文件中读取用户信息
void read_users();

//将用户信息写入文件中
void write_users();

//保存到文件
void saveToFile();

//从文件中加载
void initSystem();

// 添加学生
void addStudent();

// 查找学生
void findStudent();

// 显示所有学生信息
void showAllStudents();

// 删除学生信息
void deleteStudent();

//模糊查找
void fuzzyFind();

//显示单个学生信息
void printStudentInfo(int index);

//排序
void sortStudent();

//修改学生信息
void editStudent();

//字符串转换为整数
int stringToInt(char* str);

//判断出生日期是否正确
int checkBirthday(char* birthday);

//菜单栏
void menu();




// 主函数
int main() {
    read_users(); // 程序启动时从文件中读取用户信息
    int choice;
    do {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(); // 添加学生
                system("pause");
                system("cls");
                break;
            case 2:
                findStudent(); // 查找学生
                system("pause");
                system("cls");
                break;
            case 3:
                showAllStudents(); // 显示所有学生信息
                system("pause");
                system("cls");
                break;
            case 4:
                deleteStudent();//删除学生信息
                system("pause");
                system("cls");
                break;
            case 5:
                fuzzyFind();//模糊查找
                system("pause");
                system("cls");
                break;
            case 6:
                sortStudent();//排序学生信息
                system("pause");
                system("cls");
                break;
            case 7:
                editStudent();//修改学生信息
                system("pause");
                system("cls");
                break;
            case 8:
                register_user();//用户注册
                system("pause");
                system("cls");
                break;
            case 9:
                loginUser();//用户登录
                system("pause");
                system("cls");
                break;
            case 10:
                if (isLogin == 1) {
                    printf("用户已登出\n");
                    isLogin = 0;
                    current_user = -1;
                }
                else {
                    printf("请先登录账号。\n");
                }
                system("pause");
                system("cls");
                break;
            case 0:
                printf("程序已退出。\n");
                saveToFile(); // 保存到文件
                break;
            default:
                printf("输入有误，请重新选择。\n");
                break;
        }
    } while (choice != 0);

    return 0;

}

void loginUser() {
    if (isLogin == 1) {
        printf("您已经登录！\n");
        return;
    }
    if(num_users == 0) {
        printf("当前没有用户，请先注册！\n");
        return;
    }
    char name[MAX_NAME_LEN];
    char pass[MAX_PASS_LEN];

    printf("请输入您的用户名：");
    scanf("%s", name);

    printf("请输入您的密码：");
    scanf("%s", pass);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(name, users[i].name) == 0 && strcmp(pass, users[i].pass) == 0) {
            current_user = i;
            printf("登录成功！\n");
            isLogin = 1;
            //读取文件
            initSystem();
            printf("当前登录用户为：%s\n", users[current_user].name);
            printf("当前用户通讯录学生数：%d\n", users[current_user].studentCount);
            return;
        }
    }
    printf("用户名或密码错误!\n");
}
void menu() {

    printf("**************学生通讯录管理系统*****************\n");
    printf("*************************************************\n");
    printf("********1.添加学生          2. 查找学生**********\n");
    printf("********3.显示所有学生信息  4. 删除学生信息******\n");
    printf("********5.模糊查找          6. 排序学生信息******\n");
    printf("********7.修改学生信息      8. 用户注册**********\n");
    printf("********9.用户登录          10. 用户登出*********\n");
    printf("**************  0.退出系统  *********************\n");
    printf("*************************************************\n");
    printf("请选择要执行的操作：\n");
}

// 注册新用户
void register_user() {
    if (num_users == MAX_USERS) {
        printf("用户已满，不能注册\n");
        return;
    }
    printf("请输入您的用户名：");
    char name[MAX_NAME_LEN];
    scanf("%s", name);
    //判断用户名是否重复
    for (int i = 0; i < num_users; i++) {
        if (strcmp(name, users[i].name) == 0) {
            printf("用户名已存在,请重新输入！\n");
            do {
                scanf("%s", name);
                if (strcmp(name, users[i].name) == 0) {
                    printf("用户名已存在,请重新输入！\n");
                }else{
                    break;
                }
            } while (strcmp(name, users[i].name) == 0);
        }
    }
    strcpy(users[num_users].name, name);
    printf("请输入您的密码：");
    scanf("%s", users[num_users].pass);
    num_users++;
    printf("注册成功！\n");
    printf("当前用户数：%d\n", num_users);
    write_users(); // 将用户信息写入文件
}


// 从文件中读取用户信息
void read_users() {
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
//        printf("文件打开失败！\n");
        return;
    }

    while (fscanf(fp, "%s %s", users[num_users].name, users[num_users].pass) == 2) {
        num_users++;
    }
    fclose(fp);
}


// 将用户信息写入文件
void write_users() {
    FILE *fp = fopen("users.txt", "w");
    if (fp == NULL) {
//        printf("文件打开失败\n");
        return;
    }
    int i;
    for (i = 0; i < num_users; i++) {
        fprintf(fp, "%s %s\n", users[i].name, users[i].pass);
    }
    fclose(fp);
}

//保存到文件
void saveToFile() {
    FILE* fp;
    //文件名=contactor_+当前用户的用户名.txt
    char filename[100];
    strcpy(filename, "contactor_");
    strcat(filename, users[current_user].name);
    strcat(filename, ".txt");

    fp = fopen(filename, "w"); // 打开文件，若不存在则新建

    fprintf(fp, "%d\n", users[current_user].studentCount); // 先写入学生数量
    for (int i = 0; i < users[current_user].studentCount; i++) {
        fprintf(fp, "%s %s %s %d %s %s %s\n",
                users[current_user].students[i].name, users[current_user].students[i].gender, users[current_user].students[i].id, users[current_user].students[i].age,
                users[current_user].students[i].birthday, users[current_user].students[i].phone, users[current_user].students[i].address);
    }

    fclose(fp); // 关闭文件
}

//从文件中加载当前用户通讯录信息
void initSystem() {
    FILE* fp;
    //文件名=contactor_+当前用户的用户名.txt
    char filename[100];
    strcpy(filename, "contactor_");
    strcat(filename, users[current_user].name);
    strcat(filename, ".txt");

    fp = fopen(filename, "r"); // 打开文件

    if (fp == NULL) { // 如果文件不存在，则不进行读取操作
        return;
    }

    fscanf(fp, "%d", &users[current_user].studentCount); // 读入学生数量
    for (int i = 0; i < users[current_user].studentCount; i++) {
        fscanf(fp, "%s %s %s %d %s %s %s",
               users[current_user].students[i].name, &users[current_user].students[i].gender, &users[current_user].students[i].id, &users[current_user].students[i].age,
               users[current_user].students[i].birthday, users[current_user].students[i].phone, users[current_user].students[i].address);
    }

    fclose(fp); // 关闭文件
}

// 添加学生
void addStudent() {

    if (!isLogin) {
        printf("您未登录，无法添加学生信息\n");
        return;
    }
    if (users[current_user].studentCount >= MAX_STUDENTS) {
        printf("学生人数满，无法添加新的学生。\n");
        return;
    }
    printf("**************添加联系人*****************\n");
    struct Student student;
    printf("请输入学生姓名：");
    scanf("%s", student.name);
    printf("请输入学生性别：");
    scanf("%s", student.gender);
    printf("请输入学生学号：");
    char id[20];
    scanf("%s", id);
    // 判断学号是否重复
    for (int i = 0; i < users[current_user].studentCount; i++) {
        if (strcmp(users[current_user].students[i].id, id) == 0) {
            do {
                printf("学号重复，请重新输入:");
                scanf("%s", id);
            } while (strcmp(users[current_user].students[i].id, id) == 0);
        }
    }
    strcpy(student.id, id);

    printf("请输入学生年龄：");
    int age;
    scanf("%d", &age);
    //判断年龄是否正确
    while (age < 0 || age > 100) {
        printf("输入错误，请重新输入:");
        scanf("%d", &age);
    }
    student.age = age;

    printf("请输入学生出生日期(如2000-01-01):");
    char birthday[20];
    scanf("%s", birthday);
    //判断日期格式是否正确
    while (strlen(birthday) != 10 || !checkBirthday(birthday)) {
        printf("输入错误，请重新输入:");
        scanf("%s", birthday);
    }

    strcpy(student.birthday, birthday);

    printf("请输入电话号码(11位电话号码)：");
    char phone[20];
    scanf("%s", phone);
    //判断电话号码格式是否正确
    while (strlen(phone) != 11) {
        printf("输入错误，请重新输入");
        scanf("%s", phone);
    }
    strcpy(student.phone, phone);
    printf("请输入学生地址：");
    scanf("%s", student.address);

    users[current_user].students[users[current_user].studentCount] = student;
    users[current_user].studentCount++;

    printf("添加成功！\n");
    saveToFile(); // 添加完成后保存到文件
}

// 查找学生
void findStudent() {
    if (!isLogin) {
        printf("您未登录，无法查看学生信息\n");
        return;
    }
    printf("**********************查找联系人*************************\n");
    if(users[current_user].studentCount == 0){
        printf("当前无学生信息\n");
        return;
    }
    char name[20];
    printf("请输入要查找的学生姓名：");
    scanf("%s", name);
    int i;
    for (i = 0; i < users[current_user].studentCount; i++) {
        if (strcmp(name, users[current_user].students[i].name) == 0) {
            printf("姓名：%s，性别：%s，学号：%s，年龄：%d，出生日期：%s，电话：%s，地址：%s\n", users[current_user].students[i].name,
                   users[current_user].students[i].gender, users[current_user].students[i].id, users[current_user].students[i].age, users[current_user].students[i].birthday, users[current_user].students[i].phone,
                   users[current_user].students[i].address);
            return;
        }
    }

    printf("未找到名为%s的学生。\n", name);
}

// 显示所有学生信息
void showAllStudents() {
    if (!isLogin) {
        printf("您未登录，无法查看学生信息\n");
        return;
    }
    printf("*******************************显示所有学生信息********************************** \n");
    if(users[current_user].studentCount == 0){
        printf("当前无学生信息\n");
        return;
    }
    int i;
    printf("姓名\t性别\t学号\t\t年龄\t出生日期\t电话\t\t地址\n");
    for (i = 0; i < users[current_user].studentCount; i++) {
        printf("%-6s\t%-5s\t%-8s\t%d\t%-10s\t%-10s\t%-10s\n", users[current_user].students[i].name, users[current_user].students[i].gender,
               users[current_user].students[i].id, users[current_user].students[i].age, users[current_user].students[i].birthday, users[current_user].students[i].phone, users[current_user].students[i].address);
    }
    printf("********************************************************************************* \n");
}

// 删除学生信息
void deleteStudent() {

    if (!isLogin) {
        printf("您未登录，无法删除学生信息\n");
        return;
    }
    if (users[current_user].studentCount == 0) {
        printf("学生数量为0，无法删除学生信息。\n");
        return;
    }
    printf("**********************删除联系人*************************\n");
    int i;
    printf("序号\t姓名\t性别\t学号\t\t年龄\t出生日期\t电话\t\t地址\n");
    for (i = 0; i < users[current_user].studentCount; i++) {
        printf("%d\t%-6s\t%-5s\t%-8s\t%d\t%-10s\t%-10s\t%-10s\n", i, users[current_user].students[i].name, users[current_user].students[i].gender,
               users[current_user].students[i].id, users[current_user].students[i].age, users[current_user].students[i].birthday, users[current_user].students[i].phone, users[current_user].students[i].address);
    }
    printf("请输入要删除学生的序号：");
    scanf("%d", &i);
    do {
        if (i < 0 || i >= users[current_user].studentCount) {
            printf("输入错误！请重新输入\n");
            scanf("%d", &i);
        }
    } while (i < 0 || i >= users[current_user].studentCount);
    printf("确认删除学生%s吗？(y/n)", users[current_user].students[i].name);
    char c;
    scanf(" %c", &c);
    if (c == 'n') {
        printf("取消删除！\n");
        return;
    }
    for (int j = i; j < users[current_user].studentCount - 1; j++) {
        users[current_user].students[j] = users[current_user].students[j + 1];
    }
    users[current_user].studentCount--;
    printf("删除成功！\n");
    saveToFile(); // 删除完成后保存到文件
}

//模糊查找
void fuzzyFind() {
    if (!isLogin) {
        printf("您未登录，无法查找学生信息\n");
        return;
    }
    if (users[current_user].studentCount == 0) {
        printf("学生通讯录为空\n");
        return;
    }
    printf("**********************模糊查找*************************\n");
    char keyword[20];
    printf("请输入要查找的关键字：");
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
        printf("没有找到匹配的学生信息\n");
    }
    else {
        printf("共找到%d个匹配的学生信息\n", count);
    }
}

//打印单个学生信息
void printStudentInfo(int index) {
    int i;
    for (i = 0; i < users[current_user].studentCount; i++) {
        if (i == index) {
            printf("姓名：%s，性别：%s，学号：%s，年龄：%d，出生日期：%s，电话：%s，地址：%s\n", users[current_user].students[i].name,
                   users[current_user].students[i].gender, users[current_user].students[i].id, users[current_user].students[i].age, users[current_user].students[i].birthday, users[current_user].students[i].phone,
                   users[current_user].students[i].address);
        }
    }
}

//排序
void sortStudent() {
    if (!isLogin) {
        printf("您未登录，无法对学生信息进行排序\n");
        return;
    }
    //如果通讯录为空，无法排序
    if (users[current_user].studentCount == 0) {
        printf("学生数量为0，无法排序。\n");
        return;
    }
    printf("**********************联系人排序*************************\n");
    int i, j;
    struct Student temp;
    printf("请输入排序的方式\n");
    printf("1.按年龄排序\n");
    printf("2.按学号排序\n");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            //按年龄排序
            for (i = 0; i < users[current_user].studentCount - 1; i++) {
                for (j = 0; j < users[current_user].studentCount - 1 - i; j++) {
                    if (users[current_user].students[j].age > users[current_user].students[j + 1].age) {
                        temp = users[current_user].students[j];
                        users[current_user].students[j] = users[current_user].students[j + 1];
                        users[current_user].students[j + 1] = temp;
                    }
                }
            }
            printf("排序完成！\n");
            showAllStudents();
            return;
        case 2:
            //按学号排序,学号为字符串类型
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
            printf("排序完成！\n");
            showAllStudents();
            return;

        default:
            printf("输入错误！\n");
            return;
    }
}


/**
 * 修改学生信息
 */
void editStudent() {
    if (!isLogin) {
        printf("您未登录，无法修改学生信息\n");
        return;
    }
    printf("**********************修改联系人*************************\n");
    if (users[current_user].studentCount == 0) {
        printf("学生通讯录为空\n");
        return;
    }
    //    showAllStudents();
    int i;
    printf("序号\t姓名\t性别\t学号\t\t年龄\t出生日期\t电话\t\t地址\n");
    for (i = 0; i < users[current_user].studentCount; i++) {
        printf("%d\t%-6s\t%-5s\t%-8s\t%d\t%-10s\t%-10s\t%-10s\n", i, users[current_user].students[i].name, users[current_user].students[i].gender,
               users[current_user].students[i].id, users[current_user].students[i].age, users[current_user].students[i].birthday, users[current_user].students[i].phone, users[current_user].students[i].address);
    }
    printf("请输入要修改学生的序号：");
    scanf("%d", &i);
    do {
        if (i < 0 || i >= users[current_user].studentCount) {
            printf("输入错误！请重新输入\n");
            scanf("%d", &i);
        }
    } while (i < 0 || i >= users[current_user].studentCount);

    printf("1.姓名\n");
    printf("2.性别\n");
    printf("3.学号\n");
    printf("4.年龄\n");
    printf("5.出生日期\n");
    printf("6.电话\n");
    printf("7.地址\n");
    char flag = 'n';
    do {
        printf("请输入您要修改的信息:\n");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("请输入新的姓名：");
                scanf("%s", users[current_user].students[i].name);
                printf("已修改该学生的姓名\n");
                printStudentInfo(i);
                break;
            case 2:
                printf("请输入新的性别：");
                scanf("%s", users[current_user].students[i].gender);
                printf("已修改该学生的性别。\n");
                printStudentInfo(i);
                break;
            case 3:
                printf("请输入新的学号：");
                char id[20];
                scanf("%s", id);
                // 判断学号是否重复
                for (int j = 0; j < users[current_user].studentCount; j++) {
                    if (strcmp(users[current_user].students[j].id, id) == 0) {
                        do {
                            printf("学号重复，请重新输入");
                            scanf("%s", id);
                        } while (strcmp(users[current_user].students[j].id, id) == 0);
                    }
                }
                strcpy(users[current_user].students[i].id, id);
                printf("已修改该学生学号。\n");
                printStudentInfo(i);
                break;
            case 4:
                printf("请输入新的年龄：");
                int age;
                scanf("%d", &age);
                while (age < 0 || age > 100) {
                    printf("输入错误，请重新输入:");
                    scanf("%d", age);
                }
                users[current_user].students[i].age = age;
                printf("已修改该学生的年龄。\n");
                printStudentInfo(i);
                break;
            case 5:
                printf("请输入新的出生日期：(如2000-01-01)");
                char birthday[20];
                scanf("%s", birthday);
                while (strlen(birthday) != 10 || !checkBirthday(birthday)) {
                    printf("输入错误，请重新输入");
                    scanf("%s", birthday);
                }
                strcpy(users[current_user].students[i].birthday, birthday);
                printf("已修改该学生的出生日期。\n");
                printStudentInfo(i);
                break;
            case 6:
                printf("请输入新的电话：(11位)");
                char phone[20];
                scanf("%s", phone);
                //判断电话号码格式是否正确
                while (strlen(phone) != 11) {
                    printf("输入错误，请重新输入");
                    scanf("%s", phone);
                }
                strcpy(users[current_user].students[i].phone, phone);
                break;
            case 7:
                printf("请输入新的地址：");
                scanf("%s", users[current_user].students[i].address);
                break;
            default:
                printf("输入错误！\n");
                break;
        }

        printf("是否继续修改该学生？(y/n)");
        scanf("%s", &flag);

    } while (flag == 'y');
    saveToFile(); // 修改完成后保存到文件
    printf("是否修改其他学生？(y/n)");
    scanf("%s", &flag);
    if (flag == 'y') {
        editStudent();
    }
    else {
        return;
    }
}

/**
 *字符串转化为整数
 * @param str 字符串
 * @return num 整数
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
 * 判断出生日期是否正确
 * @param birthday 出生日期
 * @return 0 不正确 1 正确
 */
int checkBirthday(char* birthday) {
    char year[5];
    strncpy(year, birthday, 4);
    year[4] = '\0';
    int yearInt = stringToInt(year);
    //获取月
    char month[3];
    strncpy(month, birthday + 5, 2);
    month[2] = '\0';
    int monthInt = stringToInt(month);
    //获取日
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
