/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:19:01 by aldubar           #+#    #+#             */
/*   Updated: 2021/10/25 14:12:35 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstdlib>
# include <memory>
# include <stdexcept>
# include "iterator.hpp"
# include "reverse_iterator.hpp"
# include "type_traits.hpp"
# include "comparison.hpp"

namespace	ft {
	
	template< typename T, typename Alloc = std::allocator<T> >
	class	vector {

		public:

			/*
			* Member types
			*/

			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef std::ptrdiff_t								difference_type;
			typedef std::size_t									size_type;

			typedef ft::iterator<T>								iterator;
			typedef ft::const_iterator<T>						const_iterator;

			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			Alloc		_alloc;
			size_type	_capacity;
			size_type	_size;
			T *			_data;

		public:

			/*
			* Member functions
			*/

			vector( void ): _alloc(Alloc()), _capacity(0), _size(0), _data(NULL) {}
			explicit vector( const Alloc & alloc ): _alloc(alloc), _capacity(0), _size(0), _data(NULL) {}
			
			explicit vector( size_type n, const T & val = T(), const Alloc & alloc = Alloc() ): _alloc(alloc), _capacity(n), _size(n), _data(_alloc.allocate(_capacity)) {
				
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_data + i, val);
			}

			template< class InputIt >
			vector( InputIt first, InputIt last, const Alloc & alloc = Alloc(), typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL ) {

				_capacity = 0;
				for (InputIt it = first; it != last; it++)
					_capacity++;

				_size = 0;
				_alloc = alloc;
				_data = _alloc.allocate(_capacity);
				
				for (InputIt it = first; it != last; it++)
					_alloc.construct(_data + _size++, *it);
			}
			
			vector( vector const & src ) {
				
				_alloc = src._alloc;
				_capacity = src._capacity;
				_size = src._size;
				_data = _alloc.allocate(_capacity);

				size_type	i = 0;
				for (const_iterator it = src.begin(); it != src.end(); it++)
					_alloc.construct(_data + i++, *it);
			}

			virtual ~vector( void ) {

				this->clear();
				_alloc.deallocate(_data, _capacity);
				_capacity = 0;
			}

			vector &	operator=( vector const & rhs ) {

				if (this != &rhs) {

					this->clear();
					if (rhs._size > _capacity)
						this->reserve(rhs._size);
					_alloc = rhs._alloc;

					for (const_iterator it = rhs.begin(); it != rhs.end(); it++)
						_alloc.construct(_data + _size++, *it);
				}

				return *this;
			}

			void			assign( size_type n, T const & val ) {

				this->clear();
				this->reserve(n);
				while (_size < n)
					_alloc.construct(_data + _size++, val);
			}

			template< class InputIt >
			void			assign( InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL ) {

				this->clear();
				size_type	n = 0;
				for (InputIt it = first; it != last; it++)
					n++;
				this->reserve(n);

				_size = 0;
				for (InputIt it = first; it != last; it++, _size++)
					_alloc.construct(_data + _size, *it);
			}

			allocator_type	get_allocator( void ) const { return _alloc; }

			/*
			* Element access
			*/

			reference		at( size_type pos ) {

				if (pos >= _size)
					throw std::out_of_range("ft_vector: Out of range exception");
				return operator[](pos);
			}

			const_reference	at( size_type pos ) const {

				if (pos >= _size)
					throw std::out_of_range("ft_vector: Out of range exception");
				return operator[](pos);
			}

			reference		operator[]( size_type n ) { return _data[n]; }
			const_reference	operator[]( size_type n ) const { return _data[n]; }

			reference		front( void ) { return _data[0]; }
			const_reference	front( void ) const { return _data[0]; }

			reference		back( void ) { return _size != 0 ? _data[_size - 1] : _data[0]; }
			const_reference	back( void ) const { return _size != 0 ? _data[_size - 1] : _data[0]; }

			/*
			* Iterators
			*/

			iterator		begin( void ) { return iterator(_data); }
			iterator		end( void ) { return iterator(_data + _size); }
			
			const_iterator	begin( void ) const { return const_iterator(_data); }
			const_iterator	end( void ) const { return const_iterator(_data + _size); }

			reverse_iterator		rbegin( void ) { return reverse_iterator(end()); }
			reverse_iterator		rend( void ) { return reverse_iterator(begin()); }
			
			const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator(end()); }
			const_reverse_iterator	rend( void ) const { return const_reverse_iterator(begin()); }

			/*
			* Capacity
			*/
			bool			empty( void ) const { return (!_size ? true : false); }
			size_type		size( void ) const { return _size; }
			size_type		max_size( void ) const { return _alloc.max_size(); }
			size_type		capacity( void ) const { return _capacity; }

			void			reserve( size_type n ) {

				if (n > max_size())
					throw std::length_error("ft_vector: new capacity cannot be greater than max_size");
					
				else if (n > _capacity)
					_realloc(n);
			}

			/*
			* Modifiers
			*/

			void			clear( void ) {

				if (this->empty())
					return;

				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data + i);

				_size = 0;
			}

			void			insert( iterator pos, size_type n, T const & val ) {

				size_type	idx = pos - begin();
				if (_size + n > _capacity)
					_realloc(_size + n);

				if (!this->empty()) {

					for (size_type i = _size; i > idx; i--) {

						_alloc.construct(_data + i + n - 1, _data[i - 1]);
						_alloc.destroy(_data + i - 1);
					}
				}

				for (size_type i = idx; i < n + idx; i++)
					_alloc.construct(_data + i, val);
				
				_size += n;
			}

			iterator		insert( iterator pos, T const & val ) {

				size_type	idx = pos - begin();
				size_type	pos_idx = idx;

				if (_size + 1 > _capacity)
					_realloc(!_size ? 1 : _size * 2);
				pos = iterator(_data + pos_idx);
				this->insert(pos, 1, val);
				
				return iterator(_data + idx);
			}

			template< class InputIt >
			void			insert( iterator pos, InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL) {

				size_type	idx = pos - begin();
				size_type	n = 0;
				for (InputIt it = first; it != last; it++)
					n++;

				size_type	j = 0;
				while (_size + n > _capacity)
					_realloc(!_size ? n : (_size + j++) * 2);

				pos = iterator(_data + idx);
				size_type	i = 0;
				for (InputIt it = first; it != last; it++)
					insert(pos + i++, *it);
			}

			iterator		erase( iterator pos ) {

				if (pos != end())
					_leftShift(pos, 1);
				_size--;
				
				return (pos);
			}

			iterator		erase( iterator first, iterator last ) {

				size_type	len = 0;
				iterator	tmp(first);

				while (tmp++ != last)
					len++;
				if (first != end())
					_leftShift(first, len);
				_size -= len;
				
				return (first);
			}

			void			push_back( T const & val ) { 

				if (_size >= _capacity)
					_realloc(_capacity == 0 ? 1 : _capacity * 2);
	
				_alloc.construct(_data + _size, val);
				_size++;
			}

			void			pop_back( void ) {

				if (_size) {

					_alloc.destroy(_data + _size - 1);
					_size--;
				}
			}

			void			resize( size_type n, T val = T() ) {

				if (n < _size)
					this->erase(begin() + n, end());
				else {
					if (n + _size > _capacity)
						_realloc(!_size ? n : _size * 2);
					this->insert(end(), n - _size, val);
				}
			}

			void			swap( vector & other ) {

				allocator_type	alloc = other._alloc;
				pointer			data = other._data;
				size_type		size = other._size;
				size_type		capacity = other._capacity;

				other._alloc = _alloc;
				other._data = _data;
				other._size = _size;
				other._capacity = _capacity;

				_alloc = alloc;
				_data = data;
				_size = size;
				_capacity = capacity;
			}


		private:
			void		_realloc( size_type n ) {

				pointer	newData = _alloc.allocate(n);

				for (size_type i = 0; i < _size; i++) {
					_alloc.construct(newData + i, _data[i]);
					_alloc.destroy(_data + i);
				}
				_alloc.deallocate(_data, _capacity);
				_capacity = n;
				_data = newData;
			}

			void		_leftShift( iterator pos, size_type n ) {

				for (iterator it = pos; it != end() - n; it++) {

					_alloc.destroy(&(*it));
					_alloc.construct(&(*it), *(it + n));
				}
			}
	};

	/*
	* Non-member functions
	*/

	template< class T, class Alloc >
	bool	operator==( const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs ) {
			
			if (lhs.size() != rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class T, class Alloc >
	bool	operator!=( const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs ) { return !(lhs == rhs); }

	template< class T, class Alloc >
	bool	operator>( const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs ) { return !(lhs <= rhs); }

	template< class T, class Alloc >
	bool	operator>=( const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs ) { return !(lhs < rhs); }

	template< class T, class Alloc >
	bool	operator<=( const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs ) { return (lhs < rhs || lhs == rhs); }

	template< class T, class Alloc >
	bool	operator<( const ft::vector<T, Alloc> & lhs, const ft::vector<T, Alloc> & rhs ) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
}

#endif
