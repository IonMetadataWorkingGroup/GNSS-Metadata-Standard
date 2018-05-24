function FITWDP_OK = CheckData( doSilent )

% +1  : for pass
%  0 : fail
% -1 : not executed

% because we have a header, we need to load two full blocks
nSamples = 524288;

origFileDataType = 'int8';
newFileDataType  = 'int8';

fileL1Original = fopen('L1_ref.dat', 'rb');

dataL1Original = fread( fileL1Original, nSamples, origFileDataType );

fileL1New = fopen(sprintf('L1.dat'));

if( fileL1New == -1)
    fprintf('Failed to open input file: FAIL\n')
    FITWDP_OK = 0;
    return;
end

L1OK = 0;
if( fileL1New > 0 )
    dataL1New = fread( fileL1New, nSamples, newFileDataType );
    if( dataL1Original ==  dataL1New )
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


fileL5Original = fopen('L5_ref.dat', 'rb');

dataL5Original = fread( fileL5Original, nSamples, origFileDataType );

fileL5New = fopen(sprintf('L5.dat'));

if( fileL5New == -1)
    fprintf('Failed to open input file: FAIL\n')
    FITWDP_OK = 0;
    return;
end

L5OK = 0;
if( fileL5New > 0 )
    dataL5New = fread( fileL5New, nSamples, newFileDataType );
    if( dataL5Original ==  dataL5New )
        if(~doSilent)
            fprintf('File L5 OK\n');
        end
        L5OK = 1;
    else
        if(~doSilent)
            fprintf('File L5 Broken!\n');
        end
    end
else
    if(~doSilent)
        fprintf('File L5 Missing!\n')
    end
end



headerBytes = 3*512;

fileHeaderOriginal = fopen('headers_ref.dat', 'rb');

dataHeaderOriginal = fread( fileHeaderOriginal, headerBytes, origFileDataType );

fileHeaderNew = fopen(sprintf('RFI-Mon.hdft'));

if( fileHeaderNew == -1)
    fprintf('Failed to open input file: FAIL\n')
    FITWDP_OK = 0;
    return;
end

HeaderOK = 0;
if( fileHeaderNew > 0 )
    dataHeaderNew = fread( fileHeaderNew, headerBytes, newFileDataType );
    if( dataHeaderOriginal ==  dataHeaderNew )
        if(~doSilent)
            fprintf('File Header OK\n');
        end
        HeaderOK = 1;
    else
        if(~doSilent)
            fprintf('File Header Broken!\n');
        end
    end
else
    if(~doSilent)
        fprintf('File Header Missing!\n')
    end
end

fclose all;


FITWDP_OK = L1OK && L5OK && HeaderOK;

