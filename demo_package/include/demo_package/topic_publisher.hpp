#ifndef DEMO_PACKAGE__TOPIC_PUBLISHER_HPP_
#define DEMO_PACKAGE__TOPIC_PUBLISHER_HPP_

#include "rclcpp/rclcpp.hpp"
#include "demo_interface/msg/num.hpp"

class TopicPublisher : public rclcpp::Node
{
  public:
    TopicPublisher();
    ~TopicPublisher() = default;

  private:
    rclcpp::Publisher<demo_interface::msg::Num>::SharedPtr publisher_;
};

#endif  // DEMO_PACKAGE__TOPIC_PUBLISHER_HPP_
