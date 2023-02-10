#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
	stringstream stream;
	stream << convToLower(rawWords);
	set<string> keywords;
	string word;

	while(stream >> rawWords){ //go through words (catch spaces)
		word = "";

		for(unsigned int i = 0; i < rawWords.size(); i++){ 
			if(ispunct(rawWords[i])){  // if punctuation
				if(word.size()> 1){ //if 2+ characters 
					keywords.insert(word);
				}
			}

			else{ 
				word +=rawWords[i];
			}
		}

		if(word.size() > 1){ //if final word is +2 characters
			keywords.insert(word);
		}

	}

	return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}



/*int main(){
	string test = "hello";
	parseStringToWords(test);
	
	return 0;
}*/