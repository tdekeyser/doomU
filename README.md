## Development of `doomU` programming language

doomU is a programming language based on functional programming and especially the streaming API.

#### Current syntax
`helloworld.du`
```
#!doomU

(
    (() : "hello world!")
    ,
    ((a) : prints:a )
)
```

`operations.du`
```
#!doomU

(
    (()  : [1, 2, 3, 4, 5] )
    ,
    ((i) : add:i:10 )
    ,
    ((i) : subtract:50:i )
    ,
    ((k) : multiply:k:k )
    ,
    ((m) : mod:m:7)
    ,
    ((a) : printi:a )
)
```

#### Target syntax

`helloworld.du`
```
#!doomU

(
    "hello world!"
    ,
    prints
)
```

`function.du`
```
#!doomU

// Variable
listOfTen (
    stream_of:1:10
)

// Function
sum (
    (a, b) : a + b
)
power (
    (a) : a*a
)

// Anonymous main function
(
    listOfTen
    ,
    power
    ,
    sum
    ,
    printi
)
```

`findInUrl.du`
```
#!doomU

(
    get “blabla.com"
    ,
    search:“hello world!” > results
    ,
    create_file:“world.txt” > worldFile
    ,
    write:results:worldFile
)
```

### Goal call program

```
$ doomU helloworld.du
```

### Development
1. Parser: the parser reads a file and strips it down into typed pieces
2. Interpreter: the interpreter receives the input from the parser and executes the pieces as a program
3. Operations: built-in functionalities that can be used in programs
