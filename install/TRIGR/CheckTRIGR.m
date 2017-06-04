function TRIGR_OK = CheckTRIGR( doSilent )

nSamples = 56320;

origFileDataType = 'int8';
newFileDataType  = 'int8';

fileS0Original = fopen('Str0_truth.dat', 'rb');
fileS1Original = fopen('Str1_truth.dat', 'rb');
fileS2Original = fopen('Str2_truth.dat', 'rb');
fileS3Original = fopen('Str3_truth.dat', 'rb');

dataS0Original = fread( fileS0Original, nSamples, origFileDataType );
dataS1Original = fread( fileS1Original, nSamples, origFileDataType );
dataS2Original = fread( fileS2Original, nSamples, origFileDataType );
dataS3Original = fread( fileS3Original, nSamples, origFileDataType );

dataS0Original = 2 * dataS0Original - 1;
dataS1Original = 2 * dataS1Original - 1;
dataS2Original = 2 * dataS2Original - 1;
dataS3Original = 2 * dataS3Original - 1;

fileS0New = fopen(sprintf('Str00.dat'));
fileS1New = fopen(sprintf('Str01.dat'));
fileS2New = fopen(sprintf('Str02.dat'));
fileS3New = fopen(sprintf('Str03.dat'));


STR00OK = 0;
if( fileS0New > 0 )
    dataS0New = fread( fileS0New, nSamples, newFileDataType );
    if( dataS0Original(1:1000) ==  dataS0New(1:1000) )
        if(~doSilent)
            fprintf('File STR00 OK\n');
        end
        STR00OK = 1;
    else
        if(~doSilent)
            fprintf('File STR00 Broken!\n');
        end
    end
else
    if(~doSilent)
        fprintf('File STR00 Missing!\n')
    end
end

STR01OK = 0;
if( fileS1New > 0 )
    dataS1New = fread( fileS1New, nSamples, newFileDataType );
    if( dataS1Original(1:1000) ==  dataS1New(1:1000) )
        if(~doSilent)
            fprintf('File STR01 OK\n');
        end
        STR01OK = 1;
    else
        if(~doSilent)
            fprintf('File STR01 Broken!\n');
        end
    end
else
    if(~doSilent)
        fprintf('File STR01 Missing!\n')
    end
end

STR02OK = 0;
if( fileS2New > 0 )
    dataS2New = fread( fileS2New, nSamples, newFileDataType );
    if( dataS2Original(1:1000) ==  dataS2New(1:1000) )
        if(~doSilent)
            fprintf('File STR02 OK\n');
        end
        STR02OK = 1;
    else
        if(~doSilent)
            fprintf('File STR02 Broken!\n');
        end
    end
else
    if(~doSilent)
        fprintf('File STR02 Missing!\n')
    end
end

STR03OK = 0;
if( fileS3New > 0 )
    dataS3New = fread( fileS3New, nSamples, newFileDataType );
    if( dataS3Original(1:1000) ==  dataS3New(1:1000) )
        if(~doSilent)
            fprintf('File STR03 OK\n');
        end
        STR03OK = 1;
    else
        if(~doSilent)
            fprintf('File STR03 Broken!\n');
        end
    end
else
    if(~doSilent)
        fprintf('File STR03 Missing!\n')
    end
end


fclose all;


if(~doSilent)

    dataS0Original(1:8)'
    dataS0New(1:8)'

    dataS1Original(1:8)'
    dataS1New(1:8)'

    dataS2Original(1:8)'
    dataS2New(1:8)'

    dataS3Original(1:8)'
    dataS3New(1:8)'
    
    
end


TRIGR_OK = STR00OK && STR01OK && STR02OK && STR03OK;














