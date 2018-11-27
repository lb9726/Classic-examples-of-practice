#include "BuddyList.h"
using namespace std;

BuddyList::BuddyList()
{
}

void BuddyList::addBuddy(const string& name, const string& buddy)
{
  // Make sure this buddy isn't already there.
  // We don't want to insert an identical copy of the
  // key/value pair.
  if (!isBuddy(name, buddy)) {
    mBuddies.insert(make_pair(name, buddy));
  }
}

void BuddyList::removeBuddy(const string& name, const string& buddy)
{
  // declare two iterators into the map
  multimap<string, string>::iterator start, end;

  // Obtain the beginning and end of the range of elements with
  // key name. Use both lower_bound() and upper_bound() to demonstrate
  // their use. Otherwise, could just call equal_range().
  start = mBuddies.lower_bound(name);
  end = mBuddies.upper_bound(name); 
  
  // iterate through the elements with key name looking
  // for a value buddy
  for (start; start != end; ++start) {
    if (start->second == buddy) {
      // We found a match! Remove it from the map
      mBuddies.erase(start);
      break;
    }
  }
}

bool BuddyList::isBuddy(const string& name, const string& buddy) const
{
  // declare two iterators into the map
  multimap<string, string>::const_iterator start, end;
  // obtain the beginning and end of the range of elements with
  // key name. Use both lower_bound() and upper_bound() to demonstrate
  // their use. Otherwise, could just call equal_range().
  start = mBuddies.lower_bound(name);
  end = mBuddies.upper_bound(name);

  // iterate through the elements with key name looking
  // for a value buddy. If there are no elements with key name,
  // start equals end, so the loop body doesn't execute.
  for (start; start != end; ++start) {
    if (start->second == buddy) {
      // We found a match!
      return (true);
    }
  }
  // No matches
  return (false);
}

list<string> BuddyList::getBuddies(const string& name) const
{
  // Create a variable to store the pair of iterators.
  pair<multimap<string, string>::const_iterator,
    multimap<string, string>::const_iterator> its;

  // Obtain the pair of iterators marking the range containing
  // elements with key name
  its = mBuddies.equal_range(name);

  // Create a list with all the names in the range
  // (all the buddies of name).
  list<string> buddies;
  for (its.first; its.first != its.second; ++its.first) {
    buddies.push_back((its.first)->second);
  }

  return (buddies);
}
/*
equal_range函数其实是upper_bound函数+lower_bound函数构成的，它的作用是求一个有序的容器中 与key相等元素的上界与下界
equal_range的返回值是两个迭代器
*/
