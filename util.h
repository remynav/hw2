#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> intersection;

  //determine the larger set
  const std::set<T>* a = &s1;
  const std::set<T>* b = &s2;
  if(s1.size() > s2.size()){
    a = &s2;
    b = &s1;
  }

  typename std::set<T>::const_iterator it;
  for(it = a->begin(); it != a->end(); ++it){
    //check if current element is also in b
    if(b->find(*it)!= b->end()){
      intersection.insert(*it);
    }
  }

  return intersection;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  std::set<T> u;

  //insert all elements from s1
  typename std::set<T>::const_iterator it;
  for(it = s1.begin(); it != s1.end(); ++it){
    u.insert(*it);
  }

  //insert all elements from s2
  for(it = s2.begin(); it != s2.end(); ++it){
    u.insert(*it);
  }

  return u;

}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
