# Simple Wordlist Generator

A C-based wordlist generator that creates personalized password lists for security testing.

## How it works

1. Collects personal information (names, birthdates, pets, hobbies)
2. Builds a base wordlist from the input
3. Uses Hashcat to combine terms and apply a password rule from [this repo](https://github.com/stealthsploit/Optimised-hashcat-Rule)
4. Outputs a baseline wordlist for testing

## Requirements

- `gcc` compiler
- `hashcat`
- `wget` or `curl`

## Quick Start

```bash
# Compile
gcc -o wordgen wordmonger.c

# Run
./wordgen
```

The final wordlist will be saved as `final.txt`.

