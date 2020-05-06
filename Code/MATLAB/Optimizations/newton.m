% Copyright 2020, All Rights Reserved
% Code by 02 Liangxuan Guo, 2017302509
% For Course Science Computation Exp, Week 10
clc; clear all; close all;

eps = 1e-3;
G = [8, 0; 0, 2]; x = [0, 0]';
k = 0;
while true
    k = k + 1;
    xold = x;
    gk = g(x);
    d = -G \ gk;
    x = x + d;
    if norm(x - xold) < eps
        break;
    end
end
ans = x

x = [0, 0]';
k = 0;
while true
    k = k + 1;
    xold = x;
    gk = g(x);
    d = -G \ gk;
    syms lambda
    lmin = fminbnd(@(lambda) f(x + lambda * d),0,10);
    x = x + lmin * d;
    if norm(x - xold) < eps
        break;
    end
end
ans = x

function ret = f(x)
    ret = 4 * x(1)^2 + x(2)^2 - 8 * x(1) - 4 * x(2);
end

function ret = g(x)
    ret = [8 * x(1) - 8, 2 * x(2) - 4]';
end
