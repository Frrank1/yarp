cmake_minimum_required(VERSION 2.8.9)
project(yarp_test)
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs message_generation)
add_service_files(FILES AddTwoInts.srv)
generate_messages(DEPENDENCIES std_msgs)
catkin_package(CATKIN_DEPENDS message_runtime)
