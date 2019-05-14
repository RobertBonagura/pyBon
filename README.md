# PyBon

PyBon is a Python interpreter, written in C.

Right now, it is only capable of evaluating simple mathematical expressions. The ability to assign and retreive values from an identifier is coming soon!
 

It features the ability to read Python files via command line by passing in an text file, though it is suggested to call the program by running the REPL for now.

## Compiling

An executable for the program can be created in the terminal by running

```bash
cc -g pyBon.c helper.c dataStructs.c -o pyBon
```

## Usage

```bash
./pyBon
```
Or
```bash
./pyBon test.txt
```


## Contributing

https://github.com/RobertBonagura/pyBon

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

