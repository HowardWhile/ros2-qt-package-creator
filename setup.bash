create-new-ros-qt-package() {
    if [ $# -ne 3 ]; then
        echo "Please provide the correct parameters: PKG_NAME and NODE_NAME."
        echo "Usage example-1: create-new-ros-qt-package <PKG_NAME> <NODE_NAME>"
        echo "Usage example-2: create-new-ros-qt-package my_ros2qt demo"
        return 1
    fi

    PKG_NAME=$1
    NODE_NAME=$2


}
