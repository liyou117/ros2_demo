#ifndef DEMO_PACKAGE__SERVICE_CLIENT_HPP_
#define DEMO_PACKAGE__SERVICE_CLIENT_HPP_

#include "rclcpp/rclcpp.hpp"
#include "demo_interface/srv/add_two_ints.hpp"

class ServiceClient : public rclcpp::Node
{
  public:
    ServiceClient();
    ~ServiceClient() = default;

    rclcpp::Client<demo_interface::srv::AddTwoInts>::SharedPtr client_;
    std::shared_ptr<demo_interface::srv::AddTwoInts::Request> request_;
};

#endif  // DEMO_PACKAGE__SERVICE_CLIENT_HPP_
