#ifndef BIT_STRING_H_INCLUDED
#define BIT_STRING_H_INCLUDED

/***************************
 *将字符串转为比特
***************************/



#include <string>
#include <vector>
#include <ctime>
#include <QDebug>
using namespace std;

vector<Array> string_to_bit(const string &s)
{
    /************************************
     *字符串->比特
     *比特是反过来的，如 1 = 10000000
     *而不是000000001
     *因为这样更好操作
    ************************************/
    ///计算分块数以及tail
    int blocks = s.size() / 8;
    int tail = 0;
    if (blocks * 8 < s.size()) {
        tail = s.size() - 8 * blocks;
        blocks++;
    }

    ///开始转换
    vector<Array> res;
    Array temp(64, "stringTobit");
    srand(time(NULL));
    //前64比特保存末尾长度
    srand(time(NULL));
    for (int i = 0; i < 64; i++)
    {
        if (i < 32) //0~31随机
            temp[i] = rand() % 2;
        else {      //32~63保存尾巴数值
            temp[i] = 1 & tail;
            tail = tail >> 1;
        }
    }
    res.push_back(temp);

    //将s分块处理，每块8个字符(每个字符8b)， s = blocks * 8char * 8bit
    for (int i = 0; i < blocks; i++)
    {
        int start = i * 8;  //每个块的起始处
        int index = 0;      //数组下标
        //处理单个块，8char
        for (int j = start; j < start+8; j++)
        {
            //超过末尾，随机补位
            if (j >= s.size())
            {
                for (int k = 0; k < 8; k++)
                    temp[index++] = rand() % 2;
                continue;
            }
            //将每个字符, 8bit
            int c = int(s[j]);
            for (int k = 0; k < 8; k++) {
                temp[index++] = 1 & c;;
                c = c >> 1;
            }
        }
        res.push_back(temp);
    }

    return res;
}


string bit_to_string(const vector<Array> &v)
{
    /**********************************
     *比特->字符串
    **********************************/
    string res;
    Array temp(64, "bitToString");

    ///计算尾巴数值
    int tail = 0;
    int power = 1;
    temp = v[0];
    for (int i = 32; i < 64; i++) {
        tail += temp[i] * power;
        power *= 2;
    }

    ///开始转换字符串
    //对每个分组进行处理
    for (int i = 1; i < v.size(); i++)
    {
        int end = 8;  //每个分组字符数
        if (v.size()-1 == i && tail != 0)
            end = tail;
        //转换分组
        for (int j = 0; j < end && j < 8; j++)
        {
            int c = 0;
            power = 1;
            int start = 8 * j;
            //转换每个字符
            for (int k = start; k < start+8; k++) {
                c += power * v[i].get(k);
                power *= 2;
            }
            res += char(c);
        }
    }
    return res;
}

#endif // BIT_STRING_H_INCLUDED
