/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:52:55 by aldubar           #+#    #+#             */
/*   Updated: 2021/11/02 10:10:11 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testMap.hpp"

void	testingMap( void ) {

	std::cout << ORANGE << "===> TESTING MAP <===" << CLR << std::endl;

	std::cout << ORANGE << "[+] Testing with a map<int,std::string>" << CLR << std::endl;
	ft::map<int, std::string>	m;
	std::string	array[] = {"hello", "hi", "goodbye", "bonjour", "au revoir", "salut", "holà", "coucou", "güten tag", "ciao"};

	runTests(m, INT, STR, array, *(&array + 1) - array);



	std::cout << ORANGE << "[+] Testing with a map<int,int>" << CLR << std::endl;
	ft::map<int, int>		m2;
	int			array2[] = {-42, 42, 1, -1000, 1000, -666, 666, -543210, 543210, -1};
	for (int i = 0; i < 10; i++)
		m2[i] = i * 2;

	runTests(m2, INT, INT, array2, *(&array2 + 1) - array2);



	std::cout << ORANGE << "[+] Testing insert with a map<std::string,std::string>" << CLR << std::endl;
	ft::map<std::string, std::string>	m3;
	std::string	arrayKey[] = {"ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN"};

	moreTests(m3, arrayKey, array, *(&array + 1) - array, STR, STR);


	std::cout << ORANGE << "[+] Testing iterators with a map<int::int>" << CLR << std::endl;
	checkIt(m2);
	checkAt(m2, 10);

	std::cout << std::endl << ORANGE << "[+] Testing iterators with a map<char,char>" << CLR << std::endl;
	ft::map<char, char>		m4;
	for (int i = 'A'; i < 'A' + 26; i++)
		m4[i] = i + 32;
	checkIt(m4);


	std::cout << std::endl << std::endl << ORANGE << "[+] Testing copy not changing original map" << CLR << std::endl;
	ft::map<int, std::string>	m5;
	std::string 				array5[] = {"zéro", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf", "dix"};

	checkCopySwap(m5, array5, *(&array5 + 1) - array5, INT, STR);


	std::cout << std::endl << ORANGE << "[+] Testing map.count()" << CLR << std::endl;
	ft::map<std::string, std::string>	m14;
	std::string							array14[] = { "key", "key2", "key3", "key5", "key5" };
	size_t								size14 = *(&array14 + 1) - array14;

	for (size_t i = 0; i < size14; i++)
		m14[array14[i]] = "random_useless_value";

	checkCount(m14, array14, size14, STR, STR, "unknown key");


	ft::map<char, char>	m15;
	char				array15[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
	size_t				size15 = *(&array15 + 1) - array15;

	for (size_t i = 0; i < size15; i++)
		m15[array15[i]] = array15[i] + 32;

	checkCount(m15, array15, size15, CHAR, CHAR, '*');



	std::cout << std::endl << ORANGE << "[+] Testing map.find() with a map<std::string,std::string>" << CLR << std::endl;
	ft::map<std::string, std::string>	m6;
	std::string							array6[] = { "key", "key2", "key3", "key5", "key5" };
	size_t								size6 = *(&array6 + 1) - array6;

	for (size_t i = 0; i < size6; i++)
		m6[array6[i]] = "random_useless_value";

	checkFind(m6, array6, size6, STR, STR, "unknown key");


	std::cout << std::endl << ORANGE << "[+] Testing map.find() with a map<char,char>" << CLR << std::endl;
	ft::map<char, char>	m7;
	char				array7[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
	size_t				size7 = *(&array7 + 1) - array7;

	for (size_t i = 0; i < size7; i++)
		m7[array7[i]] = array7[i] + 32;

	checkFind(m7, array7, size7, CHAR, CHAR, '*');


	std::cout << ORANGE << "[+] Testing map.equal_range() with a map<int,int>..." << CLR << std::endl;

	ft::map<int, int>	m8;
	int					array8[] = {2, 5, 0, 10, 15, 16, 19, 20, -100, 1000};

	for (size_t i = 1; i <= 10; i++)
		m8[i * 2] = i * 12;

	for (size_t i = 0; i < *(&array8 + 1) - array8; i++)
		checkEqualRange(m8, INT, INT, array8[i]);


	std::cout << ORANGE << "[+] Testing map.equal_range() with a map<char,std::string>..." << CLR << std::endl;

	ft::map<char, std::string>	m9;
	std::string					arrayS[] = {"hello", "holà", "bonjour", "hi", "good morning", "adios"};
	char						arrayC[] = {'a', 'c', 'e', 'g', 'i', 'k'};
	char						arrayTest[] = {'A', 'a', 'b', 'e', 'i', 'j', 'k', 'l'};

	for (size_t i = 0; i < *(&arrayS + 1) - arrayS; i++)
		m9[arrayC[i]] = arrayS[i];

	for (size_t i = 0; i < *(&arrayTest + 1) - arrayTest; i++)
		checkEqualRange(m9, CHAR, STR, arrayTest[i]);


	std::cout << ORANGE <<"[+] Testing comparison..." << CLR << std::endl;

	ft::map<int, int>	m10;
	for (int i = 0; i < 10; i++)
		m10[i] = i;

	ft::map<int, int>	m11;
	for (int i = 0; i < 10; i++)
		m11[-i] = -i;

	ft::map<int, int>	m12;
	for (int i = 0; i < 5; i++)
		m12[i] = i;

	ft::map<int, int>	m13;
	for (int i = 0; i < 10; i++)
		m13[i] = i;

	checkComparison(m10, m10, INT, INT, "same");
	checkComparison(m10, m11, INT, INT, "different");
	checkComparison(m10, m12, INT, INT, "different");
	checkComparison(m11, m12, INT, INT, "different");
	checkComparison(m10, m13, INT, INT, "same");


	std::cout << std::endl << ORANGE << "[+] Testing class compare..." << CLR << std::endl << std::endl;
	std::cout << "[+] basic compare with a map<int,char>" << std::endl;
    ft::map<int, char>	map;
    map[1] = 'a';
	map[2] = 'b';
	map[3] = 'c';
	map[4] = 'd';
	map[5] = 'e';
	checkCmp(map);

	std::cout << "------------------------" << std::endl;

	std::cout << "[+] Modulo 97 compare with a map<int,char,ModuloComp> >" << std::endl;
	ft::map<int, char, ModuloComp> map2;
    map2[1] = 'a';
	map2[2] = 'b';
	map2[3] = 'c';
	map2[4] = 'd';
	map2[5] = 'e';
	checkModuloCmp(map2);

	std::cout << "------------------------" << std::endl;

	std::cout << "[+] Less compare with a map<int,char,Comp<char> >" << std::endl;
	ft::map<int, char, Comp<char> >	map3;
    map3[1] = 'a';
	map3[2] = 'b';
	map3[3] = 'c';
	map3[4] = 'd';
	map3[5] = 'e';

	ft::map<int, char, Comp<char> >::key_compare	compChar = map3.key_comp();
	checkLower(map3, 'c', compChar);

	std::cout << "------------------------" << std::endl;

	std::cout << "[+] Less compare with a map<char,int,Comp<int> >" << std::endl;
	ft::map<char, int, Comp<int> >	map4;
    map4['z'] = 39;
	map4['y'] = 40;
	map4['x'] = 41;
	map4['w'] = 42;
	map4['v'] = 43;
	map4['u'] = 44;

	ft::map<char, int, Comp<int> >::key_compare		compInt = map4.key_comp();
	checkLower(map4, 42, compInt);
}
