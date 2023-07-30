/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:33:17 by sanghwal          #+#    #+#             */
/*   Updated: 2023/07/30 16:06:31 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <algorithm>
#include <deque>
#include <exception>
#include <iostream>
#include <limits>
#include <list>
#include <vector>

class Span {
 private:
  std::vector<int> storage;
  unsigned int max_size;
  Span();

 public:
  Span(unsigned int N);
  Span(const Span& origin);
  Span& operator=(const Span& origin);

  void addNumber(int num);
  template <typename InputItr>
  void addNumber(InputItr begin, InputItr end) {
    if (std::distance(begin, end) + this->storage.size() <= this->max_size) {
      this->storage.insert(this->storage.end(), begin, end);
    } else
      throw std::length_error("storage is full!!!\n");
  }
  unsigned int shortestSpan() const;
  unsigned int longestSpan() const;

  ~Span();
};

#endif
