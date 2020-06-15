cmake_minimum_required(VERSION 3.16)
project(cook)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH )
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH "D:\\install\\mingwsecond\\5.12.8\\mingw73_64\\")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(cook main.cpp src/ui/window/MainWindow.cpp src/ui/window/MainWindow.h src/config/Config.h src/ui/widget/GameWidget.cpp src/ui/widget/GameWidget.h src/utility/RandInt.h src/utility/ConnectGameCore.cpp src/utility/ConnectGameCore.h src/ui/widget/MsgWidget.cpp src/ui/widget/MsgWidget.h)
target_link_libraries(cook Qt5::Widgets)
qt5_use_modules(cook Core Widgets Gui)