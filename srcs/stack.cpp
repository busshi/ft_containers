/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:35:51 by aldubar           #+#    #+#             */
/*   Updated: 2021/10/25 13:44:30 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if STL
	namespace ft = std;
	#include <stack>
	#include <vector>
#else
	#include "stack.hpp"
	#include "vector.hpp"
#endif

#define ORANGE	"\033[33m"
#define CLEAR	"\033[0m"
#define	STR		"std::string"


template< class T >
void	testSize( T s ) {

	std::cout << std::boolalpha;
	std::cout << "[+] stack size: " << s.size() << std::endl;
	std::cout << "[+] is empty? " << s.empty() << std::endl;

	std::cout << "--------------------------" << std::endl;
}

template< class T, class A >
void	runTests( T s, A array, size_t size, std::string type ) {

	std::cout << std::boolalpha << "Testing with a stack of " << type << std::endl;
	
	testSize(s);

	for (size_t i = 0; i < size; i++) {
		
		s.push(array[i]);
		std::cout << "[+] stack Top after push element (" << array[i] << ") => [" << s.top() << "]" << std::endl << std::endl;
	}
	testSize(s);

	for (size_t i = 0; i < size - 1; i++) {

		s.pop();
		std::cout << "[+] stack Top after pop => [" << s.top() << "]" << std::endl << std::endl;
	}
	testSize(s);

	std::cout << "[+] Removing the last element..." << std::endl;
	s.pop();
	testSize(s);
}

void	testingStack( void ) {

	std::cout << ORANGE << "===> Testing STACK <===" << CLEAR << std::endl;

	ft::vector<int>		vi;
	ft::vector<int>		vi2(10);
	ft::vector<int>		vi3(10, 42);
	ft::stack<int, ft::vector<int> >	si(vi);
	ft::stack<int, ft::vector<int> >	si2(vi2);
	ft::stack<int, ft::vector<int> >	si3(vi3);

	ft::vector<std::string>		vs;
	ft::vector<std::string>		vs2(5);
	ft::vector<std::string>		vs3(5, "hello");
	ft::stack<std::string, ft::vector<std::string> >	ss(vs);	
	ft::stack<std::string, ft::vector<std::string> >	ss2(vs2);	
	ft::stack<std::string, ft::vector<std::string> >	ss3(vs3);	

	ft::vector<char>	vc;
	ft::vector<char>	vc2(5);
	ft::vector<char>	vc3(5, '*');
	ft::stack<char, ft::vector<char> >	sc(vc);	
	ft::stack<char, ft::vector<char> >	sc2(vc2);	
	ft::stack<char, ft::vector<char> >	sc3(vc3);	

	testSize(si);
	testSize(si2);
	testSize(si3);

	testSize(ss);
	testSize(ss2);
	testSize(ss3);

	testSize(sc);
	testSize(sc2);
	testSize(sc3);


	std::string	arrayS[] = {"Hello", "holà", "bonjour", "hi", "good bye", "salut"};
	runTests(ss, arrayS, 6, STR);

	int			arrayI[42];
	for (size_t i = 0; i < 42; i++)
		arrayI[i] = i + 1;
	runTests(si, arrayI, 42, "int");

	char		arrayC[26];
	for (size_t i = 0; i < 26; i++)
		arrayC[i] = i + 65;
	runTests(sc, arrayC, 26, "char");
}
