#include <rclcpp/rclcpp.hpp>
#include<sensor_msgs/msg/joint_state.hpp>
#include<chrono>
#include<functional>
//for std::bind and placeholders
class WorkspaceVisualizer:public rclcpp::Node{
  public:
    WorkspaceVisualizer():Node("workspace_visualzer")
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
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr jspub_;
    rclcpp::TimerBase::SharedPtr timer_;
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
      msg.position = {
        0.5,6.9,4.0,2.0,0.0,0.0
      };
      msg.header.stamp = this->get_clock()->now();

      jspub_->publish(msg);


      

    }
};
int main(int argc , char * argv[]){
  rclcpp::init(argc , argv);

  auto node = std::make_shared<WorkspaceVisualizer>();
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;

  
}
