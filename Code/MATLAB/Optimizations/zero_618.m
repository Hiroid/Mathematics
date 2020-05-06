% Copyright 2020, All Rights Reserved
% Code by 02 Liangxuan Guo, 2017302509
% For Course Science Computation Exp, Week 9
clc; clear all; close all;

a = -1; b = 1; t = 0.618;
delta = 0.08;

while b - a > delta
    a_l = a + (1 - t) * (b - a);
    a_r = a + t * (b - a);
    if f(a_l) < f(a_r)
        b = a_r;
    else
        a = a_l;
    end
end
ans = (a + b) / 2

function ret = f(x)
    ret = 2*x^2 - x - 1;
end