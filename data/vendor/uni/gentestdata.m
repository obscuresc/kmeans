% generate data from 3 gaussian distributions 
% mean, covariance, number of points
R1 = mvnrnd([10 10],[0.5 0; 0 0.5],100);
R2 = mvnrnd([5 5],[0.5 0.25; 0.25 0.5],80);
R3 = mvnrnd([5 10],[0.3 0; 0 0.3],60);

R = [R1; R2; R3];

% shuffle the data (remove this if you want to check class
% labels easily)
ix = randperm(size(R,1));
Rshuff = R(ix,:);

%
fprintf('%d\n',size(Rshuff,1));
disp(Rshuff);

