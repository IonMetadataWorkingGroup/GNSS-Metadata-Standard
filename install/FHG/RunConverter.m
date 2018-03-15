function RunConverter( doSilent )

binName     = 'Converter';
outputType  = 'int8_t';
xmlFileName = 'L125_III1b_15s.usbx'; 

if ismac
    cmdString  = ['../'   binName ' ' xmlFileName ' ' outputType];
elseif isunix
    cmdString  = ['../'   binName ' ' xmlFileName ' ' outputType];
elseif ispc
    cmdString  = ['../'   binName ' ' xmlFileName ' ' outputType];
else
    disp('Operating system not supported\nPlease manually modify script (check_converter.m : line 18) to continue.\n')
    return;
end   

if doSilent
   cmdString = [cmdString ' > log.txt'];
end

system( cmdString );




