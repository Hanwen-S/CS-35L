#!/bin/sh

a=`(./randall 5 | wc -c)`
if [ $a -eq 5 ];
then
    :
else
    echo "Test #1 Fail"
    exit 1
fi

b=`(./randall 15 | wc -c)`
if [ $b -eq 15 ];
then
    :
else
    echo "Test #2 Fail"
    exit 1
fi

c=`(./randall -i rdrand 27 | wc -c)`
if [ $c -eq 27 ];
then
    :
else
    echo "Test #3 Fail"
    exit 1
fi

d=`(./randall -i rdrand 2 | wc -c)`
if [ $d -eq 2 ];
then
    :
else
    echo "Test #4 Fail"
    exit 1
fi

e=`(./randall -i mrand48_r 36 | wc -c)`
if [ $e -eq 36 ];
then
    :
else
    echo "Test #5 Fail"
    exit 1
fi

f=`(./randall -i mrand48_r 1 | wc -c)`
if [ $f -eq 1 ];
then
    :
else
    echo "Test #6 Fail"
    exit 1
fi

g=`(./randall -i /dev/random 49 | wc -c)`
if [ $g -eq 49 ];
then
    :
else
    echo "Test #7 Fail"
    exit 1
fi

h=`(./randall -i /dev/random 3 | wc -c)`
if [ $h -eq 3 ];
then
    :
else
    echo "Test #8 Fail"
    exit 1
fi

i=`(./randall -o stdio 99 | wc -c)`
if [ $i -eq 99 ];
then
    :
else
    echo "Test 9 Fail"
    exit 1
fi

j=`(./randall -o stdio 0 | wc -c)`
if [ $j -eq 0 ];
then
    :
else
    echo "Test #10 Fail"
    exit 1
fi

k=`(./randall -o 4 58 | wc -c)`
if [ $k -eq 58 ];
then
    :
else
    echo "Test #11 Fail"
    exit 1
fi

l=`(./randall -o 16 4 | wc -c)`
if [ $l -eq 4 ];
then
    :
else
    echo "Test #11 Fail"
    exit 1
fi

m=`(./randall -o 7 7 | wc -c)`
if [ $m -eq 7 ];
then
    :
else
    echo "Test #12 Fail"
    exit 1
fi

n=`(./randall -o 3 0 | wc -c)`
if [ $n -eq 0 ];
then
    :
else
    echo "Test #13 Fail"
    exit 1
fi

o=`(./randall -o 1 4 | wc -c)`
if [ $o -eq 4 ];
then
    :
else
    echo "Test #14 Fail"
    exit 1
fi

p=`(./randall -i rdrand -o 4 64 | wc -c)`
if [ $p -eq 64 ];
then
    :
else
    echo "Test #15 Fail"
    exit 1
fi

q=`(./randall -i mrand48_r -o 3 7 | wc -c)`
if [ $q -eq 7 ];
then
    :
else
    echo "Test #16 Fail"
    exit 1
fi

r=`(./randall -i /dev/random -o 18 2 | wc -c)`
if [ $r -eq 2 ];
then
    :
else
    echo "Test #16 Fail"
    exit 1
fi

s=`(./randall -i /dev/random -o stdio 200 | wc -c)`
if [ $s -eq 200 ];
then
    :
else
    echo "Test #17 Fail"
    exit 1
fi

echo "Passed All Test"
