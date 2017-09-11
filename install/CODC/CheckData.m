function CODC_OK = CheckData( doSilent )

% +1  : for pass
%  0 : fail
% -1 : not executed

nSamples = 1024*1024;

origFileDataType = 'int16';
newFileDataType  = 'int16';

fileL1Original = fopen('20170911_1118Z.dat', 'rb');

dataL1Original = fread( fileL1Original, nSamples, origFileDataType );

fileL1New = fopen(sprintf('L1.dat'));

if( fileL1New == -1)
    fprintf('Failed to open input file: FAIL\n')
    CODC_OK = 0;
    return;
end


L1OK = 0;
if( fileL1New > 0 )
    dataL1New = fread( fileL1New, nSamples, newFileDataType );
    if( dataL1Original(1:1000) ==  dataL1New(1:1000) )
        if(~doSilent)
            fprintf('File L1 OK\n');
        end
        L1OK = 1;
    else
        if(~doSilent)
            fprintf('File L1 Broken!\n');
        end
    end
else
    if(~doSilent)
        fprintf('File L1 Missing!\n')
    end
end


fclose all;


CODC_OK = L1OK;

