/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testMap.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:36:13 by aldubar           #+#    #+#             */
/*   Updated: 2021/11/02 10:10:41 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTMAP_HPP
# define TESTMAP_HPP

# include "TestContainers.hpp"

# if STL
    namespace ft = std;
    #include <map>
# else
    #include "map.hpp"
# endif

template< class T >
void	display( T map, std::string keyType, std::string valueType ) {

	std::cout << std::endl << "[+] map<" << keyType << "," << valueType << "> content: " << std::endl << std::endl << "{ ";

	typename T::iterator	it, ite = map.end();
	for (it = map.begin(); it != ite; it++)
		std::cout << it->first << ":" << it->second << " ";

	std::cout << "}" << std::endl << std::endl;
}

template< class T >
void	checkSize( T map, std::string keyType, std::string valueType ) {

	std::cout << "[+] Testing size, max_size, empty" << std::endl;
	std::cout << "map<" << keyType << ", " << valueType << "> size: " << map.size() << std::endl;
	std::cout << "map<" << keyType << ", " << valueType << "> max_size: " << map.max_size() << std::endl;
	std::cout << std::boolalpha << "is empty ? " << map.empty() << std::endl;

	std::cout << std::endl << "-------------------------" << std::endl;
}

template< class T, class A >
T		fillMap( T map, A array, size_t size ) {

	std::cout << "[+] Testing map::operator[]" << std::endl;
	for (size_t i = 0; i < size; i++)
		map[-i - 1] = array[i];

	return map;
}

template< class T >
void	checkErase( T map, std::string keyType, std::string valueType ) {

	std::cout << "🔽 Map content BEFORE erase" << std::endl;
	display(map, keyType, valueType);
	checkSize(map, keyType, valueType);

	std::cout << std::endl << "🔽 Map content AFTER erase the first element" << std::endl;
	map.erase(map.begin());
	display(map, keyType, valueType);
	checkSize(map, keyType, valueType);

	std::cout << std::endl << "🔽 Map content AFTER erase the last element" << std::endl;
	map.erase(--map.end());
	display(map, keyType, valueType);
	checkSize(map, keyType, valueType);

	std::cout << std::endl << "🔽 Map content AFTER erase a range of elements keeping the first and the last" << std::endl;
	map.erase(++map.begin(), --map.end());
	display(map, keyType, valueType);
	checkSize(map, keyType, valueType);

	std::cout << "🔽 Map content AFTER erase all elements remaining" << std::endl;
	for (int i = 0; i < 2; i++)
		map.erase(map.begin());

	display(map, keyType, valueType);
	checkSize(map, keyType, valueType);
}

template< class T >
void	checkAt( T map, size_t size ) {

	std::cout << std::endl << std::endl << "[+] Checking map.at()" << std::endl;
	
	for (size_t i = 0; i < size; i++)
		std::cout << "value for key [" << i << "] is [" << map.at(i) << "]" << std::endl;

	try {
		std::cout << "Trying to access a key out of range [" << size << "] " << map.at(size) << std::endl;
	}
	catch (std::exception &e) {
		std::cout << RED << "Exception catched" << CLR << std::endl;
	}
}

template< class T, class A >
void	runTests( T map, std::string keyType, std::string valueType, A array, size_t size ) {

	display(map, keyType, valueType);
	checkSize(map, keyType, valueType);

	std::cout << "[+] Adding elements in the container..." << std::endl;
	T	m = fillMap(map, array, size);
	display(m, keyType, valueType);
	checkSize(m, keyType, valueType);

	std::cout << "[+] Erasing elements in the container..." << std::endl;
	checkErase(m, keyType, valueType);
}

template< class T, class A >
T		tryInsert( T map, A arrayKey, A arrayValue, size_t size ) {

	ft::pair<typename T::iterator, bool> ret;

	for (size_t i = 0; i < size; i++) {

		ret = map.insert(ft::make_pair(arrayKey[i], arrayValue[i]));
		std::cout << "Pair key [" << ret.first->first << "] value: [" << ret.first->second << "]";
		std::cout << (ret.second ? "\033[32m has been inserted\033[0m" : "\033[31m failed to be inserted\033[0m") << std::endl;
	}

	return map;
}

template< class T, class A >
void	moreTests( T map, A arrayKey, A arrayValue, size_t size, std::string keyType, std::string valueType) {

	std::cout << "🔽 Map BEFORE INSERT" << std::endl;
	display(map, keyType, valueType);
	checkSize(map, keyType, valueType);

	std::cout << "[+] Trying to insert pairs key/value" << std::endl;
	map = tryInsert(map, arrayKey, arrayValue, size);


	std::cout << std::endl << "[+] Trying to insert AGAIN the same pairs key/value" << std::endl;
	map = tryInsert(map, arrayKey, arrayValue, size);


	std::cout << std::endl << "🔽 Map AFTER INSERT" << std::endl;
	display(map, keyType, valueType);
	checkSize(map, keyType, valueType);


	std::cout << "[+] Testing insert with a range..." << std::endl;

	std::cout << std::endl << "🔽 New map AFTER INSERT A RANGE of elements" << std::endl;
	T	range(++(map.begin()), --(map.end()));
	display(range, keyType, valueType);
	checkSize(range, keyType, valueType);


	std::cout << "[+] Clear the map..." << std::endl;
	map.clear();
	display(map, keyType, valueType);
	checkSize(map, keyType, valueType);

	std::cout << "[+] Clear the last map..." << std::endl;
	range.clear();
	display(range, keyType, valueType);
	checkSize(range, keyType, valueType);
}

template< class T >
void	checkIt( T map ) {

	std::cout << "Display with iterators..." << std::endl;
	for (typename T::iterator it = map.begin(); it != map.end(); ++it)
        std::cout << "[" << it->first << " : " << it->second << "] ";

	std::cout << std::endl << std::endl << "Display with const_iterators..." << std::endl;
	for (typename T::const_iterator it = map.begin(); it != map.end(); ++it)
        std::cout << "[" << it->first << " : " << it->second << "] ";

	std::cout << std::endl << std::endl << "Display with reverse_iterators..." << std::endl;
	for (typename T::reverse_iterator it = map.rbegin(); it != map.rend(); ++it)
        std::cout << "[" << it->first << " : " << it->second << "] ";

	std::cout << std::endl << std::endl << "Display with const_reverse_iterators..." << std::endl;
	for (typename T::const_reverse_iterator it = map.rbegin(); it != map.rend(); ++it)
        std::cout << "[" << it->first << " : " << it->second << "] ";

}

template< class T, class A >
void	checkCopySwap( T map, A array, int size, std::string keyType, std::string valueType ) {

	for (int i = 0; i < size; i++)
		map[i] = array[i];

	std::cout << std::endl << "🔽 Original container" << std::endl;
	display(map, keyType, valueType);

	T	copy = map;
	T	copy2(map);

	std::cout << "🔽 Copy container" << std::endl;
	display(copy, keyType, valueType);

	std::cout << "🔽 Copy2 container" << std::endl;
	display(copy2, keyType, valueType);

	std::cout << "Adding " << size - 1 << " elements in the copy container..." << std::endl;
	for (int i = 0; i < size; i++)
		copy[-i] = array[i];

	std::cout << std::endl << "Adding " << size / 2 - 1 << " elements in the copy2 container..." << std::endl;
	for (int i = 0; i < size / 2; i++)
		copy2[-i] = array[i];

	std::cout << std::endl << "🔽 Original container AFTER" << std::endl;
	display(map, keyType, valueType);

	std::cout << "🔽 Copy container AFTER" << std::endl;
	display(copy, keyType, valueType);

	std::cout << "🔽 Copy2 container AFTER" << std::endl;
	display(copy2, keyType, valueType);


	std::cout << ORANGE << "[+] Testing SWAP" << CLR << std::endl;
	copy.swap(copy2);

	std::cout << "🔽 Copy container AFTER SWAP" << std::endl;
	display(copy, keyType, valueType);

	std::cout << "🔽 Copy2 container AFTER SWAP" << std::endl;
	display(copy2, keyType, valueType);

	std::cout << "[+] Swap back copy and copy2 containers..." << std::endl;
	ft::swap(copy, copy2);

	std::cout << "🔽 Copy container AFTER SWAP BACK" << std::endl;
	display(copy, keyType, valueType);

	std::cout << "🔽 Copy2 container AFTER SWAP BACK" << std::endl;
	display(copy2, keyType, valueType);
	
}

template< class T, class A, class T2 >
void	checkCount( T map, A array, size_t size, std::string keyType, std::string valueType, T2 notAKey ) {

	display(map, keyType, valueType);

	for (size_t i = 0; i < size; i++)
		std::cout << "existing key [" << array[i] << "] => " << map.count(array[i]) << std::endl;

	std::cout << "not existing key [" << notAKey << "] => " << map.count(notAKey) << std::endl;

	std::cout << std::endl << "-------------------------" << std::endl;
}

template< class T, class C >
void	findKey( T map, C content ) {

		typename T::iterator	found = map.find(content);

		if (found != map.end())
			std::cout << "finding key [" << content << "] => " << found->first << ":" << found->second << std::endl;
		else
			std::cout << "finding key [" << content << "] => " << RED << "Not found" << CLR << std::endl;
}

template< class T, class A, class K >
void	checkFind( T map, A array, size_t size, std::string keyType, std::string valueType, K notAKey ) {

	display(map, keyType, valueType);

	for (size_t i = 0; i < size; i++)
		findKey(map, array[i]);

	findKey(map, notAKey);

	std::cout << std::endl << "-------------------------" << std::endl;
}

template< class T, class T2 >
void	checkEqualRange( T map, std::string keyType, std::string valueType, T2 key ) {

	display(map, keyType, valueType);

	typename T::iterator lower, upper, ite = map.end();

	ft::pair<typename T::iterator, typename T::iterator>	range;

	lower = map.lower_bound(key);
	upper = map.upper_bound(key);
	range = map.equal_range(key);

	std::cout << "lower_bound(" << key << ") [";
	if (lower == ite)
		std::cout << "--end--]" << std::endl;
	else
		std::cout << lower->first << ":" << lower->second << "]" << std::endl;

	std::cout << "upper_bound(" << key << ") [";
	if (upper == ite)
		std::cout << "--end--]" << std::endl;
	else
		std::cout << upper->first << ":" << upper->second << "]" << std::endl;

	std::cout << "equal_range(" << key << ") " << ((range.first == lower && range.second == upper) ? OK : KO) << std::endl;


	std::cout << std::endl << "-------------------------" << std::endl;
}

template< class T >
void	checkComparison( T m1, T m2, std::string keyType, std::string valueType, std::string s ) {

	std::cout << std::boolalpha;
	std::cout << "▶️  " << s << " map<" << keyType << "," << valueType << ">" << std::endl;
	std::cout << "is equal? " << (m1 == m2) << std::endl;
	std::cout << "is not equal? " << (m1 != m2) << std::endl;
	std::cout << "is greater or equal than? " << (m1 >= m2) << std::endl;
	std::cout << "is lower or equal than? " << (m1 <= m2) << std::endl;
	std::cout << "is greater than ? " << (m1 > m2) << std::endl;
	std::cout << "is lower than ? " << (m1 < m2) << std::endl;

	std::cout << "-------------------------" << std::endl;
}

struct ModuloComp {

	bool operator()(const int lhs, const int rhs) const { return (lhs % 97) < (rhs % 97); }
};

template< class T >
struct Comp {

	bool operator()(T lhs, T rhs) const { return (lhs < rhs); }
};

template< class T, class It >
void	compare( T map, It it, It it2) {

	bool	keyRes = map.key_comp()(it->first, it2->first);
	bool	valueRes = map.value_comp()(*it, *it2);

	std::cout << "key [" << it->first << "] vs [" << it2->first << "] ==> " << keyRes << " | " << valueRes << std::endl;
}

template< class T >
void	checkCmp( T map ) {

	std::cout << std::boolalpha;

	for (typename T::const_iterator it = map.begin(); it != map.end(); it++)
		for (typename T::const_iterator it2 = map.begin(); it2 != map.end(); it2++)
			compare(map, it, it2);
}

template< class T >
void	checkModuloCmp( T map ) {

	ft::map<int, char, ModuloComp>::key_compare	comp_func = map.key_comp();

	for (typename T::iterator it = map.begin(); it != map.end(); it++) {

        bool	before = comp_func(it->first, 100);
        bool	after = comp_func(100, it->first);

        std::cout << '[' << it->first << ':' << it->second;

        if (!before && !after)
            std::cout << "] equivalent to key 100\n";
        else if (before)
            std::cout << "] goes before key 100\n";
        else if (after)
            std::cout << "] goes after key 100\n";
    }
}

template< class T, class T2, class T3 >
void	checkLower( T map, T2 content, T3 cmp ) {

	for (typename T::const_iterator it = map.begin(); it != map.end(); it++) {

        bool	lower = cmp(it->second, content);

        std::cout << "value of pair [" << it->first << ":" << it->second;

        if (lower)
            std::cout << "] is lower than value " << content << std::endl;
        else
            std::cout << "] is greater or equal to value " << content << std::endl;
    }
}

#endif
