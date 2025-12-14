#!/bin/bash
# Test suite for minishell redirections
# Run from the minishell directory: bash tests/test_redirections.sh
# Uses ONLY external commands, no builtins

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

TESTS_PASSED=0
TESTS_FAILED=0

cleanup() {
    rm -f test_in.txt test_out.txt test_append.txt test_combined.txt test_touch.txt test_ls.txt test_input_out.txt
}

test_file() {
    local name="$1"
    local file="$2"
    local expected="$3"
    
    if [ -f "$file" ]; then
        content=$(cat "$file")
        if [ "$content" = "$expected" ]; then
            echo -e "${GREEN}[PASS]${NC} $name"
            ((TESTS_PASSED++))
        else
            echo -e "${RED}[FAIL]${NC} $name - content mismatch"
            echo "  Expected: '$expected'"
            echo "  Got:      '$content'"
            ((TESTS_FAILED++))
        fi
    else
        echo -e "${RED}[FAIL]${NC} $name - file not found"
        ((TESTS_FAILED++))
    fi
}

echo "=========================================="
echo "   MINISHELL REDIRECTIONS TEST SUITE"
echo "=========================================="
echo "   (Using only external commands)"
echo ""

# Cleanup before tests
cleanup

echo -e "${YELLOW}=== Test 1: Output redirection (>) with /bin/echo ===${NC}"
rm -f test_out.txt
echo '/bin/echo test_output > test_out.txt' | ./minishell 2>/dev/null >/dev/null
test_file "/bin/echo > file (create)" "test_out.txt" "test_output"

echo '/bin/echo overwritten > test_out.txt' | ./minishell 2>/dev/null >/dev/null
test_file "> overwrites content" "test_out.txt" "overwritten"

echo ""
echo -e "${YELLOW}=== Test 2: Output redirection (>) with touch ===${NC}"
rm -f test_touch.txt
echo 'touch test_touch.txt' | ./minishell 2>/dev/null >/dev/null
if [ -f "test_touch.txt" ]; then
    echo -e "${GREEN}[PASS]${NC} touch creates file"
    ((TESTS_PASSED++))
else
    echo -e "${RED}[FAIL]${NC} touch creates file"
    ((TESTS_FAILED++))
fi
rm -f test_touch.txt

echo ""
echo -e "${YELLOW}=== Test 3: Append redirection (>>) ===${NC}"
rm -f test_append.txt
echo '/bin/echo line1 > test_append.txt' | ./minishell 2>/dev/null >/dev/null
echo '/bin/echo line2 >> test_append.txt' | ./minishell 2>/dev/null >/dev/null
expected="line1
line2"
test_file ">> appends content" "test_append.txt" "$expected"

echo ""
echo -e "${YELLOW}=== Test 4: Input redirection (<) ===${NC}"
# Create input file and test by redirecting output to file
printf "Hello World" > test_in.txt
echo 'cat < test_in.txt > test_input_out.txt' | ./minishell 2>/dev/null >/dev/null
test_file "cat < file > output" "test_input_out.txt" "Hello World"

echo ""
echo -e "${YELLOW}=== Test 5: Combined redirections (< and >) ===${NC}"
rm -f test_combined.txt
printf "Input content" > test_in.txt
echo 'cat < test_in.txt > test_combined.txt' | ./minishell 2>/dev/null >/dev/null
test_file "< input > output" "test_combined.txt" "Input content"

echo ""
echo -e "${YELLOW}=== Test 6: ls with output redirection ===${NC}"
rm -f test_ls.txt
echo 'ls > test_ls.txt' | ./minishell 2>/dev/null >/dev/null
if [ -f "test_ls.txt" ] && [ -s "test_ls.txt" ]; then
    echo -e "${GREEN}[PASS]${NC} ls > file"
    ((TESTS_PASSED++))
else
    echo -e "${RED}[FAIL]${NC} ls > file"
    ((TESTS_FAILED++))
fi
rm -f test_ls.txt

echo ""
echo "=========================================="
echo "            TEST RESULTS"
echo "=========================================="
echo -e "Passed: ${GREEN}${TESTS_PASSED}${NC}"
echo -e "Failed: ${RED}${TESTS_FAILED}${NC}"
echo "=========================================="

cleanup

if [ $TESTS_FAILED -eq 0 ]; then
    echo -e "\n${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "\n${RED}Some tests failed.${NC}"
    exit 1
fi
