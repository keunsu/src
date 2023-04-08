#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

class MyNode(Node):
    def __init__(self):
        super().__init__("py_node")
        self.count_ = 0
        self.get_logger().info("Hello World!22212122")
        self.create_timer(0.5, self.timer_callback)

    def timer_callback(self):
        self.count_ += 1
        self.get_logger().info("timer_callback "+str(self.count_)+" times")


def main(args=None):
    rclpy.init(args=args)
    node = MyNode()
    node.get_logger().info("Hello World!")
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()