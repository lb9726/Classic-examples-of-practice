#ifndef _HAPPY_
#define _HAPPY_

#include <QDebug>
#include <ctime>
#include "Array.h"
#include "DES.h"
#include "string_bit.h"
using namespace std;

/************************************************
 *函数声明

************************************************/
vector<Array> string_to_bit(const string &s);  //将字符串转换为比特
string bit_to_string(const vector<Array> &v);  //将比特转换为字符串
void  read_data();                             //读取置换表
Array encode_DES(Array v);                     //使用DES加密
Array decode_DES(Array v);                     //使用DES解密
Array XOR(const Array &a1, const Array &a2);   //异或

void init();     //初始化

Array VI(64, "VI");

//5种DES的实现
void init()
{
    key = string_to_bit("ABCDEFGH")[1];
    read_data();
    make_key();
    srand(time(NULL));
    for (int i = 0; i < 64; i++)
        VI[i] = rand() % 2;
}


vector<Array> encode_ECB(const string &s)
{
    vector<Array> res = string_to_bit(s);
    for (int i = 0; i < res.size(); i++)
        res[i] = encode_DES(res[i]);
    return res;
}

string  decode_ECB(vector<Array> v)
{
    for (int i = 0; i < v.size(); i++)
        v[i] = decode_DES(v[i]);
    return bit_to_string(v);
}

vector<Array> encode_CBC(const string &s)
{
    vector<Array> res = string_to_bit(s);
    //res[0] = encode_DES(res[0]);
    res[0] = encode_DES(XOR(res[0], VI));
    for (int i = 1; i < res.size(); i++)
        res[i] = encode_DES(XOR(res[i], res[i-1]));
    return res;
}

string  decode_CBC(vector<Array> v)
{
    for (int i = v.size()-1; i >= 1; i--) {
        v[i] = decode_DES(v[i]);
        v[i] = XOR(v[i], v[i-1]);
    }
    //v[0] = decode_DES(v[0]);
    v[0] = decode_DES(XOR(v[0], VI));
    return bit_to_string(v);
}

vector<Array> encode_CFB(const string &s)
{
    vector<Array> res = string_to_bit(s);
    Array vi = VI;

    //处理每一个字符
    Array j;
    Array p;
    Array c;

    for (int i = 0; i < res.size(); i++)
    {
        int index = 0;
        //处理每个字符
        for (int k = 0; k < 8; k++) {
            j = encode_DES(vi).sub(0, 7);             //取DES处理的vi的前8个比特
            p = res[i].sub(index, index+7);           //获取明文字符的比特
            c = XOR(j, p);                            //异或得到密文
            for (int m = 0; m < 8; m++)               //将密文放入res
                 res[i][index++] = c[m];
            if (i == 0 && index == 8)    //第一轮不用处理
                continue;
            for (int m = 0; m <= 55; m++)             //移位
                vi[m] = vi[m+8];
            for (int m = 0; m < 8; m++)               //56~63位为密文
                vi[m+56] = c[m];
        }
    }
    return res;
}

string  decode_CFB(vector<Array> v)
{
    Array vi = VI;
    //处理每一个字符
    Array j;
    Array p;
    Array c;
    for (int i = 0; i < v.size(); i++)
    {
        int index = 0;
        for (int k = 0; k < 8; k++) {
            j = encode_DES(vi).sub(0, 7);
            c = v[i].sub(index, index+7);
            p = XOR(j, c);
            for (int m = 0; m < 8; m++)
                v[i][index++] = p[m];
            if (i == 0 && index == 8)
                continue;
            for (int m = 0; m <= 55; m++)  //移位
                vi[m] = vi[m+8];
            for (int m = 0; m < 8; m++)
                vi[m+56] = c[m];
        }
    }
    return bit_to_string(v);
}

vector<Array> encode_OFB(const string &s)
{
    vector<Array> res = string_to_bit(s);
    Array vi = VI;

    //处理每一个字符
    Array j;
    Array p;
    Array c;

    for (int i = 0; i < res.size(); i++)
    {
        int index = 0;
        //处理每个字符
        for (int k = 0; k < 8; k++) {
            j = encode_DES(vi).sub(0, 7);             //取DES处理的vi的前8个比特
            p = res[i].sub(index, index+7);           //获取明文字符的比特
            c = XOR(j, p);                            //异或得到密文
            for (int m = 0; m < 8; m++)               //将密文放入res
                 res[i][index++] = c[m];
            if (i == 0 && index == 8)    //第一轮不用处理
                continue;
            for (int m = 0; m <= 55; m++)             //移位
                vi[m] = vi[m+8];
            for (int m = 0; m < 8; m++)               //56~63位为密文
                vi[m+56] = j[m];
        }
    }
    return res;
}

string  decode_OFB(vector<Array> v)
{
    Array vi = VI;
    //处理每一个字符
    Array j;
    Array p;
    Array c;
    for (int i = 0; i < v.size(); i++)
    {
        int index = 0;
        for (int k = 0; k < 8; k++) {
            j = encode_DES(vi).sub(0, 7);
            c = v[i].sub(index, index+7);
            p = XOR(j, c);
            for (int m = 0; m < 8; m++)
                v[i][index++] = p[m];
            if (i == 0 && index == 8)
                continue;
            for (int m = 0; m <= 55; m++)  //移位
                vi[m] = vi[m+8];
            for (int m = 0; m < 8; m++)
                vi[m+56] = j[m];
        }
    }
    return bit_to_string(v);
}

/******************
 *计数器
 *让vi += 1
******************/
void counter(Array &vi)
{
    vi[vi.size()-1] += 1;
    for (int i = vi.size()-1; i >= 1; i--) {
        if (vi[i] > 1) {
            vi[i-1] += 1;
            vi[i] = 0;
        }
    }
    if (vi[0] > 1)
        vi[0] = 0;
}

vector<Array> encode_CTR(const string &s)
{
    vector<Array> res = string_to_bit(s);
    Array vi = VI;

    //处理每一个字符
    Array j;
    Array p;
    Array c;

    for (int i = 0; i < res.size(); i++)
    {
        int index = 0;
        //处理每个字符
        for (int k = 0; k < 8; k++) {
            counter(vi);
            j = encode_DES(vi).sub(0, 7);             //取DES处理的vi的前8个比特
            p = res[i].sub(index, index+7);           //获取明文字符的比特
            c = XOR(j, p);                            //异或得到密文
            for (int m = 0; m < 8; m++)               //将密文放入res
                 res[i][index++] = c[m];

        }
    }
    return res;
}

string  decode_CTR(vector<Array> v)
{
    Array vi = VI;
    //处理每一个字符
    Array j;
    Array p;
    Array c;
    for (int i = 0; i < v.size(); i++)
    {
        int index = 0;
        for (int k = 0; k < 8; k++) {
            counter(vi);
            j = encode_DES(vi).sub(0, 7);
            c = v[i].sub(index, index+7);
            p = XOR(j, c);
            for (int m = 0; m < 8; m++)
                v[i][index++] = p[m];
        }
    }
    return bit_to_string(v);
}

#endif
