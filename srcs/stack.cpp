/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:35:51 by aldubar           #+#    #+#             */
/*   Updated: 2021/10/25 15:37:52 by aldubar          ###   ########.fr       */
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
	std::cout << "stack size: " << s.size() << std::endl;
	std::cout << "is empty? " << s.empty() << std::endl;

	std::cout << "--------------------------" << std::endl;
}

template< class T, class A >
void	testPushPop( T s, A array, size_t size, std::string type ) {

	std::cout << std::boolalpha << ORANGE << "[+] Testing stack.push() and stack.pop() with a stack of " << type << CLEAR << std::endl;
	
	testSize(s);

	for (size_t i = 0; i < size; i++) {
		
		s.push(array[i]);
		std::cout << "stack Top after push element (" << array[i] << ") => [" << s.top() << "]" << std::endl << std::endl;
	}
	testSize(s);

	for (size_t i = 0; i < size - 1; i++) {

		s.pop();
		std::cout << "stack Top after pop => [" << s.top() << "]" << std::endl << std::endl;
	}
	testSize(s);

	std::cout << "Removing the last element..." << std::endl;
	s.pop();
	testSize(s);
}

template< class T, class A >
void	testCopy( T orig, T copy, T copy2, A array ) {

	std::cout << std::boolalpha << ORANGE << "[+] Testing copy not changing original stack..." << CLEAR << std::endl;

	for (size_t i = 0; i < 6; i++) {

		copy.push(array[i]);
		copy2.push(array[i]);
		std::cout << "copy stack top after push [" << copy.top() << "]" << std::endl;
		std::cout << "copy2 stack top after push [" << copy2.top() << "]" << std::endl;
		std::cout << "original stack top after push [" << orig.top() << "]" << std::endl << std::endl;
	}
	testSize(copy);
	testSize(copy2);
	testSize(orig);
}

template< class T >
void	compareStack( T s, T s2, std::string type, std::string equal ) {

	std::cout << std::boolalpha;
	std::cout << "[+] " << equal << " vector<" << type << ">" << std::endl;
	std::cout << "is equal? " << (s == s2) << std::endl;
	std::cout << "is not equal? " << (s != s2) << std::endl;
	std::cout << "is greater or equal than? " << (s >= s2) << std::endl;
	std::cout << "is lower or equal than? " << (s <= s2) << std::endl;
	std::cout << "is greater than ? " << (s > s2) << std::endl;
	std::cout << "is lower than ? " << (s < s2) << std::endl;

	std::cout << "-------------------------" << std::endl;
}

void	testingStack( void ) {

	std::cout << ORANGE << "===> TESTING STACK <===" << CLEAR << std::endl;

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
	testPushPop(ss, arrayS, 6, STR);

	int			arrayI[42];
	for (size_t i = 0; i < 42; i++)
		arrayI[i] = i + 1;
	testPushPop(si, arrayI, 42, "int");

	char		arrayC[26];
	for (size_t i = 0; i < 26; i++)
		arrayC[i] = i + 65;
	testPushPop(sc, arrayC, 26, "char");



	ft::vector<std::string>	vec(1, "original element");
	ft::stack<std::string, ft::vector<std::string> >	s(vec);
	ft::stack<std::string, ft::vector<std::string> >	scpy = s;
	ft::stack<std::string, ft::vector<std::string> >	scpy2(s);

	testCopy(s, scpy, scpy2, arrayS);


	std::cout << "\033[33m[+] Testing comparison...\033[0m" << std::endl << std::endl;

	ft::vector<int>	veci;
	ft::stack<int, ft::vector<int> >	sint(veci);

	for (size_t i = 0; i < 5; i++)
		sint.push(i);

	ft::stack<int, ft::vector<int> >	sint2(veci);
	for (size_t i = 0; i < 10; i++)
		sint2.push(-i);

	compareStack(sint, sint, "int", "same");
	compareStack(sint, sint2, "int", "different");

	ft::vector<std::string>	vstr;
	ft::stack<std::string, ft::vector<std::string> >	sstr(vstr);
	ft::stack<std::string, ft::vector<std::string> >	sstr2(vstr);
	sstr.push("hello");
	sstr2.push("heello");

	compareStack(sstr, sstr2, STR, "different");
}
