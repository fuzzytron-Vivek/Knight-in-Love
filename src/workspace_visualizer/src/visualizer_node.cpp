#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <visualization_msgs/msg/marker.hpp>

#include <geometry_msgs/msg/point.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <tf2/exceptions.h>

#include <chrono>
#include <functional>
#include <cmath>
#include <vector>
#include <string>


//for std::bind and placeholders
class WorkspaceVisualizer:public rclcpp::Node{
  public:
    WorkspaceVisualizer():Node("workspace_visualzer"),buffer_(this->get_clock()),listener_(buffer_,this,false)
  {
    RCLCPP_INFO(this->get_logger(),"Workspace visualizer online.");
    jspub_ = this->create_publisher<sensor_msgs::msg::JointState>(
        "/joint_states",10
        );
    marker_pub_ = this->create_publisher<visualization_msgs::msg::Marker>(
        "/eef_marker",10
        );
    timer_ = this-> create_wall_timer(std::chrono::milliseconds(100), 
        std::bind(
          &WorkspaceVisualizer::publish_joint_states,
          this
          )
        );
    start_time_ = this->get_clock()->now(); 


        //the placeholders correspond to the argument given to the callback,
    //so '_1' refers to the first argument being passed to callback
  }
      
  private:
    rclcpp::Time start_time_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr jspub_;
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    tf2_ros::Buffer buffer_;
    tf2_ros::TransformListener listener_;
    std::vector<geometry_msgs::msg::Point> eef_path_;
    //the const <datatype>::SharedPtr variable_name doesn't work over here 
//we're creating a publisher callback , and hence we creat the object by ourselves
//the const datatype also doesn't provide functionality since we will be using the publisher's own members 
//
    void publish_joint_states(){
      sensor_msgs::msg::JointState msg;
      msg.name = {
        "shoulder_pan_joint",
        "shoulder_lift_joint",
        "elbow_joint",
        "wrist_1_joint",
        "wrist_2_joint",
        "wrist_3_joint"
      };
      rclcpp::Time now = this->get_clock()->now();
      double t = (now - start_time_).seconds();
      msg.position = {
          2*std::sin(t),1.5*std::sin(1.3*t),1.2*std::sin(0.7*t),0.0,0.0,0.0
      };
      msg.header.stamp = this->get_clock()->now();

      jspub_->publish(msg);

      track_eef();
      

    }
    
    void track_eef(){
      const std::string source_frame = "tool0";
      const std::string target_frame = "base_link";
      geometry_msgs::msg::TransformStamped result;
      
      try{
      result = buffer_.lookupTransform(
          target_frame,
          source_frame,
          tf2::TimePointZero
          );
      RCLCPP_INFO(this->get_logger(),
          "EEF : %.3f , %.3f , %.3f",
          result.transform.translation.x,
          result.transform.translation.y,
          result.transform.translation.z
          );
//POINTS SECTION----------------------------------------------------------
    geometry_msgs::msg::Point point;

    point.x = result.transform.translation.x;
    point.y = result.transform.translation.y;
    point.z = result.transform.translation.z;

    eef_path_.push_back(point);

//SPHERE SECTION----------------------------------------------------------
    visualization_msgs::msg::Marker eef;

    eef.header.frame_id = "base_link";
    eef.header.stamp = this->get_clock()->now();

    eef.ns = "eef_current";
    eef.id = 0;
    eef.type = visualization_msgs::msg::Marker::SPHERE;
    eef.action = visualization_msgs::msg::Marker::ADD;

    eef.pose.position = point;

    eef.scale.x = 0.03;
    eef.scale.y = 0.03;
    eef.scale.z = 0.03;

    eef.color.r = 0.0;
    eef.color.g = 1.0;
    eef.color.b = 1.0;
    eef.color.a = 1.0;
//TRAIL SECTION---------------------------------------------------------- 

    visualization_msgs::msg::Marker trail;

    trail.header.frame_id = "base_link";
    trail.header.stamp = this->get_clock()->now();

    trail.ns = "eef_trail";
    trail.id = 1;
    trail.type = visualization_msgs::msg::Marker::LINE_STRIP;
    trail.action = visualization_msgs::msg::Marker::ADD;

    trail.scale.x = 0.01;

    trail.color.r = 0.0;
    trail.color.g = 1.0;
    trail.color.b = 1.0;
    trail.color.a = 1.0;

    trail.points = eef_path_;

    
    marker_pub_ -> publish(eef);
    marker_pub_ -> publish(trail);

  }
  catch(const tf2::TransformException &ex)
  {
        RCLCPP_WARN(this->get_logger(), "TF lookup failed %s",ex.what());

    }
  }
};
int main(int argc , char * argv[]){
  rclcpp::init(argc , argv);

  auto node = std::make_shared<WorkspaceVisualizer>();
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;

  
}
