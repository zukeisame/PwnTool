# PwnTool

- Warning
  - It only work for little-endian architecture
  - For little-endian architecture, it should work correctly (I hope)

- Introduction
  - Basically pwntools in C
  - But is uses foramt string (i.e. functions like printf()/scanf()) to handle I/O

- Usage (You should only call functions in PwnType.h)
  - ptRemote:
    - Pass the domain name and port number to run remote process
  - ptLocal:
    - Pass a path to execute local process
  - ptClose:
    - Close remote/local connection
  - ptRecvf: (# is an unsigned number, ptSendf will return number of bytes it received)
    - %J will discard all the data it received so far (pass nothing)
    - %S will received until this string pattern happened (pass a string)
    - %P will print all bytes received on the screen (pass nothing)
    - %#J will discard # bytes (pass nothing)
    - %#P will print # bytes (pass nothing)
    - %#a will received #(<= 4) bytes and put it into a 32-bit address parameter (pass a pointer to a variable of FourBytes)
    - %#A will received #(<= 8) bytes and put it into a 64-bit address parameter (pass a pointer to a variable of EightBytes)
    - %#L will received at most # bytes or until it reaches the end of line (pass a buffer)
    - %#C will received at most # bytes (pass a buffer)
  - ptSendf: (# is an unsigned number, ptSendf will return number of bytes it sent)
    - %C will send single byte (pass a character)
    - %S will send a string (pass a string)
    - %D will send a decimal (pass a number)
    - %U will send a unsigned int (pass a unsigned number)
    - %a will send a 32-bit address (pass a variable of FourBytes) 
    - %A will send a 64-bit address (pass a variable of EightBytes)
    - %F will send a file (pass a string of filename, I use it to send shellcode)
    - %r will send all 32-bit addresses until it reach PWN_END_OF_FOUR_BYTES (pass a series of ROP chain)
    - %R will send all 64-bit addresses until it reach PWN_END_OF_EIGHT_BYTES (pass a series of ROP chain)
    - %#C will send # bytes (pass a character)
    - %#a will send # 32-bit addresses repeatedly (pass a variable of FourBytes) 
    - %#A will send # 64-bit addresses repeatedly (pass a variable of EightBytes)
  - ptFlush:
    - Basically, all data you sent will be buffered until you call ptRecvf
    - If you want to send out data earlier, call ptFlush()
  - ptShell:
    - Call it to interact with the opened shell

- Compilation
  - Clone the repository
    ```sh
    git clone https://github.com/zukeisame/PwnTool.git
    ```
  - Important! Go to PwnVB.h and include the right path of VB.h (VB is another my repository) 
  - PwnTool uses VB to handle data buffering
    ```C
    // change include path
    #include "/path/to/VB.h
    ```
  - Run "setup.sh" to compile all object files and place libPwn.so to /usr/lib
    ```sh
    cd PwnTool
    ./setup.sh
    ```
  - Include path to Pwn.h in your code
  - Compile your progaram with -lPwn -lVB options (cannot reverse the order)
    ```sh
    gcc example.c -o example -lPwn -lVB
    ```
