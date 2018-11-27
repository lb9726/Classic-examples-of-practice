//
// Created by 徐伟毅 on 2017/3/28.
//

#include "encode.h"

int main() {

    int L[32], R[32], LafterF[32], RafterF[32], C[28], D[28];
    int binaryplain[64], binarykey[64], binarycipher[64], expend[48], FKey[48], Sbox[32];
    char plain[8] = {'c','o','m','p','u','t','e','r'}, key[8] = {'s','e','c','u','r','i','t','y'}, cipher[16];

    cout << "本程序演示了经典的 DES 加密算法，示例以\"computer\"为明文，\"security\"为密钥，加密后的结果以十六进制输出如下：\n\n";

    CharToBinary(plain, binaryplain);       //明文转64位二进制
    CharToBinary(key, binarykey);           //密钥转64位二进制
    IP(binaryplain);                        //明文置换
    IPChoice_1(binarykey, C, D);            //密文置换选择1

    for (int i = 0; i < 64; ++i) {          //明文分组
        if (i < 32) {
            L[i] = binaryplain[i];
        } else {
            R[i-32] = binaryplain[i];
        }
    }

    //16轮加密
    for (int i = 0; i < 15; ++i) {      //前15轮加密，左右交换
        for (int j = 0; j < 32; ++j) {          //右半部分交换到左半部分
            LafterF[j] = R[j];
        }
        IPChoice_2(C, D, FKey, MoveLeft_Table);        //循环左移 + 置换选择2，生成轮密钥
        Fencode(R, L, expend, FKey, Sbox);      //生成右半部分
        for (int k = 0; k < 32; ++k) {
            L[k] = LafterF[k];
        }
    }
    for (int l = 0; l < 32; ++l) {      //第16轮加密，左右不交换
        RafterF[l] = R[l];
    }
    IPChoice_2(C, D, FKey, MoveLeft_Table);
    Fencode(R, L, expend, FKey, Sbox);
    for (int m = 0; m < 32; ++m) {
        LafterF[m] = R[m];
    }

    for (int n = 0; n < 64; ++n) {      //密文合并
        if (n < 32) {
            binarycipher[n] = LafterF[n];
        } else {
            binarycipher[n] = RafterF[n-32];
        }
    }

    IP_1(binarycipher);                 //密文逆置换
    BinaryToHexadecimal(binarycipher, cipher);      //二进制密文转换成十六进制密文，并输出

    return 0;
}
