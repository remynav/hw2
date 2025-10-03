#include "mydatastore.h"
#include "util.h"
#include <algorithm>

MyDataStore::~MyDataStore()
{
  for(Product* p: products_){
    delete p;
  }
  for(User* u: users_){
    delete u;
  }
}

void MyDataStore::addProduct(Product* p){
  if(!p) return;
  products_.push_back(p);
  
  //adds the product to related keywords
  std::set<std::string> pKeys = p->keywords();
  for(const std::string& k : pKeys){
    prodPerKeyWord[k].insert(p);
  }
}

void MyDataStore::addUser(User* u){
  users_.push_back(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  std::vector<Product*> result;
  if(terms.empty()){
    return result;
  }

  for(std::string& t : terms){
    t = convToLower(t);
  }

  //results for the first given word
  std::set<Product*> currentResults;
  std::map<std::string,std::set<Product*>>::iterator it = prodPerKeyWord.find(terms[0]); 
  if(it != prodPerKeyWord.end()){
    currentResults = it->second;
  }

  //go through the rest of the words and update currentResults
  for(size_t i = 1; i <terms.size(); i++){
    std::set<Product*> next;
    std::map<std::string,std::set<Product*>>::iterator it2 = prodPerKeyWord.find(terms[i]); 
    if( it2 != prodPerKeyWord.end()){
      next = it2->second;
    }
    //AND - keep items only in both sets
    if(type == 0){
      currentResults = setIntersection(currentResults, next);
    }
    //OR - keep items from all sets
    else{
      currentResults = setUnion(currentResults, next);
    }
  }

  result.assign(currentResults.begin(), currentResults.end());
  return result;

}

void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>\n";
  for(Product* p : products_){
    p->dump(ofile);
  }
  ofile << "</products>\n";

  ofile << "<users>\n";
  for(User* u : users_){
    u->dump(ofile);
  }
  ofile << "</users>\n";
}

User* MyDataStore::getUser(const std::string& username) const{
  std::string key = convToLower(username); 
  for(User* u : users_){
    if(convToLower(u->getName()) == key) {
      return u;
    }
  }
  return nullptr;
}

void MyDataStore::addToCart(const std::string& username, Product* p){
  if ( p == 0) return;
  User* u = getUser(username);
  if ( u == nullptr) return;
  std::string key = convToLower(username);
  carts_[key].push_back(p);
}

void MyDataStore::viewCart(const std::string& username, std::ostream& os) const {
  User* u = getUser(username);
  if(u == 0){
    os << "Invalid username" << std::endl;
    return;
  }
  
  std::string key = convToLower(username);
  std::map<std::string, std::vector<Product*>>::const_iterator it = carts_.find(key);
  if( it == carts_.end()) return;

  const std::vector<Product*>& cart = it->second;
  for(size_t i = 0; i <cart.size(); i++){
    os << "Item " << (i+1) << ":" << std::endl;
    os << cart[i]->displayString() << std::endl << std::endl;
  }
}

void MyDataStore::buyCart(const std::string& username){
  User* u = getUser(username);
  if ( u == 0){
    std::cout << "Invalid username" << std::endl;
    return;
  }

  std::string key = convToLower(username);
  std::vector<Product*>& cart = carts_[key];
  std::vector<Product*> remaining;

  //check if you can buy each item, and then buy
  for(size_t i = 0; i < cart.size(); i++){
    Product* p = cart[i];
    if(p->getQty() > 0 && u->getBalance() >= p->getPrice()) {
      u->deductAmount(p->getPrice());
      p->subtractQty(1);
    }
    else{
      remaining.push_back(p);
    }
  }
  //items left in cart
  cart.swap(remaining);
}