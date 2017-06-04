function IFEN_OK = CheckIFEN( doSilent )

if( ~doSilent )
    disp( 'Verification of IFEN AltBOC dual RF data' );
    disp( '----------------------------------------' );
end
% %%
% MAC = 0;
% WIN = 1;
% 
% SYS = WIN;
% 
% 
% testDir    = pwd;
% if SYS == WIN
%     installDir = '..';
%     binName    = 'TestApp_vs';
% elseif SYS == MAC 
%     installDir = '/Volumes/Data/GitHub/GNSS-Metadata-Standard/Converter/install/';
%     binName    = './TestApp';
% else
%     printf('System??\n');
% end
% 
% 
% 
% cd(installDir);
% system('rm *.dat');
% system(binName);
% cd(testDir);



%%
fpt=fopen( 'SX3_AltBOC_DualRF_Band0_FE0_ANT0_f1191795000.stream', 'rb' );
sampt=fread( fpt, 1000, 'bit2' );
fclose( fpt );
sampt=2*sampt+1;

fp=fopen( 'ANT0-E5L5.dat', 'rb' );
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
sampt=fread( fpt, 1000, 'bit2' );
fclose( fpt );
sampt=2*sampt+1;

fp=fopen( 'ANT0-E1L1.dat', 'rb' );
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
sampt=fread( fpt, 1000, 'bit2' );
fclose( fpt );
sampt=2*sampt+1;

fp=fopen( 'ANT1-E5L5.dat', 'rb' );
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
sampt=fread( fpt, 1000, 'bit2' );
fclose( fpt );
sampt=2*sampt+1;

fp=fopen( 'ANT1-E1L1.dat', 'rb' );
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
