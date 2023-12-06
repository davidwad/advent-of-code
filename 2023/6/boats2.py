from math import sqrt, ceil, floor


T = 53897698
D = 313109012141201

tb0 = T/2 + sqrt(T*T/4 - D)

tb1 = T/2 - sqrt(T*T/4 - D)

if tb0 > tb1:
    print(floor(tb0) - ceil(tb1) + 1)
else:
    print(floor(tb1) - ceil(tb0) + 1)
