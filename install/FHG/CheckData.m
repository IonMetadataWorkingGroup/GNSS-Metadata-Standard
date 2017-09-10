function FHG_OK = CheckData( doSilent )

% +1  : for pass
%  0 : fail
% -1 : not executed

% check the system (xmlread not supported under Octave) 
isOctave = exist('OCTAVE_VERSION', 'builtin') ~= 0;
if isOctave
    fprintf('\n***********************************************\n');
    fprintf(  '* Warning: xmlread not supported under Octave *\n');
    fprintf(  '* Skipping "CheckFHG()" converter tests.     *\n')    
    fprintf(  '***********************************************\n\n');
    
    FHG_OK = -1;
    return;
end







if( ~exist( 'doSilent', 'var') )
    doSilent = 0;
end

% https://github.com/Fraunhofer-IIS/flexiband
%
% Data frames are always 1024 bytes long. They contain a preamble, a 32-bit counter, payload data and padding to fill up the frame.
%
% The counter starts at zero when the flexiband is started with the "Start data transfer" Vendor Request. It increments with each frame. When the maximum value is reached is rolls over to zero.
%
% The padding is currently filled with 0x00 bytes. In a later version it might be used as CRC.
%
% 0	1	2	3	4	5	6	7	...	m	...	1023
% PREAMBLE	COUNTER	PAYLOAD DATA	PADDING
% 0x55	0xAA	count	(up to 1014 bytes)	0x00
% Payload
%
% The layout of the payload depends on the current FPGA configuration. Here are some examples:
%
% byte	0	1	...	1013
% I-3	L5 I [7:4]	L5 Q [3:0]	L5 I [7:4]	L5 Q [3:0]	...	L5 I [7:4]	L5 Q [3:0]
% III-1a	L2 I [7:6]	L2 Q [5:4]	L1 I [3:2]	L1 Q [1:0]	L5 I [7:4]	L5 Q [3:0]	...	L5 I [7:4]	L5 Q [3:0]
% byte	0	1	2	3	...	1011
% III-1b	L2 I [7:4]	L2 Q [3:0]	L1 I [7:4]	L1 Q [3:0]	L5 I [7:4]	L5 Q [3:0]	L5 I [7:4]	L5 Q [3:0]


% IIS specific
preamble = '55aa';
% frameDataLength = 1024; % byte
preambleDataLength = 2; % byte
counterDataLength = 4; % byte

% ION Metadata
usbx = xml2struct('L125_III1b_15s.usbx');

block.cycles = str2num(usbx.metadata.lane.block.cycles.Text);
block.sizeheader = str2num(usbx.metadata.lane.block.sizeheader.Text);
block.sizefooter = str2num(usbx.metadata.lane.block.sizefooter.Text);

chunk.countwords = str2num(usbx.metadata.lane.block.chunk.countwords.Text);
chunk.sizeword = 'int8';    % str2num(usbx.metadata.lane.block.chunk.sizeword.Text);
                            % int8 =! uint8; we are using int8, not uint8

streamL2.ratefactor = str2num(usbx.metadata.lane.block.chunk.lump.stream{1,1}.ratefactor.Text);
streamL2.quantization = str2num(usbx.metadata.lane.block.chunk.lump.stream{1,1}.quantization.Text);
streamL2.format = usbx.metadata.lane.block.chunk.lump.stream{1,1}.format.Text;

streamL1.ratefactor = str2num(usbx.metadata.lane.block.chunk.lump.stream{1,2}.ratefactor.Text);
streamL1.quantization = str2num(usbx.metadata.lane.block.chunk.lump.stream{1,2}.quantization.Text);
streamL1.format = usbx.metadata.lane.block.chunk.lump.stream{1,2}.format.Text;

