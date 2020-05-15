% Copyright 2020, All Rights Reserved
% Code by 02 Liangxuan Guo, 2017302509
% For Course Science Computation Exp, Week 12
clc; clear all; close all;

H = [1, 0; 0, 1];
x = [0, 0]';
eps = 1e-5;
k = 0;
while true
    k = k + 1;
    gk = g(x);
    if norm(gk) < eps
        break;
    end
    if k == 1 
        dk = - H * gk;
    else
        delta_x = x - x_old;
        delta_g = gk - g_old;
        H = H + (1 + delta_g' * H * delta_g / (delta_x' * delta_g)) * (delta_x * delta_x') / (delta_x' * delta_g)...
            - ((delta_x * delta_g' * H + H * delta_g * delta_x')/(delta_x' * delta_g));
        dk = - H * gk;
    end
    x_old = x;
    g_old = gk;
    alphak = fminbnd(@(lambda) f(x + lambda * dk),0,10);
    x = x + alphak* dk;
end
ans = x

function ret = f(x)
    ret = (x(1) - 1)^4 + (x(1) - x(2))^2;
end

function ret = g(x)
    ret = [4 * (x(1) - 1)^3 + 2 * (x(1) - x(2)), 2 * (x(2) - x(1))]';
end