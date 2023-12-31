#ifndef COMMENT_HPP
#define COMMENT_HPP

#include <matador/utils/time.hpp>

#include <matador/object/object_ptr.hpp>

struct comment
{
  unsigned long id{};
  std::string email;
  matador::object_ptr<post> blog_post;
  std::string content;
  matador::time created_at;  

  comment() = default;

  comment(std::string eml, std::string cnt)
    : email(std::move(eml)), content(std::move(cnt))
  {}

  template < class Operator >
  void process(Operator &op)
  {
      namespace field = matador::access;
      field::primary_key(op, "id", id);
      field::attribute(op, "email", email, 255);
      field::belongs_to(op, "post", blog_post, matador::cascade_type::NONE);
      field::attribute(op, "content", content);
      field::attribute(op, "created_at", created_at);
  }
};

#endif /* COMMENT_HPP */
