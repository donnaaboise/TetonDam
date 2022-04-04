function plot_vcatch()

close all;

fname = 'vcatch_dem.topo';
[p,ax,ay,az,bx,by,bz] = plot_topo(fname);

% Make sure aspect ratio is equal
daspect([1,1,1]);

% Grid lines
set(p,'edgecolor','k')   % Show grid lines
% set(p,'edgecolor','none')  % Don't show grid lines

% Some figure properties
set(gcf,'Clipping','off')
set(gcf,'position',[476   524   922   342]);


% camlight

% Lower left   ( 0,-800 ) 
% Upper right  ( 1000,800)
% axis([0,1000,-800,800,-30,50])
axis([ax,bx,ay,by,az,bz])

setviews;
%view(3)
view([-80,25])

axis off

shg

end

function [p,ax,ay,az,bx,by,bz] = plot_topo(fname)
% PLOT_TOPO plots the topo from file FNAME

% Only one feature
[p,ax,ay,az,bx,by,bz] = plot_feature(fname);

end


function [p,ax,ay,az,bx,by,bz] = plot_feature(fname)

fid = fopen(fname);

ncols = fscanf(fid,'%d',1);  fscanf(fid,'%s',1);
nrows = fscanf(fid,'%d',1);  fscanf(fid,'%s',1);
xll = fscanf(fid,'%g',1);    fscanf(fid,'%s',1);
yll = fscanf(fid,'%g',1);    fscanf(fid,'%s',1);
dx = fscanf(fid,'%g',1);     fscanf(fid,'%s',1);
nodata = fscanf(fid,'%g',1); fscanf(fid,'%s',1);
T = fscanf(fid,'%g',nrows*ncols);

fclose(fid);

% --------------------------------
ax = xll;
ay = yll;

bx = ax + dx*(ncols-1);
by = ay + dx*(nrows-1);

x = linspace(ax,bx,ncols);
y = linspace(ay,by,nrows);

T = reshape(T,ncols,nrows);
T = fliplr(T);


[xm,ym] = meshgrid(x,y);

nodata = find(T == nodata);
T(nodata) = nan;

% Color data (0 or 1 )
c = T;
c(~nodata) = 0;
c(nodata) = 1;

p = patch(surf2patch(xm,ym,T'));
set(p,'cdata',c');
set(p,'facecolor','flat')
set(p,'edgecolor','k');

% colormap([0.8 0.8 1; 1 1 1]);
colormap(white)
set(p,'cdatamapping','direct');


fprintf('Min height  : %12.4f\n',min(T(:)));
fprintf('Max height  : %12.4f\n',max(T(:)));

% zlim([min(T(:)), max(T(:))]);
az = min(T(:));
bz = max(T(:));


end

