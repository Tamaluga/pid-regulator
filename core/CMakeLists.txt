# Core

set(TARGET ${LIBRARY_CORE})
set(INCLUDE_DIRECTORIES ".")
set(SOURCES
	"Regulator.c"
)

add_library(${TARGET} OBJECT ${SOURCES})
target_link_libraries(${TARGET})
target_include_directories(${TARGET} PUBLIC ${INCLUDE_DIRECTORIES})