/*
矩阵加法

实现三元组表示的两个稀疏矩阵的加法。相关定义如下：

#define MAXSIZE 100         //假设非零元个数的最大值为100
typedef struct {
    int i,j;  //非零元的行下标和列下标，i 和 j 从 1 开始计数，与数学中矩阵元素的编号一致
    ElemType e;						//非零元的值
}Triple;

typedef struct {
    Triple data[MAXSIZE];	// 非零元三元组表
    int    m, n, len;		// 矩阵的行数、列数和非零元个数
}TSMatrix;
在三元组中，i 和 j 从 1 开始计数，与数学中矩阵元素的编号一致
矩阵加法函数的原型为：

bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ);
pM, pN, pQ 分别指向三个矩阵，当 pM 和 pN 两个矩阵不可加时，函数返回 false，
否则函数返回 true，且 pQ 指向两个矩阵的和。
*/
#include <stdio.h>
#include <stdlib.h>
#include "tsmatrix.h"

bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ){
    if (pM->m != pN->m || pM->n != pN->n){
        return false;// 无法进行相加运算
    }
    pQ->m = pM->m;
    pQ->n = pM->n;
    pQ->len = 0;
    int i = 0, j = 0, k = 0;
    
    while(i < pM->len && j < pN->len){
        if (pM->data[i].i < pN->data[j].i){
            pQ->data[k++] = pM->data[i++];
        }
        else if(pM->data[i].i > pN->data[j].i){
            pQ->data[k++] = pN->data[j++];
        }
        // 行号比较以后比较列号
        else {
            if (pM->data[i].j < pN->data[j].j){
                pQ->data[k++] = pM->data[i++];
            }else if(pM->data[i].j > pN->data[j].j){
                pQ->data[k++] = pN->data[j++];
            }else {
                ElemType sum = pM->data[i].e + pN->data[j].e;
                if (sum != 0){
                    pQ->data[k].i = pM->data[i].i;
                    pQ->data[k].j = pM->data[i].j;
                    pQ->data[k].e = sum;
                    k++;
                }
                i++;
                j++;
            }
        }
    }
    while (i < pM->len){
        pQ->data[k++] = pM->data[i++];
    }
    while (j < pN->len){
        pQ->data[k++] = pN->data[j++];
    }
    pQ->len = k;
    return true;
}