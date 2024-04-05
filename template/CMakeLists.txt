cmake_minimum_required(VERSION 3.8)
project(__PKG_NAME__)

# ------------------------------------------
# 使用 C++ 14
# ------------------------------------------
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# ------------------------------------------
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ------------------------------------------
# 設定編譯類型和相依套件 
# ------------------------------------------
# ros
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
# qt
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# ------------------------------------------
# 添加可執行文件 
# ------------------------------------------
add_executable(__NODE_NAME__ 
  src/main.cpp
  src/mainwindow.cpp
  src/mainwindow.h
  src/mainwindow.ui
)

# ------------------------------------------
# 鏈接依賴項
# ------------------------------------------
# ros
target_link_libraries(__NODE_NAME__ 
  ${rclcpp_LIBRARIES} 
)
# qt
target_link_libraries(__NODE_NAME__ 
  Qt5::Core 
  Qt5::Gui
  Qt5::Widgets
)

# ------------------------------------------
# 包含其他包的標頭檔路徑
# ------------------------------------------
ament_target_dependencies(__NODE_NAME__ 
  rclcpp
  std_msgs
)

# ------------------------------------------
# 設置自動MOC、UIC和RCC (與QT相關)
# ------------------------------------------
set_target_properties(__NODE_NAME__ PROPERTIES AUTOMOC ON)
set_target_properties(__NODE_NAME__ PROPERTIES AUTOUIC ON)
set_target_properties(__NODE_NAME__ PROPERTIES AUTORCC ON)
# ------------------------------------------

# 安装可执行文件
install(TARGETS __NODE_NAME__
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()
