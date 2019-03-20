# Instructions

|  Champ | OPcode | Opérande1 | Opérande2 |
|:------:|:------:|:---------:|:---------:|
| Taille | 8 bits |   8 bits  |  32 bits  |

## Résumé

|  Nom             | OPcode |
|------------------|--------|
| [MOV](#mov)      | 0x00   |
| [CP](#cp)        | 0x01   |
| [ADD](#add)      | 0x02   |
| [SUB](#sub)      | 0x03   |
| [MUL](#mul)      | 0x04   |
| [DIV](#div)      | 0x05   |
| [LD](#ld)        | 0x06   |
| [STR](#str)      | 0x07   |
| [EQ](#eq)        | 0x08   |
| [INF](#inf)      | 0x09   |
| [INFEQ](#infeq)  | 0x0A   |
| [SUP](#sup)      | 0x0B   |
| [SUPEQ](#supeq)  | 0x0C   |

## Exemples

|       Exemple      |    OPcode   | Opérande1 |  Opérande2  |
|:------------------:|:-----------:|:---------:|:-----------:|
|   `RO = RO + R1`   | [ADD](#add) |     R0    |      R1     |
|                    | 0x02        | 0x00      | 0x0000_0001 |
| `R4 = R4 * R12`    | [MUL](#mul) | R4        | R12         |
|                    | 0x04        | 0x04      | 0x0000_000C |
| `R4 = 0x9876_5432` | [MOV](#mov) | R4        | 0x9876_5432 |
|                    | 0x00        | 0x04      | 0x9876_5432 |

### MOV

Assignation de valeur à un registre depuis une donnée

```txt
MOV <ra> <val>
```

```txt
ra <- val
```

### CP

Copie de valeur entre registres
```txt
CP <ra> <rb>
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

### LD

Chargement d'un registre depuis une donnée en mémoire

```txt
LD <ra> <addr>
```

```txt
ra <- @addr
```

### STR

Stockage d'un registre en mémoire

```txt
STR <ra> <addr>
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