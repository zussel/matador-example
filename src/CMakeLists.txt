SET(SOURCES
  author.cpp
  person.cpp
  main.cpp
  post.cpp
  blog_service.cpp)

SET(HEADER
  ../include/author.hpp
  ../include/category.hpp
  ../include/comment.hpp
  ../include/person.hpp
  ../include/post.hpp
  ../include/blog_service.hpp)

ADD_EXECUTABLE(mblog ${SOURCES} ${HEADER})

TARGET_LINK_LIBRARIES(mblog
  ${MATADOR_LIBRARIES}
  ${CMAKE_DL_LIBS}
  ${SQLITE3_LIBRARY}
)
