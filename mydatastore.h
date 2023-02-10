#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "product.h"
#include "datastore.h"
#include <string>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

class MyDataStore: public DataStore{
	
	public: 
			MyDataStore();
			virtual ~MyDataStore();


			virtual void addProduct(Product* p);
			virtual void addUser(User* u);
			virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);
			virtual void dump(std::ostream& ofile);

		//edit- add cart functions 
			void addCart(std::string username, int index, std::vector<Product*> hits);
			void viewCart(std::string username);
			void buyCart(std::string username);

/****      																																			****/
			
			std::vector<Product*> products_;
			std::vector<User*> users_; 
	

		std::map<std::string,std::set<Product*>> keywordmap;
		std::map<std::string,std::vector<Product*>> cartmap;
		//std::map<std::string, User*> usermap; 
		//std::vector<Product*> search_results;

//
		



	
};
#endif