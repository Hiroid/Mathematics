% Copyright 2020, All Rights Reserved
% Code by 02 Liangxuan Guo, 2017302509
% For Course Science Computation Exp, Week 11
clc; clear all; close all;

eps = 1e-3; x = [0,0]';
k = 0;
while true
    k = k + 1;
    gk = g(x);
    if norm(gk) < eps
        break;
    end
    Gk = G(x);   
    eigval = eig(Gk);
    if (eigval(1) > 0 && eigval(2) > 0) 
        dk = - Gk \ gk;
    else
        dk = -gk;
    end
    alphak = fminbnd(@(lambda) f(x + lambda * dk),0,10);
    x = x + alphak* dk;
end
ans = x

function ret = f(x)
    ret = 100 * (x(1)^2 - x(2))^2 + (x(1) - 1)^2;
end
function ret = g(x)
    ret = [400 * x(1) * (x(1)^2 - x(2)) + 2 * (x(1) - 1), 200 * (x(2) - x(1)^2)]';
end
function ret = G(x)
    ret = [400 * (3 * x(1)^2 - x(2)), -400*x(1); -400*x(1), 200];
end