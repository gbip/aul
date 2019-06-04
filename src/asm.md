# Annexe : Présentation complète de notre jeu d'instructions

## Format

|  Champ | OPcode | Opérande1 | Opérande2 |
|:------:|:------:|:---------:|:---------:|
| Taille | 8 bits |   8 bits  |  32 bits  |

## Liste des instructions

|  Nom             | OPcode |
|------------------|--------|
| [MOVE](#MOVE)    | 0x00   |
| [COPY](#COPY)    | 0x01   |
| [ADD](#add)      | 0x02   |
| [SUB](#sub)      | 0x03   |
| [MUL](#mul)      | 0x04   |
| [DIV](#div)      | 0x05   |
| [LOAD](#LOAD)    | 0x06   |
| [STORE](#STORE)  | 0x07   |
| [EQ](#eq)        | 0x08   |
| [INF](#inf)      | 0x09   |
| [INFEQ](#infeq)  | 0x0A   |
| [SUP](#sup)      | 0x0B   |
| [SUPEQ](#supeq)  | 0x0C   |
| [PRINT](#print)  | 0x0D   |
| [JMP](#jmp)      | 0x0E   |
| [JMPRELADD](#JMPRELADD)| 0x0F |
| [JMPRELSUB](#JMPRELSUB)| 0x010|
| [JMPC](#jmpc)    | 0x11   |
| [JMPCRELADD](#JMPCRELADD)|0x12|
| [JMPCRELSUB](#JMPCRELSUB)|0x13|
| [NOT](#NOT)      | 0x14 |
| [AND](#AND)      | 0x15   |
| [OR](#OR)        | 0x16   |
| [NOP](#NOP) | 0x17 |

## Exemples

|       Exemple      |    OPcode   | Opérande1 |  Opérande2  |
|:------------------:|:-----------:|:---------:|:-----------:|
|   `RO = RO + R1`   | [ADD](#add) |     R0    |      R1     |
|                    | 0x02        | 0x00      | 0x0000_0001 |
| `R4 = R4 * R12`    | [MUL](#mul) | R4        | R12         |
|                    | 0x04        | 0x04      | 0x0000_000C |
| `R4 = 0x9876_5432` | [MOVE](#MOVE) | R4        | 0x9876_5432 |
|                    | 0x00        | 0x04      | 0x9876_5432 |

### MOVE

### Assignation de valeur à un registre depuis une donnée

```txt
MOVE <ra> <val>
```

```txt
ra <- val
```

### COPY

Copie de valeur entre registres

```txt
COPY <ra> <rb>
```

```txt
ra <- rb
```

### ADD

Addition de deux registres 

```txt
ADD <ra> <rb>

```

```txt
ra = ra+b
```

### SUB

Soustraction de deux registres

```txt
SUB <ra> <rb>
```

```txt
ra= ra - rb
```

### MUL

Multiplication de deux registres

```txt
MUL <ra> <rb>
```

```txt
ra = ra*rb
```

### DIV

Divisions de deux registres

```txt
DIV <ra> <rb>
```

```txt
ra = ra/rb
```

### LOAD

Chargement d'un registre depuis une donnée en mémoire

```txt
LOAD <ra> <addr>
```

```txt
ra <- @addr
```

### STORE

Stockage d'un registre en mémoire

```txt
STORE <ra> <addr>
```

```txt
@addr <- ra
```

### EQ

Test de l'égalité

```txt
EQ <ra> <rb>
```

```txt
ra = 1 si ra = rb
```

### INF

Test d'infériorité

```txt
INF <ra> <rb>
```

```txt
ra = 1 si ra < rb
```

### INFEQ

Test d'infériorité et d'égalité

```txt
INFEQ <ra> <rb>
```

```txt
ra = 1 si ra <= rb
```

### SUP

Test de supériorité

```txt
SUP <ra> <rb>
```

```txt
ra = 1 si ra > rb
```

### SUPEQ

Test de supériorité et d'égalité

```txt
SUPEQ <ra> <rb>
```

```txt
ra = 1 si ra >= rb
```

### PRINT

Affiche la valeur d'un registre

```txt
PRINT <ra>
```

```
display the value of <ra> on screen
```

### JMP

Sauts

```txt
JMP <unused> <ra>
```

```txt
Jump to the address of <ra>
```

### JMPRELADD

Sauts relatifs

```txt
JMPRELADD <unused> <ra>
```

```txt
Jump to pc+ <ra>
```


### JMPRELSUB

Sauts relatifs

```txt
JMPRELSUB <unused> <ra>
```

```txt
Jump to pc-<ra>
```

### JMPC


```txt
JMPC <ra> <rb>
```

```txt
Jump to <rb> if <ra> is 0
```

### JMPCRELADD

```txt
JMPCRELADD <ra> <rb>
```

```txt
Jump to pc+<rb> if <ra> is 0
```

### JMPCRELSUB

```txt
JMPCRELSUB <ra> <rb>
```

```txt
Jump to pc-<rb> if <ra> is 0
```

### NOT

```txt
NOT <ra> <rb>
```

```txt
<ra> = 1 if <rb> = 0
<ra> = 0 otherwise
```

### AND

```txt
AND <ra> <rb>
```

```txt
<ra> = 1 if (<ra> != 0 and <rb> !=0)
<ra> = 0 otherwise
```

### OR

```txt
OR <ra> <rb>
```

```txt
<ra> = 1 if (<ra> != 0 or <rb> !=0)
<ra> = 0 otherwise
```

### NOP

```txt
NOP
```
