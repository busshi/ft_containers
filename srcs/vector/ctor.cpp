/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:02:43 by aldubar           #+#    #+#             */
/*   Updated: 2021/10/21 11:17:37 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#if STL
    #include <vector>
    namespace ft = std;
#else
    #include "vector.hpp"
    #include "iterator.hpp"
#endif

template< class T >
void	checkEmpty( T & vec ) {

    bool    empty = vec.empty();
    std::cout << "is empty? " << (empty ? "true" : "false");

    std::cout << std::endl;
}

int	ctor( void ) {

	ft::vector<int>	vec;
	checkEmpty(vec);

	return 0;
}
