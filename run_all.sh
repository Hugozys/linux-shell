#!/bin/bash
for i in `ls /home/yz395/ece551/mp_miniproject/testMyShell/test*|sort`
do
    test=`basename $i`
    echo "**Input testcase ${test}**" >> test_result.txt
    echo "============================================" >> test_result.txt
    ./myShell < $i >> test_result.txt 2>&1
    echo "" >> test_result.txt
    echo "" >> test_result.txt
done

