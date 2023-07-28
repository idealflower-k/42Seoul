/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:14:50 by sanghwal          #+#    #+#             */
/*   Updated: 2023/07/28 14:03:21 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
class Array {
 private:
  T* array;
  unsigned int arr_size;

 public:
  Array();
  Array(unsigned int n);
  Array(const Array<T>& origin);
  Array<T>& operator=(const Array<T>& origin);

  unsigned int size() const;
  T& operator[](unsigned int n);

  ~Array();
};

#include "Array.tpp"

#endif
