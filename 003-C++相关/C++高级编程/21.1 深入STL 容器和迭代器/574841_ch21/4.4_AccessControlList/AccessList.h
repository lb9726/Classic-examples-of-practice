/*
集合示例： 访问控制列表
在计算机系统上实现基本安全的一种做法是通过访问控制列表。系统上的每个实体（如一个文件或一个设备）都有相应的允许访问该实体的用户列表。用户一般只能由有特殊权限的用户从一个实体的许可列表中增加和删除用户。在内部，set容器提供了一种很不错的方法来表示访问控制列表。可以对应每个实体有一个set，其中包括允许访问该实体的所有用户名。下面是一个简单的访问控制列表的类定义。
*/
#include <set>
#include <string>
#include <list>
using std::set;
using std::string;
using std::list;

class AccessList
{
 public:
  AccessList() {}

  //
  // Adds the user to the permissions list.
  //
  void addUser(const string& user);

  //
  // Removes the user from the permissions list.
  //
  void removeUser(const string& user);

  //
  // Returns true if user is in the permissionns list.
  //
  bool isAllowed(const string& user) const;

  //
  // Returns a list of all the users who have permissions.
  //
  list<string> getAllUsers() const;

 protected:
  set<string> mAllowed;
};
