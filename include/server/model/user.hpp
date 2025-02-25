#ifndef USER_HPP
#define USER_HPP

#include <string>
using namespace std;

#include "public.hpp"

// User类：表示一个用户对象 ORM类（对象映射MAP）
class User
{
public:
    // 默认构造函数
    User(int id = -1, string name = "", string pwd = "", string state = "offline")
    {
        this->id = id;
        this->name = name;
        this->password = pwd;
        this->state = state;
   }

   void setId(int id)
   {
       this->id = id;
   }
   void setName(string name) {this->name = name;}
   void setPwd(string pwd) { this->password = pwd; }
   void setState(string state){this->state = state;}

   int getId() { return this->id; }
   string getName(){ return this->name; }
   string getPwd() {return this->password;}
   string getState() {return this->state;}
   private:
   int id;
   string name;
   string password;
   string state;
};

#endif