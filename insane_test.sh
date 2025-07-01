#!/bin/bash

./nexo <<EOF
invalidcommand
clear now
ls extra_arg
pwd too_much
mkdir
cd
echo
touch
pwd
clear
mkdir insanity
cd insanity
touch test1.txt
touch test2.txt
echo Hello World > test1.txt
cat test1.txt
ls
find test1.txt
finddir insanity
cd ..
scheduling
4
miniOS> mkdir folder1
miniOS> echo Madness
miniOS> clear
miniOS> pwd
Enter: SJF
scheduling
3
miniOS> touch chaos.txt
miniOS> mkdir chaos
miniOS> cat chaos.txt
Enter: FCFS
scheduling
5
miniOS> clear
miniOS> echo oh
miniOS> find lost
miniOS> cd ..
miniOS> pwd
Enter: 9
exit
EOF
