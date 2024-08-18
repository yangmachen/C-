#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Worker.h"
#include "Manager.h"
#include "Employee.h"
#include "Boss.h"

#define FILENAME "worker.txt"

// 管理员类
class Admin
{
public:
    // 构造函数
    Admin();

    // 输出菜单
    void printMenu();

    // 退出系统
    void exitSystem();

    // 添加员工
    void addWorker();

    // 打印职工
    void printInfo();

    // 保存职工信息到文件中
    void save();

    // 初始时获取职工人数
    int get_worker_num();

    // 初始化职工(这个时候已经获取职工数量)
    void init_workers();

    // 删除职工
    void delWorker();

    // 查找职工是否存在，存在放回下标(职工编号版) 失败返回-1
    int isExitId(int id);

    // 查找职工是否存在，存在返回下标（职工姓名版） 失败返回-1
    int isExitName(string name);

    
    void findWorker();

    void alterWorker();

    void sortWorker();

    void clearWorker();


    // 析构函数
    ~Admin();

    // 职工数量
    int m_num;
    // 职工
    Worker **m_workers;
    // 判空
    bool m_isEmpty;
};