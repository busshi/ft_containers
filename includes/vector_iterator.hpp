/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:21:08 by aldubar           #+#    #+#             */
/*   Updated: 2021/10/30 13:10:10 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

namespace	ft {

	template< class T >
	class iterator  {
	
		public:
			typedef std::ptrdiff_t					difference_type;
			typedef T 								value_type;
			typedef T* 								pointer;
			typedef T& 								reference;
			typedef std::random_access_iterator_tag	iterator_category;

			iterator( void ): _ptr() {}
			iterator( pointer ptr ) : _ptr(ptr) {}
			iterator( const iterator& other ) { *this = other; }
		
			iterator& operator=( const iterator& other ) {

				if (this != &other)
					_ptr = other._ptr;
			
				return *this;
			}

			~iterator( void ) {}

			reference	operator*() const {	return *_ptr; }
			pointer		operator->() const { return _ptr; }

			reference operator[]( int n ) const { return *(_ptr + n); }

			friend bool operator==( const iterator& lhs, const iterator& rhs ) { return lhs._ptr == rhs._ptr; }
			friend bool operator!=( const iterator& lhs, const iterator& rhs ) { return lhs._ptr != rhs._ptr; }
			friend bool operator<( const iterator& lhs, const iterator& rhs ) { return lhs._ptr < rhs._ptr; }
			friend bool operator<=( const iterator& lhs, const iterator& rhs ) { return lhs._ptr <= rhs._ptr; }
			friend bool operator>( const iterator& lhs, const iterator& rhs ) { return lhs._ptr > rhs._ptr; }
			friend bool operator>=( const iterator& lhs, const iterator& rhs ) { return lhs._ptr >= rhs._ptr; }

			iterator&	operator++() { _ptr++; return *this; }
			iterator&	operator--() { _ptr--; return *this; }
			iterator&	operator+=( int n ) { _ptr += n; return *this; }
			iterator&	operator-=( int n ) { _ptr -= n; return *this; }

			iterator	operator++(int) {

				iterator tmp = *this;
				++(*this);
				return tmp;
			}
			iterator	operator--( int ) {

				iterator tmp = *this;
				--(*this);
				return tmp;
			}

			iterator		operator+( difference_type n ) const { return iterator(_ptr + n); }
			iterator		operator-( difference_type n ) const { return iterator(_ptr - n); }
			friend iterator	operator+( difference_type n, const iterator& rhs ) { return iterator(rhs._ptr + n); }
			friend difference_type operator-( const iterator & lhs, const iterator& rhs ) { return lhs._ptr - rhs._ptr; }

			pointer	_ptr;
	};


	template< class T >
	class const_iterator {
		
		public:
			typedef std::ptrdiff_t					difference_type;
			typedef const T							value_type;
			typedef const T*						pointer;
			typedef const T& 						reference;
			typedef std::random_access_iterator_tag	iterator_category;

			const_iterator( void ) {}
			const_iterator( pointer ptr ) : _ptr(ptr) {}
			const_iterator( const iterator<T>& other) : _ptr(other._ptr) {}
			const_iterator( const const_iterator& other ) { *this = other; }
			~const_iterator( void ) {}
			
			const_iterator &	operator=( const const_iterator& other ) {
			
			if (this != &other)
					_ptr = other._ptr;
				return *this;
			}

			reference	operator*( void ) const { return *_ptr; }
			pointer		operator->( void ) const { return _ptr; }
			
			reference	operator[]( int n ) const { return *(_ptr + n); }

			friend bool	operator==( const const_iterator& lhs, const const_iterator& rhs ) { return lhs._ptr == rhs._ptr; }
			friend bool	operator!=( const const_iterator& lhs, const const_iterator& rhs ) { return lhs._ptr != rhs._ptr; }
			friend bool operator<( const const_iterator& lhs, const const_iterator& rhs ) { return lhs._ptr < rhs._ptr; }
			friend bool	operator<=( const const_iterator& lhs, const const_iterator& rhs ) { return lhs._ptr <= rhs._ptr; }
			friend bool operator>( const const_iterator& lhs, const const_iterator& rhs ) { return lhs._ptr > rhs._ptr; }
			friend bool operator>=( const const_iterator& lhs, const const_iterator& rhs ) { return lhs._ptr >= rhs._ptr; }

			const_iterator&	operator++( void ) { _ptr++; return *this; }
			const_iterator&	operator--( void ) { _ptr--; return *this; }
			const_iterator	operator++( int ) {
		
				const_iterator tmp = *this;
				++(*this);
				return tmp;
			}
			const_iterator	operator--( int ) {
				
				const_iterator tmp = *this;
				--(*this);
				return tmp;
			}
			const_iterator&	operator+=( int n ) { _ptr += n; return *this; }
			const_iterator&	operator-=( int n ) { _ptr -= n; return *this; }
			const_iterator	operator+( difference_type n ) const { return const_iterator(_ptr + n); }
			const_iterator	operator-( difference_type n ) const { return const_iterator(_ptr - n); }
			friend const_iterator	operator+( difference_type n, const const_iterator& rhs) { return const_iterator(rhs._ptr + n); }
			friend difference_type	operator-( const const_iterator & lhs, const const_iterator& rhs ) { return lhs._ptr - rhs._ptr; }

			pointer	_ptr;
	};
}

#endif
