/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:23:12 by sanghwal          #+#    #+#             */
/*   Updated: 2023/08/01 13:37:51 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
    : AForm(target, SCF_SIGN, SCF_EXEC) {}

ShrubberyCreationForm::ShrubberyCreationForm(
    const ShrubberyCreationForm& origin)
    : AForm(origin) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(
    const ShrubberyCreationForm& origin) {
  if (this != &origin) AForm::operator=(origin);
  return (*this);
}

static void _MakeTree(Bureaucrat const& executor) {
  std::ofstream outfile(executor.getName() + "_shrubbery");

  if (!outfile.is_open()) throw std::invalid_argument("open oufile error");
  std::string ascii_tree =
      "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣦⣼⠻⠿⣦⣄⠀⢀⣼⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀"
      "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⡾⠃⠀⠀⠀⠉⠙⠚⠙⢿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
      "⠀⠀⠀⠀⠀⠀⢀⣴⡾⣦⢾⣦⣤⠀⠀⢀⢙⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠉⣿⡀⢀⣼⠿⣷⣼⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠"
      "⡴⠾⠋⠀⠀⠀⠉⣻⡿⠞⠛⢻⣅⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠙⡿⠛⠁⠀⠉⠁⠛⣿⣾⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⢿⡄⠀⠀⠀⠀"
      "⠀⠀⠈⠁⠀⠀⠀⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀"
      "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⣹⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
      "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⡶⣿⡉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⢰⣦⣶⣶⣤⣀⠀⠀⠀⠀⢹⣷⣶⣦⣤⡶⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
      "⠀⠀⠀⠀⠀⠀⠀⠈⢻⣦⠀⢹⣧⣦⣴⠆⢠⣦⣦⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⢀⣠⣶⡾⠃⠀⠀⠉⠟⠷⢶⣶⣶⡀⠀⣀⣤⣸⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣀⣤⣠⣤"
      "⡶⣿⣳⠟⠁⣤⣾⠀⠀⠘⠷⠋⠀⣸⣇⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⢰⣿⠟⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠷⡼⠏⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⠛⠀⠈⠘⠃⠉⠀⠀⠈⠛⠒"
      "⠋⠀⠀⠀⠀⠀⠀⠀⠈⠉⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⣰⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⡄⢀⣴⡇⠀⢀⣠⣾⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
      "⠀⠀⠀⠀⢾⡇⢀⣀⡀⠀⠀⠀⠀⠀⠀\n⠋⣿⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣤⠀⠀⠀⢿⡽⣿⠿⣧⠷⣼⣧⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈"
      "⠛⠋⢯⡆⠀⠀⠀⠀⠀⠀\n⠀⣾⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠋⠱⣿⣿⢶⠀⠀⢣⣿⡆⠈⡷⢷⡜⣷⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠇⠀"
      "⠀⠀⠀⠀⠀\n⢸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⣓⣾⠽⣇⠀⢁⡞⠑⠛⢻⡾⣷⣀⡄⣀⣤⣠⠄⠀⣠⣤⠀⠀⠀⠀⠀⠀⣀⡀⣤⣠⣤⡼⣉⣤⣦⡀⢀⠀⠀⠀"
      "\n⠈⠙⣿⣄⠀⣠⣦⡄⠀⠀⢰⣶⣆⠀⠀⡀⠀⠀⠀⠀⢠⣀⣴⠋⠉⠹⣆⢹⣄⠸⠀⢠⠟⢸⠃⠈⠉⢻⡏⢻⠁⠀⢠⣟⣞⣀⠀⠀⢀⠀⠀⠿⢽⣧⣹⣠⣿⠏⠉⠙⠛⢻⣖⠴⣦\n⠀⠀⠛"
      "⠿⠺⠻⠻⣧⣶⣴⣾⡿⣿⣴⠟⢛⡷⠂⠀⠀⡀⠀⠁⠀⠀⠀⠈⠛⣛⠓⣆⣞⠀⡏⠀⠀⠀⣸⠃⡏⢀⡠⠼⡟⢫⣧⡖⠊⠉⠀⠀⠀⠀⠀⠉⠙⠁⠀⠀⠀⠀⠀⠀⠀⣿\n⠀⠀⠀⠀⠀⠀⠀⠈"
      "⠛⢻⣿⣤⣀⠀⢠⡾⠁⠀⠀⠳⣽⠂⢀⠀⣀⡴⣶⣶⠉⢷⠈⠙⠀⣇⠀⠀⣰⢃⡼⠛⠉⣠⡤⠿⠻⣆⠙⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿\n⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⡏⠉⠻"
      "⡷⡞⠀⠀⠀⣠⠞⣠⠴⠞⠋⠁⠀⠈⢿⣇⡤⡶⠛⣷⣭⠀⠀⠀⠀⠁⣻⣋⣀⣀⣀⢀⣈⠳⠸⠷⠤⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸\n⠀⠀⠀⠀⢠⣾⣟⠟⠛⠋⠀⠀⠀⠀⠀⠀⠀⠠"
      "⢃⣰⠃⠀⠀⠀⠀⠀⠀⠈⠟⠀⠀⠀⢱⢿⡀⠠⡤⢤⣼⠟⠋⠛⠉⠋⠁⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⠻\n⠀⠀⠀⠀⠈⣿⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠁⠀⠀⠀"
      "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠇⣼⠁⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣄⣰⡞⠻⠃⠀\n⠀⠀⠀⠀⠀⢻⣧⣤⣀⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
      "⠀⣀⣀⣴⠾⠋⠀⠃⠠⡇⠀⠀⣀⡀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣛⣋⡁⠉⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠉⠙⠉⣿⢂⣄⠀⠀⠀⠀⠀⣿⢀⡀⠀⠀⠀⠀⠀⢴⣤⠶⠷⠛⠉⢳⠀"
      "⠀⠀⠀⣰⠿⣤⢦⠟⢻⢻⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠻⣻⠟⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣦⣴⣤⡿⢿⣋⣿⠇⠀⠀⠀⠀⠀⠈⠙⠲⡄⠀⠀⢸⠀⠀⠀⣰⠃⠀"
      "⠉⠉⠀⣾⡛⠁⠀⠀⠀⠀⠀⠀⠀⠀⣰⢦⣦⣤⣤⣴⡏⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠉⠀⠁⠀⠈⣯⡀⡀⡀⢀⠀⣠⡄⣼⠶⠾⠃⠀⠀⡞⠀⠀⠀⢹⠀⠀⠀⠀⠀⠈⢷"
      "⢦⣤⣄⠀⠀⠀⢠⣤⣴⠟⠀⠀⠉⠀⠈⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠓⠛⠛⠛⠋⠛⠋⠀⠀⠀⠀⠀⡇⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠈⠀⠹⠷⣾"
      "⡍⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣷⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠀⠀⠀⠀"
      "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
      "⠀⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡇⠀⠀⠸⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
      "⠀⠀\n⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡇⠀⠀⠀⢧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n⠀"
      "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠏⠀⠀⠀⠀⢈⡻⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";
  outfile << ascii_tree;
  outfile.close();
}

void ShrubberyCreationForm::execute(Bureaucrat const& executor) const {
  try {
    this->validExec(executor);
    _MakeTree(executor);
  } catch (std::exception& e) {
    throw;
  }
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
  std::cout << this->getName()
            << " [ShrubberyCreationForm] Destructor called\n";
}
