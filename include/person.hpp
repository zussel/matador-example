#ifndef PERSON_HPP
#define PERSON_HPP

#include <matador/utils/access.hpp>
#include <matador/utils/date.hpp>

struct person
{
  unsigned long id{};
  std::string name;
  matador::date birthday;

  person() = default;
  person(std::string n, const matador::date &bd);

  template < class Operator >
  void process(Operator &op)
  {
      namespace field = matador::access;
      field::primary_key(op, "id", id);
      field::attribute(op, "name", name, 255);
      field::attribute(op, "birthday", birthday);
  }
};

#endif /* PERSON_HPP */
