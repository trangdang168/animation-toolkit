function [] = summaryStats(data, _title, ytitle, xtitle)
  
hist(data);
title(_title);
ylabel(ytitle);
xlabel(xtitle);
  
fprintf('max %f\n', max(data));
fprintf('min %f\n', min(data));
fprintf('mean %f\n', mean(data));
fprintf('median %f\n', median(data));
fprintf('mode %f\n', mode(data));
fprintf('stdev %f\n', std(data));
  
end