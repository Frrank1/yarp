# Copyright: (C) 2009 RobotCub Consortium
# Authors: Paul Fitzpatrick, Giorgio Metta, Lorenzo Natale
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

set(YARP_HAS_MATH_LIB FALSE)
if (CREATE_LIB_MATH)
    set(YARP_HAS_MATH_LIB TRUE)
endif()

if (YARP_HAS_MATH_LIB)

    project(YARP_math)

    set(YARP_math_HDRS include/yarp/math/api.h
                       include/yarp/math/Math.h
                       include/yarp/math/NormRand.h
                       include/yarp/math/Rand.h
                       include/yarp/math/RandnScalar.h
                       include/yarp/math/RandnVector.h
                       include/yarp/math/RandScalar.h
                       include/yarp/math/RandVector.h
                       include/yarp/math/SVD.h
                       include/yarp/math/Quaternion.h
                       include/yarp/math/FrameTransform.h)

    if(NOT CREATE_LIB_MATH_USING_GSL)
        set(YARP_math_IMPL_HDRS include/yarp/impl/mt.h)
    endif()

    set(YARP_math_SRCS src/math.cpp
                       src/NormRand.cpp
                       src/Rand.cpp
                       src/RandnVector.cpp
                       src/RandVector.cpp
                       src/SVD.cpp
                       src/Quaternion.cpp
                       src/FrameTransform.cpp)

    if( NOT CREATE_LIB_MATH_USING_GSL )
        list(APPEND YARP_math_SRCS src/eigen/eigen_math.cpp)
        list(APPEND YARP_math_SRCS src/eigen/eigen_SVD.cpp)
        list(APPEND YARP_math_SRCS src/eigen/RandScalar.cpp)
        list(APPEND YARP_math_SRCS src/eigen/RandnScalar.cpp)
        list(APPEND YARP_math_SRCS src/mt.cc)
    else()
        list(APPEND YARP_math_SRCS src/gsl/gsl_math.cpp)
        list(APPEND YARP_math_SRCS src/gsl/gsl_SVD.cpp)
        list(APPEND YARP_math_SRCS src/gsl/RandScalar.cpp)
        list(APPEND YARP_math_SRCS src/gsl/RandnScalar.cpp)
    endif()

    source_group("Source Files" FILES ${YARP_math_SRCS})
    source_group("Header Files" FILES ${YARP_math_HDRS})
    source_group("Implementation Header Files" FILES ${YARP_math_IMPL_HDRS})

    set_property(GLOBAL APPEND PROPERTY YARP_TREE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
    get_property(YARP_TREE_INCLUDE_DIRS GLOBAL PROPERTY YARP_TREE_INCLUDE_DIRS)

    include_directories(${YARP_TREE_INCLUDE_DIRS})

    if(NOT CREATE_LIB_MATH_USING_GSL)
        include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR})
    else()
        include_directories(SYSTEM ${GSL_INCLUDE_DIRS})
    endif()

    # import math symbols from standard cmath
    add_definitions(-D_USE_MATH_DEFINES)

    add_library(YARP_math ${YARP_math_SRCS}
                          ${YARP_math_HDRS}
                          ${YARP_math_IMPL_HDRS})
    target_link_libraries(YARP_math LINK_PRIVATE YARP_OS)
    target_link_libraries(YARP_math LINK_PRIVATE YARP_sig)

    if(CREATE_LIB_MATH_USING_GSL)
        target_link_libraries(YARP_math LINK_PRIVATE YARP_gsl)
        target_link_libraries(YARP_math LINK_PRIVATE ${GSL_LIBRARIES})
    endif()

    set_property(TARGET YARP_math PROPERTY PUBLIC_HEADER ${YARP_math_HDRS})
    set_property(TARGET YARP_math PROPERTY PRIVATE_HEADER ${YARP_math_IMPL_HDRS})

    install(TARGETS YARP_math
            EXPORT YARP
            COMPONENT runtime
            RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/yarp/math"
            PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/yarp/math/impl")

    set_property(GLOBAL APPEND PROPERTY YARP_LIBS YARP_math)
    set_property(TARGET YARP_math PROPERTY INCLUDE_DIRS ${YARP_TREE_INCLUDE_DIRS})
endif()

set_property(GLOBAL PROPERTY YARP_HAS_MATH_LIB ${YARP_HAS_MATH_LIB})
