# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import sympy as sy

Vin=sy.symbols('Vin')
R=sy.symbols('R')
I=sy.symbols('I')
#带入参数
Vin=2
R=1
I=1
#电路叠加的计算公式
Va=(Vin/(2*R))*R+(R/2)*I
#简化表达式
exps=sy.sympify(Va)

print(exps)


