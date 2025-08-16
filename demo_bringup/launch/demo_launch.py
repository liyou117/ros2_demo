from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='demo_topic',
            executable='topic_publisher',
            name='topic_publisher_node',
            output='screen',
            emulate_tty=True,
            parameters=[
                {"param_num": 17}
            ]
        ),
        Node(
            package='demo_topic',
            executable='topic_subscriber',
            name='topic_subscriber_node',
            output='screen',
            emulate_tty=True
        )
    ])