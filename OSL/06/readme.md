- In operating systems, whenever a new page is referred and not present in memory, page fault occurs and Operating System replaces one of the existing pages with newly needed page. 
- Different page replacement algorithms suggest different ways to decide which page to replace. 
- The target for all algorithms is to `reduce` number of `page faults`. 

### Optimal Solution
- Replace the page which is not used longest period of time in future. 