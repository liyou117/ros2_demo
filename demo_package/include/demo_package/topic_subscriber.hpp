#ifndef DEMO_PACKAGE__TOPIC_SUBSCRIBER_HPP_
#define DEMO_PACKAGE__TOPIC_SUBSCRIBER_HPP_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicSubscriber : public rclcpp::Node
{
  public:
    TopicSubscriber();
    ~TopicSubscriber() = default;

  private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
};

#endif  // DEMO_PACKAGE__TOPIC_SUBSCRIBER_HPP_
