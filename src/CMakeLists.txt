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
  ../include/post.hpp ../include/blog_service.hpp)

ADD_EXECUTABLE(mblog ${SOURCES} ${HEADER})

TARGET_LINK_LIBRARIES(mblog
  ${CMAKE_DL_LIBS}
  ${MATADOR_LIBRARIES}
  ${MATADOR_BACKEND_SQLITE_LIBRARY}
  ${SQLITE3_LIBRARY}
)
