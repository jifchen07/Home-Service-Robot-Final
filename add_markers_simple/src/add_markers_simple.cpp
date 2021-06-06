#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"


double pickup_pos[2] = {1.5, 1.7};
double dropoff_pos[2] = {-1.5, 1.7};

enum State {
	PICKUP,
	CARRY,
	DROPOFF,
} state = PICKUP;


int main( int argc, char** argv )
{
	ros::init(argc, argv, "add_markers");
	ros::NodeHandle n;
	ros::Rate r(1);
	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

	uint32_t shape = visualization_msgs::Marker::CUBE;

	ROS_INFO("Start");

	while (ros::ok()) {
		visualization_msgs::Marker marker;	

		marker.header.frame_id = "map";
		marker.header.stamp = ros::Time::now();
		
		marker.ns = "basic_shapes";
		marker.id = 0;
		
		marker.type = shape;
		
		marker.action = visualization_msgs::Marker::ADD;
		
		marker.pose.position.x = 0;
		marker.pose.position.y = 0;
		marker.pose.position.z = 0;
		marker.pose.orientation.x = 0.0;
		marker.pose.orientation.y = 0.0;
		marker.pose.orientation.z = 0.0;
		marker.pose.orientation.w = 1.0;
		
		marker.scale.x = 0.25;
		marker.scale.y = 0.25;
		marker.scale.z = 0.25;		
		
		marker.color.r = 0.0f;
		marker.color.g = 0.0f;
		marker.color.b = 1.0f;
		marker.color.a = 1.0;
		
		marker.lifetime = ros::Duration();
		
		
		while (marker_pub.getNumSubscribers() < 1) {
		  if (!ros::ok()) {
			return 0;
		  }
		 ROS_WARN_ONCE("Please create a subscriber to the marker");
		  sleep(1);
		}
		
		switch (state) {
			case PICKUP: {
				ROS_INFO("Going to pickup location.");
				marker.pose.position.x = pickup_pos[0];
				marker.pose.position.y = pickup_pos[1];
				
				state = CARRY;
				break;
			}
			case CARRY: {
				ROS_INFO("Picked up.");
				marker.action = visualization_msgs::Marker::DELETE;
				state = DROPOFF;
				break;
			}
			case DROPOFF: {
				ROS_INFO("Dropped off.");
				marker.action = visualization_msgs::Marker::ADD;
				marker.pose.position.x = dropoff_pos[0];
				marker.pose.position.y = dropoff_pos[1];
				break;
			}
		}
		
		marker_pub.publish(marker);
		sleep(5);		

		ros::spinOnce();
		
		r.sleep();
	}
	
	return 0;
}

