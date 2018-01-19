cmake_minimum_required(VERSION 3.8)
project(mesh_seg)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        3dOperator.cpp
        3dOperator.h
        bsp_Frame1.cpp
        bsp_Frame1.h
        bsp_Frame2.cpp
        bsp_Frame2.h
        bsp_Frame3.cpp
        bsp_Frame3.h
        bsp_part.cpp
        bsp_part.h
        csy_ALLPART.cpp
        csy_ALLPART.h
        csy_Pitching.cpp
        csy_Pitching.h
        DialogLabel.cpp
        dijkstra.cpp
        dijkstra.h
        gy_fitting.cpp
        gy_fitting.h
        gy_show.cpp
        gy_show.h
        lty_STL.cpp
        lty_STL.h
        main.cpp
        Point3d.cpp
        Point3d.h
        Util.cpp
        Util.h
        zc_VRudder.cpp
        zc_VRudder.h)

add_executable(mesh_seg ${SOURCE_FILES})