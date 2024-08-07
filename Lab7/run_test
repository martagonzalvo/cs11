#! /bin/sh

# Sort the file to avoid reporting an error due to a different
# word order.

./test_hash_table test.in > test2
sort test2 > test3

diff -qbB test3 correct_test.out

if [ $? -ne 0 ]
then
	echo Test failed!
else
	echo Test succeeded!
fi

rm test2 test3

