/*
块链串

块链串定义如下：

#define BLOCK_SIZE 4    // 可由用户定义的块大小
#define BLS_BLANK '#'   // 用于空白处的补齐字符

typedef struct _block {
    char ch[BLOCK_SIZE];    //块的数据域
    struct _block *next;    //块的指针域
} Block;

typedef struct {
    Block *head;        // 串的头指针
    Block *tail;        // 串的尾指针
    int len;            // 串的当前长度
} BLString;

//字符串初始化函数：
void blstr_init(BLString *T) {
    T->len = 0;
    T->head = NULL;
    T->tail = NULL;
}
这些定义已包含在头文件 dsstring.h 中，请实现块链串的子串查找操作：

bool blstr_substr(BLString src, int pos, int len, BLString *sub);
src为要查找的字符串
pos为子串开始的下标
len为子串的长度
sub在函数调用运行前指向一个已经初始化好的空串，在函数返回时，sub指向串src从第pos个字符起长度为len的子串
函数查找成功返回true，参数不正确返回 false
*/
#include <stdlib.h>
#include <stdio.h>
#include "dsstring.h" // 请不要删除，否则检查不通过

bool blstr_substr(BLString src, int pos, int len, BLString *sub) {
    // 先检查参数的合法性
    if (pos < 0 || pos >= src.len || len < 1 || sub == NULL)
        return false;
        
    if (pos + len > src.len) {
        len = src.len - pos;
    }

    // 初始化
    sub->head = (Block*)malloc(sizeof(Block));
    if (sub->head == NULL) {
        return false;
    }
    Block* curr_block = sub->head, *src_block = src.head;

    int src_pos = 0, sub_pos = 0, char_count = 0;

    // 初始化尾指针和长度
    curr_block->next = NULL;
    sub->tail = curr_block;
    sub->len = 0;

    // 循环遍历
    while(char_count <= pos + len - 1 && src_block != NULL && src_block->ch[src_pos] != BLS_BLANK){
        if (char_count < pos){
            if (src_pos < BLOCK_SIZE - 1){
                src_pos++;
            }else {
                src_block = src_block->next;
                src_pos = 0;
            }
            char_count++;
        }
        else {
            curr_block->ch[sub_pos] = src_block->ch[src_pos];
            if (src_pos < BLOCK_SIZE - 1){
                src_pos++;
            }else {
                src_block = src_block->next;
                src_pos = 0;
            }

            if(sub_pos < BLOCK_SIZE - 1){
                sub_pos++;
            }else {
                curr_block->next = (Block*)malloc(sizeof(Block));
                curr_block = curr_block->next;
                curr_block->next = NULL;
                sub_pos = 0;
            }
            char_count++;
            sub->len++;
        }
    }

    // 处理尾指针和多余空间
    if (sub_pos != 0) {
        sub->tail = curr_block;
        while (sub_pos < BLOCK_SIZE){
            curr_block->ch[sub_pos++] = BLS_BLANK;
        }
    }else {//如果最后一个块空删除这个块
        // 遍历找到最后一个块的前一个块
        if (sub->head == curr_block) {
            // sub string is just empty basically? Actually if len>=1, this shouldn't happen unless len == 0.
        } else {
            Block *p = sub->head;
            while (p->next != curr_block) p = p->next;
            p->next = NULL;
            free(curr_block);
            sub->tail = p;
        }
    }
    return true;
}