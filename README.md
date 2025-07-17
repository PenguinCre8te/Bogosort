# 🐧 Multithreaded Bogosort: Penguin Chaos Edition

This repository contains a gloriously inefficient sorting algorithm—**bogosort**—implemented with multithreading and just the right amount of penguin flair. Why sort logically when you can unleash 8 threads to randomly shuffle an array until fate hands you a miracle?

## ❄️ Features
- Multithreaded bogosorting powered by `pthread`
- High CPU usage for maximal entertainment
- Timing analysis to watch chaos unfold
- Penguin-themed terminal output (because it's fun)

## 🚀 How It Works
Each thread copies and shuffles the original array until it happens to be sorted. Once one thread finds order, the others gracefully retire. Bogosort is notoriously inefficient, with runtime complexity of **O(n!)**, so expect hilarity and heat.

## 🔧 Build and Run
```bash
gcc -o bogosort bogosort.c -lpthread
./bogosort
