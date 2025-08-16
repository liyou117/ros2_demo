#include "demo_service/service_client.hpp"

#include <memory>
#include <string>
#include <chrono>

#include "rclcpp/rclcpp.hpp"
#include "demo_interface/srv/add_two_ints.hpp"

ServiceClient::ServiceClient() : rclcpp::Node("service_client_node")
{
  client_ = this->create_client<demo_interface::srv::AddTwoInts>("demo_service");
  request_ = std::make_shared<demo_interface::srv::AddTwoInts::Request>();
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  
  if (argc != 3) {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "input error");
    return 1;
  }

  auto node = std::make_shared<ServiceClient>();
  while (!node->client_->wait_for_service(std::chrono::seconds(1))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "exit");
      return 2;
    }
    RCLCPP_INFO(node->get_logger(), "waiting......");
  }

  node->request_->a = std::stoll(argv[1]);
  node->request_->b = std::stoll(argv[2]);
  auto result = node->client_->async_send_request(node->request_);
  if (rclcpp::spin_until_future_complete(node, result) == rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_INFO(node->get_logger(), "result: %ld", result.get()->sum);
  } else {
    RCLCPP_ERROR(node->get_logger(), "fail");
  }

  rclcpp::shutdown();
  return 0;
}