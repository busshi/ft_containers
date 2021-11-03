/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:17:38 by aldubar           #+#    #+#             */
/*   Updated: 2021/10/31 22:14:00 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {
	
	template< class T, class Container = ft::vector<T> >
	class stack {

			/*
			* Member objects
			*/

		protected:
			Container	c;

		public:

			/*
			* Member types
			*/

			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

			/*
			* Member functions
			*/

			explicit stack( const Container& cont = Container() ): c(cont) {}
			stack( const stack& other ): c(other.c) {}
			~stack( void ) {}

			stack&	operator=( const stack& other ) {

				if (this != &other)
					c = other.c;

				return *this;
			}

			/*
			* Elements access
			*/

			reference		top( void ) { return c.back(); }
			const_reference	top( void ) const { return c.back(); }

			/*
			* Capacity
			*/

			bool			empty( void ) const { return c.empty(); }
			size_type		size( void ) const { return c.size(); }

			/*
			* Modifiers
			*/

			void			push( const value_type& value ) { c.push_back(value); }
			void			pop( void ) { c.pop_back(); }

			/*
			* Prototypes for non-member functions
			*/

			template< class U, class C >
			friend bool	operator==( const ft::stack<U,C>& lhs, const ft::stack<U,C>& rhs );

			template< class U, class C >
			friend bool	operator!=( const ft::stack<U,C>& lhs, const ft::stack<U,C>& rhs );
			
			template< class U, class C >
			friend bool	operator<( const ft::stack<U,C>& lhs, const ft::stack<U,C>& rhs );

			template< class U, class C >
			friend bool	operator<=( const ft::stack<U,C>& lhs, const ft::stack<U,C>& rhs );

			template< class U, class C >
			friend bool	operator>( const ft::stack<U,C>& lhs, const ft::stack<U,C>& rhs );

			template< class U, class C >
			friend bool	operator>=( const ft::stack<U,C>& lhs, const ft::stack<U,C>& rhs );
	};

	/*
	* Non-member functions
	*/

	template< class T, class Container >
	bool	operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return lhs.c == rhs.c;}
	
	template< class T, class Container >
	bool	operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return lhs.c != rhs.c; }
	
	template< class T, class Container >
	bool	operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return lhs.c < rhs.c; }
	
	template< class T, class Container >
	bool	operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return lhs.c <= rhs.c; }
	
	template< class T, class Container >
	bool	operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return lhs.c > rhs.c; }

	template< class T, class Container >
	bool	operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) { return lhs.c >= rhs.c; }
}

#endif
