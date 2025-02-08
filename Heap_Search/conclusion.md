# Conclusion
In test files with small size, the normal search algorithm works faster than multi-process and multi-thread and it seems to be because of overhead of making threads and processes. In medium sized tests, the multi-thread performed better, but normal was still the best among the all.

>> Test Size: 10216

> main.out < biub.txt

```
Hi, I found the item on index: 10214
normal search took 879
Hi, I'm a thread who found the item at index: 10214
multi thread search took 1181815
Hi, I'm a process who found the item on index: 10214
multi process search took 19991400
```

# Challenges
1. Processes cannot communicate with each other, so I had to use the properties of heap to stop them searching. Whenever a process reaches an item which is bigger than the item it is looking for, it stopps.

2. Another challenge I faced was that the multi-thread function had some difficulities with referencing the strcuture of its arguments. So I had to malloc everytime I wanted to pass an argument to a new thread.

3. Another challenge was the about setting wait for processes and join for threads. The parent should wait for its children (same as real world) and the join should be invoked after all the threads are created.


## Sub-Conclusion
It was such a hard exercise and took about a whole day to code and debug. Won't ever forgive you 😒.