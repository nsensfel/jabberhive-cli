add_subdirectory(error)

set(
   SRC_FILES ${SRC_FILES}
   ${CMAKE_CURRENT_SOURCE_DIR}/main.c
   ${CMAKE_CURRENT_SOURCE_DIR}/signal.c
   ${CMAKE_CURRENT_SOURCE_DIR}/socket.c
)

set(SRC_FILES ${SRC_FILES} PARENT_SCOPE)
