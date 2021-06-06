# Home-Service-Robot

## My Packages
* **pick_objects**: The pick_objects node commands the robot to move to the pick up and drop off locations
* **add_markers**: The add_markers node subscribes to the robot odometry to keep track of the robot poss and publishes the markers in rviz:
    * Initially show the marker at the pickup zone
    * Hide the marker once your robot reaches the pickup zone
    * Wait 5 seconds to simulate a pickup
    * Show the marker at the drop off zone once your robot reaches it

## Official ROS packages
- [gmapping](http://wiki.ros.org/gmapping): With the gmapping_demo.launch file, you can easily perform SLAM and build a map of the environment with a robot equipped with laser range finder sensors or RGB-D cameras
- [turtlebot_teleop](http://wiki.ros.org/turtlebot_teleop): With the keyboard_teleop.launch file, you can manually control a robot using keyboard commands
- [turtlebot_rviz_launchers](http://wiki.ros.org/turtlebot_rviz_launchers): With the view_navigation.launch file, you can load a preconfigured rviz workspace
- [turtlebot_gazebo](http://wiki.ros.org/turtlebot_gazebo): With the turtlebot_world.launch you can deploy a turtlebot in a gazebo environment by linking the world file to it

## Other Directories
* **map**: Contains the map files and the gazebo world file
* **rvizConfig**: Contains rViz view configuration file
* **scripts**: Contains shell scripts to launch environment and run nodes

## Run the Home Service Robot
From the catkin_workspace directory, run the shell script: home_service.sh
```
./src/scripts/home_service.sh
```
