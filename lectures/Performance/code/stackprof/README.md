```
npm install cpuprofilify  # This will install it into a directory called node_modules, used by the Makefile
git clone https://github.com/brendangregg/FlameGraph
```

```
make console_main.cpuprofile
make console_main.svg
```

This example uses a modified keyboard/interrupt stack because the original
stackprof was built with an interrupt stack that passed the current `fp` to the
handler.  The latest interrupt subsystem just passes the `pc`, so for now we
modify the keyboard interrupt handler to accept `fp` and use our own interrupt
logic which passes `fp`.
