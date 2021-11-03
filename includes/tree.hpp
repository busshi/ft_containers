/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 11:51:22 by aldubar           #+#    #+#             */
/*   Updated: 2021/11/01 13:02:32 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

namespace ft {

	template< class T >
	struct	tree {
	
		T 		data;
		bool	color;
		tree*	up;
		tree*	left;
		tree*	right;
		#ifdef __linux__
			int tree;
		#endif
	};

	template< class T >
	tree<T>*	tree_min( tree<T>* node ) {
		
		tree<T>* tmp = node;
		
		while (tmp->left)
			tmp = tmp->left;
		
		return tmp;
	}

	template< class T >
	tree<T>*	tree_max( tree<T>* node ) {

		tree<T>* tmp = node;
		
		while (tmp->right)
			tmp = tmp->right;
		
		return tmp;
	}

	template< class T >
	tree<T>*	previous_node( tree<T>* node ) {
		
		if (node->left)
			return tree_max(node->left);
		
		tree<T>*	up = node->up;
		
		while (up && node == up->left) {
		
			node = up;
			up = up->up;
		}

		return up;
	}

	template< class T >
	tree<T>*	next_node( tree<T>* node ) {
		
		if (node->right)
			return tree_min(node->right);
		
		tree<T>* up = node->up;

		while (up && node == up->right) {
		
			node = up;
			up = up->up;
		}

		return up;
	}
}

#endif
