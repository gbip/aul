# Instructions

* 8 bits : opcode
* 8 bits : première opérande
* 32 bits seconde opérande

## Résumé

|  Nom             	| OPcode 	| Opérande1 	| Opérande2 	|
|------------------	|--------	|-----------	|-----------	|
| Taille (en bits) 	| 8      	| 8         	| 32        	|
| [MOV](#mov)      	| 0x00   	| <ra>      	| <value>   	|
| [CP](#cp)        	| 0x01   	| <ra>      	| <rb>      	|
| [ADD](#add)      	| 0x02   	| <ra>      	| <rb>      	|
| [SUB](#sub)      	| 0x03   	| <ra>      	| <rb>      	|
|                  	|        	|           	|           	|
|                  	|        	|           	|           	|
|                  	|        	|           	|           	|
|                  	|        	|           	|           	|
|                  	|        	|           	|           	|
|                  	|        	|           	|           	|
|                  	|        	|           	|           	|


### MOV

```
MOV <ra> <val>
```
```
ra <- val
```

### CP

```
CP <ra> <rb>
```

```
ra <- rb
```

### ADD

```
ADD <ra> <rb>
```

```
ra = ra+b
```

### SUB

```
SUB <ra> <rb>
```

```
ra= ra - rb
```

### MUL

```
MUL <ra> <rb>
```

```
ra = ra*rb
```

### DIV

```
DIV <ra> <rb>
```

```
ra = ra/rb
```

### LD

```
LD <ra> <addr>
```
```
ra <- @addr
```

### STR

```
STR <ra> <addr>
```

```
@addr <- ra
```

### EQ

```
EQ <ra> <rb>
```
```
ra = 1 si ra = rb
```

### INF

```
INF <ra> <rb>
```

```
ra = 1 si ra < rb
```

### INFEQ

```
INFEQ <ra> <rb>
```

```
ra = 1 si ra <= rb
```

### SUP

```
SUP <ra> <rb>
```

```
ra = 1 si ra > rb
```

### SUPEQ

```
SUPEQ <ra> <rb>
```

```
ra = 1 si ra >= rb
```