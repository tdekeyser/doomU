## Development of `doomU` programming language

doomU is a simple programming language based on functional programming and especially the streaming API.

It can be used to quickly perform http calls and using the responses for your own good.

### Goal syntax

`helloworld.du`
```
#!doomU

(
    "hello world!"
    ,
    d_print
)
```

`findInUrl.du`
```
#!doomU

(
    d_get “blabla.com"
    ,
    d_search “hello world!” > results
    ,
    d_create file “world.txt” > worldFile
    ,
    d_write results worldFile
)
```

`function.du`
```
#!doomU

// Variable
listOfTen (
    d_of 1..10 // implies (): d_of 1..10
)

// Function
sum (
    (a, b) : a + b
    ;
    (a) : a
)
power (
    (a) : a*a
)

// Anonymous function
(
    listOfTen
    ,
    power
    ,
    sum
    ,
    d_print
)
```

### Goal call program

```
$ doomU helloworld.du
```
