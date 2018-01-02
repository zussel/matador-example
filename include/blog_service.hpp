#ifndef MATADOR_EXAMPLE_POST_SERVICE_HPP
#define MATADOR_EXAMPLE_POST_SERVICE_HPP

#include "post.hpp"

#include <matador/object/object_ptr.hpp>

namespace matador {
  class session;
}

struct blog_service
{
  explicit blog_service(matador::session &ses);

  matador::object_ptr<author> create_author(const std::string &name, matador::date birthday);
  matador::object_ptr<category> create_category(const std::string &name, const std::string &desc);

  matador::object_ptr<post> add_post(std::string title, std::string content,
                                     const matador::object_ptr<author> &writer,
                                     const matador::object_ptr<category> &cat);

  bool remove_post(matador::object_ptr<post> p);

  matador::session &session_;
};
#endif //MATADOR_EXAMPLE_POST_SERVICE_HPP
