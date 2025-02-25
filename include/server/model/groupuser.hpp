#ifndef GROUPUSER_H
#define GROUPUSER_H

#include "user.hpp"

//群组用户，比普通用户多了一个角色属性(管理员、创建者等)
class GroupUser : public User
{
public:
    void setRole(string role)
    {
        this->role = role;
    }

    string getRole()
    {
        return this->role;
    }

private:
    string role;
};

#endif