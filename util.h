#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */

//FIND where two sets intersect 
//- IN BOTH sets = add to new set 
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	std::set<T> set_intersect; // new set for intersection
	
	typename std::set<T>::iterator it;
	for (it = s1.begin(); it != s1.end(); ++it){
		if (s2.find(*it) != s2.end()){
			set_intersect.insert(*it);
		}
	}

	return set_intersect;
}


template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
// Iterate through both sets and add all elemets 
	
	std::set<T> set_union; // new set for union
	
	typename std::set<T>::iterator it;
	std::set<T>& s2_no_repeats = s2; // copy set 2 


	//iterate 1st set
	for(it = s1.begin(); it != s1.end(); ++it){ 
		if (s2.find(*it) != s2.end()){ // delete repeats from set 2 
			s2_no_repeats.erase(*it); 
		}
			set_union.insert(*it);
	}

	//iterate 2nd set 
	for(it = s2_no_repeats.begin(); it != s2_no_repeats.end(); ++it){
		set_union.insert(*it);
	}
	return set_union; 
	
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
