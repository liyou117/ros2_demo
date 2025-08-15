#include "demo_package/topic_subscriber.hpp"

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "demo_interface/msg/num.hpp"

TopicSubscriber::TopicSubscriber() : rclcpp::Node("topic_subscriber_node")
{
  subscriber_ = this->create_subscription<demo_interface::msg::Num>(
    "demo_topic", 10,
    [this](const demo_interface::msg::Num::SharedPtr msg) {
      RCLCPP_INFO(this->get_logger(), "subscribe: %ld", msg->num);
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