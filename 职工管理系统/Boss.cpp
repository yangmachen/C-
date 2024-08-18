#include "Boss.h"

Boss::Boss(int id, string name, int dept_id)
{
    m_id = id;
    m_name = name;
    m_dept_id = dept_id;
}
// 显示信息
void Boss::show_info()
{
    cout << "职工编号: " << m_id
        << "\t姓名: " << m_name
        << "\t岗位: " << get_dept_name()
        << "\t职责: 处理公司所有的事务" << endl;
}
// 获取岗位名称
string Boss::get_dept_name()
{
    return string("老板");
}

Boss::~Boss()
{

}