#INCLUDE


add_library(app_headers INTERFACE)

target_include_directories(
	app_headers
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)

