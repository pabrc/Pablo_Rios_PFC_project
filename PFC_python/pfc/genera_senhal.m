
X = imread('signal_15.bmp');
Z = [];
p_n = 0; % número de pixeles negros

for hctr=1:360
    for vctr=1:256
       if (X(vctr,hctr)== 15) %pixel blanco
           Y(vctr,hctr) = 0; %pongo a '0' los pixeles blancos
       else
           Y(vctr,hctr) = 1; %pongo a '1' los pixeles negros
           Z(hctr) = vctr;
           p_n = p_n + 1;
       end
    end
end

senhal = Z(1:10:end)

close
plot(senhal)



num_ent = 0;
fid = fopen('signal_15.txt','w');
fprintf(fid, '###### Values of the CCP RAM #######\n');

for i=1:36 
    
    fprintf(fid, '%d\t\t%d\n', i-1, senhal(i));
    
end


