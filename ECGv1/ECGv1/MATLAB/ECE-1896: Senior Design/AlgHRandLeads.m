function [heartRate, leadsFlipped] = AlgHRandLeads(ECG_data)

    %polyfitting the data
    t = (1:size(ECG_data,2));

    opol = 9;
    [p,s,mu] = polyfit(t,ECG_data,opol);
    f_y = polyval(p,t,[],mu);

    ECG_detrend = ECG_data - f_y;
    
    % Find local maxima which corresponds to top of the QRS complex
    is_highest = islocalmax(ECG_detrend,'MinProminence', (max(ECG_detrend)+mean(ECG_detrend))/2);
    highest_value = ECG_detrend(find(is_highest));

    % Find local minima which corresponds to top of the QRS complex if
    % flipped

    modified_detrend = -ECG_detrend;
    is_lowest = islocalmax(modified_detrend,'MinProminence', (max(modified_detrend)+mean(modified_detrend))/2);
    lowest_value = ECG_detrend(find(is_lowest));

    avg_highest_value = mean(highest_value);
    avg_lowest_value = mean(lowest_value);
    
    
    if (avg_lowest_value > avg_highest_value)
        leadsFlipped = true;
        heartRate = 0;
    else
        leadsFlipped = false;
        r_index = find(highest_value);
        heartRate = size(r_index,2) * 6;
    end
end