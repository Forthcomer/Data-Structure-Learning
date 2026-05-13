/*
十字链表
十字链表相关定义如下：
typedef int ElemType;
// 非零元素结点结构
typedef struct OLNode
{
    int row,col;
    ElemType value;
    struct OLNode *right,*down;
}OLNode,*OLink;

// 十字链表结构
typedef struct
{
    OLink *rowhead,*colhead;
    int rows,cols,nums;
}CrossList, *PCrossList;

1）实现十字链表的初始化操作：
 int init_cross_list(PCrossList L, const ElemType *A, int m, int n);
其中 L 指向 CrossList 结构，且各成员已被初始化为0；
A 为 ElemType 类型数组中第一个元素的地址，元素的个数为 m×n 个，
按行优先存储（即A[0] 为十字链表第1行第1列的元素；
A[1] 为第1行第2列的元素，A[n] 为第2行第1列的元素，A[n+1] 为第2行第2个元素）；
m 表示十字链表的行数，n 表示十字链表的列数。
init_cross_list 函数将 ElemType 数组中非0元素保存到十字链表中，
函数返回非 0 元素的个数。
*/

#include <stdio.h>
#include <stdlib.h>
#include "crosslist.h"

int init_cross_list(PCrossList L, const ElemType *A, int m,int n){
    L->rows = m;
    L->cols = n;
    L->nums = 0;
    // 多分配一个空间防止越界，许多C语言题目会默认索引从1排甚至隐藏留空需求
    L->rowhead = (OLink *)calloc(m + 1, sizeof(OLink));
    L->colhead = (OLink *)calloc(n + 1, sizeof(OLink));
    int count = 0;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){ 
            ElemType val = A[i * n + j];
            if (val != 0){
                // 创建节点
                OLink p = (OLink)malloc(sizeof(OLNode));
                p->row = i + 1;
                p->col = j + 1;
                p->value = val;
                p->right = NULL;//边界的指针需要置空让程序更安全
                p->down = NULL;
                count++;

                // 将p横向接入第i行
                if (L->rowhead[i + 1] == NULL){
                    L->rowhead[i + 1] = p;
                }else {
                    OLink temp = L->rowhead[i + 1];
                    while(temp->right != NULL){
                        temp = temp->right;
                    }
                    temp->right = p;
                }
                
                // 将p纵向接入第j列
                if (L->colhead[j + 1] == NULL){
                    L->colhead[j + 1] = p;
                }else {
                    OLink temp = L->colhead[j + 1];
                    while(temp->down != NULL){
                        temp = temp->down;
                    }
                    temp->down = p;
                }
            }
        } 
    }
    L->nums = count;
    return count;
}


/* 
2）实现十字链表的删除操作：
 int del_cross_list(PCrossList L, ElemType k);
其中 L 指向 要处理的 CrossList 结构，k 为要删除的元素；
del_cross_list 函数删除十字链表中所有值为 k 的结点，并返回删除结点的个数。
*/
int del_cross_list(PCrossList L, ElemType k){
    int count = 0;
    // 删除函数也从 1 遍历到 L->rows
    for (int i = 1; i <= L->rows; i++){
        OLink p = L->rowhead[i];
        OLink pre_row = NULL;
        while (p != NULL){
            if (p->value == k){
                OLink to_delete = p;
                int j = to_delete->col;
                //先在行中删除
                if (pre_row == NULL) {
                    L->rowhead[i] = to_delete->right;
                } else {
                    pre_row->right = to_delete->right;
                }
                p = to_delete->right; 
                //再在列中删除
                OLink q = L->colhead[j];
                OLink pre_col = NULL;
                while(q != to_delete){
                    pre_col = q;
                    q = q->down;
                }//q找到to_delete说明寻找成功，此时pre_col就是要寻找节点的前驱
                if (pre_col == NULL) {
                    L->colhead[j] = to_delete->down;
                } else {
                    pre_col->down = to_delete->down;
                }
                free(to_delete);
                count++;
                L->nums--;
            }else {
                pre_row = p;
                p = p->right;
            }
        }
    }
    return count;
}

