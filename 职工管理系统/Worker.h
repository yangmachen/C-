#pragma once
#include <iostream>
#include <string>
using namespace std;

class Worker
{
public:
    // 构造函数
    Worker();
    // 显示信息
    virtual void show_info() = 0;
    // 获取岗位名称
    virtual string get_dept_name() = 0;
    // 析构函数
    ~Worker();
    

    // 成员变量
    // 姓名
    string m_name;
    // 员工id
    int m_id;
    // 部门id
    int m_dept_id;

};