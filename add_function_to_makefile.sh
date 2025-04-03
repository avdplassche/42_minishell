#!/bin/bash

# Check if a new .c file is passed as an argument
if [ -z "$1" ]; then
    echo "Usage: $0 <new_file.c>"
    exit 1
fi

# New .c file to add
new_c_file=$1
makefile="Makefile"

# Check if the file already exists in the Makefile
if grep -q "$new_c_file" "$makefile"; then
    echo "$new_c_file already exists in the Makefile."
    exit 0
fi

# Add the new .c file to the SRCS variable in the Makefile
# This will append it to the end of the list, ensuring the formatting is maintained.
sed -i "/^SRCS\s*=/ s|$|\\ \n\t\t\t$new_c_file \\\|" "$makefile"

# Confirmation
echo "$new_c_file added to the Makefile."
