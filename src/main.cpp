#include <matador/orm/persistence.hpp>
#include <matador/orm/session.hpp>
#include <matador/object/object_expression.hpp>

#include <post.hpp>
#include <blog_service.hpp>

using namespace matador;

int main()
{
  persistence p("mysql://root:root@127.0.0.1/matador_test");

  p.attach_abstract<person>("person");
  p.attach<author, person>("author");
  p.attach<comment>("comment");
  p.attach<category>("category");
  p.attach<post>("post");

  p.create();

  {
    session s(p);

    blog_service blogger(s);

    transaction tr = s.begin();
    try {
      auto me = blogger.create_author("sascha", date(29, 4, 1972));
      auto main = blogger.create_category("Main", "Main category");

      tr.commit();

      blogger.add_post("First post", "My first post content", me, main);
      blogger.add_post("Second post", "My second post content", me, main);
      blogger.add_post("Third post", "My third post content", me, main);
      blogger.add_post("Fourth post", "My fourth post content", me, main);

    } catch (std::exception &ex) {
      std::cout << "Caught exception: " << ex.what() << "\n";
      tr.rollback();
    }
  }

  p.clear();

  {
    session s(p);

    blog_service blogger(s);

    s.load();

    using t_post_view = object_view<post>;
    t_post_view posts(s.store());

    for (const auto &pst : posts) {
      std::cout << "Post title: " << pst->title << "\n";
    }

    // delete third post
    auto i = std::find_if(posts.begin(), posts.end(), [](const object_ptr<post> &p) {
      return p->title == "Third post";
    });

    if (i != posts.end()) {
      blogger.remove_post(*i);
    }

    posts = t_post_view(s.store());
    for (const auto &pst : posts) {
      std::cout << "Post title: " << pst->title << "\n";
    }
  }

  p.drop();

  return 0;
}
