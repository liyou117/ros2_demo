#include "demo_service/service_server.hpp"

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "demo_interface/srv/add_two_ints.hpp"

ServiceServer::ServiceServer() : rclcpp::Node("service_server_node")
{
  server_ = this->create_service<demo_interface::srv::AddTwoInts>(
    "demo_service",
    [this](const std::shared_ptr<demo_interface::srv::AddTwoInts::Request> request,
      std::shared_ptr<demo_interface::srv::AddTwoInts::Response> response)
    {
      response->sum = request->a + request->b;
      RCLCPP_INFO(this->get_logger(), "%ld + %ld = %ld", request->a, request->b, response->sum);
    }
  );
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ServiceServer>());
  rclcpp::shutdown();
  return 0;
}