function [heartRate, p_index, q_index, r_index, s_index, t_index, ...
    px_values, tx_values, y_values] = ECG_algorithm(ECG_data)

    %polyfitting the data
    t = (1:size(ECG_data,2));

    opol = 9;
    [p,s,mu] = polyfit(t,ECG_data,opol);
    f_y = polyval(p,t,[],mu);
    
%     plot(f_y);
%     hold on;
%     plot(ECG_data(i).val);
%     hold on;

    ECG_detrend = ECG_data - f_y;
%     p = polyfit(1:size(ECG_data(i).val,2),ECG_data(i).val,4);

    %removing noise in ECG data to better analyze
%     ECG_detrend = detrend(dt_ECG,5);
    
    % Find local maxima which corresponds to top of the QRS complex
    r_point = islocalmax(ECG_detrend,'MinProminence', (max(ECG_detrend)+mean(ECG_detrend))/2);
    r_index = find(r_point);

    %setting the default q_value and q_index and s_value and s_index size
    [q_value, q_index, s_value, s_index] = deal(zeros(1,size(r_index,2)));
    
    %finding the q and s points surrounding the r indices
    for j = 1:size(r_index,2)
        %finding q points
        [q_value(1,j), q_index(1,j)] = min(ECG_detrend(r_index(j) - 20: r_index(j)));
        q_index(1,j) = q_index(1,j) + (r_index(j) - 20) - 1;
        
        %finding s points
        if (r_index(j) + 20 > size(ECG_detrend,2))
            s_index_max = size(ECG_detrend,2);
        else
            s_index_max = r_index(j) + 20;
        end


        %use is localmin to find the lowest point in the range between 2 r
        %pointsx

%         while true
%             [s_value(1,j), s_index(1,j)] = min(ECG_detrend(r_index(j): s_index_max));
%             s_index(1,j) = s_index(1,j) + r_index(j) - 1;
% 
%             if(ECG_detrend(s_index + 1) && ECG_detrend(s_index + 1) > ECG_detrend(s_index))
%                 break;
%             end
%         end

        [s_value(1,j), s_index(1,j)] = min(ECG_detrend(r_index(j): s_index_max));
        s_index(1,j) = s_index(1,j) + r_index(j) - 1;
        
    end
    
    %default wave size
    [p_waves, p_index, t_waves, t_index, tp_valley, tp_valley_index] = deal(zeros(1,size(q_index,2)));
    %using the q and s points to find the p and t waves
    for j = 1:size(q_index,2)
        %thresholding values
        if (q_index(j) - 50 < 1)
            temp = q_index(j) - 50;
            q_index_min = q_index(j) - 50 - temp + 1;
        else       
            q_index_min = q_index(j) - 50;
        end

        [p_waves(1,j), p_index(1,j)] = max(ECG_detrend(q_index_min: q_index(j)));
        p_index(1,j) = p_index(1,j) + (q_index_min) - 1;

        %thresholding corne cases
        if (p_index(j) - 150 < 1)
            t_index_min = 1;
        else
            t_index_min = p_index(j) - 150;
        end

        if p_index(j) - 50 < 1
            temp = p_index(j) - 50;
            diff = p_index(j) - 50 - temp + 1;
        else
            diff = p_index(j) - 50;
        end
        
        %finding t wave
        [t_waves(1,j), t_index(1,j)] = max(ECG_detrend(t_index_min: diff));
        t_index(1,j) = t_index(1,j) + (t_index_min) - 1;

        %finding minimum between prior t and next p wave to show the zone
        %on the plot
        [tp_valley(1,j), tp_valley_index(1,j)] = min(ECG_detrend(t_index(j): p_index(j)));
        tp_valley_index(1,j) =  tp_valley_index(1,j) + t_index(j);
    end
    
    %multiply heart rate by 6 to find the rate per 60 seconds
    heartRate = size(r_index,2) * 6;
    
    %plotting the features and displaying heart rate
    
    [px_values, tx_values, y_values] = deal(zeros(4, size(tp_valley_index,2)));
    for j = 1:size(r_index,2)
        t_to_tpvalley_diff = (p_index(j) - tp_valley_index(j));

        if (j == 1)
            px_values(1:4,j) = [tp_valley_index(j) q_index(j)-5 q_index(j)-5 tp_valley_index(j)];
            tx_values(1:4,j) = [(t_index(j) - t_to_tpvalley_diff/2) (t_index(j)+t_to_tpvalley_diff/2) ...
                (t_index(j)+t_to_tpvalley_diff/2) (t_index(j) - t_to_tpvalley_diff/2)];
        elseif (j == size(r_index,2))
            px_values(1:4,j) = [tp_valley_index(j) q_index(j)-5 q_index(j)-5 tp_valley_index(j)];
%             tx_values(1:4,j) = [s_index(j-1)+20 tp_valley_index(j) tp_valley_index(j) s_index(j-1)+20];
            tx_values(1:4,j) = [(t_index(j) - t_to_tpvalley_diff/2) (t_index(j)+t_to_tpvalley_diff/2) ...
                (t_index(j)+t_to_tpvalley_diff/2) (t_index(j) - t_to_tpvalley_diff/2)];
        else
            px_values(1:4,j) = [tp_valley_index(j) q_index(j)-5 q_index(j)-5 tp_valley_index(j)];
%             tx_values(1:4,j) = [s_index(j-1)+20 tp_valley_index(j) tp_valley_index(j) s_index(j-1)+20];
            tx_values(1:4,j) = [(t_index(j) - t_to_tpvalley_diff/2) (t_index(j)+t_to_tpvalley_diff/2) ...
                (t_index(j)+t_to_tpvalley_diff/2) (t_index(j) - t_to_tpvalley_diff/2)];
        end
        y_values(1:4,j) = [min(ECG_detrend)*[1 1] max(ECG_detrend)*[1 1]];
    end
end