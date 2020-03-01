#!/bin/bash
for i in 1000 100 66.7 28.7 25
do
   ./main ${i} &> ../../graphs/WB_HH/s1_latency_graph/s_${i}.txt
   echo ${i}
done
