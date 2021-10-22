/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:21:08 by aldubar           #+#    #+#             */
/*   Updated: 2021/10/22 15:28:46 by aldubar          ###   ########.fr       */
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
	struct iterator_traits< T * > {
		typedef std::ptrdiff_t						difference_type;
		typedef T 									value_type;
		typedef T *									pointer;
		typedef T &									reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	template< class Iter >
	class reverse_iterator {
	
		public:
			typedef Iter												iterator_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::reference			reference;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;

		reverse_iterator( void ) : _currentIt() {}
		~reverse_iterator( void ) {}

		explicit reverse_iterator( iterator_type x ) : _currentIt(x) {}
		
		template< class U >
		reverse_iterator( const reverse_iterator<U> & src ) : _currentIt(src.base()) {}
	
		iterator_type		base( void ) const { return _currentIt; }

		template< class U >
		reverse_iterator &	operator=( const reverse_iterator<U> & rhs ) { _currentIt = rhs.base(); return *this; }
		
		reference			operator*( void ) const { Iter tmp = _currentIt; return *--tmp; }
		pointer				operator->( void ) const { return &(operator*()); }

		reference			operator[]( difference_type n ) const { return base()[- n - 1]; }

		reverse_iterator &	operator++( void ) { _currentIt--; return *this; }
		reverse_iterator &	operator--( void ) { _currentIt++; return *this; }
		reverse_iterator	operator++( int ) {

			reverse_iterator tmp = *this;
			_currentIt--;
			return tmp;
		}
		reverse_iterator operator--( int ) {
			
			reverse_iterator tmp = *this;
			_currentIt++;
			return tmp;
		}
		reverse_iterator operator+( difference_type n ) const { return reverse_iterator( base() - n ); }
		reverse_iterator operator-( difference_type n ) const { return reverse_iterator( base() + n ); }
		reverse_iterator& operator+=( difference_type n ) { _currentIt -= n; return *this; }
		reverse_iterator& operator-=( difference_type n ) { _currentIt += n; return *this; }

	protected:
		Iter _currentIt;
	};

	template< class It1, class It2 >
	bool operator==( const reverse_iterator<It1> & lhs, const reverse_iterator<It2>& rhs ) { return lhs.base() == rhs.base(); }
	template< class It1, class It2 >
	bool operator!=( const reverse_iterator<It1> & lhs, const reverse_iterator<It2> & rhs ) { return lhs.base() != rhs.base(); }
	template< class It1, class It2 >
	bool operator<( const reverse_iterator<It1> & lhs, const reverse_iterator<It2> & rhs ) { return lhs.base() > rhs.base(); }
	template< class It1, class It2 >
	bool operator<=( const reverse_iterator<It1> & lhs, const reverse_iterator<It2> & rhs ) { return lhs.base() >= rhs.base(); }
	template< class It1, class It2 >
	bool operator>( const reverse_iterator<It1> & lhs, const reverse_iterator<It2> & rhs ) { return lhs.base() < rhs.base(); }
	template< class It1, class It2 >
	bool operator>=( const reverse_iterator<It1> & lhs, const reverse_iterator<It2> & rhs ) { return lhs.base() <= rhs.base(); }

	template< class Iter >
	reverse_iterator<Iter>	operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter> & it ) { return reverse_iterator<Iter>(it.base() - n); }

	template< class It1, class It2 >
	typename reverse_iterator<It1>::difference_type	operator-( const reverse_iterator<It1> & lhs, const reverse_iterator<It2> & rhs ) { return rhs.base() - lhs.base(); }
}

#endif
