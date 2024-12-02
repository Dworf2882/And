#include <rclcpp/rclcpp.hpp>
#include "test_msgs/srv/fact.hpp"


void factorial(const std::shared_ptr<test_msgs::srv::Fact::Request> request,
 std::shared_ptr<test_msgs::srv::Fact::Response> response) {
    int number = request->numb;
    unsigned int factorial = 1;
    if(number == 0) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Factorial of %d is 1", number);
        response->result = 1;
    }
    else if(number < 0) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Uncorrect number");
    }
    else if(number > 0) {
        for(int i = 1; i <= number; i++) {
            factorial = factorial * i;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Factorial of %d is %ld", number,factorial);
        response->result = factorial;
    }

}
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("factorial_server");
    rclcpp::Service<test_msgs::srv::Fact>::SharedPtr service = 
    node->create_service<test_msgs::srv::Fact>("factorial", &factorial);
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to calculate factorial");
    rclcpp::spin(node);
    rclcpp::shutdown();
}