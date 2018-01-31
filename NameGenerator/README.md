#Name Generator
Simple namegenerator in current version can use only words with equal size


##Planned Features
- mixing diff len words


##Compilation
On linux simply use *Makefile* as follows:
```bash
make preprocessing
make namegenerator
```

Or if you need debug version:
```bash
make debug_preprocessing
# or / and
make debug_namegenerator
```

##How to use
You need some dictionary for example "dictionary.txt", firstly you have to preprocess dictionary:
```bash
$ ./preprocessing dictionary.txt
```
Now you should have files named i.e: "4", "8", "16", ... this number is a length of words inside the file.
Preprocessing is needed once / new dictionary.

Then use your preprocessed file to generate name:
```bash
$ ./namegenerator 2 4
xxxx yyyy
```
First argument is amount of words in name, second: path to the preprocessed file.

##License
Project is licensed under [MIT](LICENSE)
