#ifndef DEMO_ACTION__ACTION_SERVER_HPP_
#define DEMO_ACTION__ACTION_SERVER_HPP_

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "demo_interface/action/count.hpp"

class ActionServer : public rclcpp::Node
{
public:
  using GoalHandleCount = rclcpp_action::ServerGoalHandle<demo_interface::action::Count>;

  ActionServer();
  ~ActionServer() = default;

private:
  rclcpp_action::GoalResponse handle_goal(
    const rclcpp_action::GoalUUID & uuid,
    std::shared_ptr<const demo_interface::action::Count::Goal> goal);
  rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandleCount> goal_handle);
  void handle_accepted(const std::shared_ptr<GoalHandleCount> goal_handle);
  void execute(const std::shared_ptr<GoalHandleCount> goal_handle);

  rclcpp_action::Server<demo_interface::action::Count>::SharedPtr action_server_;
};

#endif  // DEMO_ACTION__ACTION_SERVER_HPP_
