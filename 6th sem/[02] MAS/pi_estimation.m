% Monte Carlo Simulation for Estimating Pi
clc; clear; close all;

N = 1e5;  

x = rand(N,1);
y = rand(N,1);

inside_circle = (x.^2 + y.^2) <= 1;

pi_estimate = 4 * sum(inside_circle) / N;

fprintf('Estimated value of Pi using %d random points: %f\n', N, pi_estimate);

figure;
hold on;
axis equal;
theta = linspace(0, pi/2, 100);
plot(cos(theta), sin(theta), 'r', 'LineWidth', 2); % Quarter circle boundary
scatter(x(~inside_circle), y(~inside_circle), 1, 'b'); % Points outside the circle
scatter(x(inside_circle), y(inside_circle), 1, 'g'); % Points inside the circle
title(sprintf('Monte Carlo Estimation of Pi (N = %d)', N));
legend('Quarter Circle', 'Outside Points', 'Inside Points');
hold off;