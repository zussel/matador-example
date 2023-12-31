#include "post.hpp"

using namespace matador;

post::post()
: tags(255) {}

post::post(std::string ttle, const object_ptr<author> &autr, std::string cntnt)
: title(std::move(ttle))
, writer(autr)
, content(std::move(cntnt))
, tags(255)
{}
