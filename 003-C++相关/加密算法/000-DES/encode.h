//
// Created by 徐伟毅 on 2017/3/28.
//

#ifndef DES_ENCODE_H
#define DES_ENCODE_H

#include <iostream>
#include <math.h>
#include "table.h"
using namespace std;

//明文、密钥处理
void CharToBinary(char *in, int (&out)[64]);  //十进制明文转64位二进制
void BinaryToHexadecimal(int *in, char (&out)[16]);     //64位二进制转十六进制密文
void IP(int (&in)[64]);        //初始置换 IP
void IP_1(int (&out)[64]);      //结束逆置换 IP_1

void IPChoice_1(int *key1, int (&C)[28], int (&D)[28]);       //置换选择1，64位->56位；k1为原密钥，C、D为置换选择后分组后的两部分
void IPChoice_2(int (&C)[28], int (&D)[28], int (&key)[48], int *move);       //置换选择2，56位->48位；key为轮密钥(FKey)；move为循环左移数组

//F 轮函数
void ExpendIP(int *R1, int (&R2)[48]);     //扩展置换，32位->48位；R1为原数组，R2为扩展后的数组
void XOR1(int (&E)[48], int *K);            //按位异或，E为扩展矩阵，K为轮密钥，异或结果赋值给E
void XOR2(int (&R)[32], int *L, int *S);            //按位异或，S为置换后矩阵，异或结果赋值给R
void SinF(int *in, int (&out)[32]);        //S代换盒，48位->32位
void PinF(int (&in)[32]);                  //P置换盒，32位->32位
int BinaryToDecimal(int *in, int length);       //S盒中使用的，二进制转十进制
void DecimalToBinary(int in, int (&out)[4]);        //S盒中使用的，十进制转四位二进制

//加密函数
void Fencode(int (&R)[32], int *L, int (&exp)[48], int *Fkey, int (&Sbox)[32]);

void CharToBinary(char *in, int (&out)[64]) {
    int b[8], result[8], k = 0;             //b 用来存储每个字符对应的 ASCII 码值，result 存放每个字符的二进制表达，k 为总计数器
    for (int y = 0; y < 8; y++) {
        b[y] = (int)in[y];
    }
    for (int y = 0; y < 8; y++) {           //遍历8个字符，分别准换成8位二进制
        for (int x = 0; x < 8; x++) {       //遍历8个位，确保准换的二进制有8位
            if (b[y]) {
                result[7-x] = b[y] % 2;
                b[y] = b[y] / 2;
            } else {
                result[7-x] = 0;
            }
        }
        for (int i = 0; i < 8; i++) {       //把转换结果赋值给一维数组
            out[k] = result[i];
            k++;
        }
    }
}

void BinaryToHexadecimal(int *in, char (&out)[16]) {
    for (int i = 0; i < 63; i+=4) {
        double result = 0;
        int c = 3;
        char eve;
        int temp[4] = {in[i], in[i+1], in[i+2], in[i+3]};
        for (int j = 0; j < 4; ++j) {
            result = result + temp[j] * pow(2, c);
            c--;
        }
        eve = (char)result;
        switch (eve) {
            case 10:
                out[i/4] = 'A';
                break;
            case 11:
                out[i/4] = 'B';
                break;
            case 12:
                out[i/4] = 'C';
                break;
            case 13:
                out[i/4] = 'D';
                break;
            case 14:
                out[i/4] = 'E';
                break;
            case 15:
                out[i/4] = 'F';
                break;
            default:
                out[i/4] = eve + (char)48;
                break;
        }
        cout << out[i/4];
    }
    cout << endl;
}

int BinaryToDecimal(int *in, int length) {
    double dec = 0;
    int c = length - 1, result;
    for (int i = 0; i < length; ++i) {
        dec = dec + in[i] * pow(2, c);
        c--;
    }
    result = (int)dec;
    return result;
}

