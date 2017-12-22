#include <matador/orm/persistence.hpp>
#include <matador/orm/session.hpp>

#include "person.hpp"
#include "author.hpp"

using namespace matador;

int main()
{
  persistence p("sqlite://mblog.sqlite");

  p.attach<person>("person", object_store::abstract);
  p.attach<author, person>("author");
  p.attach<comment>("comment");
  p.attach<category>("category");
  p.attach<post>("post");

  p.create();

  session s(p);

  transaction tr = s.begin();
  try {
    auto me = s.insert(new author("sascha", date(29, 4, 1972)));
    auto main = s.insert(new category("Main", "Main category"));

    auto first = s.insert(new post("First post", me, "My first post content"));

    s.push_back(first->categories, main);

    tr.commit();
  } catch(std::exception &ex) {
    tr.rollback();
  }

  p.drop();

  return 0;
}
