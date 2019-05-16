# pyBon

pyBon is a Python interpreter, written in C, entirely from scratch. It is without the use of any parser or lexical analyzer generators. 

Right now, it is only capable of evaluating simple mathematical expressions. The ability to assign vlaues to an identifier and retreive such values is coming soon!
 

## Compiling

An executable for the program can be created in the terminal by running

```bash
cc -g pyBon.c helper.c dataStructs.c -o pyBon
```

## Usage

pyBon features the ability to read Python files via command line by passing in a text file, though it is suggested to call the program by running the REPL for now. 

```bash
./pyBon
```
Or, if you have text file of mathematical expressions on each line
```bash
./pyBon test.txt
```


## Contributing

Currently need help adding and retreiving values from a set of user-defined identifiers. 

https://github.com/RobertBonagura/pyBon

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