streamL5.ratefactor = str2num(usbx.metadata.lane.block.chunk.lump.stream{1,3}.ratefactor.Text);
streamL5.quantization = str2num(usbx.metadata.lane.block.chunk.lump.stream{1,3}.quantization.Text);
streamL5.format = usbx.metadata.lane.block.chunk.lump.stream{1,3}.format.Text;

% block.cycles = 253;
% block.sizeheader = 6; %preambleDataLength + counterDataLength;
% block.sizefooter = 6;
% 
% chunk.countwords = 4;
% chunk.sizeword = 'int8'; % =! uint8; we are using int8, not uint8
% 
% streamL1.ratefactor = 1;
% streamL1.quantization = 4;
% streamL2.format = 'IQ';
% 
% streamL2.ratefactor = 1;
% streamL2.quantization = 4;
% streamL2.format = 'IQ';
% 
% streamL5.ratefactor = 2;
% streamL5.quantization = 4;
% streamL5.format = 'IQ';

% How much data shall be converted...
nrOfFrames = 10;

frameDataLength = block.sizeheader + block.cycles * chunk.countwords + block.sizefooter;
payloadDataLength = block.cycles * chunk.countwords; % == 1012

% read in raw data - multiplexed file with additional data (preamble, counters, crc)
fid = fopen('L125_III1b_15s.usb', 'r');
raw = fread(fid, frameDataLength * nrOfFrames, chunk.sizeword);
fclose(fid);

L2I = zeros(1, nrOfFrames * block.cycles * streamL1.ratefactor);
L2Q = zeros(1, nrOfFrames * block.cycles * streamL1.ratefactor);
L1I = zeros(1, nrOfFrames * block.cycles * streamL2.ratefactor);
L1Q = zeros(1, nrOfFrames * block.cycles * streamL2.ratefactor);
L5I = zeros(1, nrOfFrames * block.cycles * streamL5.ratefactor);
L5Q = zeros(1, nrOfFrames * block.cycles * streamL5.ratefactor);

raw_counter_next = 0;

for idxFrame = 1: nrOfFrames
    
    idxFrameOffset = (idxFrame - 1) * frameDataLength;
    raw_preamble = sprintf('%x', typecast(int8(raw(1 + idxFrameOffset : idxFrameOffset + preambleDataLength)),'uint8'));
    
    if ~strcmp(preamble, raw_preamble)
        error('Preamble not found... error.');
    else
        if( ~doSilent )
            disp('Preamble found.')
        end
        raw_counter = sprintf('%x', typecast(int8(raw(1 + idxFrameOffset + preambleDataLength : idxFrameOffset + block.sizeheader)),'uint8'));
        if( ~doSilent )
            disp(strcat('Frame=', num2str(idxFrame), ': Counter value= ', raw_counter))
        end
        if raw_counter_next ~= hex2dec(raw_counter);
            error('Counter error...')
            % todo: implement zero-padding if data is lost...
        else
            raw_counter_next = hex2dec(raw_counter) + 1;
            %raw_payload = raw(preambleDataLength + counterDataLength +1 : preambleDataLength + counterDataLength + payloadDataLength +1);
            raw_payload = raw(1 + idxFrameOffset + block.sizeheader : idxFrame * frameDataLength - block.sizefooter);
            
            
            % Stream #1
            idx_payload = 1;
            for idx = 1 + (idxFrame - 1) * block.cycles * streamL2.ratefactor : idxFrame * block.cycles * streamL2.ratefactor
                tmp8bit = sprintf('%.2x', typecast(int8(raw_payload(idx_payload)),'uint8'));
                L2I(idx) = nhex2dec(tmp8bit(1),4)*2+1;
                L2Q(idx) = nhex2dec(tmp8bit(2),4)*2+1;
                
                idx_payload = idx_payload + 4;
                
                % disp(idx)
                % disp(idx_payload)
            end
            
            % Stream #2
            idx_payload = 2;
            for idx = 1 + (idxFrame - 1) * block.cycles * streamL2.ratefactor : idxFrame * block.cycles * streamL1.ratefactor
                tmp8bit = sprintf('%.2x', typecast(int8(raw_payload(idx_payload)),'uint8'));
                L1I(idx) = nhex2dec(tmp8bit(1),4)*2+1;
                L1Q(idx) = nhex2dec(tmp8bit(2),4)*2+1;
                
                idx_payload = idx_payload + 4;
                
                % disp(idx)
                % disp(idx_payload)
            end
            
            % Stream #3
            idx_payload = 3;
            for idx = 1 + (idxFrame - 1) * block.cycles * streamL5.ratefactor : 2 : idxFrame * block.cycles * streamL5.ratefactor
                tmp8bit = sprintf('%.2x', typecast(int8(raw_payload(idx_payload)),'uint8'));
                L5I(idx) = nhex2dec(tmp8bit(1),4)*2+1;
                L5Q(idx) = nhex2dec(tmp8bit(2),4)*2+1;
                
                tmp8bit = sprintf('%.2x', typecast(int8(raw_payload(idx_payload+1)),'uint8'));
                L5I(idx+1) = nhex2dec(tmp8bit(1),4)*2+1;
                L5Q(idx+1) = nhex2dec(tmp8bit(2),4)*2+1;
                
                idx_payload = idx_payload + 4;
                
                % disp(idx)
                % disp(idx_payload)
            end
        end
    end
