
function main
  
    clc; clear; close all;
  
    path = 'D:/allYTPData/Out30';
    csvList = dir( sprintf( '%s/*.csv', path ) );
    
    X = zeros( length(csvList), 741 );
    SZ = [15,14,1]

    % histList2 = zeros( length(csvList)*4 , 2 );
    for( csvIdx = 1:length(csvList) )
      
      curHist = csvread( sprintf( '%s/%s', path, csvList(csvIdx).name ) );
    
      X( csvIdx, 1:741 ) = curHist;
      if(csvIdx<=15)
        y(csvIdx) = 1;
      elseif(csvIdx<=29)
        y(csvIdx) = 2;
      else
        y(csvIdx) = 3;
      endif
      % for( i = 1:4)
          % histList2 ( (csvIdx-1)*4+i , 1:2 ) = curHist(i*2-1:i*2);
          % C((csvIdx-1)*4+i) = csvIdx;
      #c(csvIdx) = floor((csvIdx+3)/4);
    #endfor
    endfor
    
    per_fileName = 'D:/allYTPData/distance.txt';
    per = textread(per_fileName)
    disp("sum = ")
    per(1)
    
    n = 741;
    [temp n] = size(X);
    labels = unique(y); 
    C = length(labels);
    Sw = zeros(n,n);
    Sb = zeros(n,n);
    mu = mean(X);
    
    for i = 1:C
      Xi = X(find(y == labels(i)),:);
      [m temp] = size(Xi);
      mu_i = mean(Xi);
      XMi = bsxfun(@minus, Xi, mu_i);
      Sw = Sw + ( XMi' * XMi);
      MiM = mu_i - mu;
      Sb = Sb + m * MiM' * MiM;
    end
    
    [W_lda, D] = eig(Sw\Sb);
    [D, i] = sort(diag(D), 'descend');
    W_lda = W_lda(:,i);

      figure;
    
    for i = 1:C
      Xi = X(find(y == labels(i)),:);
      [m temp] = size(Xi);
%      mu_i = mean(Xi);
      XMi = bsxfun(@minus, Xi, mu);
      z1(1:SZ(i), i) = XMi*W_lda(:,1);
      z2(1:SZ(i), i) = XMi*W_lda(:,2);
%      p = z*V(:,1)';
%      p = bsxfun(@plus,p,mu);
    end
      
    figure;
    
    hold on;
    
    nowCnt = 2;
    qx = 0.0;
    qy = 0.0;
    for( i = 1:C )
      
      plot( z1(1:SZ(i), i), z2(1:SZ(i), i), 'x-' );
      z1(1:SZ(i),i)
      for( j = 1:length(z1(1:SZ(i), i)))
        
        qx = qx + z1(j,i)*per(nowCnt)
        qy = qy + z2(j,i)*per(nowCnt)
        nowCnt = nowCnt + 1;
      end
      
    
    end
    
    plot(qx/per(1),qy/per(1),'*')

    hold off;

    #scale = 5;
    #pc1 = line([mu(1) - scale * W_lda(1,1) mu(1) + scale * W_lda(1,1)], [mu(2) - scale * W_lda(2,1) mu(2) + scale * W_lda(2,1)]);
    #set(pc1, 'color', [1 0 0], "linestyle", "--");
    
end

#https://octave.sourceforge.io/nan/function/train_sc.html