import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    bringup_dir = get_package_share_directory('demo_bringup')
    param_file = os.path.join(bringup_dir, 'param', 'demo_param.yaml')

    return LaunchDescription([
        Node(
            package='demo_topic',
            executable='topic_publisher',
            name='topic_publisher_node',
            output='screen',
            emulate_tty=True,
            parameters=[param_file]
        ),
        Node(
            package='demo_topic',
            executable='topic_subscriber',
            name='topic_subscriber_node',
            output='screen',
            emulate_tty=True
        )
    ])