#include "Admin.h"
using namespace std;


// 构造函数
Admin::Admin()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    // 第一种情况：文件不存在
    if(!ifs.is_open())
    {
        // 初始化变量
        this->m_num = 0;
        this->m_workers = NULL;
        this->m_isEmpty = true;

        cout << "文件不存在" << endl;
        return;
    }
    // 第二种情况：文件为空
    char ch;
    ifs >> ch;
    if(ifs.eof())
    {
        // 初始化变量
        this->m_num = 0;
        this->m_workers = NULL;
        this->m_isEmpty = true;

        cout << "文件为空" << endl;
        ifs.close();
        return;
    }
    ifs.close();
    // 第三种情况：文件存在且不为空
    // 1. 获取职工人数
    this->m_isEmpty = false;
    this->m_num = this->get_worker_num();
    this->init_workers();
}

void Admin::init_workers()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    // 创建空间
    Worker **newSpace = new Worker*[this->m_num];
    if(newSpace == NULL)
    {
        cout << "空间分配失败" << endl;
        return;
    }
    for(int i = 0; i < this->m_num; i++)
    {
        int id;
        string name;
        int did;
        ifs >> id >> name >> did;
        switch (did)
        {
        case 1: // 普通职工
        {
            newSpace[i] = new Employee(id, name, did);
            break;
        }
        case 2: // 经理
        {
            newSpace[i] = new Manager(id, name, did);
            break;
        }
        case 3: // 老板
        {
            newSpace[i] = new Boss(id, name, did);
            break;
        }
        default:
            break;
        }
    }
    this->m_workers = newSpace;
}


// 获取职工数量 默认文件存在
int Admin::get_worker_num()
{
    int count = 0;
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int did;
    while(ifs>>id && ifs>>name && ifs>>did)
    {
        count++;
    }
    ifs.close();
    return count;
}


void Admin::printMenu()
{
    cout    << "********欢迎使用职工管理系统********" << endl
            << "**********0. 退出职工系统**********" << endl
            << "**********1. 添加职工信息**********" << endl
            << "**********2. 查找职工信息**********" << endl
            << "**********3. 打印职工信息**********" << endl
            << "**********4. 修改职工信息**********" << endl
            << "**********5. 删除职工信息**********" << endl
            << "**********6. 排序职工信息**********" << endl
            << "**********7. 清空职工信息**********" << endl
            << endl;
}

void Admin::exitSystem()
{
    cout << "欢迎下次使用" << endl;
    // 按任意键继续
    system("read -s -n1 -p 'Press any key to continue...\n' key");
    exit(0);
}

void Admin::addWorker()
{
    int add_num;
    cout << "请输入要添加的职工数量:" << endl;
    cin >> add_num;
    
    if(add_num > 0)
    {
        // 开辟新空间
        int total_num = this->m_num + add_num;
        Worker **newSpace = new Worker*[total_num];
        // 复制原有的
        if(newSpace != NULL)
        {
            // 复制原有的空间
            for(int i = 0; i < this->m_num; i++)
            {
                newSpace[i] = this->m_workers[i];
            }
            // 添加新空间
            for(int i = 0; i < add_num; i++)
            {
                int id;
                string name;
                int did;
                cout << "需要添加的第 " << i + 1 << " 名职工的职工编号为：" << endl;
                cin >> id;
                cout << "姓名为：" << endl;
                cin >> name;
                cout << "职工编号为：" << endl
                    << "1 普通职工 " << endl
                    << "2 经理" << endl
                    << "3 老板" << endl;
                cin >> did;
                // 判断did
                Worker *wk = NULL;
                switch (did)
                {
                case 1:
                {
                    // 创建普通员工
                    wk = new Employee(id, name, 1);
                    break;
                }
                case 2:
                {
                    // 创建经理
                    wk = new Manager(id, name, 2);
                    break;
                }
                case 3:
                {
                    // 创建老板
                    wk = new Boss(id, name, 3);
                    break;
                }
                default:
                    break;
                }
                if(wk == NULL)
                {
                    cout << "分配空间失败或您的输入有误！" << endl;
                }
                else
                {
                    // 添加进去
                    newSpace[this->m_num + i] = wk;
                    this->m_isEmpty = false;
                    cout << "添加成功！" << endl;
                }
            }
            // 更新新空间
            delete[] this->m_workers;
            this->m_workers = newSpace;
            this->m_num = total_num;
            this->save();
        }
        else
        {
            cout << "无法分配空间" << endl;
        }

    }
    else
    {
        cout << "您的输入有误！" << endl;
    }

}

void Admin::printInfo()
{
    // 判空
    if(this->m_isEmpty)
    {
        cout << "文件为空或文件不存在" << endl;
        return;
    }
    else
    {
        cout << "职工总数：" << this->m_num << endl;
        // 挨个打印
        for(int i = 0; i < this->m_num; i++)
        {
            this->m_workers[i]->show_info();
        }
    }
}

void Admin::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    // 判断文件是否打开
    if(ofs.is_open())
    {
        // 将信息写入文件中
        for(int i = 0; i < this->m_num; i++)
        {
            ofs << this->m_workers[i]->m_id << " "
                << this->m_workers[i]->m_name << " "
                << this->m_workers[i]->m_dept_id << endl;
        }
    }
    else
    {
        cout << "文件打开失败，保存失败" << endl;
    }
}

// 查找职工是否存在，存在放回下标(职工编号版) 失败返回-1
int Admin::isExitId(int id)
{
    if(this->m_isEmpty)
    {
        cout << "文件不存在或文件为空！" << endl;        
        return -1;
    }
    // 遍历寻找
    for(int i = 0; i < this->m_num; i++)
    {
        if(this->m_workers[i]->m_id == id)
        {
            return i;
        }
    }
    return -1;
}

