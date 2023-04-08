#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class AddTwoIntsServerNode : public rclcpp::Node
{
public:
    AddTwoIntsServerNode() : Node("add_two_ints_server")
    {
        RCLCPP_INFO(this->get_logger(), "Server Started");

        service_ = this->create_service<example_interfaces::srv::AddTwoInts>(
            "add_two_ints", 
            std::bind(&AddTwoIntsServerNode::callbackAddTwoInts, 
            this, std::placeholders::_1, std::placeholders::_2));
    }

private:
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service_;

    void callbackAddTwoInts(
        const example_interfaces::srv::AddTwoInts::Request::SharedPtr request, 
        const example_interfaces::srv::AddTwoInts::Response::SharedPtr response)
    {
        response->sum = request->a + request->b;
        RCLCPP_INFO(this->get_logger(), "Request: a=%ld, b=%ld => result: %ld", request->a, request->b, response->sum);
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<AddTwoIntsServerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}