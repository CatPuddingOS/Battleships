#SRC


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# source files
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

#header files
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*.h")

add_executable(app)

target_link_libraries(
	app
	PRIVATE
	app_headers
	SDL3::SDL3
)

target_sources(app 
	PRIVATE 
		${SRC_FILES}
	PUBLIC
		FILE_SET HEADERS
		BASE_DIRS ${CMAKE_SOURCE_DIR}/include
		FILES ${HEADER_FILES}
)

add_custom_command(TARGET app POST_BUILD
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different
		"$<TARGET_FILE:SDL3::SDL3>"
		"$<TARGET_FILE_DIR:app>"
)

#source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SRC_FILES})
#source_group(TREE "${CMAKE_SOURCE_DIR}/include" FILES ${HEADER_FILES})