# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?
> Pneumonoultramicroscopicsilicovolcanoconiosis is an artificial long word said to mean a lung disease caused by inhaling very fine ash and sand dust.Apr 9, 2014

## According to its man page, what does `getrusage` do?

> getrusage() returns resource usage measures for who, which can be one of the following:

> RUSAGE_SELF
Return resource usage statistics for the calling process, which is the sum of resources used by all threads in the process.

> RUSAGE_CHILDREN
Return resource usage statistics for all children of the calling process that have terminated and been waited for. These statistics will include the resources used by grandchildren, and further removed descendants, if all of the intervening descendants waited on their terminated children.

> RUSAGE_THREAD (since Linux 2.6.26)
Return resource usage statistics for the calling thread.

## Per that same man page, how many members are in a variable of type `struct rusage`?

> 16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

> You are passing the address of before and after so you can operate on those original variables and not values that may have been changed elsewhere.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

> After checking for correct arguments, you set up getrusage so you can print the statistics at the end.
If arguments == 3, the user specified which dictionary to use.  Otherwise, load the text file to read.
For each character read in the file, if it's and alpha-character, append it to the word, otherwise it is a new word.
When you have a new word, update the word counter.
Check the spelling, update the rusage benchmark.
If the word is misspelled, add it to the number of misspellings and print the word.
Then get the next word.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

> Read each character to determine if it is a backslash, apostrophe or non-alphabetic character.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

> So we could not change them in our implementation.
