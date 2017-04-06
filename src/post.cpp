#include "post.hpp"

post::post(const std::string &ttle,
     const matador::object_ptr<author> &autr,
     const matador::object_ptr<category> &ctgry,
     const std::string &cntnt
)
  : title(ttle), writer(autr), content(cntnt)
{
  categories.push_back(ctgry);
}
