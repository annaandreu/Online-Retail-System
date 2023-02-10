#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <string>
#include <iostream>
#include <set>

class Clothing: public Product{
	
	public: 
			Clothing(const std::string category, const std::string name, double price, int qty, std::string brand, std::string size);
			virtual ~Clothing();

			virtual std::set<std::string> keywords() const;
			virtual std::string displayString() const;
			virtual void dump(std::ostream& os) const;


	private:  
		std::string brand_;
		std::string size_;


	
};
#endif