module rainfall_mod
    implicit none

    integer example
    logical :: rainfall
    real(kind=8) :: rainfall_rate
    real(kind=8) :: rainfall_time
    real(kind=8) :: mannings_channel
    real(kind=8) :: mannings_slope

    !! |y| < y_channel is the channel region
    real(kind=8) :: y_channel
    real(kind=8) :: dry_tol
    
end module rainfall_mod

subroutine setprob()
    use rainfall_mod
    implicit none

    integer :: rainfall_int

    open(10,file='setprob.data')
    read(10,*) example
    read(10,*) rainfall_int
    read(10,*) rainfall_rate
    read(10,*) rainfall_time
    read(10,*) mannings_channel
    read(10,*) mannings_slope
    read(10,*) y_channel
    read(10,*) dry_tol
    close(10)

    rainfall = rainfall_int .ne. 0
    
end subroutine setprob