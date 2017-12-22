#include "post_service.hpp"

#include <matador/orm/session.hpp>

post_service::post_service(matador::session &ses)
  : session_(ses)
{}

matador::object_ptr<post> post_service::add(std::string title, std::string content,
                                            const matador::object_ptr<author> &writer, const matador::object_ptr<category> &cat)
{
  matador::transaction tr = session_.begin();
  try {
    auto first = session_.insert(new post(title, writer, content));

    session_.push_back(first->categories, cat);

    tr.commit();

    return first;
  } catch (std::exception &ex) {
    tr.rollback();
    return matador::object_ptr<post>();
  }
}

void post_service::remove(matador::object_ptr<post> &p)
{
  session_.remove(p);
}
