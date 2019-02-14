function [ score ] = image_focus_assessment( image )
%IMAGE_FOCUS_ASSESSMENT 此处显示有关此函数的摘要
%   此处显示详细说明
%-------8x8 high pass filter
% // reference: How Iris Recognition Works. John Daugman. 2004
kernel = [-1 -1 -1 -1 -1 -1 -1 -1;
     -1 -1 -1 -1 -1 -1 -1 -1;
     -1 -1  3  3  3  3 -1 -1;
     -1 -1  3  3  3  3 -1 -1;
     -1 -1  3  3  3  3 -1 -1;
     -1 -1  3  3  3  3 -1 -1;
     -1 -1 -1 -1 -1 -1 -1 -1;
     -1 -1 -1 -1 -1 -1 -1 -1];
 
kernel = double(kernel);
image = double(image);
res_HPF_Daugman_8x8 = imfilter(image, kernel);

% res_HPF_Daugman_8x8 = im2double(res_HPF_Daugman_8x8);
[rows, cols] = size(res_HPF_Daugman_8x8);
power = 0.0;
for col=1 : cols
    for row=1 : rows
        power = power + abs(res_HPF_Daugman_8x8(row, col));
    end
end
power = power / (cols*rows);
GLOBALFOCUSVALUE_FOR50PERCENT = 60;
score = ((power*power) / (power*power + GLOBALFOCUSVALUE_FOR50PERCENT*GLOBALFOCUSVALUE_FOR50PERCENT)*100 + 0.5);

end

