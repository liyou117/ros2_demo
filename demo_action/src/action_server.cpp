#include "demo_action/action_server.hpp"

#include <memory>
#include <functional>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "demo_interface/action/count.hpp"

ActionServer::ActionServer() : rclcpp::Node("action_server_node")
{
  action_server_ = rclcpp_action::create_server<demo_interface::action::Count>(
    this,
    "demo_action",
    std::bind(&ActionServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
    std::bind(&ActionServer::handle_cancel, this, std::placeholders::_1),
    std::bind(&ActionServer::handle_accepted, this, std::placeholders::_1));
}

rclcpp_action::GoalResponse ActionServer::handle_goal(
  const rclcpp_action::GoalUUID & uuid,
  std::shared_ptr<const demo_interface::action::Count::Goal> goal)
{
  RCLCPP_INFO(this->get_logger(), "handle goal: %ld", goal->start_num);
  (void)uuid;
  if (goal->start_num < 0) {
    return rclcpp_action::GoalResponse::REJECT;
  }
  return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse ActionServer::handle_cancel(
  const std::shared_ptr<GoalHandleCount> goal_handle)
{
  RCLCPP_INFO(this->get_logger(), "handle cancel");
  (void)goal_handle;
  return rclcpp_action::CancelResponse::ACCEPT;
}

void ActionServer::handle_accepted(const std::shared_ptr<GoalHandleCount> goal_handle)
{
  std::thread{std::bind(&ActionServer::execute, this, goal_handle)}.detach();
}

void ActionServer::execute(const std::shared_ptr<GoalHandleCount> goal_handle)
{
  RCLCPP_INFO(this->get_logger(), "goal executing");
  rclcpp::Rate loop_rate(1);
  const auto goal = goal_handle->get_goal();
  auto feedback = std::make_shared<demo_interface::action::Count::Feedback>();
  auto result = std::make_shared<demo_interface::action::Count::Result>();

  feedback->current_num = goal->start_num;
  for (int i = 0; (i < 10) && rclcpp::ok(); i++) {
    if (goal_handle->is_canceling()) {
      result->final_num = feedback->current_num;
      goal_handle->canceled(result);
      RCLCPP_INFO(this->get_logger(), "goal canceled");
      return;
    }
    feedback->current_num++;
    goal_handle->publish_feedback(feedback);
    loop_rate.sleep();
  }

  if (rclcpp::ok()) {
    result->final_num = feedback->current_num;
    goal_handle->succeed(result);
    RCLCPP_INFO(this->get_logger(), "goal succeeded");
  }
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ActionServer>());
  rclcpp::shutdown();
  return 0;
}
