if (PlotType == 1)
    showpatchborders;
    setpatchborderprops('linewidth',2);
    hidepatchborders;
    cv = linspace(qmin,qmax,20);
    % drawcontourlines(cv);
    
    colormap(parula);
    caxis([-qmin,qmax])
    colorbar
    
%     add_gauges();
%     add_regions(t);
    
    hold off;
    
    axis([0 1000 -800 800])
    daspect([1 1 1]);
    set(gca,'fontsize',16);
    axis on;
end    
    

NoQuery = 0;
prt = false;
if (prt)
    filename = framename(Frame,'bowl0000','png');
    print('-dpng',filename);
end

shg

clear afterframe;
clear mapc2m;
