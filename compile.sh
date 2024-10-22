#!/bin/bash

# Name of the Docker container
CONTAINER_NAME="TPE_Arqui"

# Start the Docker container
docker start $CONTAINER_NAME

# Clean and build the project in the specified directories
docker exec -it $CONTAINER_NAME make clean -C /root/Toolchain
docker exec -it $CONTAINER_NAME make clean -C /root

# Execute the make commands
docker exec -it $CONTAINER_NAME make -C /root/Toolchain
MAKE_TOOLCHAIN_EXIT_CODE=$?

docker exec -it $CONTAINER_NAME make -C /root
MAKE_ROOT_EXIT_CODE=$?

# Stop the Docker container
docker stop $CONTAINER_NAME

# Check if both make commands were successful
if [[ $MAKE_TOOLCHAIN_EXIT_CODE -eq 0 && $MAKE_ROOT_EXIT_CODE -eq 0 ]]; then
    # Run the script if both make commands succeeded
    ./run.sh
else
    echo "One or both make commands failed. Not running ./run.sh"
fi