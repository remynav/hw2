#include "clothing.h"
#include "util.h"
#include <sstream>

Clothing::Clothing(const std::string& name, double price, int qty, const std::string& size, const std::string&brand)
    : Product("clothing", name, price, qty), size_(size), brand_(brand){}

std::set<std::string> Clothing::keywords() const{
  std::set<std::string> keys = parseStringToWords(name_);
  std::set<std::string> brandNames = parseStringToWords(brand_);
  
  //add all words from brandNames
  keys.insert(brandNames.begin(), brandNames.end());
  return keys;
}

std::string Clothing::displayString() const{
  std::ostringstream os;
  os << name_ << "\nSize: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left.";
  return os.str();
}

void Clothing::dump(std::ostream& os) const{
  os << "clothing\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n";
}