function JRC_OK = CheckJRC( doSilent )

nSamples = 1024*1024;

origFileDataType = 'int8';
newFileDataType  = 'int8';

fileL1Original = fopen('ref_1.dat', 'rb');
fileL2Original = fopen('ref_2.dat', 'rb');
fileL5Original = fopen('ref_3.dat', 'rb');

dataL1Original = fread( fileL1Original, nSamples, origFileDataType );
dataL2Original = fread( fileL2Original, nSamples, origFileDataType );
dataL5Original = fread( fileL5Original, nSamples, origFileDataType );

fileL1New = fopen(sprintf('L1.dat'));
fileL2New = fopen(sprintf('L2.dat'));
fileL5New = fopen(sprintf('L5.dat'));


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

L2OK = 0;
if( fileL2New > 0 )
    dataL2New = fread( fileL2New, nSamples, newFileDataType );
    if( dataL2Original(1:1000) ==  dataL2New(1:1000) )
        if(~doSilent)
            fprintf('File L2 OK\n');
        end
        L2OK = 1;
    else
        if(~doSilent)
            fprintf('File L2 Broken!\n');
        end
    end
else
    if(~doSilent)
        fprintf('File L2 Missing!\n')
    end
end
L5OK = 0;    
if( fileL5New > 0 )
    dataL5New = fread( fileL5New, nSamples, newFileDataType );
    if( dataL5Original(1:1000) ==  dataL5New(1:1000) )
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


fclose all;


JRC_OK = L1OK && L2OK && L5OK;