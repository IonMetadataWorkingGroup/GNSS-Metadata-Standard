

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% This is the collection of test data. Each test has one directory, in
% which there should be an XML file and corresponding binary data. 
%Each test directory should contain two matlab/octave files:
%  'CheckData.m': should compare the converted samples to the original 
%                 (or some reference), returning true upon succes
%  'CleanData.m': should delete the converted files 

testDirectories = {'FHG', 'IFEN', 'JRC', 'TRIGR', 'SJTU'};




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Purge all of the old converted sample files, to ensure that the 
% TestConverter execution acutally creates new converted files 
for t=1:numel(testDirectories)
    cd(testDirectories{t});
    CleanData( );
    cd('..');
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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
    installDir = '';
    cmdString  = [binName ' > log.txt'];
else
    disp('Operating system not supported\nPlease manually modify script (check_converter.m : line 18) to continue.\n')
    return;
end

% check the system (xmlread not supported under Octave) 
isOctave = exist('OCTAVE_VERSION', 'builtin') ~= 0;
isMatlab = ~isOctave;

% run the converter 
cd(installDir);
installDir = pwd();
system(cmdString);
cd(testDir);

% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Check each of the files
doSilent = 1;

for t=1:numel(testDirectories)
    
    cd(testDirectories{t});
    
    TEST_OK = CheckData( doSilent );
    
    TestName = '                ';
    TestName(1:length(testDirectories{t})) = testDirectories{t};
    TestName(1+length(testDirectories{t})) = ':';
    
    if(     TEST_OK ==  1 )
        fprintf('%s OK\n',TestName);
    elseif( TEST_OK ==  0 )
        fprintf('%s FAILED!\n',TestName);
    elseif( TEST_OK == -1 )
        fprintf('%s SKIPPED\n',TestName);
    else
        fprintf('%s PROBLEM WITH TEST\n',TestName);
    end
    
    cd('..');
end

return;











