#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>


std::string syntax;
ros::Publisher int_pub; 
int syntax_num = 0;

void string_callback(const std_msgs::String::ConstPtr &msg);

int main(int argc, char** argv)
{
	ros::init(argc, argv, "one");
	ros::NodeHandle nh;


	ros::Publisher bool_pub = nh.advertise<std_msgs::Bool>("/flag", 1);
	int_pub = nh.advertise<std_msgs::Int32>("/syntax_num", 1);

	ros::Subscriber string_sub;
	string_sub = nh.subscribe<std_msgs::String>("/syntax", 1, &string_callback);


	while(ros::ok())
	{
		ROS_INFO("Plaese Input Character");
		std_msgs::Bool bool_msg;
		char start;
		std::cin >> start;
		if(start == 's')
		{
			bool_msg.data = true;
			bool_pub.publish(bool_msg);
			break;
		}
		else
		{
			ROS_ERROR("Error Syntax : %c , Please Retry", start);
			bool_msg.data = false;
			bool_pub.publish(bool_msg);
			continue;
		}
	}

	ros::spin();
	return 0;
}

void string_callback(const std_msgs::String::ConstPtr &msg)
{
	syntax = msg->data;
	ROS_INFO("Get String Message : %s", syntax.c_str());
	syntax_num = syntax.length();

	std_msgs::Int32 int_msg;
	int_msg.data = syntax_num;

	int_pub.publish(int_msg);
}