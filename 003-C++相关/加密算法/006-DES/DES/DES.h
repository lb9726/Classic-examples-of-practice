#ifndef DES_H_INCLUDED
#define DES_H_INCLUDED


/*************************
 *DES的函数实现
 *用DES加密一个分组
 *用DES解密一个分组
 *读取置换表
*************************/

#include <iostream>
#include <cstdlib>
#include <QDebug>
#include <vector>
#include <fstream>
#include "Array.h"
using namespace std;

//密钥
Array key(64, "key");
Array useKey[16];

//置换表
Array IP(64, "IP"), VIP(64, "VIP");  //初始置换
Array Expend(48, "Expend");          //扩展换位
Array S[8];              //S置换表
Array P(32, "P");        //P置换表
Array PKey(56, "PKEY");  //密钥压缩换位表64-56
Array CKey(48, "CKey");  //密钥压缩换位表48-32

/****************************
 *DES函数实现
****************************/

void read_data()
{
    /*****************
     *读取置换表
     *计算逆置换表
    *****************/
    //读取初始置换
    ifstream myInput("IP.txt");
    for (int i = 0; i < 64; i++) {
        myInput >> IP[i];
        IP[i]--;
        VIP[IP[i]] = i;
    }
    myInput.close();

    //读取扩展换位盒
    myInput.open("E.txt");
    for (int i = 0; i < 48; i++) {
        myInput >> Expend[i];
        Expend[i]--;
    }
    myInput.close();

    //读取S盒
    myInput.open("S.txt");
    for (int i = 0; i < 8; i++) {
        S[i] = Array(64, "S");
        for (int j = 0; j < 64; j++)
            myInput >> S[i][j];
    }
    myInput.close();

    //读取P盒
    myInput.open("P.txt");
    for (int i = 0; i < 32; i++) {
        myInput >> P[i];
        P[i]--;
    }
    myInput.close();

    //读取密钥的奇偶校验比特去除表
    myInput.open("PKey.txt");
    for (int i = 0; i < 56; i++) {
        myInput >> PKey[i];
        PKey[i]--;
    }
    myInput.close();

    //读取密钥压缩换位盒
    myInput.open("CKey.txt");
    for (int i = 0; i < 48; i++) {
        myInput >> CKey[i];
        CKey[i]--;
    }
    myInput.close();

}


Array XOR(const Array &a1, const Array &a2)
{
    /*********************
     *两个数组异或
     *返回新数组
    *********************/
    Array res(a1.size(), "XOR");
    for (int i = 0; i < res.size(); i++)
        res[i] = a1.get(i) ^ a2.get(i);

    return res;
}


Array TBox(const Array &a, const Array &box)
{
    /*********************
     *换位盒
    **********************/
    Array res(box.size(), "transfer");
    for (int i = 0; i < res.size(); i++)
        res[i] = a.get(box.get(i));

    return res;
}

int two_to_ten(const string &s)
{
    /******************
     *二进制转10进制
    ******************/
    int power = 1;
    int sum = 0;
    for (int i = s.size()-1; i >= 0; i--) {
        sum += (s[i]-'0') * power;
        power *= 2;
    }
    return sum;
}

string ten_to_two(int n)
{
    /*******************
     *简易十进制转2进制
    *******************/
    string s = "0000";
    for (int i = 0, k = 8; i < 4; i++, k /= 2)
        if (n >= k) {
            s[i] = '1';
            n -= k;
        }
    return s;
}

