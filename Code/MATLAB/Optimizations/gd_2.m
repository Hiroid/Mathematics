% Copyright 2020, All Rights Reserved
% Code by 02 Liangxuan Guo, 2017302509
% For Course Science Computation Exp, Week 10
clc; clear all; close all;

eps = 1e-5; x = [0, 3]';

k = 0;
while true
    k = k + 1;
    gk = g(x);
    syms lambda;
    lmin = fminbnd(@(lambda) f(x - lambda * gk),0,10)
    xold = x;
    x = x - lmin * gk
    if norm(x - xold) < eps
        break;
    end
end
ans = x

function ret = f(x)
    ret = (x(1) - 2)^4 + (x(1) - 2 * x(2))^2;
end

function ret = g(x)
    ret = [4 * (x(1) - 2)^3 + (x(1) - 2 * x(2)) * 2, -4 * (x(1) - 2 * x(2))]';
end
