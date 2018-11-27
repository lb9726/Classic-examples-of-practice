#include "data.h"


int DealAddWorker(WORKERS worker);            //添加图书 ---logic 层函数
void ChangeWorker(WORKERS worker);            //更改员工信息
void DeleteWorker(WORKERS worker);            //删除员工信息
                                              //4-兼职技术人员，5-兼职推销员
void ShowJZ();                                //显示
void ChangeJZ();                              //更改

int ManagerAddWorker(WORKERS worker);         //经理添加员工时过滤  rank = 4
void ManagerChangeWorker(WORKERS worker);     //经理更改员工信息
void ManagerDeleteWorker(WORKERS worker);     //经理删除员工信息
int XSManagerAddWorker(WORKERS worker);       //3-销售经理添加员工时过滤  rank = 5
void XSManagerChangeWorker(WORKERS worker);   //3-销售经理更改员工信息
void XSManagerDeleteWorker(WORKERS worker);   //经理删除员工信息


