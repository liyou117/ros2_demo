#include "demo_package/topic_subscriber.hpp"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

TopicSubscriber::TopicSubscriber() : rclcpp::Node("topic_subscriber")
{
  subscriber_ = this->create_subscription<std_msgs::msg::String>(
    "topic", 10,
    [this](const std_msgs::msg::String::SharedPtr msg) {
      RCLCPP_INFO(this->get_logger(), "subscribe: %s", msg->data.c_str());
    }
  );
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TopicSubscriber>());
  rclcpp::shutdown();
  return 0;
}