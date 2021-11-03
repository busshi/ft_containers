/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testStack.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:35:51 by aldubar           #+#    #+#             */
/*   Updated: 2021/11/02 10:08:47 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSTACK_HPP
# define TESTSTACK_HPP

# include "TestContainers.hpp"

# if STL
	namespace ft = std;
	#include <stack>
	#include <vector>
# else
	#include "stack.hpp"
	#include "vector.hpp"
# endif


template< class T >
void	testSize( T s ) {

	std::cout << std::boolalpha;
	std::cout << "stack size: " << s.size() << std::endl;
	std::cout << "is empty? " << s.empty() << std::endl;

	std::cout << "--------------------------" << std::endl;
}

template< class T, class A >
void	testPushPop( T s, A array, size_t size, std::string type ) {

	std::cout << std::boolalpha << ORANGE << "[+] Testing stack.push() and stack.pop() with a stack of " << type << CLR << std::endl;
	
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

	std::cout << std::boolalpha << ORANGE << "[+] Testing copy not changing original stack..." << CLR << std::endl;

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

#endif