void DecimalToBinary(int in, int (&out)[4]) {
    for (int i = 0; i < 4; i++) {       //遍历4个位，确保转换后的二进制有4位
        if (in) {
            out[3-i] = in % 2;
            in = in / 2;
        } else {
            out[3-i] = 0;
        }
    }
}

void IP(int (&in)[64]) {
    int temp[64];
    for (int j = 0; j < 64; ++j) {
        temp[j] = in[j];
    }
    for (int i = 0 ; i < 64; ++i) {
        in[i] = temp[IP_Table[i]-1];
    }
}

void IP_1(int (&out)[64]) {
    int temp[64];
    for (int j = 0; j < 64; ++j) {
        temp[j] = out[j];
    }
    for (int i = 0 ; i < 64; ++i) {
        out[i] = temp[IP_1_Table[i]-1];
    }
}

void IPChoice_1(int *key1, int (&C)[28], int (&D)[28]) {
    for (int i = 0; i < 56; ++i) {                  //置换选择1，并分组
        if (i < 28) {
            C[i] = key1[IPChoice_1_Table[i]-1];
        } else {
            D[i-28] =key1[IPChoice_1_Table[i]-1];
        }
    }
}

void IPChoice_2(int (&C)[28], int (&D)[28], int (&key)[48], int *move) {
    int temp[56], x = 0, altC, altD;
    while (x < move[countF]) {           //循环左移
        altC = C[0];
        altD = D[0];
        for (int i = 0; i < 28; ++i) {
            C[i] = C[i+1];
            D[i] = D[i+1];
        }
        C[27] = altC;
        D[27] = altD;
        x++;
    }
    countF++;
    for (int i = 0; i < 56; ++i) {      //合并C、D
        if (i < 28) {
            temp[i] = C[i];
        } else {
            temp[i] = D[i-28];
        }
    }
    for (int j = 0; j < 48; ++j) {              //置换选择2
        key[j] = temp[IPChoice_2_Table[j]-1];
    }
}

void ExpendIP(int *R1, int (&R2)[48]) {
    for (int i = 0; i < 48; ++i) {
        R2[i] = R1[ExpendIP_Table[i]-1];
    }
}

void XOR1(int (&E)[48], int *K) {
    for (int i = 0; i < 48; ++i) {
        if (E[i] == K[i]) {
            E[i] = 0;
        } else {
            E[i] = 1;
        }
    }
}

void XOR2(int (&R)[32], int *L, int *S) {
    for (int i = 0; i < 32; ++i) {
        if (L[i] == S[i]) {
            R[i] = 0;
        } else {
            R[i] = 1;
        }
    }
}

void SinF(int *in, int (&out)[32]) {
    int row[2], col[4], temp[4];
    int r = 0, c = 0, result, k = 0, rowlength, collength;
    for (int i = 0; i < 43; i+=6) {
        row[0] = in[i];
        row[1] = in[i+5];
        col[0] = in[i+1];
        col[1] = in[i+2];
        col[2] = in[i+3];
        col[3] = in[i+4];
        rowlength = 2;
        collength = 4;
        r = BinaryToDecimal(row, rowlength);
        c = BinaryToDecimal(col, collength);
        result = SinF_Table[i/6][r][c];
        DecimalToBinary(result, temp);
        for (int j = 0; j < 4; ++j) {
            out[k] = temp[j];
            k++;
        }
    }
}

void PinF(int (&in)[32]) {
    int temp[32];
    for (int i = 0; i < 32; ++i) {
        temp[i] = in[i];
    }
    for (int j = 0; j < 32; ++j) {
        in[j] = temp[PinF_Table[j]-1];
    }
}

void Fencode(int (&R)[32], int *L, int (&exp)[48], int *Fkey, int (&Sbox)[32]) {
    ExpendIP(R, exp);
    XOR1(exp, Fkey);
    SinF(exp, Sbox);
    PinF(Sbox);
    XOR2(R, L, Sbox);
}

#endif //DES_ENCODE_H
