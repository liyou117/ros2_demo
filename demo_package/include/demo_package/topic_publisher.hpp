#ifndef TOPIC_PUBLISHER__TOPIC_PUBLISHER_HPP_
#define TOPIC_PUBLISHER__TOPIC_PUBLISHER_HPP_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicPublisher : public rclcpp::Node
{
  public:
    TopicPublisher();
    ~TopicPublisher() = default;

  private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

#endif  // TOPIC_PUBLISHER__TOPIC_PUBLISHER_HPP_
