#!/bin/bash
#for i in 1000 200 100 66.7 40 28.7 25
for i in 7.5 8 8.5 8.75 9 9.25 9.5 9.75 10
do
   ./main 40 ${i} &> ../../graphs/WB_HH/s1_latency_graph/L_I_${i}.txt
   wait ${i}
   echo ${i}
done
