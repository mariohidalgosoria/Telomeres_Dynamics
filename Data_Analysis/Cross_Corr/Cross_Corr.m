%/home/mhidalgosoria/Documents/Eli/Code_Data/CorrDVDISP/WTC

% Define two signals with M steps
clear
%file with drifts
load('C2T50.dat')
t=C2T50(:,1);
Rx=C2T50(:,2);
Ry=C2T50(:,3);
R0=sqrt(Rx(1).^2 + Ry(1).^2);
%relative drift vector
DV=sqrt(Rx.^2 + Ry.^2) - R0;
%2-26
%load corrected time series
ini=27;
fin=61;
MavCC=zeros(fin-ini,length(t));
for ii=ini:fin
name=sprintf('CCLAT%d.dat',ii);
data=load(name);
X=data(:,2);
Y=data(:,3);
RI=sqrt(X(1).^2 + Y(1).^2);
%corected displacement vector
R=sqrt(X.^2 + Y.^2)- RI;
mus1=mean(DV);
mus2=mean(R);
std1 = std(DV);
std2 = std(R);
% Number of steps
signal1 = (DV-mus1)/std1;   
signal2 = (R-mus2)/std2;

M = rows(DV);
% Initialize the cross-correlation result array for positive lags
crossCorr = zeros(1, M);  % Only positive lags, so we use M-length

% Manually compute the cross-correlation for positive lags only
for lag = 0:(M-1)
    sum_value = 0;
    for i = 1:(M-lag)
        sum_value += signal1(i) * signal2(i + lag);
    end
    crossCorr(lag + 1) = sum_value/  (M-lag);  % Store the result
 
end
plot(0:(M-1), crossCorr, '-o');
hold on;
CCC=[(0:(M-1))', crossCorr'];
namen=sprintf('C2ACT%d.dat',ii);
save(namen,'CCC',"-ascii");
end





%ini  =  2;//tracks at file LMNA1-3D_TEL.ods
  %Nexp = 26;//total of 25 trajectories
  %ini  =  27;//tracks at file LMNA3-3D_TEL.ods
  %Nexp = 61;//total of 35 trajectories
  %ini  =  62;//tracks at file LMNA4-3D_TEL.ods
  %Nexp = 99;//total of 38 trajectories
  %ini  =  100;//tracks at file LMNA5-3D_TEL.ods
  %Nexp = 124;//total of 25 trajectories
  %ini  =  125;//tracks at file LMNA6-3D_TEL.ods
  %Nexp = 159;//total of 35 trajectories
  %ini  =  160;//tracks at file LMNA7-3D_TEL.ods
  %Nexp = 207;//total of 48 trajectories
  %ini  =  208;//tracks at file LMNA9-3D_TEL.ods
  %Nexp = 232;//total of 25 trajectories
  %ini  =  233;//tracks at file LMNA10-3D_TEL.ods
  %Nexp = 271;//total of 39 trajectories


%%%%%KOC
%/home/mhidalgosoria/Documents/Eli/Code_Data/CorrDVDISP/KOC

% Define two signals with M steps
clear
%file with drifts
load('C2T50.dat')
t=C2T50(:,1);
Rx=C2T50(:,2);
Ry=C2T50(:,3);
R0=sqrt(Rx(1).^2 + Ry(1).^2);
%relative drift vector
DV=sqrt(Rx.^2 + Ry.^2) - R0;
%2-26
%load corrected time series
ini=21;
fin=37;
MavCC=zeros(fin-ini,length(t));
for ii=ini:fin
name=sprintf('CCWLT%d.dat',ii);
data=load(name);
X=data(:,2);
Y=data(:,3);
RI=sqrt(X(1).^2 + Y(1).^2);
%corected displacement vector
R=sqrt(X.^2 + Y.^2)- RI;
mus1=mean(DV);
mus2=mean(R);
std1 = std(DV);
std2 = std(R);
% Number of steps
signal1 = (DV-mus1)/std1;   
signal2 = (R-mus2)/std2;

M = rows(DV);
% Initialize the cross-correlation result array for positive lags
crossCorr = zeros(1, M);  % Only positive lags, so we use M-length

% Manually compute the cross-correlation for positive lags only
for lag = 0:(M-1)
    sum_value = 0;
    for i = 1:(M-lag)
        sum_value += signal1(i) * signal2(i + lag);
    end
    crossCorr(lag + 1) = sum_value/  (M-lag);  % Store the result
 
end
plot(0:(M-1), crossCorr, '-o');
hold on;
CCC=[(0:(M-1))', crossCorr'];
namen=sprintf('C2ACT%d.dat',ii);
save(namen,'CCC',"-ascii");
end



%ini  =  2;//tracks at file woLMNA10-3D_TEL
  %Nexp = 20;//total of 19 trajectories
  %ini  =  21;//tracks at file woLMNA11-3D_TEL
  %Nexp = 37;//total of 17 trajectories
  %ini  =  38;//tracks at file woLMNA13-3D_TEL
  %Nexp = 60;//total of 23 trajectories






