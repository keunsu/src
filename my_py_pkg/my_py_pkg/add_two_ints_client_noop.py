#!user/bin/env python3
import rclpy
from rclpy.node import Node

from example_interfaces.srv import AddTwoInts

def main(args=None):
    rclpy.init(args=args)
    node = Node("add_two_ints_client_noop")

    client = node.create_client(AddTwoInts, "add_two_ints")
    while not client.wait_for_service(timeout_sec=1.0):
        node.get_logger().warn("Waiting for server to start...")
    request = AddTwoInts.Request()
    request.a = 2
    request.b = 3
    future = client.call_async(request)
    rclpy.spin_until_future_complete(node, future)
    
    try:
        response = future.result()
    except Exception as e:
        node.get_logger().info("Service call failed %r" % (e,))
    else:
        node.get_logger().info("Result of add_two_ints: for %d + %d = %d" % (request.a, request.b, response.sum))



    rclpy.shutdown()


if __name__ == '__main__':
    main()
