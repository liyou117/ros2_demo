#ifndef DEMO_PACKAGE__TOPIC_SUBSCRIBER_HPP_
#define DEMO_PACKAGE__TOPIC_SUBSCRIBER_HPP_

#include "rclcpp/rclcpp.hpp"
#include "demo_interface/msg/num.hpp"

class TopicSubscriber : public rclcpp::Node
{
  public:
    TopicSubscriber();
    ~TopicSubscriber() = default;

  private:
    rclcpp::Subscription<demo_interface::msg::Num>::SharedPtr subscriber_;
};

#endif  // DEMO_PACKAGE__TOPIC_SUBSCRIBER_HPP_
