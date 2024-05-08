cmake_minimum_required(VERSION 3.1...3.23)

project( zadanierekrutacyjne )

find_package( CGAL QUIET COMPONENTS  )
if ( NOT CGAL_FOUND )
  message(STATUS "This project requires the CGAL library, and will not be compiled.")
  return()  
endif()

find_package( Boost REQUIRED )
if ( NOT Boost_FOUND )
  message(STATUS "This project requires the Boost library, and will not be compiled.")
  return()  
endif()

#add_subdirectory(library/tinyxml2-10.0.0)

create_single_source_cgal_program( "main.cpp" )

#target_link_libraries(main PUBLIC tinyxml2)