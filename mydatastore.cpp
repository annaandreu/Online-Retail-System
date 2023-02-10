#include <cctype>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include "util.h"
#include "user.h"
#include "mydatastore.h"
#include "datastore.h"
#include "book.h"
#include "clothing.h"
#include "movie.h"

MyDataStore::MyDataStore(){

}

//deconstructor- delete all products and users you're allocating 
MyDataStore::~MyDataStore(){
//products	
	std::vector<Product*>::iterator allprods;
	for(allprods= products_.begin(); allprods != products_.end(); ++allprods){
		delete *allprods;
	}

//users
	std::vector<User*>::iterator allusers;
	for (allusers= users_.begin(); allusers != users_.end(); ++allusers){
		delete *allusers;
	}

}

void MyDataStore::addProduct(Product* p){
// add to products set	
	products_.push_back(p);

//get new product keywords 
	std::set<std::string> getkey = p->keywords();

//add keywords to keyword map
	  std::set<std::string>::iterator it;
		for(it = getkey.begin(); it != getkey.end(); ++it){
			
			if(keywordmap.find(*it) != keywordmap.end()){ // if keyword already validusernames,, add it to validusernameing group 
				(keywordmap.find(*it)->second).insert(p);
				//keywordmap[*it].insert(p);
			}

			else{ // if a new keyowrd,, add it to keyword map
				std::set<Product*> newkey;
				newkey.insert(p);
				keywordmap.insert(make_pair(*it, newkey));
				//keywordmap[*it] = newkey;
			}
		}

		
}

void MyDataStore::addUser(User* u){
//add to users set	
	users_.push_back(u);

}


/**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of search_terms for each term) while
     *  type 1 = OR search (union of search_terms for each term)
     */
// are terms given matching the product keywords
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){

	std::set<Product*> temp;
	std::vector<Product*> search_terms;

//if empty 
	if(terms.empty() == true){ 
		return search_terms;
	}

//AND search
	if(type == 0){ 
		std::set<Product*> search_and;

		for(unsigned int i=0; i < terms.size(); i++){ 
			if(search_and.empty() == true){ // if first term  -> add everything w term
				search_and = keywordmap[terms[i]];
			} 
			search_and = setIntersection(keywordmap[terms[i]], search_and); 
		}
		temp = search_and; // have placeholder 
	}

//OR search 
	else if(type == 1){ 
		std::set<Product*> search_or;

		for(unsigned int i=0; i < terms.size(); i++){ 
			search_or = setUnion(keywordmap[terms[i]], search_or); 
		}
		temp = search_or; //placeholder 2
	}

//create final search terms 
	std::set<Product*>::iterator it;
	for(it= temp.begin(); it!=temp.end(); ++it){ 
		search_terms.push_back(*it);
	}
	
	std::cout << std::endl;
	return search_terms;

}

     /* Reproduce the database file from the current Products and User values
     */
void MyDataStore::dump(std::ostream& ofile){
	ofile << "<products>" << '\n';
	
	std::vector<Product*>::iterator currprods;
	for(currprods= products_.begin(); currprods != products_.end(); ++currprods){
		(*currprods) -> dump(ofile); // dump all current products 
	}

	ofile << "</products>" << '\n' << "<users>" << '\n';
	
	std::vector<User*>::iterator currusers;
	for(currusers= users_.begin(); currusers != users_.end(); ++currusers){
		(*currusers) -> dump(ofile); // dump all current users
	}
	
	ofile << "</users>" << '\n';
}

void MyDataStore::addCart(std::string username, int prod_index, std::vector<Product*> hits){
	
	bool validusername = false;

	for(unsigned int i=0; i < users_.size(); i++){ 
		if(users_[i]->getName() == username){ // username exists
			validusername = true;
		}
	}

//if user doesnt exist 
	if(validusername == false){ 
		std::cout <<  "Invalid request" << std::endl;
		return;
	}

// if valid user has cart already 
	if(cartmap.find(username) != cartmap.end()){ 
		//push back in the specific user's cart bcs FIFO
		(cartmap.find(username)->second).push_back(hits[prod_index-1]); 
	}

//valid user doesn't have a cart
	else if (cartmap.find(username) == cartmap.end()){ 
		//make a new cart
		std::vector<Product*> new_cart; 
		new_cart.push_back(hits[prod_index-1]);
		cartmap.insert(make_pair(username, new_cart));
	}
	

}

void MyDataStore::viewCart(std::string username){
	bool validusername = false;
	
	for(unsigned int i=0; i< users_.size(); i++){ 
		if(users_[i]->getName() == username){
			validusername = true;
		}
	}

	if(validusername == false){ 
		std::cout << "Invalid username" << std::endl;
		return;
	}

//if valid user and valid cart
	if(cartmap.find(username) != cartmap.end()){ 
		//keep track of cuurent items in cart
		std::vector<Product*> curr_cart; 
		curr_cart = (cartmap.find(username))->second;
		
		//print cart out
		int count= 1;
		std::vector<Product*>::iterator it; 
		for(it= curr_cart.begin(); it!= curr_cart.end(); ++it){
			std::cout << "Item "<< count << std::endl << (*it)->displayString() << std::endl;
			count++;
		}
		
	}

	
}

void MyDataStore::buyCart(std::string username){
	bool validusername = false;
	
	for(unsigned int i=0; i< users_.size(); i++){
		if(users_[i]->getName() == username){
			validusername = true;
		}
	}
	if(validusername == false){ 
		std::cout << "Invalid username" << std::endl;
		return;
	}


	User* account;
	//find the user account
		for(unsigned int i=0; i<users_.size(); i++){ 
			if(users_[i]->getName() == username){
				account = users_[i];
			}
		}

//iterate through users cart 
	std::map<std::string,std::vector<Product*>> ::iterator it = cartmap.find(username); 
	std::vector<Product*> &usersCart = (it->second); 

	std::vector<Product*>::iterator curr_product = usersCart.begin();
	unsigned int prod_index = 0;

//while we dont finish products in cart
	while(prod_index < usersCart.size()){
		double price = usersCart[prod_index]->getPrice();
		
		//if user has enough money and there is enough in stock
		if((account->getBalance() >= price) && (usersCart[prod_index]->getQty()) > 0){ 
			account->deductAmount(price); //take $ out of account
			usersCart[prod_index]->subtractQty(1); // remove one item from stock, 	
			usersCart.erase(curr_product); //remove item from their cart
		}
		
		// if don't have enough money or not in stock
		else{ 
			prod_index++; // move to next product 
		}

		}
	

}



