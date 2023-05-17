/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:59:08 by sanghwal          #+#    #+#             */
/*   Updated: 2023/05/17 20:43:59 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Point.h"

Point::Point()
	: x(0), y(0) {}

Point::Point(const float _fixed_num1, const float _fixed_num2)
	: x(Fixed(_fixed_num1)), y(Fixed(_fixed_num2)) {}

Point::Point(const Point& origin)
	: x(origin.x), y(origin.y) {}