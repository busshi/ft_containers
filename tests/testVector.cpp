/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testVector.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:50:14 by aldubar           #+#    #+#             */
/*   Updated: 2021/11/02 10:18:34 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testVector.hpp"

void	testingVector( void ) {

	std::cout << ORANGE << "===> TESTING VECTOR <===" << CLR << std::endl << std::endl;

	std::cout << ORANGE << "Empty vector of " << STR << " of size = 0" << CLR << std::endl;
	ft::vector<std::string>	vs;
	runTestsStr(vs, false);


	std::cout << ORANGE << "Empty vector of " << STR << " of size = 10" << CLR << std::endl;
	ft::vector<std::string>	vs2(10);
	runTestsStr(vs2, false);


	std::cout << ORANGE << "Filled vector of " << STR << " of size = 5" << CLR << std::endl;
	ft::vector<std::string>	vs3(5, "holà");
	runTestsStr(vs3, true);


	std::cout << ORANGE << "Empty vector of int of size = 0" << CLR << std::endl;
	ft::vector<int>	vi;
	runTestsInt(vi, false);


	std::cout << ORANGE << "Empty vector of int of size = 10" << CLR << std::endl;
	ft::vector<int>	vi2(10);
	runTestsInt(vi2, false);


	std::cout << ORANGE << "Filled vector of int of size = 5" << CLR << std::endl;
	ft::vector<int>	vi3(5, 42);
	runTestsInt(vi3, true);



	std::cout << ORANGE << "===> MORE TESTS FOR VECTOR <===" << CLR << std::endl;

	std::cout << ORANGE << "Vector of " << STR << CLR << std::endl;
	ft::vector<std::string>	vs4;
	std::string	arrayStr[] = {"bonjour", "au revoir", "salut", "bonne journée"};
	moreTests(vs4, arrayStr);


	std::cout << ORANGE << "Vector of int" << CLR << std::endl;
	ft::vector<int>	vi4;
	int arrayInt[] = {113, 4242, 666, -42};
	moreTests(vi4, arrayInt);


	std::cout << ORANGE << "===> LASTEST TESTS FOR VECTOR <===" << CLR << std::endl;
	ft::vector<int>	vi5;
	ft::vector<int>	vi6;
	for (size_t i = 0; i < 42; i++) {
		vi5.push_back(i);
		vi6.push_back(-i);
	}
	latestsTests(vi5, vi6, "int", "Differents");
	latestsTests(vi5, vi5, "int", "same");

	std::cout << std::endl << std::endl;
}
