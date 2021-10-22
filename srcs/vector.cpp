/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:04:49 by aldubar           #+#    #+#             */
/*   Updated: 2021/10/22 14:51:40 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "vector.hpp"
#include "iterator.hpp"

#define RED		"\033[31m"
#define ORANGE	"\033[33m"
#define CLEAR	"\033[0m"
#define OK		" [ \033[32mOK\033[0m ]"
#define KO		" [ \033[31mKO\033[0m ]"
#define	STR		"std::string"

using CONTAINER::vector;

template< class T >
void	checkEmpty( T & vec ) {

	bool	empty = vec.empty();

	std::cout << "is empty? " << (empty ? "true" : "false") << std::endl;
}

template< class T >
void	checkSize( T & vec, std::string type ) {

	std::cout << "vector<" << type << "> size : " << vec.size() << std::endl;
	std::cout << "vector<" << type << "> max_size : " << vec.max_size() << std::endl;
	std::cout << "Capacity :" << (vec.capacity() >= vec.size() ? OK : KO) << std::endl;

	checkEmpty(vec);
}

template< class T >
void	displayCont( T & vec ) {

	std::cout << "vector vecent: ";

	for (typename T::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << "[" << *it << "] ";
	
	std::cout << std::endl;
}

template< class T >
void	checkCont( T it, size_t size ) {

	for (size_t i = 0; i < size; i++) {
		std::cout << "index [" << i << "] [" << *it << "]" << std::endl;
		it++;
	}

	std::cout << std::endl;
}

template< class T >
void	checkAt( T vec ) {

	size_t	size = vec.size();
	size_t	array[] = {1, size - 2};

	for (size_t i = 0; i < 2; i++) {
		
		std::cout << "Checking vector.at: index [" << array[i] << "] " << vec.at(array[i]) << std::endl;

		std::cout << "Checking operator[]: index [" << array[i] << "] " << vec[array[i]] << std::endl;
	}
	try {
		std::cout << "Attempting to access a value out of range: index [" << size << "] ";
		std::cout << vec.at(size);
	}
	catch (std::exception & e) {
		std::cout << RED << e.what() << CLEAR << std::endl;
	}
	
	std::cout << std::endl;
}

template< class T >
void	checkFrontBack( T vec ) {

	std::cout << "vector->front [" << vec.front() << "]" << std::endl;

	std::cout << "vector->back [" << vec.back() << "]" << std::endl << std::endl;
}

template< class T, class Array >
void	checkPushPop( T vec, Array array, size_t sizeArray ) {

	for (size_t i = 0; i < sizeArray; i++)
		vec.push_back(array[i]);

	std::cout << std::endl << "After push_back " << sizeArray << " elements:" << std::endl;
	checkCont(vec.begin(), vec.size());
	checkFrontBack(vec);

	for (size_t i = 0; i < 2; i++)
		vec.pop_back();

	if (vec.size() > 1) {
		std::cout << "After pop_back 2 elements:" << std::endl;
		checkCont(vec.begin(), vec.size());
		checkFrontBack(vec);
	}
}

template< class T >
void	checkResize( T vec, std::string type ) {

	size_t	size = vec.size();

	std::cout << "Before resizing:" << std::endl;
	checkSize(vec, type);
	
	std::cout << std::endl << "After resizing to 10000:" << std::endl;
	vec.resize(10000);
	checkSize(vec, type);

	std::cout << std::endl << "After resizing to original size = " << size << ":" << std::endl;
	vec.resize(size);
	checkSize(vec, type);
}

template< class T >
void	checkInsertStr( T vec ) {

	std::cout << "After insert 1 element at index[size - 2]:" << std::endl;
	vec.insert(vec.end() - 1, "hiiiiiiiii");
	checkCont(vec.begin(), vec.size());

	std::cout << "After insert a range of 3 elements at the beginning:" << std::endl;
	vec.insert(vec.begin(), 3, "good bye");
	checkCont(vec.begin(), vec.size());

	checkAt(vec);
	checkFrontBack(vec);
}

template< class T >
void	checkInsertInt( T vec ) {

	std::cout << "After insert 1 element at index[size - 2]:" << std::endl;
	vec.insert(vec.end() - 1, 999);
	checkCont(vec.begin(), vec.size());

	std::cout << "After insert a range of 3 elements at the beginning:" << std::endl;
	vec.insert(vec.begin(), 3, 4242);
	checkCont(vec.begin(), vec.size());

	checkAt(vec);
	checkFrontBack(vec);
}

template< class T >
void	runTestsStr( T vec, bool filled ) {

	checkResize(vec, STR);

	if (vec.size()) {

		if (filled == true) {

			displayCont(vec);
			checkCont(vec.begin(), vec.size());
			checkFrontBack(vec);
		}

		checkInsertStr(vec);
	}	
	else {
			
		std::string	array[] = {"coucou", "holà", "hello"};
		checkPushPop(vec, array, 3);
	}
}

template< class T >
void	runTestsInt( T vec, bool filled ) {

	checkResize(vec, "int");

	if (vec.size()) {

		if (filled == true) {
			
			displayCont(vec);
			checkCont(vec.begin(), vec.size());
			checkFrontBack(vec);
		}

		checkInsertInt(vec);
	}	
	else {

		int		array[] = {1, 2, 3, 4, 5};
		checkPushPop(vec, array, 5);
	}
}

template< class T, class Array >
void	moreTests( T vec, Array array ) {

	std::cout << "Testing assign:" << std::endl;
	vec.assign(4, array[0]);
	vec.insert(vec.begin(), 4, array[1]);
	vec.push_back(array[2]);
	vec.push_back(array[3]);

	checkCont(vec.begin(), vec.size());

	std::cout << "Testing assign with a range, removing the first three elements:" << std::endl;
	vec.assign(vec.begin() + 3, vec.end());
	checkCont(vec.begin(), vec.size());

	std::cout << "Testing erase the last element:" << std::endl;
	vec.erase(vec.end() - 1);
	checkCont(vec.begin(), vec.size());

	std::cout << "Testing erase a range of elements, keeping the first and the last:" << std::endl;
	vec.erase(vec.begin() + 1, vec.end() - 1);
	checkCont(vec.begin(), vec.size());
}

void	testingVector( void ) {

	std::cout << ORANGE << "===> TESTING VECTOR <===" << CLEAR << std::endl << std::endl;

	std::cout << ORANGE << "Empty vector of " << STR << " of size = 0" << CLEAR << std::endl;
	vector<std::string>	vs;
	runTestsStr(vs, false);


	std::cout << ORANGE << "Empty vector of " << STR << " of size = 10" << CLEAR << std::endl;
	vector<std::string>	vs2(10);
	runTestsStr(vs2, false);


	std::cout << ORANGE << "Filled vector of " << STR << " of size = 5" << CLEAR << std::endl;
	vector<std::string>	vs3(5, "holà");
	runTestsStr(vs3, true);


	std::cout << ORANGE << "Empty vector of int of size = 0" << CLEAR << std::endl;
	vector<int>	vi;
	runTestsInt(vi, false);


	std::cout << ORANGE << "Empty vector of int of size = 10" << CLEAR << std::endl;
	vector<int>	vi2(10);
	runTestsInt(vi2, false);


	std::cout << ORANGE << "Filled vector of int of size = 5" << CLEAR << std::endl;
	vector<int>	vi3(5, 42);
	runTestsInt(vi3, true);



	std::cout << ORANGE << "===> MORE TESTS FOR VECTOR <===" << CLEAR << std::endl;

	std::cout << ORANGE << "Vector of " << STR << CLEAR << std::endl;
	vector<std::string>	vs4;
	std::string	arrayStr[] = {"bonjour", "au revoir", "salut", "bonne journée"};
	moreTests(vs4, arrayStr);


	std::cout << ORANGE << "Vector of int" << CLEAR << std::endl;
	vector<int>	vi4;
	int arrayInt[] = {113, 4242, 666, -42};
	moreTests(vi4, arrayInt);
}
