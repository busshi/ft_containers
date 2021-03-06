/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:24:12 by aldubar           #+#    #+#             */
/*   Updated: 2021/10/29 12:21:25 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace  ft {

	template< bool Cond, class T = void > struct enable_if {};

	template< class T > struct enable_if<true, T> { typedef T type; };



	template< class T >
	struct is_integral { static const bool value = false; };



	template<>
	struct is_integral<bool> { static const bool value = true; };

	template<>
	struct is_integral<char> { static const bool value = true; };

	template<>
	struct is_integral<short int> { static const bool value = true; };

	template<>
	struct is_integral<int> { static const bool value = true; };

	template<>
	struct is_integral<long int> { static const bool value = true; };

	template<>
	struct is_integral<long long int> { static const bool value = true; };

	template<>
	struct is_integral<float> { static const bool value = true; };

	template<>
	struct is_integral<double> { static const bool value = true; };

	template<>
	struct is_integral<long double> { static const bool value = true; };

	template<>
	struct is_integral<unsigned char> { static const bool value = true; };

	template<>
	struct is_integral<unsigned short int> { static const bool value = true; };

	template<>
	struct is_integral<unsigned int> { static const bool value = true; };

	template<>
	struct is_integral<unsigned long int> { static const bool value = true; };

	template<>
	struct is_integral<unsigned long long int> { static const bool value = true; };



	template<>
	struct is_integral<const bool> { static const bool value = true; };

	template<>
	struct is_integral<const char> { static const bool value = true; };

	template<>
	struct is_integral<const short> { static const bool value = true; };

	template<>
	struct is_integral<const int> { static const bool value = true; };

	template<>
	struct is_integral<const long> { static const bool value = true; };

	template<>
	struct is_integral<const long long> { static const bool value = true; };

	template<>
	struct is_integral<const float> { static const bool value = true; };

	template<>
	struct is_integral<const double> { static const bool value = true; };

	template<>
	struct is_integral<const long double> { static const bool value = true; };

	template<>
	struct is_integral<const unsigned char> { static const bool value = true; };

	template<>
	struct is_integral<const unsigned short> { static const bool value = true; };

	template<>
	struct is_integral<const unsigned int> { static const bool value = true; };

	template<>
	struct is_integral<const unsigned long> { static const bool value = true; };

	template<>
	struct is_integral<const unsigned long long> { static const bool value = true; };
}

#endif
