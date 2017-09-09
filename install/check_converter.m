%%%%%
% Run the Converter

binName    = 'TestConverter';

testDir    = pwd;

if ismac
    installDir = './';
    cmdString  = ['./'   binName  ' > log.txt'];
elseif isunix
    installDir = './';
    cmdString  = ['./'   binName  ' > log.txt'];
elseif ispc
    installDir = '.';
    cmdString  = [binName ' > log.txt'];
else
    disp('Operating system not supported\nPlease manually modify script (check_converter.m : line 18) to continue.\n')
    return;
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









