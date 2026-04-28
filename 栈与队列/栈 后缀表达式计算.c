/*
栈 后缀表达式计算

请使用已定义好的栈完成后缀表达式计算：
(1)如果是操作数，直接入栈
(2)如果是操作符op，连续出栈两次，得到操作数x 和 y,计算 x op y，并将结果入栈。

后缀表达式示例如下：
9  3  1  -  3  *  +  10  2  /  +
13  445  +  51  /  6  -
操作数、操作符之间由空格隔开，操作符有 +，-，*, /, %共 5 种符号，所有操作数都为整型。

栈的定义如下：

#define Stack_Size 50
typedef struct{
    ElemType elem[Stack_Size];
    int top;
}Stack;

bool push(Stack* S, ElemType x);
bool pop(Stack* S, ElemType *x);
void init_stack(Stack *S);
其中，栈初始化的实现为：

void init_stack(Stack *S){
    S->top = -1;
}
需要完成的函数定义为：int compute_reverse_polish_notation(char *str);

函数接收一个字符指针，该指针指向一个字符串形式的后缀表达式，函数返回该表达式的计算结果。
*/
#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过

int compute_reverse_polish_notation(char *str){
    Stack s;
    init_stack(&s);
    char *p = str;
    while(*p){
        // 跳过所有空格
        while(*p == ' ' || *p == '\t' || *p == '\n') p++;
        if (*p == '\0') break;
        //识别所有计算符号
        if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '%'){
            ElemType x, y;
            pop(&s, &x);//先弹出来的为算术中的右数
            pop(&s, &y);//后弹出来的为左边的数字
            int result;
            switch(*p){
                case('+'): result = y + x; break;
                case('-'): result = y - x; break;
                case('*'): result = y * x; break;
                case('/'): result = y / x; break;
                case('%'): result = y % x; break;
                default: result = 0;
            }
            push(&s, result);//push后面的接的是(&s（字符串指针）, result（原本的数据而非地址）)
            p++;
        } else{
            //标准化识别数字
            int temp = 0;
            int sign = 1;
            if (*p == '-'){
                sign = -1;
                p++;
            }
            while (*p >= '0' && *p <= '9'){
                temp = temp * 10 + (*p - '0');
                p++;
            }
            temp *= sign;
            push(&s, temp);
        }
    }
    ElemType result;
    pop(&s, &result);
    return result;
}