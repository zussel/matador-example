#ifndef CATEGORY_HPP
#define CATEGORY_HPP

#include <matador/utils/identifier.hpp>

#include <matador/object/container.hpp>

struct post;

struct category
{
  unsigned long id{};
  std::string name;
  std::string description;
  matador::container<post> posts;

  category() = default;
  explicit category(std::string n)
    : category(std::move(n), "")
  {}
  category(std::string n, std::string desc)
    : name(std::move(n)), description(std::move(desc))
  {}

  template < class Operator >
  void process(Operator &op)
  {
      namespace field = matador::access;
      field::primary_key(op, "id", id);
      field::attribute(op, "name", name, 255);
      field::attribute(op, "description", description);
      field::has_many(op, "post_category", posts, "category_id", "post_id", matador::cascade_type::NONE);
  }
};

#endif /* CATEGORY_HPP */
