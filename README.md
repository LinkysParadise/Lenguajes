## Compiling Instructions

- Open a terminal and use the `cd` command to move to the folder where you saved the project files.

- Once in the project folder, compile the program using the following command:

```sh
gcc regex.c -o regex
```

This will generate an executable called `regex`.

## Instructions for use.

1. **Do a text file with the AFD definition**:

  The text file must contain at least 5 lines:

  1. A list with all the states of the AFD.
  2. A list with the alphabet of the AFD.
  3. The initial state of the AFD.
  4. A list with the final states of the AFD.
  5. The transitions of the AFD.

  The transitions of the AFD could be more than one line.

  Here is an example of the content of a `.txt` file for an AFD:

  ```
  q0 q1 q2
  a b
  q0
  q2
  q0 a q1
  q1 b q2
  q2 a q0
  q2 b q1
  ```
  
2. **Run the program**:

 - In the terminal, inside the project folder, run the following command to start the program.

```sh
./regex rules.txt <word>
```

  **Note**: `rules.txt` is the name of the text file with AFD rules made in the first step. `<word>` corresponds to a String you want to analyze, for example `abbb` or `ababbab`. 

3. **Interpret the Result**.

The program will parse the input string according to the rules defined in the configuration file. Finally, it will tell you whether the string was accepted or rejected by the DFA.

**Example output**: `The word 'abbb' is accepted by the DFA.`


## Integrantes

- **Mateo Fonseca**
- **Santiago Garzón**
- **Karol Guerrero**
- **Sebastian Barros**
