#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class AddTwoIntsClientNode : public rclcpp::Node
{
public:
    AddTwoIntsClientNode() : Node("add_two_ints_client")
    {
        RCLCPP_INFO(this->get_logger(), "add_two_ints_client");
        threads_.push_back(std::thread(std::bind(&AddTwoIntsClientNode::callAddTwoIntsService, this, 2, 8)));
        threads_.push_back(std::thread(std::bind(&AddTwoIntsClientNode::callAddTwoIntsService, this, 3, 2)));
        threads_.push_back(std::thread(std::bind(&AddTwoIntsClientNode::callAddTwoIntsService, this, 3, 3)));
        threads_.push_back(std::thread(std::bind(&AddTwoIntsClientNode::callAddTwoIntsService, this, 3, 4)));
        threads_.push_back(std::thread(std::bind(&AddTwoIntsClientNode::callAddTwoIntsService, this, 3, 5)));
        
    }

    void callAddTwoIntsService(int a, int b)
    {
        auto client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
        while (!client->wait_for_service(std::chrono::seconds(1))) {        
            RCLCPP_WARN(this->get_logger(), "service not available, waiting again...");
        }
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;

        auto future_result = client->async_send_request(request);
        try
        {
            auto response = future_result.get();    
            RCLCPP_INFO(this->get_logger(), "Result: %ld", response->sum);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

private:
    std::thread thread1_;
    std::vector<std::thread> threads_;

    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<AddTwoIntsClientNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}