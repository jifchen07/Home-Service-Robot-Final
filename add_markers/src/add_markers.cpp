#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"


double pickup_pos[2] = {-1.7, 1.5};
double dropoff_pos[2] = {-1.7, -1.5};

double current_pos[2] = {0.25, -0.04};

bool arrived_at_pickup = false;
bool arrived_at_dropoff = false;

enum State {
	PICKUP,
	CARRY,
	DROPOFF,
} state = PICKUP;

bool arrived_at_goal(double goal_pose[2]) {
	double dx = goal_pose[0] - current_pos[0];
	double dy = goal_pose[1] - current_pos[1];
	double l2_dist = dx*dx + dy*dy;
	return l2_dist < 0.1;
}

void get_pose(const nav_msgs::Odometry::ConstPtr& msg) {
	current_pos[0] = msg->pose.pose.position.x;
	current_pos[1] = msg->pose.pose.position.y;
	arrived_at_pickup = arrived_at_goal(pickup_pos);
	arrived_at_dropoff = arrived_at_goal(dropoff_pos);
}


int main( int argc, char** argv )
{
	ros::init(argc, argv, "add_markers");
	ros::NodeHandle n;
	ros::Rate r(1);
	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
	ros::Subscriber pose_sub = n.subscribe("odom", 10, get_pose);

	uint32_t shape = visualization_msgs::Marker::CUBE;

	ROS_INFO("Start");

	while (ros::ok()) {
		visualization_msgs::Marker marker;	

		marker.header.frame_id = "odom";
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
				
				if (arrived_at_pickup) {
					ROS_INFO("Arrived at pickup location.");
					marker.action = visualization_msgs::Marker::DELETE;
					marker_pub.publish(marker);
					sleep(5);
					ROS_INFO("Now going to dropoff location.");
					state = CARRY;
				}
				break;
			}
			case CARRY: {
				marker.action = visualization_msgs::Marker::DELETE;
				
				if (arrived_at_dropoff) {
					ROS_INFO("Arrived at dropoff location.");
					state = DROPOFF;
				}
				break;
			}
			case DROPOFF: {
				marker.action = visualization_msgs::Marker::ADD;
				marker.pose.position.x = dropoff_pos[0];
				marker.pose.position.y = dropoff_pos[1];
				
				break;
			}
		}
		
		marker_pub.publish(marker);
		
		ros::spinOnce();
		
		r.sleep();
	}
	
	return 0;
}

