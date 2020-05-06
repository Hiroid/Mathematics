% Copyright 2020, All Rights Reserved
% Code by 02 Liangxuan Guo, 2017302509
% For Course Science Computation Exp, Week 10
clc; clear all; close all;

eps = 1e-5;
G = [6, 0; 0, 4]; b = [-4, -6]'; x = [0, 0]';
while true
    gk = g(x);
    if norm(gk) < eps
        break;
    end
    alpha = gk' * gk / (gk' * G * gk);
    x = x - alpha * gk;
end
ans = x

function ret = g(x)
    ret = [6 * x(1) - 4, 4 * x(2) - 6]';
end
