/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:04:49 by aldubar           #+#    #+#             */
/*   Updated: 2021/10/21 00:27:12 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "iterator.hpp"
#include <vector>
#include <iostream>

#define RED		"\033[31m"
#define ORANGE	"\033[33m"
#define CLEAR	"\033[0m"
#define OK		" [ \033[32mOK\033[0m ]"
#define KO		" [ \033[31mKO\033[0m ]"
#define	STR		"std::string"

template< class T, class Tft >
int		checkEmpty( T & cont, Tft & ftCont ) {

	bool	real = cont.empty();
	bool	mine = ftCont.empty();

	std::cout << "is empty? " << (real ? "true" : "false") << " vs " << (mine ? "true" : "false");

	(real == mine) ? std::cout << OK : std::cout << KO;
	std::cout << std::endl;

	return (real == mine ? 0 : 1);
}

std::string		compareSizeT( size_t cont, size_t ftCont ) {

	return (cont == ftCont ? OK : KO);
}

template< class T, class Tft >
int		checkSize( T & cont, Tft & ftCont, std::string type ) {

	int		ret = 0;
	std::cout << "vector<" << type << "> size : " << cont.size() << " vs " << ftCont.size() << compareSizeT(cont.size(), ftCont.size()) << std::endl;
	std::cout << "vector<" << type << "> max_size : " << cont.max_size() << " vs " << ftCont.max_size() << compareSizeT(cont.max_size(), ftCont.max_size()) << std::endl;
	std::cout << "Capacity :" << (ftCont.capacity() >= ftCont.size() ? OK : KO) << std::endl;

	if (ftCont.size() != cont.size())
		ret++;
	if (ftCont.max_size() != cont.max_size())
		ret++;
	if (ftCont.capacity() < ftCont.size())
		ret++;

	ret += checkEmpty(cont, ftCont);

	return ret;
}

template< class T >
void	displayCont( T & c, std::string vec ) {

	std::cout << (vec.length() ? vec : "")  << "vector content: ";

	for (typename T::iterator it = c.begin(); it != c.end(); it++)
		std::cout << "[" << *it << "] ";
	
	std::cout << std::endl << std::endl;
}

template< class T, class Tft >
int			checkCont( T it, Tft itft, size_t size ) {

	int		ret = 0;
	
	for (size_t i = 0; i < size; i++) {
		std::cout << "index [" << i << "] [" << *it << "] vs [" << *itft << "]" << (*it == *itft ? OK : KO) << std::endl;
		if (*it != *itft)
			ret++;
		it++;
		itft++;
	}

	std::cout << std::endl;

	return ret;
}

template< class T, class Tft >
int		checkAt( T cont, Tft ftCont ) {

	int		ret = 0;
	size_t	size = ftCont.size();
	size_t	array[] = {1, size - 2};

	for (size_t i = 0; i < 2; i++) {
		
		std::cout << "Checking vector.at: index [" << array[i] << "] " << cont.at(array[i]) << " vs " << ftCont.at(array[i]);
		if (cont.at(array[i]) != ftCont.at(array[i])) {
			ret++;
			std::cout << KO << std::endl;
		}
		else
			std::cout << OK << std::endl;

		std::cout << "Checking operator[]: index [" << array[i] << "] " << cont[array[i]] << " vs " << ftCont[array[i]];
		if (cont[array[i]] != ftCont[array[i]]) {
			ret++;
			std::cout << KO << std::endl;
		}
		else
			std::cout << OK << std::endl;
	}
	try {
		std::cout << "Attempting to access a value out of range: index [" << size << "] ";
		std::cout << ftCont.at(size);
	}
	catch (std::exception & e) {
		std::cout << RED << e.what() << CLEAR << std::endl;
	}
	
	std::cout << std::endl;

	return ret;
}

template< class T, class Tft >
int		checkFrontBack( T cont, Tft ftCont ) {

	int		ret = 0;

	if (ftCont.size() <= 1)
		return 0;

	std::cout << "vector->front [" << cont.front() << "] vs [" << ftCont.front() << "]";
	if (cont.front() == ftCont.front())
		std::cout << OK << std::endl;
	else {
		std::cout << KO << std::endl;
		ret++;
	}

	std::cout << "vector->back [" << cont.back() << "] vs [" << ftCont.back() << "]";
	if (cont.back() == ftCont.back())
		std::cout << OK << std::endl << std::endl;
	else {
		std::cout << KO << std::endl << std::endl;
		ret++;
	}

	return ret;
}

template< class T, class Tft, class Array >
int		checkPushPop( T cont, Tft ftCont, Array array, size_t sizeArray ) {

	int		ret = 0;
	
	for (size_t i = 0; i < sizeArray; i++) {

		cont.push_back(array[i]);
		ftCont.push_back(array[i]);
	}
	std::cout << std::endl << "After push_back " << sizeArray << " elements:" << std::endl;
	ret += checkCont(cont.begin(), ftCont.begin(), ftCont.size());
	ret += checkFrontBack(cont, ftCont);

	for (size_t i = 0; i < 2; i++) {
		
		cont.pop_back();
		ftCont.pop_back();
	}
	if (ftCont.size() > 1) {
		std::cout << "After pop_back 2 elements:" << std::endl;
		ret += checkCont(cont.begin(), ftCont.begin(), ftCont.size());
		ret += checkFrontBack(cont, ftCont);
	}

	return ret;
}

template< class T, class Tft >
int		checkResize( T cont, Tft ftCont, std::string s ) {

	int		ret = 0;
	size_t	size = ftCont.size();

	std::cout << "Before resizing:" << std::endl;
	ret += checkSize(cont, ftCont, s);
	
	std::cout << std::endl << "After resizing to 10000:" << std::endl;
	cont.resize(10000);
	ftCont.resize(10000);
	ret += checkSize(cont, ftCont, s);

	std::cout << std::endl << "After resizing to original size = " << size << ":" << std::endl;
	cont.resize(size);
	ftCont.resize(size);
	ret += checkSize(cont, ftCont, s);

	return ret;
}

template< class T, class Tft >
int		checkInsertStr( T cont, Tft ftCont ) {

	int		ret = 0;

	std::cout << "After insert 1 element at index[size - 2]:" << std::endl;
	cont.insert(cont.end() - 1, "hiiiiiiiii");
	ftCont.insert(ftCont.end() - 1, "hiiiiiiiii");
	ret += checkCont(cont.begin(), ftCont.begin(), ftCont.size());

	std::cout << "After insert a range of 3 elements at the beginning:" << std::endl;
	cont.insert(cont.begin(), 3, "good bye");
	ftCont.insert(ftCont.begin(), 3, "good bye");
	ret += checkCont(cont.begin(), ftCont.begin(), ftCont.size());

	ret += checkAt(cont, ftCont);
	ret += checkFrontBack(cont, ftCont);
	
	return ret;
}

template< class T, class Tft >
int		checkInsertInt( T cont, Tft ftCont ) {

	int		ret = 0;

	std::cout << "After insert 1 element at index[size - 2]:" << std::endl;
	cont.insert(cont.end() - 1, 999);
	ftCont.insert(ftCont.end() - 1, 999);
	ret += checkCont(cont.begin(), ftCont.begin(), ftCont.size());

	std::cout << "After insert a range of 3 elements at the beginning:" << std::endl;
	cont.insert(cont.begin(), 3, 4242);
	ftCont.insert(ftCont.begin(), 3, 4242);
	ret += checkCont(cont.begin(), ftCont.begin(), ftCont.size());

	ret += checkAt(cont, ftCont);
	ret += checkFrontBack(cont, ftCont);
	
	return ret;
}

template< class T, class Tft >
int		runTestsStr( T cont, Tft ftCont, bool filled ) {

	int		ret = 0;

	ret += checkResize(cont, ftCont, STR);

	if (ftCont.size()) {

		if (filled == true) {

			displayCont(cont, "");
			displayCont(ftCont, "ft_");
			ret += checkCont(cont.begin(), ftCont.begin(), ftCont.size());
			ret += checkFrontBack(cont, ftCont);
		}

		ret += checkInsertStr(cont, ftCont);
	}	
	else {
			
		std::string	array[] = {"coucou", "holà", "hello"};
		ret += checkPushPop(cont, ftCont, array, 3);
	}

	return ret;
}

template< class T, class Tft >
int		runTestsInt( T cont, Tft ftCont, bool filled ) {

	int		ret = 0;

	ret += checkResize(cont, ftCont, "int");

	if (ftCont.size()) {

		if (filled == true) {
			
			displayCont(cont, "");
			displayCont(ftCont, "ft_");
			ret += checkCont(cont.begin(), ftCont.begin(), ftCont.size());
			ret += checkFrontBack(cont, ftCont);
		}

		ret += checkInsertInt(cont, ftCont);
	}	
	else {

		int		array[] = {1, 2, 3, 4, 5};
		ret += checkPushPop(cont, ftCont, array, 5);
	}

	return ret;
}

template< class T, class Tft, class Array >
int		moreTests( T cont, Tft ftCont, Array array ) {

	int		ret = 0;

	std::cout << "Testing assign:" << std::endl;
	cont.assign(4, array[0]);
	cont.insert(cont.begin(), 4, array[1]);
	cont.push_back(array[2]);
	cont.push_back(array[3]);

	ftCont.assign(4, array[0]);
	ftCont.insert(ftCont.begin(), 4, array[1]);
	ftCont.push_back(array[2]);
	ftCont.push_back(array[3]);
	
	ret += checkCont(cont.begin(), ftCont.begin(), ftCont.size());

	std::cout << "Testing assign with a range, removing the first three elements:" << std::endl;
	cont.assign(cont.begin() + 3, cont.end());
	ftCont.assign(ftCont.begin() + 3, ftCont.end());
	ret += checkCont(cont.begin(), ftCont.begin(), ftCont.size());

	std::cout << "Testing erase the last element:" << std::endl;
	cont.erase(cont.end() - 1);
	//ftCont.erase(ftCont.end() - 1);
	//ret += checkCont(cont.begin(), ftCont.begin(), ftCont.size());

	std::cout << "Testing erase a range of elements, keeping the first and the last:" << std::endl;
	cont.erase(cont.begin() + 1, cont.end() - 1);
	//ftCont.erase(ftCont.begin() + 1, ftCont.end() - 1);
	//ret += checkCont(cont.begin(), ftCont.begin(), ftCont.size());

	return ret;
}

int		testingVector( void ) {

	int		ret = 0;

	std::cout << ORANGE << "===> TESTING VECTOR <===" << CLEAR << std::endl << std::endl;

	std::cout << ORANGE << "Empty vector of " << STR << " of size = 0" << CLEAR << std::endl;
	std::vector<std::string>	vs;
	ft::vector<std::string>		ftvs;
	ret += runTestsStr(vs, ftvs, false);


	std::cout << ORANGE << "Empty vector of " << STR << " of size = 10" << CLEAR << std::endl;
	std::vector<std::string>	vs2(10);
	ft::vector<std::string>		ftvs2(10);
	ret += runTestsStr(vs2, ftvs2, false);


	std::cout << ORANGE << "Filled vector of " << STR << " of size = 5" << CLEAR << std::endl;
	std::vector<std::string>	vs3(5, "holà");
	ft::vector<std::string>		ftvs3(5, "holà");
	ret += runTestsStr(vs3, ftvs3, true);


	std::cout << ORANGE << "Empty vector of int of size = 0" << CLEAR << std::endl;
	std::vector<int>	vi;
	ft::vector<int>		ftvi;
	ret += runTestsInt(vi, ftvi, false);


	std::cout << ORANGE << "Empty vector of int of size = 10" << CLEAR << std::endl;
	std::vector<int>	vi2(10);
	ft::vector<int>		ftvi2(10);
	ret += runTestsInt(vi2, ftvi2, false);


	std::cout << ORANGE << "Filled vector of int of size = 5" << CLEAR << std::endl;
	std::vector<int>	vi3(5, 42);
	ft::vector<int>		ftvi3(5, 42);
	ret += runTestsInt(vi3, ftvi3, true);



	std::cout << ORANGE << "===> MORE TESTS FOR VECTOR <===" << CLEAR << std::endl;

	std::cout << ORANGE << "Vector of " << STR << CLEAR << std::endl;
	std::vector<std::string>	vs4;
	ft::vector<std::string>		ftvs4;
	std::string	arrayStr[] = {"bonjour", "au revoir", "salut", "bonne journée"};
	ret += moreTests(vs4, ftvs4, arrayStr);


	std::cout << ORANGE << "Vector of int" << CLEAR << std::endl;
	std::vector<int>	vi4;
	ft::vector<int>		ftvi4;
	int arrayInt[] = {113, 4242, 666, -42};
	ret += moreTests(vi4, ftvi4, arrayInt);

	return ret;
}
