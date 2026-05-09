/*
串替换

不调用库函数，自己实现字符串替换操作，函数原型为：

int str_replace(const char *in, char *out, int outlen, const char *oldstr, const char *newstr);
参数说明:

in， 原始字符串，保持不变
out, 存放替换结果的字符串
outlen，out空间的大小
oldstr，要替换的旧字符串
newstr，替换成的新字符串
函数返回成功替换的次数，即有多少个子串被成功替换
在替换过程中，任何情况下所得字符串（及结束符）不应该超过 outlen，
如果某次替换所得字符串的长度超过 outlen，则不进行这次替换操作，整个替换操作结束。如：
原始串为 "aaabbbccc"，outlen 为14, oldstr 为 "c"，newstr 为 "333" 时，
两次替换后得 "aaabbb333333c"，此时字符串占用空间为14字节。
如果再进行替换，则会超出 out 所占用的空间，所以停止替换操作。
此时函数应该返回 2, out指向的串为 "aaabbb333333c"
再如：原始串为 "aaabbbccc"，outlen 为10, oldstr 为 "b"，newstr 为 "123456"，
进行替换后所得的串长度为14，与结束符一共占 15 个字节，超过outlen的10字节，此时不进行替换，函数应该返回 0。
*/
#include<stdio.h>
#include<stdlib.h>
#include "dsstring.h"

int str_len (const char *str, int pos){
    int count = 0;
    for (int i = pos; str[i] != '\0'; i++){
        count++;
    }
    return count;
}
int str_replace(const char *in, char *out, int outlen, const char *oldstr, const char *newstr){
    int count = 0;
    int i = 0, out_i = 0;
    int oldlen = str_len(oldstr, 0);
    int newlen = str_len(newstr, 0);
    
    // 初始化 out 字符串数组
    for (int k = 0; k < outlen; k++){
        out[k] = '\0';
    }
    
    if (outlen <= 0) return 0;

    while (in[i] != '\0') {
        int match = 1;
        for (int j = 0; j < oldlen; j++) {
            if (in[i + j] != oldstr[j]) {
                match = 0;
                break;
            }
        }
        
        if (match && oldlen > 0) {
            // 需要判断替换后总长度是否超过 outlen
            int rest_len = str_len(in, i + oldlen);
            if (out_i + newlen + rest_len + 1 <= outlen) {
                for (int k = 0; k < newlen; k++) {
                    out[out_i++] = newstr[k];
                }
                i += oldlen;
                count++;
            } else {
                // 如果发现替换后超出长度，停止本次及后续替换，直接复制原字符串剩余部分
                while (in[i] != '\0' && out_i < outlen - 1) {
                    out[out_i++] = in[i++];
                }
                break;
            }
        } else {
            // 复制当前字符
            if (out_i < outlen - 1) {
                out[out_i++] = in[i];
            }
            i++;
        }
    }
    out[out_i] = '\0';
    return count;
}