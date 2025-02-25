#include "json.hpp"
#include <iostream>
using json=nlohmann::json;
using std::endl;
using std::cout;

#include <vector>
#include <map>
//json序列化示例
void func1(){
    json js;
    js["msg_type"]= 2;
    js["name"] = "zhang san";
    js["from"] = "li si";
    js["msg"]="hello what are you doing now?";
    cout<<js<<endl;
}

int main(){
    func1();
    return 0;
}