// 查找职工是否存在，存在返回下标（职工姓名版） 失败返回-1
int Admin::isExitName(string name)
{
    if(this->m_isEmpty)
    {
        cout << "文件不存在或文件为空！" << endl;        
        return -1;
    }
    // 遍历寻找
    for(int i = 0; i < this->m_num; i++)
    {
        if(this->m_workers[i]->m_name == name)
        {
            return i;
        }
    }
    return -1;
}

// 删除职工
void Admin::delWorker()
{
    int id;
    cout << "请输入要删除的职工的编号：" << endl;
    cin >> id;
    int index = this->isExitId(id);
    if(index == -1)
    {
        cout << "查无此人" << endl;
        return;
    }

    // 释放原来的空间
    delete this->m_workers[index];
    // 将后面的前移
    for(int i = index; i < this->m_num - 1; i++)
    {
        this->m_workers[i] = this->m_workers[i + 1];
    }
    this->m_num--;
    if(this->m_num == 0)
    {
        this->m_isEmpty = true;
    }
    cout << "删除成功！" << endl;
    this->save();
}

// 查找职工 输出职工信息
void Admin::findWorker()
{
    int op;
    cout << "1 根据职工id查找" << endl
        << "2 根据职工姓名查找" << endl;
    cin >> op;
    if(op == 1)
    {
        int id;
        cout << "请输入职工id:" << endl;
        cin >> id;
        int index = 0;
        index = this->isExitId(id);
        if(index == -1)
        {
            cout << "查无此人" << endl;
        }
        else
        {
            // 输出所有职工编号为id的人
            for(int i = 0; i < this->m_num; i++)
            {
                if(this->m_workers[i]->m_id == id)
                {
                    this->m_workers[i]->show_info();
                }
            }
        }
    }
    else if(op == 2)
    {
        string name;
        cout << "请输入职工姓名:" << endl;
        cin >> name;
        int index = 0;
        index = this->isExitName(name);
        if(index == -1)
        {
            cout << "查无此人" << endl;
        }
        else
        {
            // 输出所有职工姓名为name的人
            for(int i = 0; i < this->m_num; i++)
            {
                if(this->m_workers[i]->m_name == name)
                {
                    this->m_workers[i]->show_info();
                }
            }
        }
    }
    else
    {
        cout << "您的输入有误" << endl;
    }
}

void Admin::alterWorker()
{
    int id;
    cout << "请输入要修改的职工的编号：" << endl;
    cin >> id;
    int index = this->isExitId(id);
    if(index == -1)
    {
        cout << "查无此人" << endl;
        return;
    }

    int newId;
    string newName;
    int newDid;
    cout << "请输入新的职工id:" << endl;
    cin >> newId;
    cout << "请输入新的职工姓名:" << endl;
    cin >> newName;
    cout << "请输入新的职工岗位:" << endl;
    cout << "1 普通职工" << endl
        << "2 经理" << endl
        << "3 老板" << endl;
    cin >> newDid;
    // 修改
    Worker *newWk = NULL;
    switch (newDid)
    {
    case 1:
    {
        newWk = new Employee(newId, newName, newDid);
        break;
    }
    case 2:
    {
        newWk = new Manager(newId, newName, newDid);
        break;
    }
    case 3:
    {
        newWk = new Boss(newId, newName, newDid);
        break;
    }
    default:
        break;
    }
    if(newWk == NULL)
    {
        cout << "空间分配失败或输入有误！" << endl;
        return;
    }
    else
    {
        // 释放原来的空间
        delete this->m_workers[index];
        this->m_workers[index] = newWk;
        cout << "修改成功！" << endl;
    }

    this->save();
}

bool cmp1(Worker* wk1, Worker* wk2)
{
    return wk1->m_id < wk2->m_id;
}

bool cmp2(Worker* wk1, Worker* wk2)
{
    return wk1->m_id > wk2->m_id;
}

void Admin::sortWorker()
{
    if(this->m_isEmpty)
    {
        cout << "文件不存在或者文件为空！" << endl;
        return;
    }
    cout << "1 升序" << endl
        << "2 降序" << endl;
    int op;
    cin >> op;
    if(op == 1)
    {
        sort(this->m_workers, this->m_workers + this->m_num, cmp1);
    }
    else if(op == 2)
    {
        sort(this->m_workers, this->m_workers + this->m_num, cmp2);
    }
    else
    {
        cout << "输入有误！" << endl;
    }
}


void Admin::clearWorker()
{
    cout << "请确认是否清空？" << endl
        << "1 确定" << endl
        << "2 返回" << endl;
    int op;
    cin >> op;
    if(op == 1)
    {
        // 清空文件
        ofstream ofs;
        ofs.open(FILENAME, ios::trunc);
        // 清空内存
        if(this->m_workers != NULL)
        {
            for(int i = 0; i < this->m_num; i++)
            {
                delete this->m_workers[i];
            }
            delete[] this->m_workers;
            this->m_workers = NULL;
        }
        this->m_num = 0;
        this->m_isEmpty = true;
        cout << "清空完成！" << endl;
    }
    else
    {
        return;
    }
}




Admin::~Admin()
{
    if(this->m_workers != NULL)
    {
        for(int i = 0; i < this->m_num; i++)
        {
            if(this->m_workers[i] != NULL)
            {
                delete this->m_workers[i];
            }
        }
        delete[] this->m_workers;
    }

}