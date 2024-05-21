cmake_minimum_required(VERSION 3.8)
project(__PKG_NAME__)

# ------------------------------------------
# Use C++ 17
# ------------------------------------------
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# ------------------------------------------
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ------------------------------------------
# Set compilation type and dependencies
# ------------------------------------------
# ROS
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
# Qt
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# ------------------------------------------
# Add executable
# ------------------------------------------
add_executable(__NODE_NAME__ 
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  src/mainwindow.ui
)

# ------------------------------------------
# Link dependencies
# ------------------------------------------
# ROS
target_link_libraries(__NODE_NAME__ 
  ${rclcpp_LIBRARIES} 
)
# Qt
target_link_libraries(__NODE_NAME__ 
  Qt5::Core 
  Qt5::Gui
  Qt5::Widgets
)

# ------------------------------------------
# Include header paths of other packages
# ------------------------------------------
ament_target_dependencies(__NODE_NAME__ 
  rclcpp
  std_msgs
)

# ------------------------------------------
# Set up automatic MOC, UIC, and RCC (related to Qt)
# ------------------------------------------
set_target_properties(__NODE_NAME__ PROPERTIES AUTOMOC ON)
set_target_properties(__NODE_NAME__ PROPERTIES AUTOUIC ON)
set_target_properties(__NODE_NAME__ PROPERTIES AUTORCC ON)
# ------------------------------------------

# Install executable
install(TARGETS __NODE_NAME__
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
