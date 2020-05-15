% Copyright 2020, All Rights Reserved
% Code by 02 Liangxuan Guo, 2017302509
% For Course Science Computation Exp, Week 12
clc; clear all; close all;

x = [0, 0]';
eps = 1e-6;
k = 0;
delta = 1;
deltaup = 2;
while true
    k = k + 1;
    gk = g(x);
    if norm(gk) < eps
        break;
    end
    Bk = G(x);
    d = trustq(gk, Bk, delta);
    deltaf = f(x) - f(x + d);
    deltaq = - qk(x, d);
    rk = deltaf / deltaq;
    if (rk <= 0.25)
        delta = 0.5 * delta;
    else
        if (rk >= 0.75 && norm(d) == delta)
            delta = min(2 * delta, deltaup);
        end
    end
    if (rk > 0.25)
        x = x + d;
    end
end
ans = x

% d = trustq([400, -200]', [1202, -400; -400, 200], 5)
function d = trustq(gk, Bk, dta)
    n = length(gk); gamma = 0.05;
    epsilon = 1e-6; rho = 0.6; sigma = 0.2;
    mu0 = 0.05; lam0 = 0.05;
    d0 = ones(n, 1); u0 = [mu0, zeros(1, n + 1)]';
    z0 = [mu0, lam0, d0']';
    k = 0;
    z = z0; mu = mu0; lam = lam0; d = d0;
    while (k <= 150)
        dh = dah(mu, lam, d, gk, Bk, dta);
        if (norm(dh) < epsilon)
            break;    
        end
        A = JacobiH(mu, lam, d, Bk, dta);
        b = beta(mu, lam, d, gk, Bk, dta, gamma) * u0 - dh;
        dz = A \ b; 
        dmu = dz(1); dlam = dz(2); dd = dz(3 : n + 2);
        m = 0; mk = 0;
        while (m <= 20)
            dhnew = dah(mu + rho^m * dmu, lam + rho^m * dlam, d + rho^m * dd, gk, Bk, dta);
            if (norm(dhnew) <= (1 - sigma * (1 - gamma * mu0) * rho^m) * norm(dh))
                mk = m;
                break;
            end
            m = m + 1;
        end
        alpha = rho^mk;
        mu = mu + alpha * dmu;
        lam = lam + alpha * dlam;
        d = d + alpha * dd;
        k = k + 1;
    end
end
function ret = phi(mu, a, b)
    ret = a + b - sqrt((a - b)^2 + 4 * mu);
end
function ret = dah(mu, lam, d, gk, Bk, dta)
    n = length(d); ret(1) = mu; ret(2) = phi(mu, lam, dta^2 - norm(d)^2);
    mh = (Bk + lam * eye(n)) * d + gk;
    for i = 1 : n
        ret(i + 2) = mh(i);
    end
    ret = ret(:);
end
function ret = beta(mu, lam, d, gk, Bk, dta, gamma)
    dh = dah(mu, lam, d, gk, Bk, dta);
    ret = gamma * norm(dh) * min(1, norm(dh));
end
function ret = JacobiH(mu, lam, d, Bk, dta)
    n = length(d);
    ret = zeros(n + 2, n + 2);
    pmu = -4 * mu / sqrt((lam + norm(d)^2 - dta^2)^2 + 4 * mu^2);
    thetak = (lam + norm(d)^2 - dta^2) / sqrt((lam + norm(d)^2 - dta^2)^2 + 4 * mu^2);
    ret = [1, 0, zeros(1, n);
         pmu, 1 - thetak, -2 * (1 + thetak) * d';
         zeros(n, 1), d, Bk + lam * eye(n)];
end
function ret = qk(x, d)
    gk = g(x); Bk = G(x);
    ret = gk' * d + d' * Bk * d / 2;
end
function ret = f(x)
    ret = 10 * (x(1) - x(2))^2 + (x(1) - 1)^2;
end
function ret = g(x)
    ret = [20 * (x(1) - x(2)) + 2 * (x(1) - 1), 20 * (x(2) - x(1))]';
end
function ret = G(x)
    ret = [22, -20; -20, 20];
end

