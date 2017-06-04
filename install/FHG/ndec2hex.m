function [hexstring]=ndec2hex(x,n)
% x : input decimal number
% n :   number of bits to perform 2's complements
% hexstring : hex representation of two's complement of x 
x=x + (x<0).*2^n; 
hexstring=dec2hex(x, ceil(n/4));