import launch
import launch_ros
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
  package_share_path = get_package_share_directory('demo_diff_robot')
  urdf_path = package_share_path + '/urdf/diff_robot.urdf.xacro'
  rviz_path = package_share_path + '/config/rviz/diff_robot.rviz'
  world_path = package_share_path + '/config/gazebo/room.world'
  urdf_content = launch.substitutions.Command(['xacro ', urdf_path])

  robot_state_publisher_node = launch_ros.actions.Node(
      package='robot_state_publisher',
      executable='robot_state_publisher',
      parameters=[{'robot_description': urdf_content}]
  )

  rviz_node = launch_ros.actions.Node(
      package='rviz2',
      executable='rviz2',
      arguments=['-d', rviz_path]
  )

  launch_gazebo = launch.actions.IncludeLaunchDescription(
    launch.launch_description_sources.PythonLaunchDescriptionSource(
      [get_package_share_directory('gazebo_ros'), '/launch', '/gazebo.launch.py']),
    launch_arguments=[('world', world_path), ('verbose', 'true')],
  )

  spawn_entity_node = launch_ros.actions.Node(
      package='gazebo_ros',
      executable='spawn_entity.py',
      arguments=['-topic', '/robot_description', '-entity', 'diff_robot']
  )

  load_joint_state_broadcaster = launch.actions.ExecuteProcess(
      cmd=['ros2', 'control', 'load_controller', 'diff_robot_joint_state_broadcaster',
        '--set-state', 'active'],
      output='screen'
  )

  load_diff_drive_controller = launch.actions.ExecuteProcess(
      cmd=['ros2', 'control', 'load_controller', 'diff_robot_diff_drive_controller',
        '--set-state', 'active'],
      output='screen'
  )

  return launch.LaunchDescription([
      robot_state_publisher_node,
      rviz_node,
      launch_gazebo,
      spawn_entity_node,
      launch.actions.RegisterEventHandler(
        event_handler=launch.event_handlers.OnProcessExit(
            target_action=spawn_entity_node,
            on_exit=[load_joint_state_broadcaster]
        )
      ),
      launch.actions.RegisterEventHandler(
        event_handler=launch.event_handlers.OnProcessExit(
            target_action=load_joint_state_broadcaster,
            on_exit=[load_diff_drive_controller]
        )
      )
  ])
