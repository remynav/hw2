#include "book.h"
#include "util.h"
#include <sstream>

Book::Book(const std::string name, double price, 
            int qty, const std::string isbn, 
            const std::string author)
          : Product("book", name, price, qty), isbn_(isbn), author_(author){}

std::set<std::string> Book::keywords() const{
  std::set<std::string> keys = parseStringToWords(name_);
  std::set<std::string> authorNames = parseStringToWords(author_);
  
  //add all words from name, author, and isbn as keywords
  keys.insert(authorNames.begin(), authorNames.end());
  keys.insert(isbn_);
  return keys;
}

std::string Book::displayString() const{
  std::ostringstream os;
  os << name_ << "\nAuthor: " << author_ << " ISBN: " << isbn_ <<"\n" << price_ << " " << qty_ << " left.";
  return os.str();
}

void Book::dump(std::ostream& os) const{
  os <<"book\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << "\n";
}