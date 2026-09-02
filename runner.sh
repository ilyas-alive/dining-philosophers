#!/usr/bin/env bash

TESTS_FILE="tests.txt"
OUTPUT_DIR="burnout_test"
TMP_LOG="current_run.log"

# Check if tests.txt exists
if [ ! -f "$TESTS_FILE" ]; then
    echo "Error: $TESTS_FILE not found! Please create it and add your arguments (one test per line)."
    exit 1
fi

# Create the folder to hold the test results
mkdir -p "$OUTPUT_DIR"

# Trap Ctrl+C (SIGINT) to print all stats and clean up before exiting
trap '
    echo -e "\n\n--- Final Summary ---"
    # Print the stats for every test we ran
    for stats in "$OUTPUT_DIR"/stats*.txt; do
        if [ -f "$stats" ]; then
            test_number=$(echo "$stats" | grep -o -E "[0-9]+")
            echo "=> Test $test_number Stats ($stats):"
            cat "$stats"
            echo ""
        fi
    done
    rm -f "$TMP_LOG"
    exit 0
' SIGINT

echo "Running tests from $TESTS_FILE... Press Ctrl+C to stop and view statistics."

# Infinite loop to cycle through the tests.txt file
while true; do
    test_num=1
    
    # Read tests.txt line by line
    while IFS= read -r args || [ -n "$args" ]; do
        # Skip empty lines
        [ -z "$args" ] && continue

        STATS_FILE="$OUTPUT_DIR/stats${test_num}.txt"
        LOG_FILE="$OUTPUT_DIR/burnout${test_num}.txt"

        # Initialize stats file for this specific test if it doesn't exist
        if [ ! -f "$STATS_FILE" ]; then
            cat << 'EOF' > "$STATS_FILE"
burnout
0
no_burnout
0
EOF
        fi

        echo -e "\n>>> Running Test $test_num: ./codexion $args"

        # 1. Run program with the arguments from the file, write to TMP_LOG
        # $args is deliberately left unquoted so bash splits the arguments correctly
        ./codexion $args 2>&1 | tee "$TMP_LOG"

        # Ensure log is fully flushed to disk
        sync "$TMP_LOG"

        # 2. Append the current run and separator to this specific test's log file
        cat "$TMP_LOG" >> "$LOG_FILE"
        echo "***************" >> "$LOG_FILE"

        # 3. Read current counts for this specific test
        burnout_count=$(sed -n '2p' "$STATS_FILE")
        no_burnout_count=$(sed -n '4p' "$STATS_FILE")

        # 4. Check the physical file for "burned out"
        if grep -q "burned out" "$TMP_LOG"; then
            burnout_count=$((burnout_count + 1))
        else
            no_burnout_count=$((no_burnout_count + 1))
        fi

        # 5. Update stats file for this specific test
        cat << EOF > "$STATS_FILE"
burnout
$burnout_count
no_burnout
$no_burnout_count
EOF

        echo "--- Test $test_num Stats Updated | Burnout: $burnout_count | No Burnout: $no_burnout_count ---"
        sleep 0.1
        
        # Increment the test number for the next line in the file
        test_num=$((test_num + 1))
        
    done < "$TESTS_FILE"
done
