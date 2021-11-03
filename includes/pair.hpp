/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 11:49:17 by aldubar           #+#    #+#             */
/*   Updated: 2021/11/01 13:03:51 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {
    template< class T1, class T2 >
    struct pair {

		/*
		* Member types
		*/

		typedef T1	first_type;
		typedef T2	second_type;

		/*
		* Member objects
		*/

		T1	first;
		T2	second;

		/*
		* Member functions
		*/

        pair( void ) {}
        pair( const T1& x, const T2& y ) : first(x), second(y) {}
		
		template< class U1, class U2 >
        pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}
        
		pair&	operator=( const pair& other ) {

			if (this != &other) {

				first = other.first;
				second = other.second;
			}

			return *this;
		}
    };

	/*
	* Non-member functions
	*/

    template< class T1, class T2 >
    pair<T1,T2> make_pair( T1 t, T2 u ) { return pair<T1, T2>(t, u); }

    template< class T1, class T2 >
    bool	operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return (lhs.first == rhs.first && lhs.second == rhs.second); }

    template< class T1, class T2 >
    bool	operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return !(lhs == rhs); }

    template< class T1, class T2 >
    bool	operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second)); }
	
	template< class T1, class T2 >
    bool	operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return lhs = rhs || lhs < rhs; }

    template< class T1, class T2 >
    bool	operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return !(lhs < rhs); }

    template< class T1, class T2 >
    bool	operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) { return lhs == rhs || !(lhs < rhs); }
}

#endif
