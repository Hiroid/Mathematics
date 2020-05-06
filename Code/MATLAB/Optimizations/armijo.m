% Copyright 2020, All Rights Reserved
% Code by 02 Liangxuan Guo, 2017302509
% For Course Science Computation Exp, Week 9
clc; clear all; close all;

xk = [-1, 1]'; dk = [1, 1]';
beta = 0.5; sigma = 0.2;
m = 0; mmax = 100;
while m < mmax
    if f(xk + beta^m * dk) <= (f(xk) + sigma * beta^m * g(xk)' * dk)
        mk = m;
        break;
    end
    m = m + 1;
end
alpha = beta^mk;
xk_new = xk + alpha * dk;
fk = f(xk)
fk_new = f(xk_new)


function ret = f(x)
    ret = 100 * (x(2) - x(1)^2)^2 + (1 - x(1))^2;
end

function ret = g(x)
    ret = [400 * x(1) * (x(1)^2 - x(2)) + 2 * (x(1) - 1), 200 * (x(2) - x(1)^2)]';
end