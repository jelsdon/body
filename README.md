body
===================
> You've heard of 'head' and 'tail', well here's 'body'!

Print the body of a file, defaulting to the middle 10 lines.


```
 body [options...] <file>
 Options:
 -r        Randomly select body location of file (10 lines output)
```

currently prints out up to `10` lines of a files body (file center). `-r` takes these 10 lines from a random location within the file _between_ lines *1* and *EOF*  

Building
===================
`make`

Installing
===================
`sudo make install`
 
TODO
===================
Add flags
- ~~`-r` Output random part of body~~  [commit](https://github.com/jelsdon/body/commit/821e0e738ac4b8c342273a744f6cdaa78f9b06d5#diff-d2a906635104318d0d2da63cc2f15ea4 "commit")
- `-#` set body width (lines)


