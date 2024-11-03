#!/bin/bash

echo "const std::set<std::string> expected = {"
while IFS= read -r line; do
    echo "    \"$line\","
done
echo "};"
