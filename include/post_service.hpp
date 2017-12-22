#ifndef MATADOR_EXAMPLE_POST_SERVICE_HPP
#define MATADOR_EXAMPLE_POST_SERVICE_HPP

#include "post.hpp"

#include <matador/object/object_ptr.hpp>

namespace matador {
  class session;
}

struct post_service
{
  explicit post_service(matador::session &ses);

  matador::object_ptr<post> add(std::string title, std::string content,
                                const matador::object_ptr<author> &writer, const matador::object_ptr<category> &cat);

  void remove(matador::object_ptr<post> &p);

  matador::session &session_;
};
#endif //MATADOR_EXAMPLE_POST_SERVICE_HPP
