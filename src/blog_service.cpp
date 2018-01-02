#include "blog_service.hpp"

#include <matador/orm/session.hpp>

blog_service::blog_service(matador::session &ses)
  : session_(ses)
{}

matador::object_ptr<author> blog_service::create_author(const std::string &name, matador::date birthday)
{
  return session_.insert(new author(name, std::move(birthday)));
}

matador::object_ptr<category> blog_service::create_category(const std::string &name, const std::string &desc)
{
  return session_.insert(new category(name, desc));
}

matador::object_ptr<post> blog_service::add_post(std::string title, std::string content,
                                                 const matador::object_ptr<author> &writer,
                                                 const matador::object_ptr<category> &cat)
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

bool blog_service::remove_post(matador::object_ptr<post> p)
{
  matador::transaction tr = session_.begin();
  try {
    session_.clear(p->categories);
    session_.clear(p->comments);
    session_.clear(p->tags);
    session_.remove(p);

    tr.commit();

    return true;
  } catch (std::exception &ex) {
    tr.rollback();
    return false;
  }
}
