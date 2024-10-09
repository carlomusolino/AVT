if(NOT VT_ROOT )
set(VT_ROOT "")
set(VT_ROOT "$ENV{VT_ROOT}")
endif()

message(STATUS "Searching path ${VT_ROOT}")

find_package( virtual-transport REQUIRED PATHS "${VT_ROOT}" ) 

message(STATUS "virtual-transport libraries: ${VT_LIBRARIES}")
message(STATUS "virtual-transport includes: ${VT_INCLUDE_DIR}")

if( NOT TARGET vt::vt )
    add_library( vt::vt IMPORTED INTERFACE )

    set_property(TARGET vt::vt APPEND PROPERTY 
                 INTERFACE_INCLUDE_DIRECTORIES  "${VT_INCLUDE_DIRS}")
    set_property(TARGET vt::vt APPEND PROPERTY 
                 INTERFACE_LINK_LIBRARIES  "${VT_LIBRARIES}")
endif()