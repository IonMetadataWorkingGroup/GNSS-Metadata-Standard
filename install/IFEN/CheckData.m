function IFEN_OK = CheckData( doSilent )

% +1  : for pass
%  0 : fail
% -1 : not executed

if( ~doSilent )
    disp( 'Verification of IFEN AltBOC dual RF data' );
    disp( '----------------------------------------' );
end


% check the system (xmlread not supported under Octave) 
isOctave = exist('OCTAVE_VERSION', 'builtin') ~= 0;
isMatlab = ~isOctave;


%%
fpt=fopen( 'SX3_AltBOC_DualRF_Band0_FE0_ANT0_f1191795000.stream', 'rb' );

% James's - quick Octave-ready hack
if isMatlab
    % if we are Matlab, then use the fancy 'binN' functionality
    sampt=fread( fpt, 1000, 'bit2' );
    fclose( fpt );
    sampt=2*sampt+1;
else
    % otherwise do the old-fashioned bit manipulation
    data=fread( fpt, 250, 'uint8' );
    fclose( fpt );

    sampt = zeros(1000,1);
    LUT = [1 3 -3 -1];
    for b=1:250
        for ofst=0:3
            sampt( 4*(b-1) + ofst + 1 ) = LUT( 1 + uint8( bitand(bitshift( data( b ) ,-2*ofst),uint8(3)) )  );
        end
    end
end


fp=fopen( 'ANT0-E5L5.dat', 'rb' );
if( sum( fp == -1 ) > 0 )
    fprintf('Failed to open input file: FAIL\n')
    IFEN_OK = 0;
    return;
end
samp = fread( fp, 1000, 'int8' );
fclose( fp );

A0E5_OK = 1;
if max( abs( samp-sampt ) ) == 0
    if( ~doSilent )
        disp( 'ANT0-E5L5.dat correct' );
    end
else
    A0E5_OK = 0;
    if( ~doSilent )
        disp( 'ANT0-E5L5.dat failed' );
    end
end

%[sampt(1:20)'; samp(1:20)']

%%
fpt=fopen( 'SX3_AltBOC_DualRF_Band1_FE0_ANT0_f1575420000.stream', 'rb' );

% James's - quick Octave-ready hack
if isMatlab
    % if we are Matlab, then use the fancy 'binN' functionality
    sampt=fread( fpt, 1000, 'bit2' );
    fclose( fpt );
    sampt=2*sampt+1;
else
    % otherwise do the old-fashioned bit manipulation
    data=fread( fpt, 250, 'uint8' );
    fclose( fpt );

    sampt = zeros(1000,1);
    LUT = [1 3 -3 -1];
    for b=1:250
        for ofst=0:3
            sampt( 4*(b-1) + ofst + 1 ) = LUT( 1 + uint8( bitand(bitshift( data( b ) ,-2*ofst),uint8(3)) )  );
        end
    end
end



fp=fopen( 'ANT0-E1L1.dat', 'rb' );
if( sum( fp == -1 ) > 0 )
    fprintf('Failed to open input file: FAIL\n')
    IFEN_OK = 0;
    return;
end
samp = fread( fp, 1000, 'int8' );
fclose( fp );

A0E1_OK = 1;
if max( abs( samp-sampt ) ) == 0
    if( ~doSilent )
        disp( 'ANT0-E1L1.dat correct' );
    end
else
    A0E1_OK = 0;
    if( ~doSilent )
        disp( 'ANT0-E1L1.dat failed' );
    end
end

%%
fpt=fopen( 'SX3_AltBOC_DualRF_Band2_FE0_ANT1_f1191795000.stream', 'rb' );
% James's - quick Octave-ready hack
if isMatlab
    % if we are Matlab, then use the fancy 'binN' functionality
    sampt=fread( fpt, 1000, 'bit2' );
    fclose( fpt );
    sampt=2*sampt+1;
else
    % otherwise do the old-fashioned bit manipulation
    data=fread( fpt, 250, 'uint8' );
    fclose( fpt );

    sampt = zeros(1000,1);
    LUT = [1 3 -3 -1];
    for b=1:250
        for ofst=0:3
            sampt( 4*(b-1) + ofst + 1 ) = LUT( 1 + uint8( bitand(bitshift( data( b ) ,-2*ofst),uint8(3)) )  );
        end
    end
end

fp=fopen( 'ANT1-E5L5.dat', 'rb' );
if( sum( fp == -1 ) > 0 )
    fprintf('Failed to open input file: FAIL\n')
    IFEN_OK = 0;
    return;
end
samp = fread( fp, 1000, 'int8' );
fclose( fp );

A1E5_OK = 1;
if max( abs( samp-sampt ) ) == 0
    if( ~doSilent )
        disp( 'ANT1-E5L5.dat correct' );
    end
else
    A1E5_OK = 0;
    if( ~doSilent )
        disp( 'ANT1-E5L5.dat failed' );
    end
end


%%
fpt=fopen( 'SX3_AltBOC_DualRF_Band3_FE0_ANT1_f1575420000.stream', 'rb' );
% James's - quick Octave-ready hack
if isMatlab
    % if we are Matlab, then use the fancy 'binN' functionality
    sampt=fread( fpt, 1000, 'bit2' );
    fclose( fpt );
    sampt=2*sampt+1;
else
    % otherwise do the old-fashioned bit manipulation
    data=fread( fpt, 250, 'uint8' );
    fclose( fpt );

    sampt = zeros(1000,1);
    LUT = [1 3 -3 -1];
    for b=1:250
        for ofst=0:3
            sampt( 4*(b-1) + ofst + 1 ) = LUT( 1 + uint8( bitand(bitshift( data( b ) ,-2*ofst),uint8(3)) )  );
        end
    end
end

fp=fopen( 'ANT1-E1L1.dat', 'rb' );
if( sum( fp == -1 ) > 0 )
    fprintf('Failed to open input file: FAIL\n')
    IFEN_OK = 0;
    return;
end
samp = fread( fp, 1000, 'int8' );
fclose( fp );

A1E1_OK = 1;
if max( abs( samp-sampt ) ) == 0
    if( ~doSilent )
        disp( 'ANT1-E1L1.dat correct' );
    end
else
    A1E1_OK = 0;
    if( ~doSilent )
        disp( 'ANT1-E1L1.dat failed' );
    end
end

IFEN_OK = A0E5_OK && A0E1_OK && A1E1_OK && A1E5_OK;
