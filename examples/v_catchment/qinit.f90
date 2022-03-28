! qinit routine for parabolic bowl problem, only single layer
SUBROUTINE vcatch_qinit(meqn,mbc,mx,my,xlower,ylower,dx,dy,q,maux,aux)

    use geoclaw_module, only: grav

    implicit none

    ! Subroutine arguments
    integer, intent(in) :: meqn,mbc,mx,my,maux
    real(kind=8), intent(in) :: xlower,ylower,dx,dy
    real(kind=8), intent(inout) :: q(meqn,1-mbc:mx+mbc,1-mbc:my+mbc)
    real(kind=8), intent(inout) :: aux(maux,1-mbc:mx+mbc,1-mbc:my+mbc)

    ! Other storage
    INTEGER :: i,j
    REAL(kind=8) :: x,y

    DO i=1-mbc,mx+mbc
        x = xlower + (i - 0.5d0)*dx
        do j=1-mbc,my+mbc
           y = ylower + (j - 0.5d0) * dx
           q(1,i,j) = 1.5e-8
           q(2,i,j) = 0.d0
           q(3,i,j) = 0.d0
        enddo
     ENDDO

   END SUBROUTINE vcatch_qinit


