
set(wxWidgets_ROOT_DIR     D:/sw/CPPCompilersAndLibraries/wxWidgets-3.1.4/)

#USE WX DYNAMIC LIBRARIES (The libraries will need to be copied into the final directory)
#SET(wxWidgets_LIB_DIR      D:/sw/CPPCompilersAndLibraries/wxWidgets-3.1.4/lib/vc_x64_dll)
#USE WX STATIC LIBRARIES
SET(wxWidgets_LIB_DIR      D:/sw/CPPCompilersAndLibraries/wxWidgets-3.1.4/lib/vc_x64_lib)

SET(wxWidgets_LIBRARIES    D:/sw/CPPCompilersAndLibraries/wxWidgets-3.1.4/lib/)
SET(wxWidgets_INCLUDE_DIRS D:/sw/CPPCompilersAndLibraries/wxWidgets-3.1.4/include/)

set(wxWidgets_CONFIGURATION mswud)    #use this config for: debug
#set(wxWidgets_CONFIGURATION mswu)     #use this config for: release

set(SOURCE_FILES main.cpp MyFrame.cpp MyFrame.h MyApp.cpp MyApp.h)
add_executable(simpleFrame WIN32 ${SOURCE_FILES})

SET(wxWidgets_USE_LIBS)

find_package(wxWidgets COMPONENTS net core base REQUIRED)
if(wxWidgets_FOUND)
    message("wxWidgets found!")
    include(${wxWidgets_USE_FILE})
    target_link_libraries(simpleFrame ${wxWidgets_LIBRARIES})
else(wxWidgets_FOUND)
    message("wxWidgets NOT found!")
endif()
