# Engine Only

file(GLOB_RECURSE GRPO-Engine-src "*.cpp")
file(GLOB_RECURSE GRPO-Engine-hpp "*.h")

set(MYENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "" FORCE)

add_library(GRPO-Engine ${GRPO-Engine-src} ${GRPO-Engine-hpp})

target_link_libraries(GRPO-Engine ${SGE_LIBRARIES})

target_include_directories(GRPO-Engine PUBLIC ${MYENGINE_INCLUDE_DIR})
target_include_directories(GRPO-Engine PUBLIC "3rdParty")
