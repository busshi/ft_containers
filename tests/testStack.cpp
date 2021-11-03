/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testStack.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:51:58 by aldubar           #+#    #+#             */
/*   Updated: 2021/11/02 09:54:27 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testStack.hpp"

void	testingStack( void ) {

	std::cout << ORANGE << "===> TESTING STACK <===" << CLR << std::endl;

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
