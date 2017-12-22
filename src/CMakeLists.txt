SET(SOURCES
  author.cpp
  person.cpp
  main.cpp
  post.cpp
  post_service.cpp)

SET(HEADER
  ../include/author.hpp
  ../include/category.hpp
  ../include/comment.hpp
  ../include/person.hpp
  ../include/post.hpp ../include/post_service.hpp)

ADD_EXECUTABLE(mblog ${SOURCES} ${HEADER})

TARGET_LINK_LIBRARIES(mblog
  matador-utils
  matador-object
  matador-sql
  matador-orm
  matador-sqlite
  ${CMAKE_DL_LIBS}
  ${DB_LIBRARIES}
)
