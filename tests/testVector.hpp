/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testVector.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:04:49 by aldubar           #+#    #+#             */
/*   Updated: 2021/11/02 10:18:07 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTVECTOR_HPP
# define TESTVECTOR_HPP

# include "TestContainers.hpp"

# if STL
	namespace ft = std;
	#include <vector>
# else
	#include "vector.hpp"
# endif

template< class T >
void	checkEmpty( T & vec ) {

	bool	empty = vec.empty();

	std::cout << "[+] is empty? " << (empty ? "true" : "false") << std::endl;
}

template< class T >
void	checkSize( T & vec, std::string type ) {

	std::cout << "[+] vector<" << type << "> size : " << vec.size() << std::endl;
	std::cout << "[+] vector<" << type << "> max_size : " << vec.max_size() << std::endl;
	std::cout << "[+] Capacity :" << (vec.capacity() >= vec.size() ? OK : KO) << std::endl;

	checkEmpty(vec);
}

template< class T >
void	displayCont( T & vec ) {

	std::cout << "[+] vector vecent: ";

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

	std::cout << "[+] Testing access:" << std::endl;

	for (size_t i = 0; i < 2; i++) {
		
		std::cout << "Checking vector.at: index [" << array[i] << "] " << vec.at(array[i]) << std::endl;

		std::cout << "Checking operator[]: index [" << array[i] << "] " << vec[array[i]] << std::endl;
	}
	try {
		std::cout << "Attempting to access a value out of range: index [" << size << "] ";
		std::cout << vec.at(size);
	}
	catch (std::exception & e) {
		std::cout << RED << "Out of range exception" << CLR << std::endl;
	}
	
	std::cout << std::endl;
}

template< class T >
void	checkFrontBack( T vec ) {

	std::cout << "[+]Testing vector.front() and vector.back():" << std::endl;

	std::cout << "vector->front [" << vec.front() << "]" << std::endl;

	std::cout << "vector->back [" << vec.back() << "]" << std::endl << std::endl;
}

template< class T, class Array >
void	checkPushPop( T vec, Array array, size_t sizeArray ) {

	for (size_t i = 0; i < sizeArray; i++)
		vec.push_back(array[i]);

	std::cout << std::endl << "[+] Testing push_back and pop_back" << std::endl;
	std::cout << "After push_back " << sizeArray << " elements:" << std::endl;
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

	std::cout << "[+] Testing vector.resize()" << std::endl;
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

	std::cout << "[+] Testing vector.insert()" << std::endl;
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

	std::cout << "[+] Testing vector.insert()" << std::endl;
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

	std::cout << "[+] Testing vector.assign():" << std::endl;
	vec.assign(4, array[0]);
	vec.insert(vec.begin(), 4, array[1]);
	vec.push_back(array[2]);
	vec.push_back(array[3]);

	checkCont(vec.begin(), vec.size());

	std::cout << "[+] Testing assign with a range, removing the first three elements:" << std::endl;
	vec.assign(vec.begin() + 3, vec.end());
	checkCont(vec.begin(), vec.size());

	std::cout << "[+] Testing erase the last element:" << std::endl;
	vec.erase(vec.end() - 1);
	checkCont(vec.begin(), vec.size());

	std::cout << "[+] Testing erase a range of elements, keeping the first and the last:" << std::endl;
	vec.erase(vec.begin() + 1, vec.end() - 1);
	checkCont(vec.begin(), vec.size());

	std::cout << "[+] Testing vector.clear():" << std::endl;
	vec.clear();
	checkCont(vec.begin(), vec.size());
}

template< class T >
void	latestsTests( T vec, T vec2, std::string type, std::string s ) {

	std::cout << std::boolalpha;
	std::cout << "[+] Testing comparison operators:" << std::endl;
	std::cout << s << " vector<" << type << ">" << std::endl;
	std::cout << "is equal? " << (vec == vec2) << std::endl;
	std::cout << "is not equal? " << (vec != vec2) << std::endl;
	std::cout << "is greater or equal than? " << (vec >= vec2) << std::endl;
	std::cout << "is lower or equal than? " << (vec <= vec2) << std::endl;
	std::cout << "is greater than ? " << (vec > vec2) << std::endl;
	std::cout << "is lower than ? " << (vec < vec2) << std::endl;

	std::cout << std::endl << "[+] Testing vec.reserve():" << std::endl;
	vec.reserve(100);
	checkCont(vec.begin(), vec.size());
	checkSize(vec, s);
	vec.reserve(1000);
	checkCont(vec.begin(), vec.size());
	checkSize(vec, s);
	vec2.reserve(0);
	checkCont(vec2.begin(), vec2.size());
	checkSize(vec2, s);
}

#endif
