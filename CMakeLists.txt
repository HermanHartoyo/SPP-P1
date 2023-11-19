cmake_minimum_required(VERSION 3.23)
project(code_task)

set(CMAKE_CXX_STANDARD 14)

include_directories(ParallelNbody/include)
include_directories(ParallelNbody/include/gui)

add_executable(code_task
        ParallelDaxpy/daxpy.cpp
        ParallelNbody/include/gui/SimulationGUI.h
        ParallelNbody/include/Body.h
        ParallelNbody/include/Config.h
        ParallelNbody/include/Logger.h
        ParallelNbody/include/PTime.h
        ParallelNbody/include/SimGUIAdapter.h
        ParallelNbody/include/Simulation.h
        ParallelNbody/include/SimulationData.h
        ParallelNbody/include/Vec2.h
        ParallelNbody/src/gui/SimulationGUI.cpp
        ParallelNbody/src/Body.cpp
        ParallelNbody/src/Config.cpp
        ParallelNbody/src/OmpPractical.cpp
        ParallelNbody/src/Simulation.cpp
        ParallelQuickSort/quicksort.cpp)
