/*
多映射示例：好友列表
大多数在线聊天程序运行用户有一个“好友列表”或朋友列表“。 聊天程序会对好友列表中列出的用户授予特权，如允许他们想用户发送主动消息。
为在线聊天程序实现好友列表的一种方法是把信息存储在一个multimap中。一个multimap可以存储所有用户的好友列表。容器中的每一项存储对应一个用户的好友。键是用户，值是好友。例如，如果这本书的两个作者都在对方的好友列表中，那么就会有形式如下的两项：”Nicholas Solter“映射至”Scott Kleper" 和 “Scott Kleper"映射至”Nicholas Solter“。multimap允许同一个键有多个值，因此一个用户可以有多个好友。以下是BuddyList类的定义
*/
#include <map>
#include <string>
#include <list>

using std::multimap;
using std::string;
using std::list;

class BuddyList
{
 public:
  BuddyList();

  //
  // Adds buddy as a friend of name.
  //
  void addBuddy(const string& name, const string& buddy);

  //
  // Removes buddy as a friend of name
  //
  void removeBuddy(const string& name, const string& buddy);

  //
  // Returns true if buddy is a friend of name.
  // Otherwise returns false.
  //
  bool isBuddy(const string& name, const string& buddy) const;

  //
  // Retrieves a list of all the friends of name.
  //
  list<string> getBuddies(const string& name) const;

 protected:
  multimap<string, string> mBuddies;
 private:
  // prevent assignment and pass-by-value
  BuddyList(const BuddyList& src);
  BuddyList& operator=(const BuddyList& rhs);
};
