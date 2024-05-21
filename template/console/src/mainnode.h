#ifndef MAINNODE_H_
#define MAINNODE_H_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <QObject>
#include <QTimer>
#include <QString>

class MainNode : public QObject
{
    Q_OBJECT

public:
    MainNode();
    ~MainNode();

private:
    // -------------------------------------
    // ROS Components
    // -------------------------------------
    // Ros node
    rclcpp::Node::SharedPtr node_;

    // ROS publisher
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    
    // ROS subscriber
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    void subscription_callback(std_msgs::msg::String::UniquePtr msg);

    // -------------------------------------
    // Spin Function
    // -------------------------------------
    void initSpin(void);
    QTimer spin_timer_;
    // -------------------------------------
    // Example for workloop
    // -------------------------------------
    int count_;
    QTimer workloop_timer_;
    void workloop_timer_callback();
    // -------------------------------------

};

#endif
