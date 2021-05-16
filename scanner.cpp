#include <iostream>
#include <string.h>
using namespace std;
#define KEY_NUM 14
#define PRA_NUM 16
string K[15] =
{
    "",
    "int",
    "void",
    "break",
    "float",
    "while",
    "do",
    "struct",
    "const",
    "case",
    "for",
    "return",
    "if",
    "default",
    "else"
};

string P[17] =
{
    "",
    "-",
    "/",
    "(",
    ")",
    "==",
    "<=",
    "<",
    "+",
    "*",
    ">",
    "=",
    ",",
    ";",
    "++",
    "{",
    "}"
};

string I[50]
{
    ""
};

int C[50]
{
    0
};


int main()
{
    string all_ch;
    string buf;
    while (cin >> buf) {    // 将所有行的代码缩为一整行，且去掉空格
        all_ch = all_ch + buf;
    }
    //string 不需要'\0'来判断结束
    const char* cur_ptr = all_ch.c_str();
    // 将连接起来的串转为char*
    int identifier_num = 1;
    int count_num = 1;
    cout << "Token序列：";
    while (*cur_ptr) {
        if (*cur_ptr >= 48 && *cur_ptr <= 57) { // 常整数表

            int sum = *cur_ptr - 48; // 需要将所有的一连串数字组装成一个整数
            cur_ptr++;
            while (*cur_ptr >= 48 && *cur_ptr <= 57) { // 直到读到的字符不是数字停止
                sum = sum * 10 + *cur_ptr - 48;
                cur_ptr++;
            }

            int i = 1;
            for (; i < count_num; i++) {
                if (sum == C[i]) {         // 如果有重复的话，直接用原有的输出
                    printf("(C %d)", i);
                    break;
                }
            }
            if (i == count_num) {          //无重复的话，加入并打印
                C[count_num] = sum;
                printf("(C %d)", count_num);
                count_num++;
            }

        }
        else if (*cur_ptr == '_' || (*cur_ptr >= 'a' && *cur_ptr <= 'z')
            || (*cur_ptr >= 'A' && *cur_ptr <= 'Z')) {
            char* mystring = new char[20];
            // 必须要每次开辟每次释放，否则上次遗留的会对下一次的结果产生影响
            int length = 0;
            mystring[length++] = *cur_ptr;

            int flag = 1;
            // 这个用来表示是否读到数字或者是下划线，如果读到则一定是标识符
            // flag = 0 则直接搜索标识符  1时需要搜索 标识符和关键字
            cur_ptr++;
            while (*cur_ptr == '_' || (*cur_ptr >= 'a' && *cur_ptr <= 'z')
                || (*cur_ptr >= 'A' && *cur_ptr <= 'Z') || (*cur_ptr >= '0' && *cur_ptr <= '9')) {
                if (*cur_ptr == '_' || (*cur_ptr >= '0' && *cur_ptr <= '9')) {
                    flag = 0;
                }
                mystring[length++] = *cur_ptr;
                cur_ptr++;
            }
            // 一定要加这一句，否则不能构成一个完整的字符串
            mystring[length++] = '\0';
            // 读完了
            if (flag) {
                // 先搜索关键字
                bool isfind = false;
                for (int i = 1; i <= KEY_NUM; i++) {
                    if (mystring == K[i]) {
                        isfind = true;
                        printf("(K %d)", i);
                        break;
                    }
                }

                if (!isfind) { // 关键字没找到，则是标识符
                    int i = 1;
                    for (; i < identifier_num; i++) {
                        if (mystring == I[i] && strlen(mystring) == I[i].length()) {
                            // 如果有重复的话，直接用原有的输出
                            printf("(I %d)", i);
                            break;
                        }
                    }
                    if (i == identifier_num) {          //无重复的话，加入并打印
                        I[identifier_num] = mystring;
                        printf("(I %d)", identifier_num);
                        identifier_num++;
                    }
                }
            }
            else {
                int i = 1;
                for (; i < identifier_num; i++) {
                    if (mystring == I[i] && strlen(mystring) == I[i].length()) {
                        // 如果有重复的话，直接用原有的输出
                        printf("(I %d)", i);
                        break;
                    }
                }
                if (i == identifier_num) {          //无重复的话，加入并打印
                    I[identifier_num] = mystring;
                    printf("(I %d)", identifier_num);
                    identifier_num++;
                }
            }

            delete[]mystring;
            mystring = nullptr;
        }
        else {
            // 需判断两个字符
            if (*cur_ptr == '=' || *cur_ptr == '+' || *cur_ptr == '<') {
                switch (*cur_ptr) {
                case '=':
                {
                    cur_ptr++;
                    if (*cur_ptr == '=') {
                        printf("(P %d)", 5);
                        cur_ptr++;
                    }
                    else {
                        printf("(P %d)", 11);
                    }
                    break;
                }

                case '+':
                {
                    cur_ptr++;
                    if (*cur_ptr == '+') {
                        printf("(P %d)", 14);
                        cur_ptr++;
                    }
                    else {
                        printf("(P %d)", 8);
                    }
                    break;
                }

                case '<':
                {
                    cur_ptr++;
                    if (*cur_ptr == '=') {
                        printf("(P %d)", 16);
                        cur_ptr++;
                    }
                    else {
                        printf("(P %d)", 7);
                    }
                    break;
                }
                default:
                    break;
                }
            }
            else { // 单一字符
                int i = 1;
                for (; i <= PRA_NUM; i++) {
                    if (*cur_ptr == P[i][0]) {
                        printf("(P %d)", i);
                        break;
                    }
                }
                cur_ptr++;
            }
        }
    }
    // cout<<"safe exit"<<endl;
    cout << endl;
    cout << "标识符表：";
    int i = 1;
    for (; i < identifier_num - 1; i++) {
        cout << I[i] << " ";
    }
    cout << I[i] << endl;
    cout << "常数表：";
    i = 1;
    for (; i < count_num - 1; i++) {
        cout << C[i] << " ";
    }
    cout << C[i] << endl;
    return 0;
}