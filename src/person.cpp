#include "person.hpp"

using namespace matador;

person::person(std::string n, const date &bd)
  : name(std::move(n)), birthday(bd)
{}
