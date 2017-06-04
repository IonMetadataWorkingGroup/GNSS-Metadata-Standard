fs       = 62e6;
IFL1CA   = 7.42e6;
IFBDSB1  = -6.902e6;

fid      = fopen('sjtu_l1b1_metadata_test_20151105.dat', 'rb');
sis      = fread(fid, 2000, 'int8');
sis      = sis(1:2:2000) + 1i*sis(2:2:2000);
Nsamples = 1000;