/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 19:53:13 by aldubar           #+#    #+#             */
/*   Updated: 2021/10/29 11:29:58 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "reverse_iterator.hpp"

namespace	ft {

	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> >
	class	map {
		
		public:

		/*
		* Member types
		*/

			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const Key, T>					value_type;
			typedef std::size_t								size_type;
			typedef std::ptdfiff_t							difference_type;
			typedef Compare									key_compare;
			typedef Allocator								Allocator;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef map_iterator<value_type>				iterator;
			typedef map_const_iterator<value_type>			const_iterator;
			typedef reverse_iterator<iterator>				reverse_iterator;
			typedef const_reverse_iterator<const_iterator>	const_reverse_iterator;

		/*
		* Member classes
		*/

			class value_compare {

				protected:
					Compare	comp;
					value_compare( Compare c ): comp(c) {}

				public:
					value_compare( void ): comp(Compare()) {}
					~value_compare( void ) {}

					bool operator()( const value_type& lhs, const value_type& rhs ) const { return comp(lhs.first, rhs.first); }
			};

		/*
		* Member functions
		*/

			map( void ) {}
			explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) {}
			
			template< class InputIt >
			map( Input It first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) {}

			map( const map& other ) {}

			~map( void ) {}

			map &	operator=( const map& other ) {}

			allocator_type	get_allocator( void ) const {}

		/*
		* Elements access
		*/
			
			T&			at( const Key& key ) {}
			const T&	at( const Key& key ) const {}

			T&			operator[]( const Key& key ) {}

		/*
		* Iterators
		*/
			
			iterator		begin( void ) {}
			const_iterator	begin( void ) const {}

			iterator		end( void ) {}
			const_iterator	end( void ) const {}

			reverse_iterator		rbegin( void ) {}
			const_reverse_iterator	rbegin( void ) const {}

			reverse_iterator		rend( void ) {}
			const_reverse_iterator	rend( void ) const {}

		/*
		* Capacity
		*/
			
			bool		empty( void ) const { return begin() == end(); }
			size_type	size( void ) const { return _size; }
			size_type	max_size( void ) const {}

		/*
		* Modifiers
		*/

			void	clear( void ) {}

			ft::pair<iterator, bool>	insert( const value_type& value ) {}
			iterator					insert( iterator hint, const value_type& value ) {}

			template< class InputIt >
			void 						insert( InputIt first, InputIt last ) {}

			void		erase( iterator pos ) {}
			void		erase( iterator first, iterator last ) {}
			size_type	erase( const key_type& key ) {}

			void	swap( map& other ) {}

		/*
		* Lookup
		*/

			size_type	count( const Key& key ) const {}

			iterator		find( const Key& key ) {}
			const_iterator	find( const Key& key ) const {}

			ft::pair<iterator, iterator>				equal_range( const Key& key ) {}
			ft::pair<const_iterator, const_iterator>	equal_range( const Key& key ) const {}

			iterator		lower_bound( const Key& key ) {}
			const_iterator	lower_bound( const Key& key ) const {}

			iterator		upper_bound( const Key& key ) {}
			const_iterator	upper_bound( const Key& key ) const {}

		/*
		* Observers
		*/

			key_compare				key_comp( void ) const {}

			ft::map::value_compare	value_comp( void ) const {}

	};

		/*
		* Non members functions
		*/

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs ) {}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs ) {}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs ) {}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs ) {}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs ) {}

}

#endif
