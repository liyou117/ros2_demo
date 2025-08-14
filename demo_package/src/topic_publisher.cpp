#include "demo_package/topic_publisher.hpp"

#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

TopicPublisher::TopicPublisher() : rclcpp::Node("topic_publisher")
{
  publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
  std_msgs::msg::String message;
  message.data = "topic test";
  while (rclcpp::ok()) {
    publisher_->publish(message);
    RCLCPP_INFO(this->get_logger(), "publish: %s", message.data.c_str());
    rclcpp::sleep_for(std::chrono::seconds(1));
  }
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TopicPublisher>());
  rclcpp::shutdown();
  return 0;
}
