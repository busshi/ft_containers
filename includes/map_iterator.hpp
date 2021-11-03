/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 11:46:48 by aldubar           #+#    #+#             */
/*   Updated: 2021/11/01 13:03:08 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "tree.hpp"

namespace ft {

	template< class T >
	class map_iterator {
		
		public:
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::random_access_iterator_tag	iterator_category;
			typedef tree<T>							tree;

			map_iterator( void ) {}
			map_iterator( tree* node ) : node(node) {}
			map_iterator( const map_iterator& other ) { *this = other; }
		
			map_iterator&	operator=( const map_iterator& other ) {
			
				if (this != &other)
					node = other.node;
				
				return *this;
			}
			
			~map_iterator( void ) {}

			reference		operator*( void ) const { return node->data; }

			pointer			operator->( void ) const { return &(node->data); }

			friend bool		operator==( const map_iterator& lhs, const map_iterator& rhs ) { return lhs.node == rhs.node; }
			friend bool		operator!=( const map_iterator& lhs, const map_iterator& rhs ) { return lhs.node != rhs.node; }

			map_iterator&	operator++( void ) {

				node = next_node(node);

				return *this;
			}
	
			map_iterator	operator++( int ) {
			
				map_iterator tmp = *this;
				++*this;
			
				return tmp;
			}
		
			map_iterator&	operator--( void ) {

				node = previous_node(node);
				
				return *this;
			}

			map_iterator	operator--( int ) {

				map_iterator	tmp = *this;
				--*this;
				
				return tmp;
			}

			tree* node;
	};

	template< class T >
	class const_map_iterator {

		public:

			typedef std::ptrdiff_t 					difference_type;
			typedef const T 						value_type;
			typedef const T* 						pointer;
			typedef const T& 						reference;
			typedef std::random_access_iterator_tag	iterator_category;
			typedef tree<T> 							tree;

			const_map_iterator( void ) {}
			const_map_iterator( const const_map_iterator& other ) { *this = other; }
			const_map_iterator( tree* node ) : node(node){}
			const_map_iterator( const map_iterator<T>& src ) : node(src.node) {}
			
			const_map_iterator&	operator=( const const_map_iterator& other ) {
		
				if (this != &other)
					node = other.node;

				return *this;
			}

			~const_map_iterator( void ) {}

			reference	operator*( void ) const { return node->data; }
			pointer		operator->( void ) const { return &(node->data); }

			friend bool	operator==( const const_map_iterator& lhs, const const_map_iterator& rhs ) { return lhs.node == rhs.node; }
			friend bool operator!=( const const_map_iterator& lhs, const const_map_iterator& rhs ) { return lhs.node != rhs.node; }

			const_map_iterator&	operator++( void ) {
		
				node = next_node(node);
				
				return *this;
			}
	
			const_map_iterator	operator++( int ) {

				const_map_iterator tmp = *this;
				++*this;
			
				return tmp;
			}
		
			const_map_iterator&	operator--( void ) {

				node = previous_node(node);

				return *this;
			}
	
			const_map_iterator	operator--( int ) {

				const_map_iterator tmp = *this;
				--*this;
			
				return tmp;
			}

			tree* node;
	};
}

#endif
