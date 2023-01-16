#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>

bool flag = false;
int syntax_num = 0;

ros::Publisher string_pub; 
std::string syntax = "";

void bool_callback(const std_msgs::Bool::ConstPtr &msg);
void int_callback(const std_msgs::Int32::ConstPtr &msg);

int main(int argc, char** argv)
{
    ros::init(argc, argv, "two");
    ros::NodeHandle nh;

    ROS_INFO("sequence start");
    string_pub = nh.advertise<std_msgs::String>("/syntax", 1);

    ros::Subscriber bool_sub;
    ros::Subscriber int_sub;

    bool_sub = nh.subscribe<std_msgs::Bool>("/flag", 1, &bool_callback);
    int_sub = nh.subscribe<std_msgs::Int32>("/syntax_num", 1, &int_callback);

    ros::spin();
    return 0;

}

void bool_callback(const std_msgs::Bool::ConstPtr &msg)
{
    flag = msg->data;

    if(flag)
    {
        ROS_INFO("flag is %s, please input syntax string ", flag ? "true" : "false");

        std::cin >> syntax;
        std_msgs::String string_msg;
        string_msg.data = syntax;


        string_pub.publish(string_msg);
    }
}

void int_callback(const std_msgs::Int32::ConstPtr &msg)
{
    syntax_num = msg->data;
    ROS_INFO("syntax %s's length is %d", syntax.c_str(), syntax_num);
}