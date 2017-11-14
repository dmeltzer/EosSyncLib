cmake_minimum_required(VERSION 3.2)
project(EosSyncLib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES 
    EosLog.cpp
    EosOsc.cpp
    EosSyncLib.cpp
    EosTcp.cpp
    EosTimer.cpp
    EosUdp.cpp
    main.cpp
    OSCParser.cpp
)

set(HEADER_FILES
    EosLog.h
    EosOsc.h
    EosSyncLib.h
    EosTcp.h
    EosTimer.h
    EosUdp.h
    OSCParser.h
)
set(SOURCE_FILES 
    ${SOURCE_FILES}
    EosTcp_Mac.cpp
    EosUdp_Mac.cpp
)

if(WIN32)
    set(SOURCE_FILES
        ${SOURCE_FILES}
        EosTcp_Win.cpp
        EosTcp_Mac.cpp
    )
endif(WIN32)


add_library(eossynclib SHARED ${SOURCE_FILES})
install(TARGETS eossynclib DESTINATION lib)
INSTALL(FILES ${HEADER_FILES} DESTINATION include/EosSyncLib)
