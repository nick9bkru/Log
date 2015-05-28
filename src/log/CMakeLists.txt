##############################################
set (PROJECT_NAME log)
project(${PROJECT_NAME})
cmake_minimum_required(VERSION 2.6)
message("################# CMAKE ${PROJECT_NAME} ####################### ")
###############################################
set(CMAKE_MODULE_PATH 
${CMAKE_SOURCE_DIR}/cmake 
${CMAKE_SOURCE_DIR}/cmake/externModules
)
message(${CMAKE_MODULE_PATH})
#Preven warn
if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
###############################################
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
###############################################
set(HEADERS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_BUILD_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
###############################################
include_directories(${CMAKE_SOURCE_DIR}/src_lib/)
include_directories(${TEST_BUILD_DIRECTORY}/${PROJECT_NAME})
###############################################
set(LIBRARIES_NAME_
)
###############################################
### подключаем БИБЛИОТЕКИ
set(LIBRARIES_NAME
# QtNetwork
#thread
)
###############################################
message("Libraries will link ")
foreach(LIBRARY ${LIBRARIES_NAME_})
   include_directories(${CMAKE_SOURCE_DIR}/src_lib/${LIBRARY}/ ${CMAKE_SOURCE_DIR}/src_lib/${LIBRARY}/include)
   message(${CMAKE_SOURCE_DIR}/src_lib/${LIBRARY}/)
endforeach(LIBRARY)
#set(RPM_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/rpm)
###############################################
include_directories(${HEADERS_DIRECTORY} ${SOURCES_DIRECTORY})
message("HEADERS_DIRECTORY - " ${HEADERS_DIRECTORY})
message("SOURCES_DIRECTORY - " ${SOURCES_DIRECTORY})
###############################################
set(HEADERS
${HEADERS_DIRECTORY}/log.h
${HEADERS_DIRECTORY}/typeOut.h
${HEADERS_DIRECTORY}/typeOutFile.h
)
##############################################
set(SOURCES
${SOURCES_DIRECTORY}/main.cpp
${SOURCES_DIRECTORY}/log.cpp
${SOURCES_DIRECTORY}/typeOutFile.cpp
)
message("SOURCES---------------- - " ${SOURCES})
###############################################
#Включение в зависимости только h-ов, чтобы при 
#изменении cpp'ов в библиотеках не пересобиралось все подряд
message("######    include headers !!!!!!")
INCLUDE(IncludeOnlyHeaders)
include_only_headers(${HEADERS}})

################################################
message( "######## add_definitions")
add_definitions(-pipe -O2 -Wall -Wunused-parameter -g -ggdb -fPIC -D_REENTRANT -W -std=c++11 ) #для профилировщика gprof
message( "######## add_executable")
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

###############################################
#set(ALLLIBS ${Boost_LIBRARIES} ${LIBRARIES_TESTER_NAME})
#подключаем qt
message( "######## target_link_libraries all LIBRARIES")
target_link_libraries (${PROJECT_NAME} ${LIBRARIES_NAME})  
#target_link_libraries(${PROJECT_TESTER} ${ALLLIBS})
###############################################
install(TARGETS ${PROJECT_NAME} DESTINATION ${RUNTIME_OUTPUT_DIRECTORY})
###############################################
