/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:19:01 by aldubar           #+#    #+#             */
/*   Updated: 2021/11/01 13:00:43 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstdlib>
# include <memory>
# include <stdexcept>
# include "vector_iterator.hpp"
# include "reverse_iterator.hpp"
# include "type_traits.hpp"
# include "comparison.hpp"

namespace	ft {
	
	template< class T, class Allocator = std::allocator<T> >
	class	vector {

		public:

			/*
			* Member types
			*/

			typedef T											value_type;
			typedef Allocator									allocator_type;
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
			Allocator	_alloc;
			size_type	_capacity;
			size_type	_size;
			T *			_data;

		public:

			/*
			* Member functions
			*/

			vector( void ): _alloc(Allocator()), _capacity(0), _size(0), _data(NULL) {}
			explicit vector( const Allocator & alloc ): _alloc(alloc), _capacity(0), _size(0), _data(NULL) {}
			
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator() ): _alloc(alloc), _capacity(count), _size(count), _data(_alloc.allocate(_capacity)) {
				
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_data + i, value);
			}

			template< class InputIt >
			vector( InputIt first, typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type last, const Allocator& alloc = Allocator()) {

				_capacity = 0;
				for (InputIt it = first; it != last; it++)
					_capacity++;

				_size = 0;
				_alloc = alloc;
				_data = _alloc.allocate(_capacity);
				
				for (InputIt it = first; it != last; it++)
					_alloc.construct(_data + _size++, *it);
			}
			
			vector( vector const& other ) {
				
				_alloc = other._alloc;
				_capacity = other._capacity;
				_size = other._size;
				_data = _alloc.allocate(_capacity);

				size_type	i = 0;
				for (const_iterator it = other.begin(); it != other.end(); it++)
					_alloc.construct(_data + i++, *it);
			}

			~vector( void ) {

				this->clear();
				_alloc.deallocate(_data, _capacity);
				_capacity = 0;
			}

			vector&	operator=( const vector& other ) {

				if (this != &other) {

					this->clear();
					if (other._size > _capacity)
						this->reserve(other._size);
					_alloc = other._alloc;

					for (const_iterator it = other.begin(); it != other.end(); it++)
						_alloc.construct(_data + _size++, *it);
				}

				return *this;
			}

			void			assign( size_type count, const T& value ) {

				this->clear();
				this->reserve(count);
				while (_size < count)
					_alloc.construct(_data + _size++, value);
			}

			template< class InputIt >
			void			assign( InputIt first, typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type last) {

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

				if (!(pos < size()))
					throw std::out_of_range("ft_vector: Out of range exception");
				return operator[](pos);
			}

			const_reference	at( size_type pos ) const {

				if (!(pos < size()))
					throw std::out_of_range("ft_vector: Out of range exception");
				return operator[](pos);
			}

			reference		operator[]( size_type pos ) { return _data[pos]; }
			const_reference	operator[]( size_type pos ) const { return _data[pos]; }

		//	reference		front( void ) { return _data[0]; }
		//	const_reference	front( void ) const { return _data[0]; }
			reference		front( void ) { return *begin(); }
			const_reference	front( void ) const { return *begin(); }

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

			void			reserve( size_type new_cap ) {

				if (new_cap > max_size())
					throw std::length_error("ft_vector: new capacity cannot be greater than max_size");
					
				else if (new_cap > _capacity)
					_realloc(new_cap);
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

			iterator		insert( iterator pos, const T& value ) {

				size_type	idx = pos - begin();
				size_type	pos_idx = idx;

				if (_size + 1 > _capacity)
					_realloc(!_size ? 1 : _size * 2);
				pos = iterator(_data + pos_idx);
				this->insert(pos, 1, value);
				
				return iterator(_data + idx);
			}

			void			insert( iterator pos, size_type count, const T& value ) {

				size_type	idx = pos - begin();
				if (_size + count > _capacity)
					_realloc(_size + count);

				if (!this->empty()) {

					for (size_type i = _size; i > idx; i--) {

						_alloc.construct(_data + i + count - 1, _data[i - 1]);
						_alloc.destroy(_data + i - 1);
					}
				}

				for (size_type i = idx; i < count + idx; i++)
					_alloc.construct(_data + i, value);
				
				_size += count;
			}

			template< class InputIt >
			void			insert( iterator pos, InputIt first, typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type last) {

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
				_alloc.destroy(_data + _size);
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
				while (len) {
					_alloc.destroy(_data + len);
					_size--;
					len--;
				}
				
				return (first);
			}

			void			push_back( const T& value ) { 

				if (_size >= _capacity)
					_realloc(_capacity == 0 ? 1 : _capacity * 2);
	
				_alloc.construct(_data + _size, value);
				_size++;
			}

			void			pop_back( void ) {

				if (_size) {

					_alloc.destroy(_data + _size - 1);
					_size--;
				}
			}

			void			resize( size_type count, T value = T() ) {

				if (count < _size)
					this->erase(begin() + count, end());
				else {
					if (count + _size > _capacity)
						_realloc(!_size ? count : _size * 2);
					this->insert(end(), count - _size, value);
				}
			}

			void			swap( vector& other ) {

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

				pointer	tmp = _alloc.allocate(n);

				for (size_type i = 0; i < _size; i++) {
					_alloc.construct(tmp + i, _data[i]);
					_alloc.destroy(_data + i);
				}
				_alloc.deallocate(_data, _capacity);
				_capacity = n;
				_data = tmp;
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
	bool	operator==( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs ) {
			
			if (lhs.size() != rhs.size())
				return false;

			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class T, class Alloc >
	bool	operator!=( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs ) { return !(lhs == rhs); }

	template< class T, class Alloc >
	bool	operator>( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs ) { return !(lhs <= rhs); }

	template< class T, class Alloc >
	bool	operator>=( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs ) { return !(lhs < rhs); }

	template< class T, class Alloc >
	bool	operator<=( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs ) { return (lhs < rhs || lhs == rhs); }

	template< class T, class Alloc >
	bool	operator<( const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs ) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template< class T, class Alloc >
	void	swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) { lhs.swap(rhs); }
}

#endif
