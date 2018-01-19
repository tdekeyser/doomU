## Development of `doomU` programming language

doomU should be a language to easily look up 

### Goal syntax

`helloworld.du`
```
#!doomU

(
    Print "hello world!"
)
```


`findInUrl.du`
```
#!doomU

(
    Get “blabla.com"
    ,
    Search “hello world!” > results
    ,
    Create file “world.txt” > worldFile
    ,
    Write results to worldFile
)
```

### Goal call program

   $ doomU helloworld.du
