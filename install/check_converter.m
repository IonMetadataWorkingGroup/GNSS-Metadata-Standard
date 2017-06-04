%%
MAC = 0;
WIN = 1;


%%%%%
% Run the Converter

SYS = MAC;
binName    = 'TestConverter';

testDir    = pwd;
if SYS == WIN
    installDir = '.';
    cmdString  = [binName ' > log.txt'];
elseif SYS == MAC 
    installDir = './';
    cmdString  = ['./'   binName  ' > log.txt'];
else
    printf('System??\n');
end

cd(installDir);
installDir = pwd();
system(cmdString);
cd(testDir);


%%%%%%
% Check each of the files
doSilent = 1;

%FHG
cd('./FHG/');
FHG_OK = CheckFHG( doSilent );
if( FHG_OK )
    fprintf('FGH:   OK\n');
else
    fprintf('FGH:   PROBLEM!\n');
end
cd('..');

%IFEN
cd('./IFEN/');
IFEN_OK = CheckIFEN( doSilent );
if( IFEN_OK )
    fprintf('IFEN:  OK\n');
else
    fprintf('IFEN:  PROBLEM!\n');
end
cd('..');

%JRC
cd('./JRC/');
JRC_OK = CheckJRC( doSilent );
if( JRC_OK )
    fprintf('JRC:   OK\n');
else
    fprintf('JRC:   PROBLEM!\n');
end
cd('..');



%TRIGR
cd('./TRIGR/');
TRIGR_OK = CheckTRIGR( doSilent );
if( TRIGR_OK )
    fprintf('TRIGR: OK\n');
else
    fprintf('TRIGR: PROBLEM!\n');
end
cd('..');









