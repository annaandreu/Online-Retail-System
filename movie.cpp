#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <string>
#include "util.h"
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, 
std::string genre, std::string rating):
Product(category, name, price, qty),
genre_(genre),
rating_(rating)
{

}

Movie::~Movie(){

}

/**
     * Returns the appropriate keywords that this product should be associated with
     */
std::set<std::string> Movie::keywords() const{
	set<std::string> temp = parseStringToWords(name_);
	set<std::string> temp2 = parseStringToWords(genre_);

	set<std::string> key= setUnion(temp, temp2);
	key.insert(rating_);

	return key;

}

 std::string Movie::displayString() const{
	 std:: string display = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ +  "\n" +
	 to_string(price_) + " " + to_string(qty_) + " left." + "\n";

	 return display; 
 }



void Movie::dump(std::ostream& os) const{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_  << "\n" << genre_  << "\n" << rating_ << endl;
}
 