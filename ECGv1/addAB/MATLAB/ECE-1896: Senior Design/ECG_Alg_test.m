%setting the default base folder
clear; clc; close all;
NSRfolder = './1 NSR'; 
if ~isfolder(NSRfolder)
  errorMessage = sprintf('Error: The following folder does not exist:\n%s', NSRfolder);
  uiwait(warndlg(errorMessage));
  return;
end

%finding the file names
filePattern = fullfile(NSRfolder, '*.mat');
matFiles = dir(filePattern);

%loading and looping through all .mat data
% for i = 1:length(matFiles)
%   baseFileName = matFiles(i).name;
%   fullFileName = fullfile(NSRfolder, baseFileName);
%   temp = load(fullFileName).val;
%   ECG_data(i,:) = temp;
% end

  baseFileName = matFiles(1).name;
  fullFileName = fullfile(NSRfolder, baseFileName);
  ECG_data = load(fullFileName).val;

[heartRate, p_index, q_index, r_index, s_index, t_index, ...
    px_values, tx_values, y_values] = ECG_algorithm(ECG_data);