function CleanData( )

% delte the old files, to make sure that the 'TestConverter' execution
% actually creates some new files.

delete('L1.dat');
delete('L5.dat');
delete('RFI-Mon.hdft');

