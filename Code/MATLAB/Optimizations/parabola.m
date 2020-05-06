% Copyright 2020, All Rights Reserved
% Code by 02 Liangxuan Guo, 2017302509
% For Course Science Computation Exp, Week 9
clc; clear all; close all;

a = 0; b = 3; eps = 1e-2;  x = [0:0.01:3]; y = f(x);
plot(x, y)
half = (a+b)/2;
k = 0;
while true && k <= 1000
    k = k + 1;
    min_x = intp(a, f(a), half, f(half), b, f(b));
    if abs(min_x - half) < eps
        ans = (min_x + half) / 2;
        break;
    end
    array = [f(a), f(half), f(b)];
    [val, index] = max(array);
    array(index) = [];
    array(3) = min_x;
    next = sort(array);
    a = next(1); b = next(3);half = next(2);
end
k
ans

function min_x =  intp(x_1, f_1, x_2, f_2, x_3, f_3)
    b = [f_1, f_2, f_3]';
    A = [x_1^2, x_1, 1; x_2^2, x_2, 1; x_3^2, x_3, 1];
    res = A\b;
    a = res(1); b = res(2); c = res(3);
    min_x = -b / (2 * a);
end

function ret = f(x)
    ret = x.^3 -x .* 2 + 1;
end