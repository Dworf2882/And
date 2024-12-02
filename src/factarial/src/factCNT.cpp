#include <rclcpp/rclcpp.hpp>
#include "test_msgs/srv/fact.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    if(argc != 2) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Uncorrect number of arguments");
        return 1;
    }
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("factorial_client");
    rclcpp::Client<test_msgs::srv::Fact>::SharedPtr client =
     node->create_client<test_msgs::srv::Fact>("factorial");

    test_msgs::srv::Fact::Request::SharedPtr request = std::make_shared<test_msgs::srv::Fact::Request>();
    request->numb = atoi(argv[1]);

    while(!client->wait_for_service(1s)) {
        if(!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
            return 0;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Waiting for the service...");
    }

    rclcpp::Client<test_msgs::srv::Fact>::FutureAndRequestId result = client->async_send_request(request);
    if(rclcpp::spin_until_future_complete(node, result) == 
    rclcpp::FutureReturnCode::SUCCESS) 
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Factorial of %d is %d", request->numb, result.get()->result);
    }
    else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service");
    }
    rclcpp::shutdown();
    return 0;
}