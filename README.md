# Block-chain-Hash

## Ekspermentines analizes rezultatai:

### Pirmas punktas
empty.txt - tuscias failas

a.txt - failas su viena raide a

b.txt - failas su viena raide b

"The Name of the Wind.txt" - citata iš knygos, 11088 simboliai

"The Name of the Wind(1).txt" - citata iš knygos, 11088 simboliai, pakeistas 1 simbolis is I i l

plrabn121.txt - poemos, 44838 simboliai

|Failas   |Hash   |
|---|---|
|empty.txt   |9a10c2f44d671685374790a9485a4b15   |
|a.txt   |8803dd1615ccf40b18a1e30f2140b51c   |
|failas su viena raide b   |8c6c557416691bbf018f888621ca95f3   |
|"The Name of the Wind.txt"   |0d11fb080d4e3328008539dc00d777e2   |
|"The Name of the Wind(1).txt"   |0f1e2e98092e57380091ec1300f5d11c   |
|plrabn121.txt   |4cca1d6f23b9a5a1152feeb69bda274d   |

### Antras punktas

konstitucija.txt - hash laikas 0.194663s

### Trečias punktas 

1000000 porų po du penkių simbolių ilgio string.

0 kolizijų

### Ketvirtas punktas

1000000 porų po du penkių simbolių ilgio string, poroje string reikšmės skiraisi tik 1 simboliu.

Skaičiuoja kiek bitų procentaliai skirasi hash pavertus i dvejetainę sistemą

min skirtumas =  23.44%  , max skirtumas = 60,16%   , average skirtumas = 41,64%
