#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include "util.h"
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, 
std::string brand, std::string size):
Product(category, name, price, qty),
brand_(brand),
size_(size)
{

}

Clothing::~Clothing(){

}

/**
     * Returns the appropriate keywords that this product should be associated with
     */
std::set<std::string> Clothing::keywords() const{
	set<std::string> temp = parseStringToWords(name_);
	set<std::string> temp2 = parseStringToWords(brand_);

	set<std::string> key= setUnion(temp, temp2);
	//key.insert(size_);

	return key;

}

 std::string Clothing::displayString() const{
	 std:: string display = name_ + "\n" + "Size: " + size_ + + " Brand: " + brand_ + "\n" + 
	 to_string(price_) + " " + to_string(qty_) + " left." + "\n";

	 return display; 
 }



void Clothing::dump(std::ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
 