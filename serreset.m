for angle = 0.40:-0.4:0
       writePosition(s, angle);
       current_pos = readPosition(s);
       current_pos = current_pos*180;
       fprintf('Current motor position is %d degrees\n', current_pos);
       pause(2);
end