https://github.com/BrianSidebotham/arm-tutorial-rpi/blob/master/part-5/armc-016/armc-start.S

enable cacbe and branch prediction

0. tests.s

1. Arm timer
   - number of instructions
   - arm timer runs at the system core clock : 250 Mhz
   - millions of instructions per second (mips)

2. Performance counters
   - pmu.h and pmu.c
   - cycles
   - instructions
   - cycles per instruction (cpi)

3. Cache
   - system_enable_cache
     - measure_icache()
     - measure_dcache()
   - system_enable_branch_prediction
     - measure_branch_prediction()
        - what is the branch prediction algorithm



