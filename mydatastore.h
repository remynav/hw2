#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include <vector>

class MyDataStore : public DataStore{
public:
  ~MyDataStore() override;

  void addProduct(Product* p) override;
  void addUser(User* u) override;
  std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
  void dump(std::ostream& ofile) override;

  User* getUser(const std::string& username) const;
  void addToCart(const std::string& username, Product* p);
  void viewCart(const std::string& username, std::ostream& os) const;
  void buyCart(const std::string& username);

private:
  std::vector<Product*> products_;
  std::vector<User*> users_;
  
  // map of keywords to corresponding products
  std::map<std::string, std::set<Product*>> prodPerKeyWord;
  // map of username to items in cart
  std::map<std::string, std::vector<Product*>> carts_;
};

#endif