#ifndef POST_HPP
#define POST_HPP

#include "category.hpp"
#include "comment.hpp"
#include "author.hpp"

#include <matador/utils/time.hpp>

#include <matador/object/container.hpp>
#include <matador/object/object_ptr.hpp>

struct author;

struct post
{
  unsigned long id{};
  std::string title;
  matador::object_ptr<author> writer;
  matador::time created_at;
  matador::container<category> categories;
  matador::container<comment> comments;
  matador::container<std::string> tags;
  std::string content;

  post();

  post(std::string title, const matador::object_ptr<author> &autr, std::string cntnt);

  template < class Operator >
  void process(Operator &op)
  {
      namespace field = matador::access;
      field::primary_key(op, "id", id);
      field::attribute(op, "title", title, 255);
      field::belongs_to(op, "author", writer, matador::cascade_type::NONE);
      field::attribute(op, "created_at", created_at);
      field::has_many(op, "post_category", categories, "category_id", "post_id", matador::cascade_type::INSERT);
      field::has_many(op, "comment", comments, "comment", "id", matador::cascade_type::ALL);
      field::has_many(op, "post_tag", tags, "post_id", "tag", matador::cascade_type::ALL);
      field::attribute(op, "content", content);
  }
};

#endif /* POST_HPP */
