file(GLOB_RECURSE APPLICATION_SRC CONFIGURE_DEPENDS "*.h" "*.c" "*.hpp" "*.cpp")

add_executable(Application
	${APPLICATION_SRC}
)

set_target_properties(Application PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
	C_STANDARD 17
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
	POSITION_INDEPENDENT_CODE ON
	OUTPUT_NAME ExerciseGameMODE
)

target_include_directories(Application
	PRIVATE
		${PROJECT_SOURCE_DIR}/Application/src
)

target_link_libraries(Application
	PRIVATE 
		${OpenCV_LIBS}
		raylib
)

target_compile_definitions(Application
	PRIVATE
		APPLICATION
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(Application
		PRIVATE
			NOMINMAX
			_CRT_SECURE_NO_WARNINGS
			WIN32_LEAN_AND_MEAN
			APP_WINDOWS
	)
	if (MSVC)
		target_compile_options(Application
			PRIVATE
				/Zc:__cplusplus
		)
	elseif (MINGW)
		target_link_libraries(Application
			PRIVATE
				m
		)
		target_link_options(Application
			PRIVATE
		)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Application
			PRIVATE
		)
		target_link_options(Application
			PRIVATE
		)
	endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_definitions(Application
		PRIVATE
			APP_LINUX
	)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_link_libraries(Application
			PRIVATE
				dl
				m
  				pthread
		)
		target_link_options(Application PRIVATE
		)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_link_libraries(Application
			PRIVATE
		)
		target_link_options(Application
			PRIVATE
		)
	endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	target_compile_definitions(Application
		PRIVATE
			APP_OSX
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(Application
		PRIVATE
			APP_DEBUG
			DEBUG
	)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "CXX flags" FORCE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C flags" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Linker flags" FORCE)
	target_compile_definitions(Application
		PRIVATE
			APP_RELEASE
			NDEBUG
	)
endif()

add_custom_command(
	TARGET Application POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/Application/res
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
	COMMENT "Copying resource folder to binary directory"
)