# Charm particles vizualization

This repository contains macros for visualizing the lifetime and quark composition of charm particles in the form of pie charts. Different quarks are shown in different colors, and a quark and an antiquark of the same flavor are shown in different shades of the same color. The area of the pie charts is proportional to the particle's lifetime.

There are to ways to run this code:

## 1. Using CERN ROOT (C++)

In this case one needs pre-installed [CERN ROOT](https://root.cern/) package. Then to build plots simply run following commands:
```
source /path-to-your-root-installation/thisroot.sh
root DrawPlots.C
```

## 2. Using Julia

In this case one needs pre-installed [Julia](https://julialang.org/) programming language. Then to build plots simply run following command:
```
julia DrawPlots.jl
```
