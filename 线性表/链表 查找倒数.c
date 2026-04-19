/*
链表 倒数查找

已知一个带有表头结点的单链表, 假设链表只给出了头指针L。在不改变链表的前提下，请设计一个尽可能高效的算法，查找链表中倒数第k个位置上的结点（k为正整数）。
函数原型为：int lnk_search(LinkList L, int k, ElemType* p_ele)
若查找成功，函数通过指针参数 p_ele 返回该结点 data 域的值，此时函数返回 1；否则，函数返回 0。相关定义如下：

struct _lnklist{
    ElemType data;
    struct _lnklist *next;
};

typedef struct _lnklist Node;
typedef struct _lnklist *LinkList;
*/
#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过

int lnk_search(LinkList L, int k, ElemType* p_ele) {
    Node *pa = L->next;//不要忘记用*pa
    Node *pf = L->next;
    for (int i = 0; i < k; i++){
        if (pa == NULL){
            return 0;
        }
        pa = pa->next;
    }
    while(pa != NULL){
        pf = pf->next;
        pa = pa->next;
    }
    *p_ele = pf->data;
    return 1;
}