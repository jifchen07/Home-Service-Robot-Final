#!/bin/sh
xterm  -e  "source $(pwd)/devel/setup.bash;
roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/src/map/FakeHome" &
sleep 5
xterm  -e  "source $(pwd)/devel/setup.bash;
roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/src/map/map.yaml" &
sleep 5
xterm  -e  "source $(pwd)/devel/setup.bash;
roslaunch turtlebot_rviz_launchers view_navigation.launch rviz_config_file:=$(pwd)/src/rvizConfig/home_service.rviz" &
sleep 5
xterm  -e  "source $(pwd)/devel/setup.bash;
rosrun add_markers add_markers" &
sleep 5
xterm  -e  "source $(pwd)/devel/setup.bash;
rosrun pick_objects pick_objects"
