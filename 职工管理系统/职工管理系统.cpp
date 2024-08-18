#include <iostream>

// 引用所有有关类的头文件
#include "Admin.h"

using namespace std;

int main(void)
{
    // 创建一个管理员
    Admin ad;
    while (1)
    {
        int op = 0;
        ad.printMenu();
        cout << "请输入您的选择:" << endl;
        cin >> op;
        switch (op)
        {
        case 0: // 退出系统
        {   
            ad.exitSystem();
            break;
        }
        case 1: // 添加职工
        {   
            ad.addWorker();
            break;
        }
        case 2: // 查找职工
        {   
            ad.findWorker();
            break;
        }
        case 3: // 打印职工
        {   
            ad.printInfo();
            break;
        }
        case 4: // 修改职工
        {   
            ad.alterWorker();
            break;
        }
        case 5: // 删除职工
        {   
            ad.delWorker();
            break;
        }
        case 6: // 排序职工
        {   
            ad.sortWorker();
            break;
        }
        case 7: // 清空职工
        {   
            ad.clearWorker();
            break;
        }
        default:
            break;
        }
        system("read -s -n1 -p 'Press any key to continue...\n' key");
        system("clear");
    }
    

    return 0;
}