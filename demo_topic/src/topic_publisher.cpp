#include "demo_topic/topic_publisher.hpp"

#include <memory>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "demo_interface/msg/num.hpp"

TopicPublisher::TopicPublisher() : rclcpp::Node("topic_publisher_node")
{
  this->declare_parameter("param_num", rclcpp::ParameterValue(0));
  publisher_ = this->create_publisher<demo_interface::msg::Num>("demo_topic", 10);
  timer_ = this->create_wall_timer(
    std::chrono::seconds(1),
    [this]() {
      demo_interface::msg::Num message;
      message.num = this->get_parameter("param_num").as_int();
      publisher_->publish(message);
      RCLCPP_INFO(this->get_logger(), "publish: %ld", message.num);
    }
  );
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TopicPublisher>());
  rclcpp::shutdown();
  return 0;
}
