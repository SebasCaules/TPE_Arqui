#!/bin/bash

# Name of the Docker container
CONTAINER_NAME="TPE"

# Start the Docker container
docker start $CONTAINER_NAME

# Clean and build the project in the specified directories
docker exec -it $CONTAINER_NAME make clean -C /root/Toolchain
docker exec -it $CONTAINER_NAME make clean -C /root
docker exec -it $CONTAINER_NAME make -C /root/Toolchain
docker exec -it $CONTAINER_NAME make -C /root

# Stop the Docker container
docker stop $CONTAINER_NAME