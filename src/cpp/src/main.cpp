#include <rclcpp/rclcpp.hpp>
#include "sensor_msgs/msg/laser_scan.hpp"
class LidarCallback : public rclcpp::Node {
    public:
        LidarCallback() : Node("lidar_callback") {
            sub_lidar = this->create_subscription<sensor_msgs::msg::LaserScan>("/uav1/scan", 10, std::bind(&LidarCallback::lidar_circle, this, std::placeholders::_1));
            pub_lidarCallback = this->create_publisher<sensor_msgs::msg::LaserScan>("/lidar_callback", 10);
        }
    private:
        void lidar_circle(const sensor_msgs::msg::LaserScan & msg) {
            sensor_msgs::msg::LaserScan msg_callback = sensor_msgs::msg::LaserScan();
            msg_callback.angle_min = msg.angle_min;
            msg_callback.angle_max = msg.angle_max;
            msg_callback.angle_increment = msg.angle_increment;
            msg_callback.time_increment = msg.time_increment;
            msg_callback.scan_time = msg.scan_time;
            msg_callback.header.frame_id = msg.header.frame_id;
            msg_callback.intensities = msg.intensities;
            msg_callback.range_max = msg.range_max;
            msg_callback.range_min = msg.range_min;
            msg_callback.header.stamp.sec = msg.header.stamp.sec;
            msg_callback.header.stamp.nanosec = msg.header.stamp.nanosec;
            // msg_callback.intensities = msg.intensities;

            for(int i=0;i<msg.ranges.size();i++){
                float range = msg.ranges[i];
                if (range > 2.0){
                    range = 2.0;
                }
                msg_callback.ranges.push_back(range);
            }
            pub_lidarCallback->publish(msg_callback);
        }
        rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sub_lidar;
        rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr pub_lidarCallback;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LidarCallback>());
    rclcpp::shutdown();
    return 0;
}

// #include <chrono>
// #include <functional>
// #include <memory>
// #include <string>

// #include "rclcpp/rclcpp.hpp"
// #include "std_msgs/msg/string.hpp"

// using namespace std::chrono_literals;

// /* This example creates a subclass of Node and uses std::bind() to register a
// * member function as a callback from the timer. */

// class MinimalPublisher : public rclcpp::Node
// {
//   public:
//     MinimalPublisher()
//     : Node("minimal_publisher"), count_(0)
//     {
//       publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
//       timer_ = this->create_wall_timer(
//       500ms, std::bind(&MinimalPublisher::timer_callback, this));
//     }

//   private:
//     void timer_callback()
//     {
//       auto message = std_msgs::msg::String();
//       message.data = "Hello, world! " + std::to_string(count_++);
//       RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
//       publisher_->publish(message);
//     }
//     rclcpp::TimerBase::SharedPtr timer_;
//     rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
//     size_t count_;
// };

// int main(int argc, char * argv[])
// {
//   rclcpp::init(argc, argv);
//   rclcpp::spin(std::make_shared<MinimalPublisher>());
//   rclcpp::shutdown();
//   return 0;
// }