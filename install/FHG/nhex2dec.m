function [x]=nhex2dec(hexstring,n)
% hexstring : hex representation of two's complement of xmydec=hex2dec(hexstring);
% x : input decimal number
% n :   number of bits to perform 2's complements
x = hex2dec(hexstring);
x = x - (x >= 2.^(n-1)).*2.^n;