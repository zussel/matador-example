#include "blog_service.hpp"

#include <matador/orm/session.hpp>
#include <utility>

blog_service::blog_service(matador::session &ses)
  : session_(ses)
{}

matador::object_ptr<author> blog_service::create_author(const std::string &name, const matador::date& birthday)
{
  return session_.insert(new author(name, birthday));
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
    auto first = session_.insert(new post(std::move(title), writer, std::move(content)));

    first.modify()->categories.push_back(cat);

    tr.commit();

    return first;
  } catch (std::exception &ex) {
    std::cout << "Caught exception: " << ex.what() << "\n";
    tr.rollback();
    return {};
  }
}

bool blog_service::remove_post(matador::object_ptr<post> p)
{
  matador::transaction tr = session_.begin();
  try {
    auto pp = p.modify();
    pp->categories.clear();
    pp->comments.clear();
    pp->tags.clear();
    session_.remove(p);

    tr.commit();

    return true;
  } catch (std::exception &ex) {
    std::cout << "Caught exception: " << ex.what() << "\n";
    tr.rollback();
    return false;
  }
}
