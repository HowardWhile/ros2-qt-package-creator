#include "mainnode.h"

MainNode::MainNode()
{
    // -------------------------------------
    // ROS Initialization Example
    // -------------------------------------
    rclcpp::init(0, nullptr);
    this->node_ = rclcpp::Node::make_shared("__NODE_NAME__");

    // Publisher
    publisher_ = this->node_->create_publisher<std_msgs::msg::String>("/ros2qt_pub", 10);

    // Subscriber
    subscription_ = this->node_->create_subscription<std_msgs::msg::String>("/ros2qt_sub", 10, std::bind(&MainNode::subscription_callback, this, std::placeholders::_1));

    // -------------------------------------
    // WorkLoop Example
    // -------------------------------------
    // Initialize spinning with a timer interval of 1000ms
    this->workloop_timer_.setInterval(1000);
    QObject::connect(&this->workloop_timer_, &QTimer::timeout, this, &MainNode::workloop_timer_callback);
    this->workloop_timer_.start();
    // -------------------------------------

    std::string node_name = this->node_->get_name();

    RCLCPP_INFO(this->node_->get_logger(), "MainMode Initialized Node Name: %s", node_name.c_str() );

    this->initSpin();
    // -------------------------------------

}

MainNode::~MainNode()
{
    // Stop the spin timer
    this->spin_timer_.stop();
    this->workloop_timer_.stop();

    // Shutdown ROS
    rclcpp::shutdown();
}

void MainNode::initSpin()
{
    // Initialize spinning with a timer interval of 1 ms
    this->spin_timer_.setInterval(1);
    QObject::connect(&this->spin_timer_,
                     &QTimer::timeout,
                     [&]()
                     {
                         // Spin ROS for handling callbacks
                         rclcpp::spin_some(node_);
                     });
    this->spin_timer_.start();
}

void MainNode::subscription_callback(std_msgs::msg::String::UniquePtr msg)
{
    RCLCPP_INFO(this->node_->get_logger(), "I heard: %s", msg->data.c_str());
}

void MainNode::workloop_timer_callback()
{
    // -------------------------------------
    // WorkLoop Example
    // -------------------------------------
    std_msgs::msg::String message;
    QString txt = QString("hello world (%1)").arg(this->count_++);
    message.data = txt.toStdString().c_str();
    this->publisher_->publish(message);

    RCLCPP_INFO(this->node_->get_logger(), "Publish message: %s", message.data.c_str());
}
