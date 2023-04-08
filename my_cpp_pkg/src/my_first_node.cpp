#include "rclcpp/rclcpp.hpp"

class MyNode : public rclcpp::Node
{
public:
    MyNode() : Node("my_node")
    {
        RCLCPP_INFO(this->get_logger(), "Hello Cpp Node");

        timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&MyNode::timerCallback, this));
    }

private:
    void timerCallback()
    {
        RCLCPP_INFO(this->get_logger(), "Timer Callback");
    }

    rclcpp::TimerBase::SharedPtr  timer_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<MyNode>();
    RCLCPP_INFO(node->get_logger(), "Hello Cpp Node");

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}