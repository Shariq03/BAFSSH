%% Face recognition
% This algorithm uses the eigenface system (based on pricipal component
% analysis - PCA) to recognize faces. For more information on this method
% refer to http://cnx.org/content/m12531/latest/

%% Download the face database
% You can find the database at the follwoing link, 
% http://www.cl.cam.ac.uk/research/dtg/attarchive/facedatabase.html The
% database contains 400 pictures of 40 subjects. Download the zipped
% database and unzip it in the same directory as this file. 

%% Loading the database into matrix v
w=load_database();

% writeDigitalPin(a, 'D12', 0);

%% Initializations
% We randomly pick an image from our database and use the rest of the
% images for training. Training is done on 399 pictues. We later
% use the randomly selectted picture to test the algorithm.


size (w) %%initializations %the initial conditions are initialized. %the new image input and video configuarion. %that will be used for recognition is set.
v = videoinput('winvideo', 2); %initialize video input
triggerconfig (v, 'manual') %configure trigger 
v.FramesPerTrigger = 1; 
set (v,'TriggerFrameDelay',20); %Set trigger delay 
%preview(v); 
start(v); 
trigger(v) %Triggering snapshot 
set(v, 'ReturnedColorSpace','grayscale'); 
rgbImage = getdata(v); 
stop(v); 
fullImageFileName = fullfile(pwd, 'new.pgm'); 
imwrite(rgbImage,fullImageFileName); 
B=imread('new.pgm'); 
r = imresize(B, [112 92]); %Resizing image to 112x92 
imwrite(r,'new.pgm'); im =(r); %r contains the image we use to test the algorithm 
tempimg = im(:,:,1); r = reshape(tempimg, 10304,1); v=w;


N=20;                               % Number of signatures used for each image.
%% Subtracting the mean from v
O=uint8(ones(1,size(v,2))); 
m=uint8(mean(v,2));                 % m is the maen of all images.
vzm=v-uint8(single(m)*single(O));   % vzm is v with the mean removed. 

%% Calculating eignevectors of the correlation matrix
% We are picking N of the 400 eigenfaces.
L=single(vzm)'*single(vzm);
[V,D]=eig(L);
V=single(vzm)*V;
V=V(:,end:-1:end-(N-1));            % Pick the eignevectors corresponding to the 10 largest eigenvalues. 


%% Calculating the signature for each image
cv=zeros(size(v,2),N);
for i=1:size(v,2);
    cv(i,:)=single(vzm(:,i))'*V;    % Each row in cv is the signature for one image.
end


%% Recognition 
%  Now, we run the algorithm and see if we can correctly recognize the face. 
subplot(121); 
imshow(reshape(r,112,92));title('Looking for ...','FontWeight','bold','Fontsize',16,'color','red');

subplot(122);
p=r-m;                              % Subtract the mean
s=single(p)'*V;
z=[];
for i=1:size(v,2)
    z=[z,norm(cv(i,:)-s,2)];
    if(rem(i,20)==0),imshow(reshape(v(:,i),112,92)),end;
    drawnow;
end

[a,i]=min(z);


tt=a;
if (a>=9000000 && a<=17000000 && i>=20 && i<=30) 
    disp('Shariq');
    subplot(122);
    imshow(reshape(v(:,i),112,92));title('Found!','FontWeight','bold','Fontsize',16,'color','red');
      a=arduino('com5','uno');
        writeDigitalPin(a, 'D12', 1);
       % pir=readDigitalPin(a,'D50');
       % if(pir==1)
        %     writeDigitalPin(a, 'D10', 1);
       % else
       %      writeDigitalPin(a, 'D26', 0);
      %  end
       % disp(pir);
       pause(3);
   s = servo(a, 'D8');
        servo();
         writeDigitalPin(a, 'D12', 0);
      clear a;
elseif a>=4000000 && a<=18000000 && i>=31 && i<=40
   disp('Rambabu');
    subplot(122);
    imshow(reshape(v(:,i),112,92));title('Found!','FontWeight','bold','Fontsize',16,'color','red');
      a=arduino('com5','uno');
        writeDigitalPin(a, 'D12', 1);
       % pir=readDigitalPin(a,'D50');
       % if(pir==1)
        %     writeDigitalPin(a, 'D10', 1);
       % else
       %      writeDigitalPin(a, 'D26', 0);
      %  end
       % disp(pir);
       pause(3);
       
   s = servo(a, 'D8');
        servo();
         writeDigitalPin(a, 'D12', 0);
      clear a;
else
      %   a = arduino('com3', 'Mega2560', 'Libraries', 'Servo');
      %writeDigitalPin(a, 'D26', 0);
 
    xy=imread('C:\Users\dharma\Desktop\blank.jpg');
     imshow(xy);title('Not found!','FontWeight','bold','Fontsize',16,'color','red');
    title('Not Found!','FontWeight','bold','Fontsize',16,'color','red');
    pause(2);
         clear a;
    disp('Not found');
   % clear all;
   %  a = arduino('com5', 'uno', 'Libraries', 'Servo');
   %s = servo(a, 'D8');
    %    serreset();
       
end
clear all;
 %   a=arduino('com5','uno');
%     writeDigitalPin(a, 'D12', 0);
     b = arduino('com5', 'uno', 'Libraries', 'Servo');

while 1   
    x=readDigitalPin(b,'D11');
    if x==1
        s = servo(b, 'D8');
        serreset();
        clear all;
        break;
    end
end

%writeDigitalPin(b, 'D13', 0);
clear b;
clear x;