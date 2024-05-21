
create-new-ros-qt-widget-package() {
    if [ $# -ne 2 ]; then
        echo "Please provide the correct parameters: PKG_NAME and NODE_NAME."
        echo "Usage example-1: create-new-ros-qt-widget-package <PKG_NAME> <NODE_NAME>"
        echo "Usage example-2: create-new-ros-qt-widget-package my_ros2qt demo"
        return 1
    fi

    PKG_NAME=$1
    NODE_NAME=$2

    if [ -d ./$PKG_NAME ]; then
        echo "Error: Directory $PKG_NAME already exists."
        return 1
    fi
    cp -R $CREATE_NEW_ROS_QT_PKG_CMD_DIR/template/widget ./$PKG_NAME

    # Use the "find" to locate all files and use "sed" for replacement __PKG_NAME__ and __NODE_NAME__.
    find ./$PKG_NAME -type f -exec sed -i "s/__PKG_NAME__/$PKG_NAME/g" {} +
    find ./$PKG_NAME -type f -exec sed -i "s/__NODE_NAME__/$NODE_NAME/g" {} +
}

# Get the directory path of the shell file and assign it to an environment variable.
SETUP_BASH_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export CREATE_NEW_ROS_QT_PKG_CMD_DIR=$SETUP_BASH_DIR