end
%
%%
%
fid = fopen('L1E1bc.dat', 'r');
if( sum( fid == -1 ) > 0 )
    fprintf('Failed to open input file: FAIL\n')
    FHG_OK = 0;
    return;
end
rawL1 = fread(fid, 2 * nrOfFrames * block.cycles * streamL1.ratefactor, chunk.sizeword); % 2* for I/Q
fclose(fid);

fid = fopen('L2L2C.dat', 'r');
if( sum( fid == -1 ) > 0 )
    fprintf('Failed to open input file: FAIL\n')
    FHG_OK = 0;
    return;
end
rawL2 = fread(fid, 2 * nrOfFrames * block.cycles * streamL2.ratefactor, chunk.sizeword); % 2* for I/Q
fclose(fid);

fid = fopen('L5E5a.dat', 'r');
if( sum( fid == -1 ) > 0 )
    fprintf('Failed to open input file: FAIL\n')
    FHG_OK = 0;
    return;
end
rawL5 = fread(fid, 2 * nrOfFrames * block.cycles * streamL5.ratefactor, chunk.sizeword); % 2* for I/Q
fclose(fid);

%
if( ~doSilent )
    disp('verifiying the converted data...')
end


L2OK = 1;
L1OK = 1;
L5OK = 1;
if sum( abs(  L2I - rawL2(1:2:nrOfFrames*2*block.cycles*streamL2.ratefactor).' ) ); L2OK = 0; disp('error in L2I conversion'); end
if sum( abs(  L2Q - rawL2(2:2:nrOfFrames*2*block.cycles*streamL2.ratefactor).' ) ); L2OK = 0; disp('error in L2Q conversion'); end
if sum( abs(  L1I - rawL1(1:2:nrOfFrames*2*block.cycles*streamL1.ratefactor).' ) ); L1OK = 0; disp('error in L1I conversion'); end
if sum( abs(  L1Q - rawL1(2:2:nrOfFrames*2*block.cycles*streamL1.ratefactor).' ) ); L1OK = 0; disp('error in L1Q conversion'); end
if sum( abs(  L5I - rawL5(1:2:nrOfFrames*2*block.cycles*streamL5.ratefactor).' ) ); L5OK = 0; disp('error in L5I conversion'); end
if sum( abs( L5Q - rawL5(2:2:nrOfFrames*2*block.cycles*streamL5.ratefactor).'  ) ); L5OK = 0; disp('error in L5Q conversion'); end

if( ~doSilent )
    disp('done.')
end
%
FHG_OK = L2OK && L1OK && L5OK;