/**************DES函数****************/
void make_key()
{
    /********************
     *用于生成16个密钥
    ********************/
    //去掉奇偶校验位
    Array key56(56, "key56");
    key56 = TBox(key, PKey);

    //生成16个密钥
    Array L = key56.sub(0, 27);
    Array R = key56.sub(28, 55);
    Array combineLR = Array(56, "make_key_temp");

    for (int i = 0; i < 16; i++)
    {
        //换位
        if (i == 0 || i == 1 || i == 8 || i == 15) {
            int tempL = L[0];
            int tempR = R[0];
            for (int j = 0; j < 27; j++) {
                L[j] = L[j+1];
                R[j] = R[j+1];
            }
            L[27] = tempL;
            R[27] = tempR;
        }
        else {
            int tempL0 = L[0];
            int tempL1 = L[1];
            int tempR0 = R[0];
            int tempR1 = R[1];
            for (int j = 0; j < 26; j++) {
                L[j] = L[j+2];
                R[j] = R[j+2];
            }
            L[26] = tempL0;
            R[26] = tempR0;
            L[27] = tempL1;
            R[27] = tempR1;
        }
        //合并
        for (int k = 0, j = 28; k < 28; k++, j++) {
            combineLR[k] = L[k];
            combineLR[j] = R[k];
        }
        useKey[i] = TBox(combineLR, CKey);
    }
}


Array SBox(const Array &arr)
{
    /************************
     *计算通过换位盒S后结果
    ************************/
    Array myInput(6, "SBoxmyInput");
    Array res(32, "SBoxRes");
    int resIndex = 0;
    for (int i = 0; i < 8; i++)
    {
        //获取6位比特
        int index = 0;
        int b = i * 6, e = i * 6 + 6;
        for (int j = b; j < e; j++)
            myInput[index++] = arr.get(j);
        //S盒处理
        string rowBit = "00";
        string colBit = "0000";
        rowBit[0] = myInput[0] + '0';
        rowBit[1] = myInput[5] + '0';
        colBit[0] = myInput[1] + '0';
        colBit[1] = myInput[2] + '0';
        colBit[2] = myInput[3] + '0';
        colBit[3] = myInput[4] + '0';
        int row = two_to_ten(rowBit);
        int col = two_to_ten(colBit);
        string temp = ten_to_two(S[i][row*16+col]);
        for (int i = 0; i < 4; i++)
            res[resIndex++] = temp[i] - '0';
    }

    return res;
}

Array encode_DES(Array p)
{
    ///初始置换
    p = TBox(p, IP);

    ///对每个分组进行DES加密
    Array L = p.sub(0, 31);  //保存分组左半部分
    Array R = p.sub(32, 63); //保存分组右半部分
    //16轮
    for (int j = 0; j < 16; j++)
    {
        Array nextL = R;        //下一个L
        R = TBox(R, Expend);    //扩展换位32 - 48
        R = XOR(R, useKey[j]);  //得到R ^ key
        R = SBox(R);            //通过S换位盒
        R = TBox(R, P);         //通过P换位盒
        R = XOR(L, R);          //与左边异或
        L = nextL;              //让左边等于变换前的右边
    }
    Array temp = R;
    R = L;
    L = temp;

    for (int k = 0, j = 32; k < 32; k++, j++) {
        p[k] = L[k];
        p[j] = R[k];
    }
    ///最终置换
    p = TBox(p, VIP);
    return p;
}

Array decode_DES(Array v)
{
    ///初始置换
    v = TBox(v, IP);

    ///对每个分组进行DES加密
    Array L = v.sub(0, 31);  //保存分组左半部分
    Array R = v.sub(32, 63); //保存分组右半部分
    //16轮
    for (int j = 15; j >= 0; j--)
    {
        Array nextL = R;        //下一个L
        R = TBox(R, Expend);    //扩展换位32 - 48
        R = XOR(R, useKey[j]);  //得到R ^ key
        R = SBox(R);            //通过S换位盒
        R = TBox(R, P);         //通过P换位盒
        R = XOR(L, R);          //与左边异或
        L = nextL;              //让左边等于变换前的右边
    }
    Array temp = R;
    R = L;
    L = temp;

    for (int k = 0, j = 32; k < 32; k++, j++) {
        v[k] = L[k];
        v[j] = R[k];
    }

    ///最终置换
    v = TBox(v, VIP);
    return v;
}

#endif // DES_H_INCLUDED
