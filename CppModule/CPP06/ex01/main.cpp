/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:55:41 by sanghwal          #+#    #+#             */
/*   Updated: 2023/07/26 20:36:29 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"

int	main(void) {
	Data	data = {"sanghwal", 2, 3};
	Data*	p_data = &data;
	// Data	wrong_data = {"wrong", 1, 1};
	// Data*	p_wrong = &wrong_data;

	uintptr_t uint_data = Serializer::serialize(p_data);
	Data*	after_dese = Serializer::deserialize(uint_data);

	if (p_data == after_dese) {
		std::cout << "p_data: " << p_data << " == afte_dese: " << after_dese;
		std::cout << "\np_data == after_dese!!\n";
	}
	else
		std::cout << "deserialize error\n";
	uintptr_t after_uint = Serializer::serialize(after_dese);
	
	if (uint_data == after_uint) {
		std::cout << "uint_data: " << uint_data << " == after_uint: " << after_uint;
		std::cout << "\nuint_data == after_uint!!\n";
	}
	else
		std::cout << "Serializer error\n";
}
