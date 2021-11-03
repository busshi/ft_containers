/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:21:08 by aldubar           #+#    #+#             */
/*   Updated: 2021/10/29 15:40:10 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace	ft {

	template< class Iter >
	struct iterator_traits {
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template< class T >
	struct iterator_traits< T* > {
		typedef std::ptrdiff_t						difference_type;
		typedef T 									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	template< class Iter >
	class reverse_iterator {
	
		/*
		* Member types
		*/

		public:
			typedef Iter												iterator_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::reference			reference;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;

		/*
		* Member functions
		*/

		reverse_iterator( void ) : _current() {}
		~reverse_iterator( void ) {}

		explicit reverse_iterator( iterator_type x ) : _current(x) {}
		
		template< class U >
		reverse_iterator( const reverse_iterator<U>& other ) : _current(other.base()) {}
	
		template< class U >
		reverse_iterator&	operator=( const reverse_iterator<U>& other ) { _current = other.base(); return *this; }

		iterator_type		base( void ) const { return _current; }
		
		reference			operator*( void ) const { Iter tmp = _current; return *--tmp; }
		pointer				operator->( void ) const { return &(operator*()); }

		reference			operator[]( difference_type n ) const { return base()[- n - 1]; }

		reverse_iterator&	operator++( void ) { _current--; return *this; }
		reverse_iterator&	operator--( void ) { _current++; return *this; }
		reverse_iterator	operator++( int ) {

			reverse_iterator tmp = *this;
			_current--;
			return tmp;
		}
		reverse_iterator operator--( int ) {
			
			reverse_iterator tmp = *this;
			_current++;
			return tmp;
		}
		reverse_iterator	operator+( difference_type n ) const { return reverse_iterator( base() - n ); }
		reverse_iterator	operator-( difference_type n ) const { return reverse_iterator( base() + n ); }
		reverse_iterator&	operator+=( difference_type n ) { _current -= n; return *this; }
		reverse_iterator&	operator-=( difference_type n ) { _current += n; return *this; }

		/*
		* Member objects
		*/

	protected:
		Iter _current;
	};

	/*
	* Non-member functions
	*/

	template< class Iterator1, class Iterator2 >
	bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return lhs.base() == rhs.base(); }

	template< class Iterator1, class Iterator2 >
	bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return lhs.base() != rhs.base(); }

	template< class Iterator1, class Iterator2 >
	bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return lhs.base() > rhs.base(); }
	
	template< class Iterator1, class Iterator2 >
	bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return lhs.base() >= rhs.base(); }
	
	template< class Iterator1, class Iterator2 >
	bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return lhs.base() < rhs.base(); }
	
	template< class Iterator1, class Iterator2 >
	bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return lhs.base() <= rhs.base(); }

	template< class Iter >
	reverse_iterator<Iter>	operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) { return reverse_iterator<Iter>(it.base() - n); }

	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type	operator-( const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs ) { return rhs.base() - lhs.base(); }

	template< class Iterator1, class Iterator2 >
	typename reverse_iterator<Iterator1>::difference_type	operator-( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) { return rhs.base() - lhs.base(); }
}

#endif
