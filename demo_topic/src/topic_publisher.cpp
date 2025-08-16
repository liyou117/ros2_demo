#include "demo_topic/topic_publisher.hpp"

#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "demo_interface/msg/num.hpp"

TopicPublisher::TopicPublisher() : rclcpp::Node("topic_publisher_node")
{
  publisher_ = this->create_publisher<demo_interface::msg::Num>("demo_topic", 10);
  demo_interface::msg::Num message;
  message.num = 0;
  while (rclcpp::ok()) {
    message.num++;
    publisher_->publish(message);
    RCLCPP_INFO(this->get_logger(), "publish: %ld", message.num);
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
