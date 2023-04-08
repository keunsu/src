#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class SmartphoneNode : public rclcpp::Node
{
public:
    SmartphoneNode() : Node("smartphone_node")
    {
        RCLCPP_INFO(this->get_logger(), "SmartphoneNode Node");
        subscription_ = this->create_subscription<example_interfaces::msg::String>(
            "robot_news",
            10,
            std::bind(&SmartphoneNode::callbackRobotNews, this, std::placeholders::_1));
    }

    private:

        rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscription_;


        void callbackRobotNews(const example_interfaces::msg::String::SharedPtr msg)
        {
            RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
        }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<SmartphoneNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}