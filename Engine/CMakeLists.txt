# Engine Only

file(GLOB_RECURSE GRPO-Engine-src "*.cpp")
file(GLOB_RECURSE GRPO-Engine-hpp "*.h")

set(MYENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "" FORCE)

add_library(GRPO-Engine ${GRPO-Engine-src} ${GRPO-Engine-hpp} "3rdParty/rapidjson/allocators.h" "3rdParty/rapidjson/document.h" "3rdParty/rapidjson/encodedstream.h" "3rdParty/rapidjson/encodings.h" "3rdParty/rapidjson/filereadstream.h" "3rdParty/rapidjson/filewritestream.h" "3rdParty/rapidjson/fwd.h" "3rdParty/rapidjson/istreamwrapper.h" "3rdParty/rapidjson/memorybuffer.h" "3rdParty/rapidjson/memorystream.h" "3rdParty/rapidjson/ostreamwrapper.h" "3rdParty/rapidjson/pointer.h" "3rdParty/rapidjson/prettywriter.h" "3rdParty/rapidjson/rapidjson.h" "3rdParty/rapidjson/reader.h" "3rdParty/rapidjson/schema.h" "3rdParty/rapidjson/stream.h" "3rdParty/rapidjson/stringbuffer.h" "3rdParty/rapidjson/writer.h" "3rdParty/rapidjson/error/en.h" "3rdParty/rapidjson/error/error.h" "3rdParty/rapidjson/internal/biginteger.h" "3rdParty/rapidjson/internal/diyfp.h" "3rdParty/rapidjson/internal/dtoa.h" "3rdParty/rapidjson/internal/ieee754.h" "3rdParty/rapidjson/internal/itoa.h" "3rdParty/rapidjson/internal/meta.h" "3rdParty/rapidjson/internal/pow10.h" "3rdParty/rapidjson/internal/regex.h" "3rdParty/rapidjson/internal/stack.h" "3rdParty/rapidjson/internal/strfunc.h" "3rdParty/rapidjson/internal/strtod.h" "3rdParty/rapidjson/internal/swap.h" "3rdParty/rapidjson/msinttypes/inttypes.h" "3rdParty/rapidjson/msinttypes/stdint.h")
target_link_libraries(GRPO-Engine ${SGE_LIBRARIES})

target_include_directories(GRPO-Engine PUBLIC "Engine")
target_include_directories(GRPO-Engine PUBLIC "3rdParty")
