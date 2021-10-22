/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:58:22 by aldubar           #+#    #+#             */
/*   Updated: 2021/10/21 14:39:10 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

int		testingVector( void );
int		testingStack( void );
int		testingMap( void );

int		main( int ac, char **av ) {

	std::string	arg;

	if (ac > 1)
		arg = av[1];

	if (arg == "vector")
		testingVector();
	else if (arg == "stack")
		testingStack();
	else if (arg == "map")
		testingMap();
	else {
		testingVector();
		testingStack();
		testingMap();
	}

	return 0;
}
