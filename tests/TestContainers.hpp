/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestContainers.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldubar <aldubar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:27:13 by aldubar           #+#    #+#             */
/*   Updated: 2021/11/01 19:42:39 by aldubar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTCONTAINERS_HPP
# define TESTCONTAINERS_HPP

# include <iostream>
# include <string>

# define INT     "int"
# define STR     "std::string"
# define CHAR    "char"
# define RED     "\033[31m"
# define ORANGE  "\033[33m"
# define CLR     "\033[0m"
# define OK      "[ \033[32mOK\033[0m ]"
# define KO      "[ \033[31mKO\033[0m ]"

void    testingVector( void );
void    testingStack( void );
void    testingMap( void );

#endif
