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
    d_of 1..10 // implies () : d_of 1..10
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

### Development
1. Tokenizer (A lexer is a software program that performs lexical analysis.  Lexical analysis is the process of separating a stream of characters into different words, which in computer science we call 'tokens'.)
2. Parser (A parser goes one level further than the lexer and takes the tokens produced by the lexer and tries to determine if proper sentences have been formed.)

Source: https://www.quora.com/What-is-the-difference-between-a-lexer-and-a-parser

3. Integrator, which performs the requested stream.
