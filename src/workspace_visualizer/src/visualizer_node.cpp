#include <rclcpp/rclcpp.hpp>
#include<sensor_msgs/msg/joint_state.hpp>
#include<chrono>
#include<functional>
#include<tf2_ros/buffer.h>
#include<tf2_ros/transform_listener.h>
#include<tf2/exceptions.h>


//for std::bind and placeholders
class WorkspaceVisualizer:public rclcpp::Node{
  public:
    WorkspaceVisualizer():Node("workspace_visualzer"),buffer_(this->get_clock()),listener_(buffer_,this,false)
  {
    RCLCPP_INFO(this->get_logger(),"Workspace visualizer online.");
    jspub_ = this->create_publisher<sensor_msgs::msg::JointState>(
        "/joint_states",10
        ); 
    timer_ = 
      this-> create_wall_timer(std::chrono::milliseconds(100), 
        std::bind(
          &WorkspaceVisualizer::publish_joint_states,
          this
          )
        );

        //the placeholders correspond to the argument given to the callback,
    //so '_1' refers to the first argument being passed to callback
  }
      
  private:
    rclcpp::Time start_time = this->get_clock()->now(); 
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr jspub_;
    rclcpp::TimerBase::SharedPtr timer_;
    tf2_ros::Buffer buffer_;
    tf2_ros::TransformListener listener_;

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
      double t = (now - start_time).seconds();
      msg.position = {
          2*sin(t),0.0,0.0,0.0,0.0,0.0
      };
      msg.header.stamp = this->get_clock()->now();

      jspub_->publish(msg);

      track_eef();
      

    }
    
    void track_eef(){
      const::std::string source_frame = "base_link";
      const::std::string target_frame = "tool0";
      geometry_msgs::msg::TransformStamped result;
      try{
      result = buffer_.lookupTransform(
          source_frame,
          target_frame,
          tf2::TimePointZero
          );
      RCLCPP_INFO(this->get_logger(),
          "EEF : %.3f , %.3f , %.3f",
          result.transform.translation.x,
          result.transform.translation.y,
          result.transform.translation.z
          );
    }
      catch(const tf2::TransformException &ex){
        RCLCPP_WARN(this->get_logger(), "TF lookup failed %.s",ex.what());

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
