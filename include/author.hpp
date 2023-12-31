#ifndef AUTHOR_HPP
#define AUTHOR_HPP

#include "person.hpp"
#include "post.hpp"

#include <matador/object/container.hpp>

#include <matador/utils/base_class.hpp>

struct author : public person
{
  // many to one
  matador::container<post> posts;

  author() = default;
  author(const std::string &name, const matador::date &birthday);

  template < class Operator >
  void process(Operator &op)
  {
      namespace field = matador::access;
      field::process(op, *matador::base_class<person>(this));
      field::has_many(op, "post", posts, "post", "id", matador::cascade_type::NONE);
  }
};

#endif /* AUTHOR_HPP */