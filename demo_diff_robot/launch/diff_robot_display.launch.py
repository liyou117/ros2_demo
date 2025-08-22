import launch
import launch_ros
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
  urdf_path = get_package_share_directory('demo_diff_robot') + '/urdf/diff_robot.urdf.xacro'
  rviz_path = get_package_share_directory('demo_diff_robot') + '/config/rviz/diff_robot.rviz'
  urdf_content = launch.substitutions.Command(['xacro ', urdf_path])

  robot_state_publisher_node = launch_ros.actions.Node(
      package='robot_state_publisher',
      executable='robot_state_publisher',
      parameters=[{'robot_description': urdf_content}]
  )

  joint_state_publisher_node = launch_ros.actions.Node(
      package='joint_state_publisher',
      executable='joint_state_publisher'
  )

  rviz_node = launch_ros.actions.Node(
      package='rviz2',
      executable='rviz2',
      arguments=['-d', rviz_path]
  )

  return launch.LaunchDescription([
      robot_state_publisher_node,
      joint_state_publisher_node,
      rviz_node
  ])
