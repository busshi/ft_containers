/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 19:53:13 by aldubar           #+#    #+#             */
/*   Updated: 2021/11/01 20:09:47 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>
# include <limits>
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"
# include "comparison.hpp"
# include "type_traits.hpp"
# include "pair.hpp"

namespace	ft {

	template< class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class	map {
		
		public:

			/*
			* Member types
			*/

			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const Key, T>					value_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef tree<value_type>							tree;
			typedef map_iterator<value_type>				iterator;
			typedef const_map_iterator<value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			/*
			* Member classes
			*/

			class value_compare {

				protected:
					Compare	comp;

				public:
					typedef bool        result_type;
					typedef value_type  first_argument_type;
					typedef value_type  second_argument_type;

					value_compare( Compare c ): comp(c) {}
					~value_compare( void ) {}

					bool operator()( const value_type& lhs, const value_type& rhs ) const { return comp(lhs.first, rhs.first); }
			};

			/*
			* Member functions
			*/

			map( void ) { _init(Compare(), Allocator()); }
			explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) { _init(comp, alloc); }
			
			template< class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) {
				_init(comp, alloc);
			
				for (InputIt it = first; it != last; it++)
					insert(*it);
			}

			map( const map& other ) {

				_init(Compare(), Allocator());

				_comp = other._comp;
    			_alloc = other._alloc;
    			_node = other._node;

				for (const_iterator it = other.begin(); it != other.end(); it++)
					insert(*it);
			}

			~map( void ) {
				
				clear();
				_deallocNode(_end);
			}

			map&	operator=( const map& other ) {

				if (this != &other) {

					clear();
					_comp = other._comp;
    				_alloc = other._alloc;
    				_node = other._node;

					for (const_iterator it = other.begin(); it != other.end(); it++)
						insert(*it);
				}

				return *this;
			}

			allocator_type	get_allocator( void ) const { return _alloc; }

			/*
			* Elements access
			*/
			
			T&			at( const Key& key ) {

				iterator	tmp = find(key);

        		if (tmp == end())
            		throw std::out_of_range("map::at:  key not found");

        		return tmp->second;
			}

			const T&	at( const Key& key ) const {

				const_iterator	tmp = find(key);

        		if (tmp == end())
            		throw std::out_of_range("map::at:  key not found");

        		return tmp->second;
			}

			T&			operator[]( const Key& key ) {

          		iterator	tmp = find(key);
            
				if (tmp == end())
                	return insert(ft::make_pair(key, T())).first->second;
            	else
                	return tmp->second;
			}

			/*
			* Iterators
			*/
			
			iterator				begin( void ) {
				
				tree*	tmp = _root;

				while (tmp->left)
					tmp = tmp->left;

				return iterator(tmp);

			}
			const_iterator			begin( void ) const {

				tree*	tmp = _root;

				while (tmp->left)
					tmp = tmp->left;

				return iterator(tmp);
			}

			iterator				end( void ) { return iterator(_end); }
			const_iterator			end( void ) const { return const_iterator(_end); }

			reverse_iterator		rbegin( void ) { return reverse_iterator(end()); }
			const_reverse_iterator	rbegin( void ) const { return const_reverse_iterator(end()); }

			reverse_iterator		rend( void ) { return reverse_iterator(begin()); }
			const_reverse_iterator	rend( void ) const { return const_reverse_iterator(begin()); }

			/*
			* Capacity
			*/
			
			bool		empty( void ) const { return begin() == end(); }
			size_type	size( void ) const { return _size; }
			size_type	max_size( void ) const { return _node.max_size(); }

			/*
			* Modifiers
			*/

			void		clear( void ) {

				if (!_size)
					return;

				_clearTree(_root);
				_size = 0;
				_root = _end;
				_end->up = NULL;
				_alreadyIn = NULL;
				_latestAdded = NULL;
			}

			ft::pair<iterator, bool>	insert( const value_type& value ) {

				size_type	size = _size;
            	tree*		node;

				_insertNode(value, _root);
            	node = _size != size ? _latestAdded : _alreadyIn;
            	if (_root == _end) {

					_root = node;
					_root->right = _end;
					_end->up = _root;
            	}

				return ft::make_pair(iterator(node), _size != size);
			}

			iterator					insert( iterator hint, const value_type& value ) {
				
				size_type	size = _size;
				tree*		node;
				tree*		root = hint.node;

				while (root->up)
					root = root->up;

				_insertNode(value, root);
				node = _size != size ? _latestAdded : _alreadyIn;
				if (_root == _end) {

					_root = node;
					_root->right = _end;
					_end->up = _root;
				}

				return iterator(node);
			}

			template< class InputIt >
			void 						insert( InputIt first, InputIt last ) {
				
				for (InputIt it = first; it != last; it++)
					insert(*it);
			}

			void		erase( iterator pos ) { erase(pos.node->data.first); }

			void		erase( iterator first, iterator last ) {

				for (iterator it = first; it != last; it++)
					erase(it.node->data.first);
			}

			size_type	erase( const key_type& key ) {

				size_type	old_size = _size;
				_removeNode(key);

				return _size != old_size;
			}

			void		swap( map& other ) {

				tree*		root = _root;
				tree*		end = _end;
				tree*		latestAdded = _latestAdded;
				tree*		alreadyIn = _alreadyIn;
				size_type	size = _size;

				_root = other._root;
				other._root = root;

				_end = other._end;
				other._end = end;

				_latestAdded = other._latestAdded;
				other._latestAdded = latestAdded;

				_alreadyIn = other._alreadyIn;
				other._alreadyIn = alreadyIn;

				_size = other._size;
				other._size = size;
			}

			/*
			* Lookup
			*/

			size_type		count( const Key& key ) const { return find(key) != end(); }

			iterator		find( const Key& key ) {
				
				tree*	tmp = _searchNode(key);

				return (tmp != NULL && tmp != _end ? iterator(tmp) : end()); 
			}

			const_iterator	find( const Key& key ) const {

				tree*	tmp = _searchNode(key);
				
				return (tmp != NULL && tmp != _end ? iterator(tmp) : end()); 
			}

			ft::pair<iterator, iterator>				equal_range( const Key& key ) { return ft::make_pair(lower_bound(key), upper_bound(key)); }
			ft::pair<const_iterator, const_iterator>	equal_range( const Key& key ) const { return ft::make_pair(lower_bound(key), upper_bound(key)); }

			iterator		lower_bound( const Key& key ) {

				for (iterator it = begin(); it != end(); it++) {

					if (it->first == key || !_comp(it->first, key))
						return it;
				}
			
				return end();
			}

			const_iterator	lower_bound( const Key& key ) const {

				for (const_iterator it = begin(); it != end(); it++) {

					if (it->first == key || !_comp(it->first, key))
						return it;
				}

				return end();
			}

			iterator		upper_bound( const Key& key ) {

				for (iterator it = begin(); it != end(); it++) {

					if (it->first != key && !_comp(it->first, key))
						return it;
				}

				return end();
			}

			const_iterator	upper_bound( const Key& key ) const {

				for (const_iterator it = begin(); it != end(); it++) {

					if (it->first != key && !_comp(it->first, key))
						return it;
				}

				return end();
			}

			/*
			* Observers
			*/

			key_compare		key_comp( void ) const { return _comp; }

			value_compare	value_comp( void ) const { return value_compare(_comp); }


		private:

			Compare		_comp;
			Allocator	_alloc;			
			size_type	_size;
			tree*		_root;
			tree*		_end;
			tree*		_latestAdded;
			tree*		_alreadyIn;
			typename Allocator::template rebind<tree>::other	_node;

		    void	_init( const Compare& comp, const Allocator& alloc ) {

				_comp = comp;
				_alloc = alloc;
				_size = 0;
				_root = _addNode(ft::make_pair(key_type(), mapped_type()));
				_end = _root;
				_latestAdded = NULL;
				_alreadyIn = NULL;
			}

			tree*	_addNode( const value_type& data ) {

				tree*	tmp = _node.allocate(1);
				
				_alloc.construct(&tmp->data, data);
				tmp->left = NULL;
				tmp->right = NULL;
				tmp->up = NULL;
				
				return tmp;
			}

			tree*	_insertNode( const value_type& data, tree* node ) {

				if (node == NULL || node == _end) {
				
					_size++;
					_latestAdded = _addNode(data);

					if (node == _end) {
						
						_end->up = _latestAdded;
						_latestAdded->right = _end;
					}
				
					return _latestAdded;
				}
				if (_comp(data.first, node->data.first)) {
			
					tree* left_child = _insertNode(data, node->left);
					node->left = left_child;
					left_child->up = node;
				}
				else if (data.first != node->data.first) {
			
					tree* right_child = _insertNode(data, node->right);
					node->right = right_child;
					right_child->up = node;
				}
				else
					_alreadyIn = node;
		
				return node;
			}

			tree*	_searchNode( const Key& key, tree* node ) const {


				if (!node || node == _end || (node != NULL && node != _end && key == node->data.first))
					return node;
				else if (_comp(key, node->data.first))
					return _searchNode(key, node->left);
				else
					return _searchNode(key, node->right);
			}

			tree*	_searchNode( const Key& key ) const { return _searchNode(key, _root); }

			void	_deallocNode( tree* node ) {

				_alloc.destroy(&node->data);
				_node.deallocate(node, 1);
			}

			tree*	_removeNode( const key_type& key ) { return _removeNode(key, _root); }

			tree*	_removeNode( const key_type& key, tree* root ) {

				if (root == NULL || root == _end)
					return root;

				if (_comp(key, root->data.first)) {
			
					root->left = _removeNode(key, root->left);
					return root;
				}
				else if (_comp(root->data.first, key)) {
			
					root->right = _removeNode(key, root->right);
					return root;
				}

				_size--;
				
				return _removeNoChild(root);
			}

			tree*	_removeNoChild( tree* root ) {

				if (!root->left && !root->right) {
				
					if (root == _root)
						_root = _end;
					_deallocNode(root);
					
					return NULL;
				}
				else if (!root->left || !root->right) {
			
					tree*	tmp = root->left == NULL ? root->right : root->left;
					tmp->up = root->up;
					if (root == _root)
						_root = tmp;
					_deallocNode(root);
				
					return tmp;
				}
				else
					return _removeBothChildren( root);
			}

			tree*	_removeBothChildren( tree* root) {

				tree*	succ_up = root;
				tree*	succ = root->right;

				while (succ->left != NULL) {
				
					succ_up = succ;
					succ = succ->left;
				}
				if (succ_up != root)
					succ_up->left = succ->right;
				else
					succ_up->right = succ->right;
				if (succ->right)
					succ->right->up = succ_up;

				succ->right = root->right;
				if (succ->right)
					succ->right->up = succ;
					
				succ->left = root->left;
				if (succ->left)
					succ->left->up = succ;
					
				succ->up = root->up;
				if (root == _root)
					_root = succ;
					
				_deallocNode(root);
			
				return succ;
			}

			void	_clearTree( tree* node ) {
			
				if (node->left)
					_clearTree(node->left);

				if (node->right && node->right != _end)
					_clearTree(node->right);
				
				_deallocNode(node);
			}
	};

	/*
	* Non members functions
	*/

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {

		if (lhs.size() != rhs.size())
			return false;

		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) { return !(lhs == rhs); }

	template< class Key, class T, class Compare, class Alloc >
	bool	operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template< class Key, class T, class Compare, class Alloc >
	bool	operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) { return (lhs == rhs || lhs < rhs); }

	template< class Key, class T, class Compare, class Alloc >
	bool	operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) { return !(lhs <= rhs); }

	template< class Key, class T, class Compare, class Alloc >
	bool	operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) { return !(lhs < rhs); }

	template< class Key, class T, class Compare, class Alloc >
	void	swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ) { lhs.swap(rhs); }

}

#endif
