subroutine vcatch_flooded(mx,my,mbc,mfields,dx,dy, & 
        area,q,sum,c_kahan)
  implicit none

  integer mx,my,mbc,mfields
  double precision dx, dy
  double precision sum(mfields), c_kahan(mfields)
  double precision q(1-mbc:mx+mbc,1-mbc:my+mbc,mfields)
  double precision t, y, area_ij
  double precision area(-mbc:mx+mbc+1,-mbc:my+mbc+1)

  integer i,j,m
  integer*8 cont, get_context
  double precision flood_depth
  logical fclaw2d_map_is_used

  logical use_kahan

  use_kahan = .true.

  cont = get_context()
    
  flood_depth = 1.e-3

  area_ij = dx*dy  !! Area in each mesh cell is constant
  do m = 1,mfields
    do j = 1,my
        do i = 1,mx
            if (fclaw2d_map_is_used(cont)) then
                  area_ij = area(i,j)  !! Area varies
            endif
            if (use_kahan) then
                !! Flood depth : 1e-3
                !! May need to convert to latlong
                if (m == 1) then
                    if (q(i,j,m) .gt. flood_depth) then
                        y = area_ij - c_kahan(m)
                        t = sum(m) + y
                        c_kahan(m) = (t-sum(m)) - y
                        sum(m) = t
                    endif
                endif
            else
                if (m == 1) then
                    if (q(i,j,m) .gt. flood_depth ) then
                        sum(m) = sum(m) + area_ij
                    endif
                endif
            endif
        enddo
    enddo
enddo
end