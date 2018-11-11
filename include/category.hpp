#ifndef CATEGORY_HPP
#define CATEGORY_HPP

#include "matador/utils/identifier.hpp"
#include "matador/utils/varchar.hpp"

#include "matador/object/has_many.hpp"

struct post;

struct category
{
  matador::identifier<unsigned long> id;
  matador::varchar<255> name;
  std::string description;
  matador::has_many<post> posts;

  category() = default;
  explicit category(std::string n)
    : category(n, "")
  {}
  category(std::string n, std::string desc)
    : name(std::move(n)), description(std::move(desc))
  {}

  template < class Serializer >
  void serialize(Serializer &serializer)
  {
    serializer.serialize("id", id);
    serializer.serialize("name", name);
    serializer.serialize("description", description);
    serializer.serialize("post_category", posts, "category_id", "post_id", matador::cascade_type::NONE);
  }
};

#endif /* CATEGORY_HPP */
