#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class RobotNewsStationNode : public rclcpp::Node
{
public:
    RobotNewsStationNode() : Node("my_node")
    {
        RCLCPP_INFO(this->get_logger(), "RobotNewsStationNode Node");

        robot_name_ = "Robot123";

        publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&RobotNewsStationNode::publishNews, this));
    }

    private:
        rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        std::string robot_name_;

        void publishNews()
        {
            auto message = example_interfaces::msg::String();
            message.data = std::string("Hello World CPP ") + robot_name_;
            publisher_->publish(message);
        }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<RobotNewsStationNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}