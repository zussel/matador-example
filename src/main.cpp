#include <matador/orm/persistence.hpp>
#include <matador/orm/session.hpp>
#include <matador/object/object_expression.hpp>

#include <post.hpp>
#include <post_service.hpp>

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

  {
    session s(p);

    post_service pservice(s);

    transaction tr = s.begin();
    try {
      auto me = s.insert(new author("sascha", date(29, 4, 1972)));
      auto main = s.insert(new category("Main", "Main category"));

      tr.commit();

      pservice.add("First post", "My first post content", me, main);
      pservice.add("Second post", "My first post content", me, main);
      pservice.add("Third post", "My first post content", me, main);
      pservice.add("Fourth post", "My first post content", me, main);

    } catch (std::exception &ex) {
      tr.rollback();
    }
  }

  p.clear();

  {
    session s(p);

    s.load();

    using t_post_view = object_view<post>;
    t_post_view posts(s.store());

    for (const auto &p : posts) {
      std::cout << "Post title: " << p->title << "\n";
    }


    // delete third post
    auto i = std::find_if(posts.begin(), posts.end(), [](const object_ptr<post> &p) {
      return p->title == "Third post";
    });

//    if (i != posts.end()) {
//      auto third = *i;
//      s.remove(third);
//    }
//
//    for (const auto &p : posts) {
//      std::cout << "Post title: " << p->title << "\n";
//    }
  }

  p.drop();

  return 0;
}
