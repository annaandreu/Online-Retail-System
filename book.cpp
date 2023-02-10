#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include "util.h"
#include "book.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, 
std::string author, std::string isbn):
Product(category, name, price, qty),
author_(author),
isbn_(isbn)
{

}

Book::~Book(){

}

/**
     * Returns the appropriate keywords that this product should be associated with
     */
std::set<std::string> Book::keywords() const{
	set<std::string> temp = parseStringToWords(name_);
	set<std::string> temp2 = parseStringToWords(author_);

	set<std::string> key= setUnion(temp, temp2);
	key.insert(isbn_);

	return key;

}

 std::string Book::displayString() const{
	 std:: string display = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" +
	 to_string(price_) + " " + to_string(qty_) + " left." + "\n";

	 return display; 
 }


//datbase format
void Book::dump(std::ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}
 