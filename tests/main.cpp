/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:58:22 by aldubar           #+#    #+#             */
/*   Updated: 2021/11/02 09:45:59 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestContainers.hpp"
#include "testVector.hpp"
#include "testStack.hpp"
#include "testMap.hpp"

int		main( int ac, char **av ) {

	std::string	arg;

	if (ac > 1) {

		for (int i = 1; i < ac; i++) {

			arg = av[i];

			if (arg == "vector")
				testingVector();
			
			else if (arg == "stack")
				testingStack();
			
			else if (arg == "map")
				testingMap();
		}
	}	
	else {
	
		testingVector();
		testingStack();
		testingMap();
	}

	return 0;
}
