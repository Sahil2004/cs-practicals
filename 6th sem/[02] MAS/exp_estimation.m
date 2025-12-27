% e^x integral calculation using Monte Carlo

clc; clear; close;

n0 = 1;
k = 3;
m = 7;

xmin = input("Enter the minimum value: ");
xmax = input("Enter the maximum value: ");

ni = zeros(1, m-1);
ri = zeros(1, m-1);
xi = zeros(1, m-1);
fi = zeros(1, m-1);
sum = 0;

for i = 1:m-1
    ni(i) = mod((k*i), m);
    ri(i) = ni(i)/m;
    xi(i) = xmin + (ri(i)*(xmax-xmin));
    fi(i) = exp(xi(i));
    sum = sum + fi(i);
end

i = sum / 6;

disp(i);