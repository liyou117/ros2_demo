cmake_minimum_required(VERSION 3.8)
project(demo_package)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(demo_interface REQUIRED)

include_directories(include)

add_executable(topic_publisher src/topic_publisher.cpp)
ament_target_dependencies(topic_publisher rclcpp demo_interface)

add_executable(topic_subscriber src/topic_subscriber.cpp)
ament_target_dependencies(topic_subscriber rclcpp demo_interface)

add_executable(service_server src/service_server.cpp)
ament_target_dependencies(service_server rclcpp demo_interface)

add_executable(service_client src/service_client.cpp)
ament_target_dependencies(service_client rclcpp demo_interface)

install(TARGETS
  topic_publisher
  topic_subscriber
  service_server
  service_client
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
