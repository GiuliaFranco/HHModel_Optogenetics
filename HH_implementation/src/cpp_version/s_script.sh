#!/bin/bash
for i in 1000 200 100 66.7 
#40 33.3 28.7 25
#for i in 7 7.5 8 8.5 8.75 9 9.5 9.75 10  
do
   ./a.out ${i} 7.96  &>  ../../graphs/WB_HH_Stoch/Guler/L_f_${i}.txt
   echo ${i}
done
