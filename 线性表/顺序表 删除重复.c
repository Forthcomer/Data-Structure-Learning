/*
顺序表 删除重复

编写算法，在一非递减的顺序表L中，删除所有值相等的多余元素。
要求时间复杂度为O(n)，空间复杂度为O(1)。

函数原型如下：
void del_dupnum(SeqList *L)

相关定义如下：
struct _seqlist{
    ElemType elem[MAXSIZE];
    int last;
};
typedef struct _seqlist SeqList;

*/
#include <stdio.h>
#include <stdlib.h>
#include "list.h" // 请不要删除，否则检查不通过

void del_dupnum(SeqList *L)  {
    int prev = -1;
    int curr = 0;
    //双指针，当后一个指针发发现没有发现的数字时，后一个指针后移一个，前一个指针保持跟随，由于是非递减有序（这里有一个文字游戏），相同的元素一定相邻。
    while(curr <= L->last){
        if (L->elem[prev] == L->elem[curr]){
            curr++;
        } else{
            prev++;
            L->elem[prev] = L->elem[curr];
            curr++;
        }
    }
    L->last = prev;
}