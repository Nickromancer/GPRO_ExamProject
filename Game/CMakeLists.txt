# Game Only

file(GLOB_RECURSE GRPO-Game-src "*.h" "*.cpp")

configure_file(${CMAKE_SOURCE_DIR}/GPRO_ExamProject/Game/data/scene.json ${CMAKE_BINARY_DIR}/GPRO_ExamProject/Game/data/scene.json COPYONLY)

add_executable(GRPO-Game ${GRPO-Game-src})

target_include_directories(GRPO-Game PUBLIC ${MYENGINE_INCLUDE_DIR})

target_link_libraries(GRPO-Game GRPO-Engine ${SGE_LIBRARIES})

# Copy project data to output path
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


IF (WIN32)
	## Copy dll's to output path
	file(COPY ${SGE_LIBRARIES_SHARED} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
	file(COPY ${SGE_LIBRARIES_SHARED} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
	file(COPY ${SGE_LIBRARIES_SHARED} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
ENDIF(WIN32)