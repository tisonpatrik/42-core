#!/bin/bash

# Compile with TSan first for maximum sensitivity
# gcc -pthread -fsanitize=thread -g *.c -o philo

for i in {1..100}
do
    echo "Running test #$i"
    # Run philo for a limited time or until death
    # Adjust args: 4 philos, 410 die, 200 eat, 200 sleep, must eat 5x
    ./bin/philo 4 410 200 200 5 > /dev/null

    if [ $? -ne 0 ]; then
        echo "Crash or Error detected at iteration $i!"
        break
    fi
done
echo "Finished."
