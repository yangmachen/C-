#include "Employee.h"

Employee::Employee(int id, string name, int dept_id)
{
    m_id = id;
    m_name = name;
    m_dept_id = dept_id;
}
// 显示信息
void Employee::show_info()
{
    cout << "职工编号: " << m_id
        << "\t姓名: " << m_name
        << "\t岗位: " << get_dept_name()
        << "\t职责: 完成经理交给的任务" << endl;
}
// 获取岗位名称
string Employee::get_dept_name()
{
    return string("普通员工");
}

Employee::~Employee()
{

}